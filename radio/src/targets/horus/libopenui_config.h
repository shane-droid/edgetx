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

#pragma once

constexpr uint32_t ALERT_FRAME_TOP =               70;
constexpr uint32_t ALERT_FRAME_HEIGHT =            (LCD_H - 2 * ALERT_FRAME_TOP);
constexpr uint32_t ALERT_BITMAP_TOP =              ALERT_FRAME_TOP + 15;
constexpr uint32_t ALERT_BITMAP_LEFT =             40;
constexpr uint32_t ALERT_TITLE_TOP =               ALERT_FRAME_TOP + 10;
constexpr uint32_t ALERT_TITLE_LEFT =              186;
constexpr uint32_t ALERT_MESSAGE_TOP =             ALERT_TITLE_TOP + 90;
constexpr uint32_t ALERT_MESSAGE_LEFT =            ALERT_TITLE_LEFT;

constexpr coord_t INPUT_EDIT_CURVE_WIDTH = 132;
constexpr coord_t INPUT_EDIT_CURVE_HEIGHT = INPUT_EDIT_CURVE_WIDTH;
constexpr coord_t MENUS_LINE_HEIGHT = 30;
constexpr coord_t MENUS_WIDTH = 200;
constexpr coord_t MENUS_MAX_HEIGHT = LCD_H * 0.9;

constexpr rect_t MENUS_TOOLBAR_RECT =              { 100, 51, 30, 209 };

#define ROTARY_ENCODER_SPEED() rotencSpeed
