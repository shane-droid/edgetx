/*
 * Copyright (C) OpenTX
 *
 * Based on code named
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

#include "constants.h"
#include "radio/src/MultiProtoDefs.h"

#include <QtCore>

class Firmware;
class RadioDataConversionState;
class AbstractStaticItemModel;
class GeneralSettings;

// from radio/src/pulses/module_constants.h
enum ModuleType {
  MODULE_TYPE_NONE = 0,
  MODULE_TYPE_PPM,
  MODULE_TYPE_XJT_PXX1,
  MODULE_TYPE_ISRM_PXX2,
  MODULE_TYPE_DSM2,
  MODULE_TYPE_CROSSFIRE,
  MODULE_TYPE_MULTIMODULE,
  MODULE_TYPE_R9M_PXX1,  // R9M
  MODULE_TYPE_R9M_PXX2,  // R9M ACCESS
  MODULE_TYPE_R9M_LITE_PXX1,  //R9MLite
  MODULE_TYPE_R9M_LITE_PXX2,  //R9MLP
  MODULE_TYPE_GHOST,     // Replaces MODULE_TYPE_R9M_LITE_PRO_PXX1 which doesn't exist
  MODULE_TYPE_R9M_LITE_PRO_PXX2,
  MODULE_TYPE_SBUS,
  MODULE_TYPE_XJT_LITE_PXX2,
  MODULE_TYPE_FLYSKY, //no more protocols possible because of 4 bits value
  MODULE_TYPE_LEMON_DSMP,
  MODULE_TYPE_COUNT,
  MODULE_TYPE_MAX = MODULE_TYPE_COUNT - 1
};

enum PulsesProtocol {
  PULSES_OFF,
  PULSES_PPM,
  PULSES_SILV_A,
  PULSES_SILV_B,
  PULSES_SILV_C,
  PULSES_CTP1009,
  PULSES_LP45,
  PULSES_DSM2,
  PULSES_DSMX,
  PULSES_PPM16,
  PULSES_PPMSIM,
  PULSES_PXX_XJT_X16,
  PULSES_PXX_XJT_D8,
  PULSES_PXX_XJT_LR12,
  PULSES_PXX_DJT,
  PULSES_CROSSFIRE,
  PULSES_MULTIMODULE,
  PULSES_PXX_R9M,
  PULSES_PXX_R9M_LITE,
  PULSES_PXX_R9M_LITE_PRO,
  PULSES_SBUS,
  PULSES_ACCESS_ISRM,
  PULSES_ACCST_ISRM_D16,
  PULSES_ACCESS_R9M,
  PULSES_ACCESS_R9M_LITE,
  PULSES_ACCESS_R9M_LITE_PRO,
  PULSES_XJT_LITE_X16,
  PULSES_XJT_LITE_D8,
  PULSES_XJT_LITE_LR12,
  PULSES_AFHDS3,
  PULSES_GHOST,
  PULSES_LEMON_DSMP,
  PULSES_PROTOCOL_LAST
};

enum ModuleSubtypeR9M {
  MODULE_SUBTYPE_R9M_FCC,
  MODULE_SUBTYPE_R9M_EU,
  MODULE_SUBTYPE_R9M_EUPLUS,
  MODULE_SUBTYPE_R9M_AUPLUS,
  MODULE_SUBTYPE_R9M_LAST=MODULE_SUBTYPE_R9M_AUPLUS
};

#define PPM_NUM_SUBTYPES  2

constexpr int PXX2_MAX_RECEIVERS_PER_MODULE = 3;
constexpr int PXX2_LEN_RX_NAME              = 8;

class ModuleData {
  Q_DECLARE_TR_FUNCTIONS(ModuleData)

  public:
    ModuleData()
    {
      clear();
    }

    unsigned int modelId;
    unsigned int protocol;   // type in datastructs.h
    int          rfProtocol; // rfProtocol in datastructs.h

    unsigned int subType;
    bool         invertedSerial;
    unsigned int channelsStart;
    int          channelsCount; // 0=8 channels
    unsigned int failsafeMode;

    struct PPM {
      int delay;
      bool pulsePol;           // false = positive
      bool outputType;         // false = open drain, true = push pull
      int frameLength;
    } ppm;

    struct Multi {
      unsigned int rfProtocol;
      bool disableTelemetry;
      bool disableMapping;
      bool autoBindMode;
      bool lowPowerMode;
      int optionValue;
    } multi;

    struct Afhds3 {
      unsigned int rxFreq;
      unsigned int rfPower;
      unsigned int emi;
      unsigned int telemetry;
      unsigned int phyMode;
      unsigned int reserved;
    } afhds3;

    struct PXX {
      unsigned int power;          // 0 10 mW, 1 100 mW, 2 500 mW, 3 1W
      bool receiverTelemetryOff;     // false = receiver telem enabled
      bool receiverHigherChannels;  // false = pwm out 1-8, true 9-16
      int antennaMode;       // false = internal antenna, true = external antenna
    } pxx;

    struct GHOST {
      bool raw12bits;
      unsigned int telemetryBaudrate;
    } ghost;

    struct CRSF {
      unsigned int telemetryBaudrate;
    } crsf;

    struct Access {
      unsigned int receivers;
      char         receiverName[PXX2_MAX_RECEIVERS_PER_MODULE][PXX2_LEN_RX_NAME+1];
      unsigned int racingMode;
    } access;

    struct DSMP {
      unsigned int flags;
    } dsmp;

    void clear() { memset(this, 0, sizeof(ModuleData)); }
    void convert(RadioDataConversionState & cstate);
    bool isPxx2Module() const;
    bool supportRxNum() const;
    QString polarityToString() const { return ppm.pulsePol ? tr("Positive") : tr("Negative"); }
    QString rfProtocolToString() const;
    QString subTypeToString(int type = -1) const;
    QString powerValueToString(Firmware * fw) const;
    static QString indexToString(int index, Firmware * fw);
    static QString protocolToString(unsigned int protocol);
    static QStringList powerValueStrings(enum PulsesProtocol protocol, int subType, Firmware * fw);
    bool hasFailsafes(Firmware * fw) const;
    int getMaxChannelCount();
    static int getTypeFromProtocol(unsigned int protocol);
    static int getSubTypeFromProtocol(unsigned int protocol);
    static QString typeToString(int type);
    static AbstractStaticItemModel * internalModuleItemModel(int board = -1);
    static bool isProtocolAvailable(int moduleidx, unsigned int  protocol, GeneralSettings & generalSettings);
    static AbstractStaticItemModel * protocolItemModel(GeneralSettings & settings);
    static AbstractStaticItemModel * telemetryBaudrateItemModel(unsigned int  protocol);
    static bool isAvailable(PulsesProtocol proto, int port = 0);  //  moved from OpenTxFirmware EdgeTX v2.9 - TODO remove and use isProtocolAvailable
};
