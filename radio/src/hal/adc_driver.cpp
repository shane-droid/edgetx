/*
 * Copyright (C) EdgeTx
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

#include "adc_driver.h"
#include "board.h"

// IS_POT_SLIDER_AVAILABLE()
#include "opentx.h"


const etx_hal_adc_driver_t* _hal_adc_driver = nullptr;
const etx_hal_adc_inputs_t* _hal_adc_inputs = nullptr;

static uint16_t adcValues[MAX_ANALOG_INPUTS] __DMA;

bool adcInit(const etx_hal_adc_driver_t* driver)
{
  // If there is an init function, it MUST succeed
  if (driver && (!driver->init || driver->init())) {
    _hal_adc_driver = driver;
    _hal_adc_inputs = driver->inputs;
    return true;
  }

  _hal_adc_driver = nullptr;
  return false;
}

static bool adcSingleRead()
{
  if (!_hal_adc_driver)
    return false;

  if (_hal_adc_driver->start_conversion &&
      !_hal_adc_driver->start_conversion())
    return false;

  if (_hal_adc_driver->wait_completion)
    _hal_adc_driver->wait_completion();

  return true;
}

bool adcRead()
{
  adcSingleRead();
  
  // TODO: this hack needs to go away...
  if (isVBatBridgeEnabled()) {
    disableVBatBridge();
  }

  return true;
}

void adcCalibSetMidPoint()
{
  uint8_t max_inputs = adcGetMaxCalibratedInputs();
  uint8_t pot_offset = adcGetInputOffset(ADC_INPUT_POT);

  for (uint8_t i = 0; i < max_inputs; i++) {

    auto& calib = reusableBuffer.calib.inputs[i];
    if (i < pot_offset || !IS_POT_MULTIPOS(i - pot_offset)) {
      calib.input.loVal = 15000;
      calib.input.hiVal = -15000;
      calib.input.midVal = getAnalogValue(i) >> 1;
    } else {
      calib.xpot.stepsCount = 0;
      calib.xpot.lastCount = 0;
      memclear(calib.xpot.steps, sizeof(calib.xpot.steps));
    }
  }
}

#define XPOT_DELTA 10
#define XPOT_DELAY 10 /* cycles */

#define XPOT_CALIB_SHIFT 5

static void writeAnalogCalib(uint8_t input, int16_t low, int16_t mid, int16_t high)
{
  auto& calib = g_eeGeneral.calib[input];
  calib.mid = mid;

  int16_t v = mid - low;
  calib.spanNeg = v - v / STICK_TOLERANCE;

  v = high - mid;
  calib.spanPos = v - v / STICK_TOLERANCE;
}

static void writeXPotCalib(uint8_t input, int16_t* steps, uint8_t n_steps)
{
  if (n_steps < 1) return;

  StepsCalibData* calib = (StepsCalibData*)&g_eeGeneral.calib[input];
  calib->count = n_steps - 1;

  for (int i = 0; i < calib->count; i++) {
    calib->steps[i] = (steps[i + 1] + steps[i]) >> XPOT_CALIB_SHIFT;
  }
}

void adcCalibSetMinMax()
{
  // get low and high vals for sticks and pots
  uint8_t max_input = adcGetMaxCalibratedInputs();
  uint8_t pot_offset = adcGetInputOffset(ADC_INPUT_POT);

  for (uint8_t i = 0; i < max_input; i++) {

    auto& calib = reusableBuffer.calib.inputs[i];

    if (i < pot_offset || !IS_POT_MULTIPOS(i - pot_offset)) {
      int16_t vt = anaIn(i);
      calib.input.loVal = min(vt, calib.input.loVal);
      calib.input.hiVal = max(vt, calib.input.hiVal);

      if (i >= pot_offset && IS_POT_WITHOUT_DETENT(i - pot_offset)) {
        calib.input.midVal = (calib.input.hiVal + calib.input.loVal) / 2;
      }

      // in case we enough input movement, store the result
      if (abs(calib.input.loVal - calib.input.hiVal) > 50) {
	writeAnalogCalib(i, calib.input.loVal, calib.input.midVal, calib.input.hiVal);
      }
    } else {
      auto& xpot = calib.xpot;
      int count = xpot.stepsCount;
      if (count <= XPOTS_MULTIPOS_COUNT) {
        // use raw analog value for multipos calibraton,
        // anaIn() already has multipos decoded value
        int16_t vt = getAnalogValue(i) >> 1;
        if (xpot.lastCount == 0 || vt < xpot.lastPosition - XPOT_DELTA ||
            vt > xpot.lastPosition + XPOT_DELTA) {
          xpot.lastPosition = vt;
          xpot.lastCount = 1;
        } else {
          if (xpot.lastCount < 255) xpot.lastCount++;
        }
        if (xpot.lastCount == XPOT_DELAY) {
          int16_t position = xpot.lastPosition;
          bool found = false;
          for (int j = 0; j < count; j++) {
            int16_t step = xpot.steps[j];
            if (position >= step - XPOT_DELTA &&
                position <= step + XPOT_DELTA) {
              found = true;
              break;
            }
          }
          if (!found) {
            if (count < XPOTS_MULTIPOS_COUNT) {
              int j = 0;
              for (; j < count; j++) {
                if (position < xpot.steps[j]) {
                  memmove(&xpot.steps[j + 1], &xpot.steps[j],
                          (count - j) * sizeof(int16_t));
                  break;
                }
              }
              xpot.steps[j] = position;
            }

            xpot.stepsCount = ++count;
	    writeXPotCalib(i, xpot.steps, count);
          }
        }
      }
    }
  }
}

