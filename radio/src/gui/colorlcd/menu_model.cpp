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

#include "menu_model.h"

#include "translations.h"
#include "view_channels.h"
#include "model_curves.h"
#include "model_flightmodes.h"
#include "model_gvars.h"
#include "model_heli.h"
#include "model_inputs.h"
#include "model_logical_switches.h"
#include "model_mixer_scripts.h"
#include "model_mixes.h"
#include "model_outputs.h"
#include "model_setup.h"
#include "model_telemetry.h"
#include "opentx.h"
#include "special_functions.h"

ModelMenu::ModelMenu():
  TabsGroup(ICON_MODEL)
{
  build();
}

void ModelMenu::build()
{
  _modelHeliEnabled = modelHeliEnabled();
  _modelFMEnabled = modelFMEnabled();
  _modelCurvesEnabled = modelCurvesEnabled();
  _modelGVEnabled = modelGVEnabled();
  _modelLSEnabled = modelLSEnabled();
  _modelSFEnabled = modelSFEnabled();
  _modelCustomScriptsEnabled = modelCustomScriptsEnabled();
  _modelTelemetryEnabled = modelTelemetryEnabled();

  addTab(new ModelSetupPage());
#if defined(HELI)
  if (_modelHeliEnabled)
    addTab(new ModelHeliPage());
#endif
#if defined(FLIGHT_MODES)
  if (_modelFMEnabled)
    addTab(new ModelFlightModesPage());
#endif
  addTab(new ModelInputsPage());
  addTab(new ModelMixesPage());
  addTab(new ModelOutputsPage());
  if (_modelCurvesEnabled)
    addTab(new ModelCurvesPage());
#if defined(GVARS)
  if (_modelGVEnabled)
    addTab(new ModelGVarsPage());
#endif
  if (_modelLSEnabled)
    addTab(new ModelLogicalSwitchesPage());
  if (_modelSFEnabled)
    addTab(new SpecialFunctionsPage(g_model.customFn));
#if defined(LUA_MODEL_SCRIPTS)
  if (_modelCustomScriptsEnabled)
    addTab(new ModelMixerScriptsPage());
#endif
  if (_modelTelemetryEnabled)
    addTab(new ModelTelemetryPage());

#if defined(PCBNV14) || defined(PCBPL18)
  addGoToMonitorsButton();
#endif
}

void ModelMenu::checkEvents()
{
  TabsGroup::checkEvents();

  if (_modelHeliEnabled != modelHeliEnabled() ||
      _modelFMEnabled != modelFMEnabled() ||
      _modelCurvesEnabled != modelCurvesEnabled() ||
      _modelGVEnabled != modelGVEnabled() ||
      _modelLSEnabled != modelLSEnabled() ||
      _modelSFEnabled != modelSFEnabled() ||
      _modelCustomScriptsEnabled != modelCustomScriptsEnabled() ||
      _modelTelemetryEnabled != modelTelemetryEnabled()) {
    removeAllTabs();
    build();
    setCurrentTab(0);
  }
}

void ModelMenu::onEvent(event_t event)
{
#if defined(HARDWARE_KEYS)
  if (event == EVT_KEY_FIRST(KEY_MODEL)) {
    killEvents(event);
    new ChannelsViewMenu();
  } else {
    TabsGroup::onEvent(event);
  }
#endif
}

#if defined(PCBNV14) || defined(PCBPL18)
void ModelMenu::addGoToMonitorsButton()
{
  new TextButton(
      &header, {LCD_W / 2 + 6, MENU_TITLE_TOP + 1, LCD_W / 2 - 8, MENU_TITLE_HEIGHT - 2},
      STR_OPEN_CHANNEL_MONITORS, [=]() {
        pushEvent(EVT_KEY_FIRST(KEY_MODEL));
        return 0;
      });
}
#endif
