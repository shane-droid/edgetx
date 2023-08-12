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

#include "fab_button.h"
#include "font.h"
#include "theme.h"

const uint8_t __alpha_button_on[] {
#include "alpha_button_on.lbm"
};
LZ4Bitmap ALPHA_BUTTON_ON(BMP_ARGB4444, __alpha_button_on);

const uint8_t __alpha_button_off[] {
#include "alpha_button_off.lbm"
};
LZ4Bitmap ALPHA_BUTTON_OFF(BMP_ARGB4444, __alpha_button_off);

FabButton::FabButton(FormWindow* parent, coord_t x, coord_t y, uint8_t icon,
                     std::function<uint8_t(void)> pressHandler,
                     WindowFlags windowFlags) :
    Button(parent,
           {x, y, FAB_BUTTON_SIZE, FAB_BUTTON_SIZE},
           pressHandler, windowFlags),
    icon(icon)
{
}

FabButton::FabButton(FormWindow* parent, uint8_t icon,
                     std::function<uint8_t(void)> pressHandler,
                     WindowFlags windowFlags) :
    Button(parent, {}, pressHandler, windowFlags), icon(icon)
{
}

void FabButton::paint(BitmapBuffer * dc)
{
  const BitmapBuffer* bitmap = checked() ? &ALPHA_BUTTON_ON : &ALPHA_BUTTON_OFF;

  dc->drawBitmap((width() - bitmap->width()) / 2,
                 (FAB_BUTTON_SIZE - bitmap->height()) / 2, bitmap);

  const BitmapBuffer* mask = theme->getIconMask(icon);
  if (mask) {
    dc->drawMask((width() - mask->width()) / 2,
                 (FAB_BUTTON_SIZE - mask->height()) / 2, mask, COLOR2FLAGS(WHITE));
  }
}