static void disableUncalibratedXPots()
{
  uint8_t pot_offset = adcGetInputOffset(ADC_INPUT_POT);
  uint8_t max_pots = adcGetMaxInputs(ADC_INPUT_POT);

  for (uint8_t i = 0; i < max_pots; i++) {
    if (IS_POT_MULTIPOS(i)) {
      StepsCalibData* calib = (StepsCalibData*)&g_eeGeneral.calib[i + pot_offset];
      if(!IS_MULTIPOS_CALIBRATED(calib)) {
        // not enough config points
#if defined(XPOS_CALIB_DEFAULT)
        size_t index = 0;
        calib->count = XPOTS_MULTIPOS_COUNT - 1;
        for (const auto &value : XPOS_CALIB_DEFAULT) calib->steps[index++] = value;
#else
        g_eeGeneral.potsConfig &= POT_CONFIG_DISABLE_MASK(i);
#endif
      }
    }
  }
}

void adcCalibStore()
{
  disableUncalibratedXPots();
  g_eeGeneral.chkSum = evalChkSum();
  storageDirty(EE_GENERAL);
}

uint16_t getRTCBatteryVoltage()
{
  // anaIn() outputs value divided by (1 << ANALOG_SCALE)
  if (adcGetMaxInputs(ADC_INPUT_RTC_BAT) < 1) return 0;
#if defined(STM32F413xx)
  return (anaIn(adcGetInputOffset(ADC_INPUT_RTC_BAT)) * ADC_VREF_PREC2) /
         (1024 >> ANALOG_SCALE);
#else
  return (anaIn(adcGetInputOffset(ADC_INPUT_RTC_BAT)) * ADC_VREF_PREC2) /
         (2048 >> ANALOG_SCALE);
#endif
}

uint16_t getAnalogValue(uint8_t index)
{
  if (index >= MAX_ANALOG_INPUTS) return 0;
  return adcValues[index];
}

void setAnalogValue(uint8_t index, uint16_t value)
{
  if (index >= MAX_ANALOG_INPUTS) return;
  adcValues[index] = value;
}

uint16_t* getAnalogValues()
{
  return adcValues;
}

// used by diaganas
uint32_t s_anaFilt[MAX_ANALOG_INPUTS];

#define ANALOG_MULTIPLIER       (1<<ANALOG_SCALE)
#define ANA_FILT(chan)          (s_anaFilt[chan] / (JITTER_ALPHA * ANALOG_MULTIPLIER))
#if (JITTER_ALPHA * ANALOG_MULTIPLIER > 32)
  #error "JITTER_FILTER_STRENGTH and ANALOG_SCALE are too big, their summ should be <= 5 !!!"
#endif

uint16_t anaIn(uint8_t chan)
{
  if (chan >= MAX_ANALOG_INPUTS) return 0;
  return ANA_FILT(chan);
}

uint32_t anaIn_diag(uint8_t chan)
{
  if (chan >= MAX_ANALOG_INPUTS) return 0;
  return s_anaFilt[chan] / JITTER_ALPHA;
}

void anaSetFiltered(uint8_t chan, uint16_t val)
{
  val += RESX;
  s_anaFilt[chan] = val * (JITTER_ALPHA * ANALOG_MULTIPLIER);
}

