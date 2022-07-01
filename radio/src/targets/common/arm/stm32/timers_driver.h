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

#if defined(SIMU)

uint16_t getTmr2MHz();

#define watchdogSuspend(timeout)
#else

#include "hal.h"

void init2MhzTimer();
void init1msTimer();
void stop1msTimer();

static inline uint16_t getTmr2MHz() { return TIMER_2MHz_TIMER->CNT; }

void watchdogSuspend(uint32_t timeout);

#endif

#include "opentx_types.h"

extern "C" volatile tmr10ms_t g_tmr10ms;

static inline tmr10ms_t get_tmr10ms()
{
  return g_tmr10ms;
}
