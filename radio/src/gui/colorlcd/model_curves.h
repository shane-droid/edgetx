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

#ifndef _MODEL_CURVES_H_
#define _MODEL_CURVES_H_

#include "tabsgroup.h"

class ModelCurvesPage: public PageTab {
  public:
    ModelCurvesPage();
    static void pushEditCurve(int index);

    virtual void build(FormWindow * window) override;

  protected:
    uint8_t focusIndex = -1;
    Button* addButton = nullptr;

    void rebuild(FormWindow * window);
    void editCurve(FormWindow * window, uint8_t curve);
    void presetMenu(FormWindow * window, uint8_t index);
    void plusPopup(FormWindow * window);
    void newCV(FormWindow * window, bool presetCV);
};

#endif // _MODEL_CURVES_H_