void anaResetFiltered()
{
  memset(s_anaFilt, 0, sizeof(s_anaFilt));
}

#if defined(JITTER_MEASURE)
JitterMeter<uint16_t> rawJitter[MAX_ANALOG_INPUTS];
JitterMeter<uint16_t> avgJitter[MAX_ANALOG_INPUTS];
tmr10ms_t jitterResetTime = 0;
#endif

uint16_t getBatteryVoltage()
{
  // using filtered ADC value on purpose
  if (adcGetMaxInputs(ADC_INPUT_VBAT) < 1) return 0;
  int32_t instant_vbat = anaIn(adcGetInputOffset(ADC_INPUT_VBAT));

  // TODO: remove BATT_SCALE / BATTERY_DIVIDER defines
#if defined(BATT_SCALE)
  instant_vbat =
      (instant_vbat * BATT_SCALE * (128 + g_eeGeneral.txVoltageCalibration)) /
      BATTERY_DIVIDER;
  // add voltage drop because of the diode TODO check if this is needed, but
  // removal will break existing calibrations!
  instant_vbat += VOLTAGE_DROP;
  return (uint16_t)instant_vbat;
#else
  return (uint16_t)((instant_vbat * (1000 + g_eeGeneral.txVoltageCalibration)) /
                    BATTERY_DIVIDER);
#endif
}

void getADC()
{
  uint8_t max_analogs = adcGetMaxInputs(ADC_INPUT_ALL);
  uint8_t pot_offset = adcGetInputOffset(ADC_INPUT_POT);

#if defined(JITTER_MEASURE)
  if (JITTER_MEASURE_ACTIVE() && jitterResetTime < get_tmr10ms()) {
    // reset jitter measurement every second
    for (uint32_t x = 0; x < max_analogs; x++) {
      rawJitter[x].reset();
      avgJitter[x].reset();
    }
    jitterResetTime = get_tmr10ms() + 100;  //every second
  }
#endif

  DEBUG_TIMER_START(debugTimerAdcRead);
  if (!adcRead())
      TRACE("adcRead failed");
  DEBUG_TIMER_STOP(debugTimerAdcRead);

  // TODO: jitter filter should probably still be applied
  //       to VBAT and RTC_BAT, no matter what is configured
  //
  for (uint8_t x = 0; x < max_analogs; x++) {

    uint32_t v = getAnalogValue(x) >> (1 - ANALOG_SCALE);

    // Jitter filter:
    //    * pass trough any big change directly
    //    * for small change use Modified moving average (MMA) filter
    //
    // Explanation:
    //
    // Normal MMA filter has this formula:
    //            <out> = ((ALPHA-1)*<out> + <in>)/ALPHA
    //
    // If calculation is done this way with integer arithmetics, then any small change in
    // input signal is lost. One way to combat that, is to rearrange the formula somewhat,
    // to store a more precise (larger) number between iterations. The basic idea is to
    // store undivided value between iterations. Therefore an new variable <filtered> is
    // used. The new formula becomes:
    //           <filtered> = <filtered> - <filtered>/ALPHA + <in>
    //           <out> = <filtered>/ALPHA  (use only when out is needed)
    //
    // The above formula with a maximum allowed ALPHA value (we are limited by
    // the 16 bit s_anaFilt[]) was tested on the radio. The resulting signal still had
    // some jitter (a value of 1 was observed). The jitter might be bigger on other
    // radios.
    //
    // So another idea is to use larger input values for filtering. So instead of using
    // input in a range from 0 to 2047, we use twice larger number (temp[x] is divided less)
    //
    // This also means that ALPHA must be lowered (remember 16 bit limit), but test results
    // have proved that this kind of filtering gives better results. So the recommended values
    // for filter are:
    //     JITTER_FILTER_STRENGTH  4
    //     ANALOG_SCALE            1
    //
    // Variables mapping:
    //   * <in> = v
    //   * <out> = s_anaFilt[x]
    uint32_t previous = s_anaFilt[x] / JITTER_ALPHA;
    uint32_t diff = (v > previous) ? (v - previous) : (previous - v);

    // Combine ADC jitter filter setting form radio and model.
    // Model can override (on or off) or use setting from radio setup.
    // Model setting is active when 1, radio setting is active when 0
    uint8_t useJitterFilter = 0;
    if (g_model.jitterFilter == OVERRIDE_GLOBAL) {
       // Use radio setting - which is inverted
      useJitterFilter = !g_eeGeneral.noJitterFilter;
    } else {
      // Enable if value is "On", disable if "Off"
      useJitterFilter = (g_model.jitterFilter == OVERRIDE_ON)?1:0;
    }

    if (useJitterFilter && diff < (10*ANALOG_MULTIPLIER)) {
      // apply jitter filter
      s_anaFilt[x] = (s_anaFilt[x] - previous) + v;
    }
    else {
      // use unfiltered value
      s_anaFilt[x] = v * JITTER_ALPHA;
    }

#if defined(JITTER_MEASURE)
    if (JITTER_MEASURE_ACTIVE()) {
      avgJitter[x].measure(ANA_FILT(x));
    }
#endif

    #define ANAFILT_MAX    (2 * RESX * JITTER_ALPHA * ANALOG_MULTIPLIER)
    StepsCalibData * calib = (StepsCalibData *) &g_eeGeneral.calib[x];
    if (IS_POT_MULTIPOS(x - pot_offset) && IS_MULTIPOS_CALIBRATED(calib)) {
      // TODO: consider adding another low pass filter to eliminate multipos switching glitches
      uint8_t vShifted = ANA_FILT(x) >> 4;
      s_anaFilt[x] = ANAFILT_MAX;
      for (uint32_t i = 0; i < calib->count; i++) {
        if (vShifted < calib->steps[i]) {
          s_anaFilt[x] = (i * (ANAFILT_MAX + JITTER_ALPHA * ANALOG_MULTIPLIER)) / calib->count;
          break;
        }
      }
    }
  }
}

