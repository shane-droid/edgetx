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

#ifndef _MENU_MODEL_H_
#define _MENU_MODEL_H_

#include "tabsgroup.h"

class ModelMenu : public TabsGroup
{
  public:
    ModelMenu();

    void onEvent(event_t event) override;

#if defined(DEBUG_WINDOWS)
    std::string getName() const override { return "ModelMenu"; }
#endif

  protected:
#if defined(PCBNV14) || defined(PCBPL18)
    void addGoToMonitorsButton(void);
#endif
    bool _modelHeliEnabled = true;
    bool _modelFMEnabled = true;
    bool _modelCurvesEnabled = true;
    bool _modelGVEnabled = true;
    bool _modelLSEnabled = true;
    bool _modelSFEnabled = true;
    bool _modelCustomScriptsEnabled = true;
    bool _modelTelemetryEnabled = true;

    void build();
    void checkEvents() override;
};

#endif // _MENU_MODEL_H_
