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

#include "pulses_common.h"
#include "hal/serial_driver.h"
#include "hal/module_driver.h"

class UartMultiPulses: public DataBuffer<uint8_t, 64>
{
  public:
    void initFrame()
    {
      initBuffer();
    }

    void sendByte(uint8_t b)
    {
      if (getSize() < 64)
         *ptr++ = b;
    }
};

extern const etx_proto_driver_t MultiDriver;