potconfig_t adcGetDefaultPotsConfig()
{
  if (!_hal_adc_driver) return 0;
  return _hal_adc_driver->default_pots_cfg;
}

uint8_t adcGetMaxInputs(uint8_t type)
{
  if (type > ADC_INPUT_ALL) return 0;
  return _hal_adc_inputs[type].n_inputs;
}

uint8_t adcGetInputOffset(uint8_t type)
{
  if (type > ADC_INPUT_ALL) return 0;
  return _hal_adc_inputs[type].offset;
}

uint8_t adcGetMaxCalibratedInputs()
{
  // ADC_INPUT_MAIN + ADC_INPUT_POT + ADC_INPUT_AXIS
  return adcGetInputOffset(ADC_INPUT_VBAT);
}

uint16_t adcGetInputValue(uint8_t type, uint8_t idx)
{
  if (type >= ADC_INPUT_ALL) return 0;

  const auto& inputs = _hal_adc_inputs[type];
  auto n_inputs = inputs.n_inputs;
  auto offset = inputs.offset;
  if (!n_inputs || idx >= n_inputs) return 0;

  return getAnalogValue(offset + idx);
}

const char* adcGetInputName(uint8_t type, uint8_t idx)
{
  if (type >= ADC_INPUT_ALL ||
      idx >= _hal_adc_inputs[type].n_inputs)
    return "";

  return _hal_adc_inputs[type].inputs[idx].name;
}

const char* adcGetInputName(uint8_t idx)
{
  uint8_t type = ADC_INPUT_MAIN;

  // find the proper input type
  while (_hal_adc_inputs[type].offset + _hal_adc_inputs[type].n_inputs <= idx) {
    if (++type > ADC_INPUT_AXIS) return nullptr;
  }

  idx -= _hal_adc_inputs[type].offset;
  return _hal_adc_inputs[type].inputs[idx].name;
}

int adcGetInputIdx(const char* input, uint8_t len)
{
  int idx = 0;
  uint8_t type = ADC_INPUT_MAIN;

  do {
    for (uint8_t i = 0; i < _hal_adc_inputs[type].n_inputs; i++, idx++) {
      if (!strncmp(_hal_adc_inputs[type].inputs[i].name, input, len))
        return idx;
    }
  } while(++type < ADC_INPUT_ALL);

  return -1;
}

const char* adcGetInputLabel(uint8_t type, uint8_t idx)
{
  if (type >= ADC_INPUT_ALL ||
      idx >= _hal_adc_inputs[type].n_inputs)
    return "";

  return _hal_adc_inputs[type].inputs[idx].label;
}

const char* adcGetInputShortLabel(uint8_t type, uint8_t idx)
{
  if (type >= ADC_INPUT_ALL ||
      idx >= _hal_adc_inputs[type].n_inputs)
    return "";

  return _hal_adc_inputs[type].inputs[idx].short_label;
}
