/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "view_main_decoration.h"
#include "layout.h"

// because of IS_POT_MULTIPOS() and pal
#include "opentx.h"

// these 2 need things from opentx.h
#include "layouts/sliders.h"
#include "layouts/trims.h"

#include "board.h"
#include "hal/adc_driver.h"

static Window* create_layout_box(Window* parent, lv_align_t align,
                                 lv_flex_flow_t flow)
{
  lv_obj_t* lv_parent = parent->getLvObj();

  auto box = window_create(lv_parent);
  lv_obj_set_size(box, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_align(box, align);
  lv_obj_set_flex_flow(box, flow);

  if (_LV_FLEX_COLUMN & flow) {
    lv_obj_set_style_pad_row(box, 0, 0);
  } else {
    lv_obj_set_style_pad_column(box, 0, 0);
  }

  return new Window(parent, box);
}

ViewMainDecoration::ViewMainDecoration(Window* parent) :
  parent(parent)
{
  memset(sliders, 0, sizeof(sliders));
  memset(trims, 0, sizeof(trims));
  flightMode = nullptr;

  w_ml = create_layout_box(parent, LV_ALIGN_LEFT_MID, LV_FLEX_FLOW_ROW_REVERSE);
  w_mr = create_layout_box(parent, LV_ALIGN_RIGHT_MID, LV_FLEX_FLOW_ROW);
  w_bl = create_layout_box(parent, LV_ALIGN_BOTTOM_LEFT, LV_FLEX_FLOW_COLUMN);
  w_br = create_layout_box(parent, LV_ALIGN_BOTTOM_RIGHT, LV_FLEX_FLOW_COLUMN);

  w_bc = create_layout_box(parent, LV_ALIGN_BOTTOM_MID, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(w_bc->getLvObj(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);

  createTrims(w_ml, w_mr, w_bl, w_br);
  createFlightMode(w_bc);
  createSliders(w_ml, w_mr, w_bl, w_bc, w_br);
}

void ViewMainDecoration::setSlidersVisible(bool visible)
{
  auto fct = !visible ? lv_obj_add_flag : lv_obj_clear_flag;
  for (int i=0; i < SLIDERS_MAX; i++) {
    if (sliders[i]) {
      fct(sliders[i]->getLvObj(), LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void ViewMainDecoration::setTrimsVisible(bool visible)
{
  auto fct = !visible ? lv_obj_add_flag : lv_obj_clear_flag;
  for (int i=0; i < TRIMS_MAX; i++) {
    if (trims[i]) {
      fct(trims[i]->getLvObj(), LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void ViewMainDecoration::setFlightModeVisible(bool visible)
{
  auto fct = !visible ? lv_obj_add_flag : lv_obj_clear_flag;
  if (flightMode) {
    fct(flightMode->getLvObj(), LV_OBJ_FLAG_HIDDEN);
  }
}

void ViewMainDecoration::updateFromTheme()
{
  // Hack to fix flight mode color on main view
  // Required because theme is loaded after the main view has been created
  if (flightMode) {
    lv_obj_set_style_text_color(flightMode->getLvObj(), makeLvColor(COLOR_THEME_SECONDARY1), 0);
    flightMode->invalidate();
  }
}

rect_t ViewMainDecoration::getMainZone() const
{
  // update layout first
  lv_obj_update_layout(parent->getLvObj());

  auto x_left = lv_obj_get_x2(w_ml->getLvObj());
  auto x_right = lv_obj_get_x(w_mr->getLvObj());

  lv_coord_t bottom = LCD_H;
  Window* boxes[] = { w_bl, w_bc, w_br };

  for ( auto box : boxes ) {
    auto obj = box->getLvObj();
    auto y = lv_obj_get_y(obj);
    if (y < bottom) bottom = y;
  }

  return rect_t{ x_left, 0, x_right - x_left, bottom};
}

void ViewMainDecoration::createSliders(Window* ml, Window* mr, Window* bl, Window* bc, Window* br)
{
  sliders[0] = new MainViewHorizontalSlider(bl, 0);

  if (!IS_POT_AVAILABLE(2))
    bc = br;
  
  if (IS_POT_MULTIPOS(1))
    sliders[1] = new MainView6POS(bc, 1);
  else if (IS_POT_AVAILABLE(1))
    sliders[1] = new MainViewHorizontalSlider(bc, 1);

  if (IS_POT_AVAILABLE(2))
    sliders[2] = new MainViewHorizontalSlider(br, 2);

  // TODO: check how many pots are configured instead
  auto max_pots = adcGetMaxInputs(ADC_INPUT_POT);
  if (max_pots > 3) {
    // create containers for the sliders, so that they are at the borders of the display
    // on top of each other, when there are two sliders to display per side
    auto leftPots = create_layout_box(ml, LV_ALIGN_LEFT_MID, LV_FLEX_FLOW_COLUMN);
    leftPots->setHeight(VERTICAL_SLIDERS_HEIGHT);

    auto rightPots = create_layout_box(mr, LV_ALIGN_RIGHT_MID, LV_FLEX_FLOW_COLUMN);
    rightPots->setHeight(VERTICAL_SLIDERS_HEIGHT);

    coord_t lsh = (IS_POT_AVAILABLE(5)) ? VERTICAL_SLIDERS_HEIGHT / 2 : VERTICAL_SLIDERS_HEIGHT;
    coord_t rsh = (IS_POT_AVAILABLE(6)) ? VERTICAL_SLIDERS_HEIGHT / 2 : VERTICAL_SLIDERS_HEIGHT;

    if (IS_POT_AVAILABLE(3))
      sliders[3] = new MainViewVerticalSlider(leftPots, rect_t{0, 0, TRIM_SQUARE_SIZE, lsh}, 3);

    if (IS_POT_AVAILABLE(4))
      sliders[4] = new MainViewVerticalSlider(rightPots, rect_t{0, 0, TRIM_SQUARE_SIZE, rsh}, 4);

    if (IS_POT_AVAILABLE(5))
      sliders[5] = new MainViewVerticalSlider(leftPots, rect_t{0, 0, TRIM_SQUARE_SIZE, lsh}, 5);

    if (IS_POT_AVAILABLE(6))
      sliders[6] = new MainViewVerticalSlider(rightPots, rect_t{0, 0, TRIM_SQUARE_SIZE, rsh}, 6);
  }
}

void ViewMainDecoration::createTrims(Window* ml, Window* mr, Window* bl, Window* br)
{
  // Trim order TRIM_LH, TRIM_LV, TRIM_RV, TRIM_RH
  trims[TRIMS_LH] = new MainViewHorizontalTrim(bl, TRIMS_LH);
  trims[TRIMS_RH] = new MainViewHorizontalTrim(br, TRIMS_RH);
  trims[TRIMS_LV] = new MainViewVerticalTrim(ml, TRIMS_LV);
  trims[TRIMS_RV] = new MainViewVerticalTrim(mr, TRIMS_RV);
}

void ViewMainDecoration::createFlightMode(Window* bc)
{
  std::function<std::string()> getFM = []() -> std::string {
      return stringFromNtString(g_model.flightModeData[mixerCurrentFlightMode].name);
  };

  flightMode = new DynamicText(bc, rect_t{}, getFM, COLOR_THEME_SECONDARY1);
}

