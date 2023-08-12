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

#pragma once

#include "debug.h"
#include "board.h"
#include "colors.h"
#include "keys.h"
#include "opentx_types.h"

enum FontIndex
{
  FONT_STD_INDEX,
  FONT_BOLD_INDEX,
  FONT_XXS_INDEX,
  FONT_XS_INDEX,
  FONT_L_INDEX,
  FONT_XL_INDEX,
  FONT_XXL_INDEX,

  // this one MUST be last
  FONTS_COUNT
};

constexpr uint32_t MENU_HEADER_BUTTON_WIDTH =      33;
constexpr uint32_t MENU_HEADER_BUTTONS_LEFT =      47;

constexpr uint32_t MENUS_TOOLBAR_BUTTON_WIDTH =    30;
constexpr uint32_t MENUS_TOOLBAR_BUTTON_PADDING =  3;

constexpr uint32_t MENU_HEADER_HEIGHT =            45;
constexpr uint32_t MENU_TITLE_TOP =                48;
constexpr uint32_t MENU_TITLE_HEIGHT =             21;
constexpr uint32_t MENU_BODY_TOP =                 MENU_TITLE_TOP + MENU_TITLE_HEIGHT;
constexpr uint32_t MENU_FOOTER_HEIGHT =            0;
constexpr uint32_t MENU_FOOTER_TOP =               LCD_H - MENU_FOOTER_HEIGHT;
constexpr uint32_t MENU_BODY_HEIGHT =              MENU_FOOTER_TOP - MENU_BODY_TOP;
constexpr uint32_t MENUS_MARGIN_LEFT =             6;

constexpr uint32_t MENU_HEADER_BACK_BUTTON_WIDTH  = MENU_HEADER_HEIGHT;
constexpr uint32_t MENU_HEADER_BACK_BUTTON_HEIGHT = MENU_HEADER_HEIGHT;

constexpr coord_t  PAGE_PADDING =                  6;
constexpr uint32_t PAGE_LINE_HEIGHT =              20;
constexpr uint32_t FH =                            PAGE_LINE_HEIGHT;
constexpr uint32_t NUM_BODY_LINES =                MENU_BODY_HEIGHT / PAGE_LINE_HEIGHT;

constexpr uint32_t FIELD_PADDING_LEFT =            3;
constexpr uint32_t FIELD_PADDING_TOP =             2;

constexpr uint32_t CURVE_SIDE_WIDTH =              100;
constexpr uint32_t CURVE_CENTER_X =                LCD_W - CURVE_SIDE_WIDTH - 7;
constexpr uint32_t CURVE_CENTER_Y =                151;
constexpr uint32_t CURVE_COORD_WIDTH =             36;
constexpr uint32_t CURVE_COORD_HEIGHT =            17;

constexpr uint32_t DATETIME_SEPARATOR_X =          LCD_W - 53;
constexpr uint32_t DATETIME_LINE1 =                7;
constexpr uint32_t DATETIME_LINE2 =                22;
constexpr uint32_t DATETIME_MIDDLE =               (LCD_W + DATETIME_SEPARATOR_X + 1) / 2;

constexpr uint32_t PAGE_TITLE_TOP =                2;
constexpr uint32_t PAGE_TITLE_LEFT =               50;

constexpr coord_t POPUP_HEADER_HEIGHT = 30;
constexpr coord_t MODEL_SELECT_FOOTER_HEIGHT = 24;

#define BLINK                          0
#define TIMEHOUR                       0

/* drawText flags */
#define LEFT                           0x00u /* align left */
// 0x01u used by Lua in api_colorlcd.h
#define VCENTERED                      0x02u /* align center vertically */
#define CENTERED                       0x04u /* align center */
#define RIGHT                          0x08u /* align right */
#define SHADOWED                       0x80u /* black copy at +1 +1 */
// 0x1000u used by Lua in api_colorlcd.h
// 0x8000u used by Lua in api_colorlcd.h

/* drawNumber flags */
#define LEADING0                       0x10u
#define PREC1                          0x20u
#define PREC2                          0x30u
#define MODE(flags)                    ((((int8_t)(flags) & 0x30) - 0x10) >> 4)

/* telemetry flags */
#define NO_UNIT                        0x40u

#define FONT_MASK                      0x0F00u
#define FONT_INDEX(flags)              (((flags) & FONT_MASK) >> 8u)
#define FONT(xx)                       (unsigned(FONT_ ## xx ## _INDEX) << 8u)

#define LV_OBJ_FLAG_ENCODER_ACCEL LV_OBJ_FLAG_USER_1

#include "libopenui_config.h"

