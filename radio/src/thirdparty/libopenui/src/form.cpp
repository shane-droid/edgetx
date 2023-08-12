/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   libopenui - https://github.com/opentx/libopenui
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

#include "form.h"
#include "bitmapbuffer.h"

FormField::FormField(Window* parent, const rect_t& rect,
                     WindowFlags windowFlags, LcdFlags textFlags,
                     LvglCreate objConstruct) :
    Window(parent, rect, windowFlags, textFlags, objConstruct)
{
  lv_obj_add_flag(lvobj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

void FormField::setEditMode(bool newEditMode)
{
  editMode = newEditMode;

  if (lvobj != nullptr) {
    lv_group_t* grp = (lv_group_t*)lv_obj_get_group(lvobj);
    if (grp != nullptr) lv_group_set_editing(grp, editMode);
  }

  if (editMode && lvobj != nullptr) {
    lv_obj_add_state(lvobj, LV_STATE_EDITED);
  } else if (lvobj != nullptr) {
    lv_obj_clear_state(lvobj, LV_STATE_EDITED);
  }
  invalidate();
}

void FormField::enable(bool value)
{
  if (value) {
    lv_obj_clear_state(lvobj, LV_STATE_DISABLED);
  } else {
    lv_obj_add_state(lvobj, LV_STATE_DISABLED);
  }
}

void FormField::onClicked()
{
  lv_indev_type_t indev_type = lv_indev_get_type(lv_indev_get_act());
  if(indev_type != LV_INDEV_TYPE_POINTER) {
    setEditMode(!editMode);
    invalidate();
  }
}

void FormField::onCancel()
{
  if (isEditMode()) {
    setEditMode(false);
    invalidate();
  } else {
    Window::onCancel();
  }
}

FormWindow::Line::Line(Window* parent, lv_obj_t* obj, FlexGridLayout* layout) :
    Window(parent, obj), layout(layout)
{
  construct();
}

FormWindow::Line::Line(Window* parent, FlexGridLayout* layout) :
    Window(parent, rect_t{}), layout(layout)
{
  construct();
}

void FormWindow::Line::construct()
{
  // Focus
  windowFlags |=  NO_FOCUS;
  lv_obj_clear_flag(lvobj, LV_OBJ_FLAG_CLICK_FOCUSABLE);

  if (layout) {
    layout->apply(lvobj);
  }

  lv_obj_set_width(lvobj, lv_pct(100));
  lv_obj_set_height(lvobj, LV_SIZE_CONTENT);
}

void FormWindow::Line::setLayout(FlexGridLayout *l)
{
  layout = l;
  if (layout) layout->apply(lvobj);
}

void FormWindow::Line::addChild(Window* window)
{
  Window::addChild(window);
  if (layout) {
    layout->add(window->getLvObj());
    layout->nextCell();
  }
}

FormWindow::FormWindow(Window* parent, const rect_t& rect,
                     WindowFlags windowflags) :
   Window(parent, rect, windowflags, 0, etx_form_window_create)
{
}

void FormWindow::setFlexLayout(lv_flex_flow_t flow, lv_coord_t padding)
{
  lv_obj_set_flex_flow(lvobj, flow);
  if (_LV_FLEX_COLUMN & flow) {
    lv_obj_set_style_pad_row(lvobj, padding, LV_PART_MAIN);
  } else {
    lv_obj_set_style_pad_column(lvobj, padding, LV_PART_MAIN);
  }
  lv_obj_set_width(lvobj, lv_pct(100));
  lv_obj_set_height(lvobj, LV_SIZE_CONTENT);
}

FormWindow::Line* FormWindow::newLine(FlexGridLayout* layout, lv_coord_t left_padding)
{
  if (layout) layout->resetPos();
  auto lv_line = window_create(lvobj);
  if (left_padding) lv_obj_set_style_pad_left(lv_line, left_padding, 0);
  return new Line(this, lv_line, layout);
}
