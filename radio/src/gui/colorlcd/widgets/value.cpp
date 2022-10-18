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

#include "opentx.h"
#include "widgets_container_impl.h"

const coord_t NUMBERS_PADDING = 4;

class ValueWidget: public Widget
{
  public:
   ValueWidget(const WidgetFactory* factory, Window* parent,
               const rect_t& rect, Widget::PersistentData* persistentData) :
       Widget(factory, parent, rect, persistentData)
   {
   }

    void refresh(BitmapBuffer * dc) override
    {
      // get source from options[0]
      mixsrc_t field = persistentData->options[0].value.unsignedValue;

      // get color from options[1]
      LcdFlags color = COLOR2FLAGS(persistentData->options[1].value.unsignedValue);

      coord_t xValue, yValue, xLabel, yLabel;
      LcdFlags attrValue, attrLabel = 0;

      if (width() < 120 && height() < 50) {
        xValue = 0;
        yValue = 14;
        xLabel = 0;
        yLabel = 0;
        attrValue = LEFT | NO_UNIT | FONT(L);
        attrLabel = LEFT;
      }
      else if (height() < 50) {
        xValue = width() - NUMBERS_PADDING;
        yValue = -2;
        xLabel = NUMBERS_PADDING;
        yLabel = +2;
        attrValue = RIGHT | NO_UNIT | FONT(L);
      }
      else {
        xValue = NUMBERS_PADDING;
        yValue = 18;
        xLabel = NUMBERS_PADDING;
        yLabel = 2;
        if (field >= MIXSRC_FIRST_TELEM) {
          if (isGPSSensor(1 + (field - MIXSRC_FIRST_TELEM) / 3)) {
            attrValue = LEFT | FONT(L) | PREC1;
          }
          else {
            attrValue = LEFT | FONT(XL);
          }
        }
#if defined(INTERNAL_GPS)
        else if (field == MIXSRC_TX_GPS) {
          attrValue = LEFT | FONT(L) | PREC1;
        }
#endif
        else {
          attrValue = LEFT | FONT(XL);
        }
      }

      if (field >= MIXSRC_FIRST_TIMER && field <= MIXSRC_LAST_TIMER) {
        TimerState & timerState = timersStates[field - MIXSRC_FIRST_TIMER];
        if (timerState.val < 0) {
          color = COLOR_THEME_WARNING;
        }
        if (persistentData->options[2].value.boolValue) {
          drawSource(dc, xLabel + 1, yLabel + 1, field, attrLabel | COLOR2FLAGS(BLACK));
          drawTimer(dc, xValue + 1, yValue + 1, abs(timerState.val),
                    attrValue | FONT(STD) | COLOR2FLAGS(BLACK));
        }
        drawSource(dc, xLabel, yLabel, field, attrLabel | color);
        drawTimer(dc, xValue, yValue, abs(timerState.val),
                    attrValue | FONT(STD) | color);        

      } else if (field == MIXSRC_TX_TIME) {
        int32_t tme = getValue(MIXSRC_TX_TIME);
        if (persistentData->options[2].value.boolValue) {
          drawSource(dc, xLabel + 1, yLabel + 1, field, COLOR2FLAGS(BLACK));
          drawTimer(dc, xValue + 1, yValue + 1, tme,
                    attrValue | FONT(STD) | COLOR2FLAGS(BLACK) | TIMEHOUR);
        }
        drawSource(dc, xLabel, yLabel, field, attrLabel | color);
        drawTimer(dc, xValue, yValue, tme,
                  attrValue | FONT(STD) | color | TIMEHOUR);
      } else {

        if (field >= MIXSRC_FIRST_TELEM) {
          TelemetryItem& telemetryItem =
              telemetryItems[(field - MIXSRC_FIRST_TELEM) / 3];
          if (!telemetryItem.isAvailable() || telemetryItem.isOld()) {
            color = COLOR_THEME_DISABLED;
          }
        }

        if (persistentData->options[2].value.boolValue) {
          drawSource(dc, xLabel + 1, yLabel + 1, field,
                     attrLabel | COLOR2FLAGS(BLACK));
          drawSourceValue(dc, xValue + 1, yValue + 1, field,
                          attrValue | COLOR2FLAGS(BLACK));
        }

        drawSource(dc, xLabel, yLabel, field, attrLabel | color);
        drawSourceValue(dc, xValue, yValue, field, attrValue | color);
      }
    }

    void checkEvents() override
    {
      Widget::checkEvents();

      auto newValue = getValue(persistentData->options[0].value.unsignedValue);
      if (lastValue != newValue) {
        lastValue = newValue;
        invalidate();
      }
    }

    static const ZoneOption options[];
    int32_t lastValue = 0;
};

const ZoneOption ValueWidget::options[] = {
  { STR_SOURCE, ZoneOption::Source, OPTION_VALUE_UNSIGNED(MIXSRC_Rud) },
  { STR_COLOR, ZoneOption::Color, OPTION_VALUE_UNSIGNED(COLOR_THEME_PRIMARY2) },
  { STR_SHADOW, ZoneOption::Bool, OPTION_VALUE_BOOL(false)  },
  { nullptr, ZoneOption::Bool }
};

BaseWidgetFactory<ValueWidget> ValueWidget("Value", ValueWidget::options,
                                           STR_WIDGET_VALUE);
