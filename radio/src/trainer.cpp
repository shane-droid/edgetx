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
#include "hal/trainer_driver.h"
#include "heartbeat_driver.h"

int16_t trainerInput[MAX_TRAINER_CHANNELS];
uint8_t trainerInputValidityTimer;
uint8_t currentTrainerMode = 0xff;

enum {
  TRAINER_NOT_CONNECTED = 0,
  TRAINER_CONNECTED,
  TRAINER_DISCONNECTED,
  TRAINER_RECONNECTED
};
uint8_t trainerStatus = TRAINER_NOT_CONNECTED;

void checkTrainerSignalWarning()
{
  enum {
    TRAINER_IN_IS_NOT_USED = 0,
    TRAINER_IN_IS_VALID,
    TRAINER_IN_IS_INVALID
  };

  static uint8_t trainerInputValidState = TRAINER_IN_IS_NOT_USED;

  if (trainerInputValidityTimer && (trainerInputValidState == TRAINER_IN_IS_NOT_USED)) {
    trainerInputValidState = TRAINER_IN_IS_VALID;
    trainerStatus = TRAINER_CONNECTED;
    AUDIO_TRAINER_CONNECTED();
  }
  else if (!trainerInputValidityTimer && (trainerInputValidState == TRAINER_IN_IS_VALID)) {
    trainerInputValidState = TRAINER_IN_IS_INVALID;
    trainerStatus = TRAINER_DISCONNECTED;
    AUDIO_TRAINER_LOST();
  }
  else if (trainerInputValidityTimer && (trainerInputValidState == TRAINER_IN_IS_INVALID)) {
    trainerInputValidState = TRAINER_IN_IS_VALID;
    trainerStatus = TRAINER_RECONNECTED;
    AUDIO_TRAINER_BACK();
  }
}

void stopTrainer()
{
  switch (currentTrainerMode) {
    case TRAINER_MODE_MASTER_TRAINER_JACK:
      stop_trainer_capture();
      break;

    case TRAINER_MODE_SLAVE:
      stop_trainer_ppm();
      break;

#if defined(SBUS_TRAINER)
    case TRAINER_MODE_MASTER_SERIAL:
      sbusSetGetByte(nullptr);
      break;
#endif

#if defined(TRAINER_MODULE_CPPM)
    case TRAINER_MODE_MASTER_CPPM_EXTERNAL_MODULE:
      stop_trainer_module_cppm();
      break;
#endif

#if defined(TRAINER_MODULE_SBUS)
    case TRAINER_MODE_MASTER_SBUS_EXTERNAL_MODULE:
      sbusSetGetByte(nullptr);
      stop_trainer_module_sbus();
      break;
#endif
  }

#if defined(INTMODULE_HEARTBEAT_GPIO) && !defined(SIMU) && \
    (defined(TRAINER_MODULE_CPPM) || defined(TRAINER_MODULE_SBUS))
  if ((currentTrainerMode == TRAINER_MODE_MASTER_CPPM_EXTERNAL_MODULE ||
       currentTrainerMode == TRAINER_MODE_MASTER_SBUS_EXTERNAL_MODULE)
      && (isModulePXX2(INTERNAL_MODULE) || isModulePXX1(INTERNAL_MODULE))) {
    init_intmodule_heartbeat();
  }
#endif

  currentTrainerMode = 0xFF;
}

void checkTrainerSettings()
{
  uint8_t requiredTrainerMode = g_model.trainerData.mode;

  if (requiredTrainerMode != currentTrainerMode) {
    if (currentTrainerMode != 0xFF) {
      stopTrainer();
    }

    currentTrainerMode = requiredTrainerMode;

    switch (requiredTrainerMode) {
      case TRAINER_MODE_MASTER_TRAINER_JACK:
        init_trainer_capture();
        break;

      case TRAINER_MODE_SLAVE:
        init_trainer_ppm();
        break;

#if defined(SBUS_TRAINER)
      case TRAINER_MODE_MASTER_SERIAL:
        sbusSetGetByte(sbusAuxGetByte);
        break;
#endif

#if defined(TRAINER_MODULE_CPPM)
      case TRAINER_MODE_MASTER_CPPM_EXTERNAL_MODULE:
        init_trainer_module_cppm();
        break;
#endif

#if defined(TRAINER_MODULE_SBUS)
      case TRAINER_MODE_MASTER_SBUS_EXTERNAL_MODULE:
        init_trainer_module_sbus();
        sbusSetGetByte(trainerModuleSbusGetByte);
        break;
#endif
    }

#if defined(INTMODULE_HEARTBEAT_GPIO) && !defined(SIMU) && \
    (defined(TRAINER_MODULE_CPPM) || defined(TRAINER_MODULE_SBUS))
    if (requiredTrainerMode == TRAINER_MODE_MASTER_CPPM_EXTERNAL_MODULE ||
        requiredTrainerMode == TRAINER_MODE_MASTER_SBUS_EXTERNAL_MODULE) {
      stop_intmodule_heartbeat();
    }
#endif
  }
}
