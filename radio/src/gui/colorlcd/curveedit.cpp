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

#include "curveedit.h"
#include "opentx.h" // TODO for applyCustomCurve
#include "libopenui.h"

#define SET_DIRTY()     storageDirty(EE_MODEL)

static const lv_coord_t default_col_dsc[] = {LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
static const lv_coord_t default_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};

CurveDataEdit::CurveDataEdit(Window * parent, const rect_t & rect, uint8_t index) :
  Window(parent, rect),
  index(index)
{
  lv_obj_set_style_bg_color(lvobj, makeLvColor(COLOR_THEME_SECONDARY3), 0);
  lv_obj_set_scrollbar_mode(lvobj, LV_SCROLLBAR_MODE_AUTO);
}

#if LCD_W > LCD_H
  #define   NUM_BTN_WIDTH   44
#else
  #define   NUM_BTN_WIDTH   48
#endif

void CurveDataEdit::curvePointsRow(FormWindow::Line* parent, int start, int count, int curvePointsCount, bool isCustom)
{
  static const lv_coord_t points_col_dsc[] = {11, LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

  auto form = new FormWindow(parent, rect_t{});
  form->padAll(0);
  form->setFlexLayout();

  FlexGridLayout grid(points_col_dsc, default_row_dsc, 4);
  
  auto line = form->newLine(&grid);
  line->padAll(0);
  line->padLeft(4);
  line->padRight(4);
  lv_obj_set_grid_align(line->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  new StaticText(line, rect_t{}, "", CENTERED|COLOR_THEME_PRIMARY1);
  
  // Point number
  for (int i = 0; i < count; i++) {
    new StaticText(line, rect_t{}, std::to_string(i + start + 1), 0, FONT(XS) | CENTERED | COLOR_THEME_PRIMARY1);
  }

  line = form->newLine(&grid);
  line->padAll(2);
  line->padLeft(4);
  line->padRight(4);
  lv_obj_set_grid_align(line->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  new StaticText(line, rect_t{}, "X", 0, CENTERED|COLOR_THEME_PRIMARY1);

  int8_t* points = curveAddress(index);

  // x value
  if (isCustom) {
    uint8_t i = 0;
    uint8_t c = count;
    if (start == 0) {
      new StaticText(line, rect_t{}, "-100", 0, CENTERED | COLOR_THEME_SECONDARY1);
      i += 1;
    }
    if ((start + count) == curvePointsCount) {
      c -= 1;
    }
    // Adjustable points for custom curves
    for (; i < c; i++) {
      uint8_t px = i + start - 1;
      numEditX[px] = new NumberEdit(
          line, rect_t{ 0, 0, NUM_BTN_WIDTH, 0 },
          (px == 0) ? -100 : points[curvePointsCount + px - 1],
          (px == curvePointsCount - 3) ? 100 : points[curvePointsCount + px + 1],
          GET_VALUE(points[curvePointsCount + px]),
          [=](int32_t newValue) {
            points[curvePointsCount + px] =  newValue;
            if (px > 0) {
              numEditX[px-1]->setMax(newValue);
            }
            if (px < curvePointsCount - 3) {
              numEditX[px+1]->setMin(newValue);
            }
            SET_DIRTY();
            curveEdit->updatePreview();
          },
          0, RIGHT);
          lv_obj_set_grid_cell(numEditX[px]->getLvObj(), LV_GRID_ALIGN_CENTER, i+1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
          lv_textarea_set_align(numEditX[px]->getLvObj(), LV_TEXT_ALIGN_CENTER);
    }
    if ((start + count) == curvePointsCount) {
      new StaticText(line, rect_t{}, "100", 0, CENTERED | COLOR_THEME_SECONDARY1);
    }
  } else {
    for (uint8_t i = 0; i < count; i++) {
      new StaticText(line, rect_t{},
                     std::to_string(-100 + (200 * (i + start)) / (curvePointsCount - 1)),
                     0, CENTERED | COLOR_THEME_SECONDARY1);
    }
  }

  line = form->newLine(&grid);
  line->padAll(2);
  line->padLeft(4);
  line->padRight(4);
  lv_obj_set_grid_align(line->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  new StaticText(line, rect_t{}, "Y", 0, CENTERED|COLOR_THEME_PRIMARY1);

  // y value
  for (uint8_t i = 0; i < count; i++) {
    auto numedit = new NumberEdit(
        line, rect_t{ 0, 0, NUM_BTN_WIDTH, 0 },
        -100, 100, GET_VALUE(points[i+start]),
        [=](int32_t newValue) {
          points[i+start] = newValue;
          SET_DIRTY();
          curveEdit->updatePreview();
        },
        0, RIGHT);
    lv_obj_set_grid_cell(numedit->getLvObj(), LV_GRID_ALIGN_CENTER, i+1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_textarea_set_align(numedit->getLvObj(), LV_TEXT_ALIGN_CENTER);
  }
}

void CurveDataEdit::update()
{
  clear();

  memset(numEditX, 0, sizeof(numEditX));

  auto form = new FormWindow(this, rect_t{});
  form->padAll(0);
  form->padBottom(4);
  form->setFlexLayout();

  FlexGridLayout grid(default_col_dsc, default_row_dsc, 4);

  CurveHeader & curve = g_model.curves[index];
  uint8_t curvePointsCount = 5 + curve.points;

  for (int i = 0; i < curvePointsCount; i += 5) {
    int count = 5;
    if (i + count > curvePointsCount) count = curvePointsCount - i;
    auto line = form->newLine(&grid);
    line->padAll(0);
    lv_obj_set_grid_align(line->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);
    curvePointsRow(line, i, count, curvePointsCount, curve.type == CURVE_TYPE_CUSTOM);
  }
}

void CurveEdit::SetCurrentSource(uint32_t source)
{
  CurveEdit::currentSource = source;
  if (source)
    lockSource = true;
  else
    lockSource = false;
}

mixsrc_t CurveEdit::currentSource = 0;
bool CurveEdit::lockSource = false;

CurveEdit::CurveEdit(Window* parent, const rect_t& rect, uint8_t index) :
    FormField(parent, rect, NO_FOCUS),
    preview(
        this, {0, 0, width(), height()},
        [=](int x) -> int { return applyCustomCurve(x, index); },
        [=]()->int {
          return getValue(CurveEdit::currentSource);
        }),
    index(index),
    current(0)
{
  TRACE("CurveEdit::currentSource=%d\tCurveEdit::lockSource=%d",
        CurveEdit::currentSource, CurveEdit::lockSource);
  updatePreview();
}

void CurveEdit::updatePreview()
{
  preview.clearPoints();
  CurveHeader & curve = g_model.curves[index];
  for (uint8_t i = 0; i < 5 + curve.points; i++) {
    preview.addPoint(getPoint(index, i), COLOR_THEME_SECONDARY1);
  }
  invalidate();
}

void CurveEdit::checkEvents()
{
  if (!lockSource) {
    int16_t val = getMovedSource(MIXSRC_FIRST_INPUT);
    if (val > 0) {
      // TODO: this code seems odd
      if (val > MAX_STICKS + MAX_POTS)
        CurveEdit::currentSource = val + 1 - MIXSRC_FIRST_INPUT;
      else {
        CurveEdit::currentSource = expoAddress(val - 1)->srcRaw;
        TRACE("Detected source=%d", val);
      }
      TRACE("Applied source=%d", CurveEdit::currentSource);
    }
  }
  FormField::checkEvents();
}

CurveEditWindow::CurveEditWindow(uint8_t index):
  Page(ICON_MODEL_CURVES),
  index(index)
{
  buildBody(&body);
  buildHeader(&header);
}

void CurveEditWindow::buildHeader(Window * window)
{
  header.setTitle(STR_MENUCURVES);
  char s[16];
  strAppendStringWithIndex(s, STR_CV, index + 1);
  header.setTitle2(s);
}

void CurveEditWindow::buildBody(FormWindow * window)
{
  CurveHeader & curve = g_model.curves[index];
  int8_t * points = curveAddress(index);

  auto form = new FormWindow(window, rect_t{});
  form->padAll(0);
  form->setFlexLayout();

  FlexGridLayout grid(default_col_dsc, default_row_dsc, 0);
  
  auto line = form->newLine(&grid);
  line->padAll(0);
  lv_obj_set_grid_align(line->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

#if LCD_H > LCD_W // portrait
  lv_obj_set_flex_flow(line->getLvObj(), LV_FLEX_FLOW_COLUMN);
  coord_t curveWidth = window->width() - 88;
  coord_t boxWidth = window->width();
  coord_t boxHeight = window->height() - curveWidth;
#else
  lv_obj_set_flex_flow(line->getLvObj(), LV_FLEX_FLOW_ROW);
  coord_t curveWidth = window->height() - 2 * PAGE_PADDING;
  coord_t boxWidth = window->width() - curveWidth;
  coord_t boxHeight = window->height();
#endif

  auto box = new Window(line, rect_t{});
  box->setWidth(boxWidth);
  box->setHeight(boxHeight);
  box->padAll(0);

  static const lv_coord_t controls_col_dsc[] = {LV_GRID_FR(5), LV_GRID_FR(8), LV_GRID_FR(5), LV_GRID_TEMPLATE_LAST};

  form = new FormWindow(box, rect_t{});
  form->padAll(0);
  form->setFlexLayout();

  FlexGridLayout iGrid(controls_col_dsc, default_row_dsc, 0);
  
  auto iLine = form->newLine(&iGrid);
  iLine->padAll(4);
  iLine->padBottom(0);
  lv_obj_set_grid_align(iLine->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  // Name
  new StaticText(iLine, rect_t{}, STR_NAME, 0, COLOR_THEME_PRIMARY1);
  new ModelTextEdit(iLine, rect_t{0, 0, 100, 0}, curve.name, sizeof(curve.name));

  // Smooth
  auto smooth = new TextButton(iLine, rect_t{0, 0, 70, 0}, STR_SMOOTH, [=]() {
    g_model.curves[index].smooth = !g_model.curves[index].smooth;
    curveEdit->updatePreview();
    return g_model.curves[index].smooth;
  });
  smooth->check(g_model.curves[index].smooth);
  
  iLine = form->newLine(&iGrid);
  iLine->padAll(4);
  iLine->padBottom(0);
  lv_obj_set_grid_align(iLine->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  // Type
  new StaticText(iLine, rect_t{}, STR_TYPE, 0, COLOR_THEME_PRIMARY1);
  new Choice(iLine, rect_t{0, 0, 100, 0}, STR_CURVE_TYPES, 0, 1, GET_DEFAULT(g_model.curves[index].type),
             [=](int32_t newValue) {
                 CurveHeader &curve = g_model.curves[index];
                 if (newValue != curve.type) {
                   for (int i = 1; i < 4 + curve.points; i++) {
                     points[i] = calcRESXto100(applyCustomCurve(calc100toRESX(-100 + i * 200 / (4 + curve.points)), index));
                   }
                   if (moveCurve(index, newValue == CURVE_TYPE_CUSTOM ? 3 + curve.points : -3 - curve.points)) {
                     if (newValue == CURVE_TYPE_CUSTOM) {
                       resetCustomCurveX(points, 5 + curve.points);
                     }
                     curve.type = newValue;
                   }
                   SET_DIRTY();
                   curveEdit->updatePreview();
                   if (curveDataEdit) {
                     curveDataEdit->update();
                   }
                 }
             });

  // Points count
  auto edit = new NumberEdit(iLine, rect_t{0, 0, 70, 0}, 2, 17, GET_DEFAULT(g_model.curves[index].points + 5),
                             [=](int32_t newValue) {
                                 newValue -= 5;
                                 CurveHeader &curve = g_model.curves[index];
                                 int newPoints[MAX_POINTS_PER_CURVE];
                                 newPoints[0] = points[0];
                                 newPoints[4 + newValue] = points[4 + curve.points];
                                 for (int i = 1; i < 4 + newValue; i++)
                                   newPoints[i] = calcRESXto100(applyCustomCurve(-RESX + (i * 2 * RESX) / (4 + newValue), index));
                                 if (moveCurve(index, (newValue - curve.points) * (curve.type == CURVE_TYPE_CUSTOM ? 2 : 1))) {
                                   for (int i = 0; i < 5 + newValue; i++) {
                                     points[i] = newPoints[i];
                                     if (curve.type == CURVE_TYPE_CUSTOM && i != 0 && i != 4 + newValue)
                                       points[5 + newValue + i - 1] = -100 + (i * 200) / (4 + newValue);
                                   }
                                   curve.points = newValue;
                                   SET_DIRTY();
                                   curveEdit->updatePreview();
                                   if (curveDataEdit) {
                                     curveDataEdit->update();
                                   }
                                 }
                             });
  edit->setSuffix(STR_PTS);

  iLine = form->newLine(&iGrid);
  iLine->padAll(0);
  lv_obj_set_grid_align(iLine->getLvObj(), LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);

  curveDataEdit = new CurveDataEdit(iLine, rect_t{ 0, 0, box->width(), box->height() - 72 }, index);

  // Curve editor
  lv_obj_set_flex_align(line->getLvObj(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
  curveEdit = new CurveEdit(line, { 0, 0, curveWidth, curveWidth }, index);
  
  curveDataEdit->setCurveEdit(curveEdit);
}
