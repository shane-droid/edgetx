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
 *
 */

// Original SE translations author: Kjell Kernen <kjell.kernen@gmail.com>
// Adapted to new string handling in EdgeTX, added and somewhat revised translations: Ulf Hedlund <ulfh05@hotmail.com>

/*
 * Formatting octal codes available in TR_ strings:
 *  \037\x           -sets LCD x-coord (x value in octal)
 *  \036             -newline
 *  \035             -horizontal tab (ARM only)
 *  \001 to \034     -extended spacing (value * FW/2)
 *  \0               -ends current string
 */

// NON ZERO TERMINATED STRINGS
#define TR_OFFON                        "Av","På"
#define TR_MMMINV                       "---","INV"
#define TR_VBEEPMODE                    "Tyst","Alarm","EjKnp","Alla"
#define TR_COUNTDOWNVALUES              "5s","10s","20s","30s"
#define TR_VBLMODE                      "Av",TR("Knapp","Knappar"),TR("Spak","Spakar"),"Allt","PÅ"
#define TR_TRNMODE                      "Av","+=",":="
#define TR_TRNCHN                       "KN1","KN2","KN3","KN4"

#if defined(CLI) || defined(DEBUG)
  #define TR_AUX_SERIAL_MODES           "Debug","Spegling av S-Port","Telemetri","SBUS Instruktör","Lua"
#else
  #define TR_AUX_SERIAL_MODES           "Av","Spegling av S-Port","Telemetri","SBUS Instruktör","Lua"
#endif

#define TR_SWTYPES                      "Ingen","Flipp","2Pos","3Pos"
#define TR_POTTYPES                     TR("None","Ingen"),TR("Pot w. det","Mittläges-pot"),TR("Multipos","Flerlägesväljare"),TR("Pot","Potentiometer")
#define TR_SLIDERTYPES                  "Ingen","Skjutpot"
#define TR_VLCD                         "Normal","Optrex"
#define TR_VPERSISTENT                  "Av","Flygning","Nolla själv"
#define TR_COUNTRY_CODES                TR("US","Amerika"),TR("JP","Japan"),TR("EU","Europa")
#define TR_USBMODES                     "Fråga",TR("Joyst","Joystick"),TR("SD-kort","Lagring"),"Seriell"
#define TR_JACK_MODES                   "Fråga","Audio","Instruktör"
#define TR_TELEMETRY_PROTOCOLS          "FrSky S.Port","FrSky D","FrSky D (sladd)","TBS Crossfire","Spektrum","AFHDS2A IBUS","Multi Telemetry"
#define TR_MULTI_CUSTOM                 "Custom"
#define TR_VTRIMINC                     TR("Expo","Exponentiell"),TR("xFin","Extra Fin"),"Fin","Medium","Grov"
#define TR_VDISPLAYTRIMS                "Nej","Ändra","Ja"
#define TR_VBEEPCOUNTDOWN               "Tyst","Pip","Röst","Vibrera"
#define TR_VVARIOCENTER                 "Pip","Tyst"
#define TR_CURVE_TYPES                  "Normal","Egen"

#define TR_ADCFILTERVALUES              "Global","Av","På"

#if defined(PCBX10)
  #define TR_RETA123                    "R","H","G","S","1","3","2","4","5","6","7","V","H"
#elif defined(PCBHORUS)
  #define TR_RETA123                    "R","H","G","S","1","3","2","4","5","V","H"
#elif defined(PCBX9E)
  #define TR_RETA123                    "R","H","G","S","1","2","3","4","V","H","V","H"
#elif defined(PCBTARANIS)
  #define TR_RETA123                    "R","H","G","S","1","2","3","V","H"
#else
  #define TR_RETA123                    "R","H","G","S","1","2","3"
#endif
                                  
#define TR_VCURVEFUNC                   "---","x>0","x<0","|x|","f>0","f<0","|f|"
#define TR_VMLTPX                       "Addera","Förstärk","Ersätt"
#define TR_VMLTPX2                      "+=","*=",":="

#if defined(PCBHORUS)
  #define TR_VMIXTRIMS                  "Av","På","Rod","Hjd","Gas","Ske","T5","T6"
#else
  #define TR_VMIXTRIMS                  "Av","På","Rod","Hjd","Gas","Ske"
#endif

#if defined(PCBTARANIS)
  #define TR_CSWTIMER                   "Timer"
  #define TR_CSWSTICKY                  "Seg"
  #define TR_CSWRANGE                   "Vidd"
  #define TR_CSWSTAY                    "Kant"
#else
  #define TR_CSWTIMER                   "Tim"
  #define TR_CSWSTICKY                  "Seg"
    #define TR_CSWRANGE                 "Vidd"
    #define TR_CSWSTAY                  "Kant"
#endif

#define TR_CSWEQUAL                     "a=x"
#define TR_VCSWFUNC                     "---",TR_CSWEQUAL,"a~x","a>x","a<x",TR_CSWRANGE,"|a|>x","|a|<x","AND","OR","XOR",TR_CSWSTAY,"a=b","a>b","a<b","Δ≥x","|Δ|≥x",TR_CSWTIMER,TR_CSWSTICKY

#define TR_TEXT_SIZE                    "Standard","Tiny","Small","Mid","Double"

#if defined(VARIO)
  #define TR_VVARIO                     "Vario"
#else
  #define TR_VVARIO                     "[Vario]"
#endif

#if defined(AUDIO)
  #define TR_SOUND                      "Spela ljud"
#else
  #define TR_SOUND                      "Pip"
#endif

#if defined(HAPTIC)
  #define TR_HAPTIC                     "Vibrator"
#else
  #define TR_HAPTIC                     "[Vibrator]"
#endif

#if defined(VOICE)
  #define TR_PLAY_TRACK                 "Spela upp"
  #define TR_PLAY_BOTH                  "Spela båda"
  #define TR_PLAY_VALUE                 "Säg värdet"
#else
  #define TR_PLAY_TRACK                 "[Sp. spår]"
  #define TR_PLAY_BOTH                  "[Sp. båda]"
  #define TR_PLAY_VALUE                 "[Sp. värde]"
#endif

#define TR_SF_BG_MUSIC                  "Musik","Pausa musik"

#if defined(SDCARD)
  #define TR_SDCLOGS                    "SD-loggar"
#else
  #define TR_SDCLOGS                    "[SD-loggar]"
#endif

#ifdef GVARS
  #define TR_ADJUST_GVAR                "Justera"
#else
  #define TR_ADJUST_GVAR                "[Just. GV]"
#endif

#if defined(LUA)
  #define TR_SF_PLAY_SCRIPT             "Lua-skript"
#else
  #define TR_SF_PLAY_SCRIPT             "[Lua]"
#endif

#if defined(DEBUG)
  #define TR_SF_TEST                    "Test"
#else
  #define TR_SF_TEST
#endif

#if defined(OVERRIDE_CHANNEL_FUNCTION) && LCD_W >= 212
  #define TR_SF_SAFETY                  "Säkra"
#elif defined(OVERRIDE_CHANNEL_FUNCTION)
  #define TR_SF_SAFETY                  "Säkra"
#else
  #define TR_SF_SAFETY                  "---"
#endif

#define TR_SF_SCREENSHOT                "Skärmbild"
#define TR_SF_RACING_MODE               "Tävlingsläge"
#define TR_SF_DISABLE_TOUCH             "No touch"
#define TR_SF_RESERVE                   "[reserve]"

#define TR_VFSWFUNC                     TR_SF_SAFETY,"Instruktör","Sätt trimm","Nollställ","Sätt",TR_ADJUST_GVAR,"Volym","SetFailsfe","RangeCheck","ModuleBind",TR_SOUND,TR_PLAY_TRACK,TR_PLAY_VALUE, TR_SF_RESERVE,TR_SF_PLAY_SCRIPT,TR_SF_RESERVE,TR_SF_BG_MUSIC,TR_VVARIO,TR_HAPTIC,TR_SDCLOGS,"Belysning", TR_SF_SCREENSHOT,TR_SF_RACING_MODE,TR_SF_DISABLE_TOUCH,TR_SF_TEST

#define TR_FSW_RESET_TELEM              TR("Telm","Telemetri")

#if defined(PCBTARANIS)
  #define TR_FSW_RESET_TIMERS           "Timer 1","Timer 2","Timer 3"
#else
  #define TR_FSW_RESET_TIMERS           "Tmr1","Tmr2","Tmr3"
#endif

#define TR_VFSWRESET                    TR_FSW_RESET_TIMERS,"Alla",TR_FSW_RESET_TELEM
#define TR_FUNCSOUNDS                   TR("Bp1","Beep1"),TR("Bp2","Beep2"),TR("Bp3","Beep3"),TR("Wrn1","Warn1"),TR("Wrn2","Warn2"),TR("Chee","Cheep"),TR("Rata","Ratata"),"Tick",TR("Sirn","Siren"),"Ring",TR("SciF","SciFi"),TR("Robt","Robot"),TR("Chrp","Chirp"),"Tada",TR("Crck","Crickt"),TR("Alrm","AlmClk")

#define TR_TELEM_RESERVE                TR("[--]","[---]")
#define TR_TELEM_TIME                   TR("Tid","H:M")
#define TR_RAS                          "SWR"
#define TR_RX_BATT                      TR("BtRx","BatRx")
#define TR_A3_A4                        "A3","A4"
#define TR_A3_A4_MIN                    "A3-","A4-"
#define TR_ASPD_MAX                     TR("ASp+","ASpd+")

#if defined(PCBTARANIS)
  #define TR_TELEM_RSSI_RX             "RSSI"
#else
  #define TR_TELEM_RSSI_RX             "Rx"
#endif

#define TR_TELEM_TIMERS                "Tmr1","Tmr2","Tmr3"

#define LENGTH_UNIT_IMP                "fot"
#define SPEED_UNIT_IMP                 "mph"
#define LENGTH_UNIT_METR               "m"
#define SPEED_UNIT_METR                "kmh"

#define TR_VUNITSSYSTEM                TR("Metri.","Metriska"),TR("Imper.","Imperial")
#define TR_VTELEMUNIT        "-","V","A","mA","kts","m/s","f/s","kmh","mph","m","ft","@C","@F","%","mAh","W","mW","dB","rpm","g","@","rad","ml","fOz","mlm","Hz","mS","uS","km"

#define STR_V                          (STR_VTELEMUNIT[1])
#define STR_A                          (STR_VTELEMUNIT[2])

#define TR_VTELEMSCREENTYPE            "Inget","Siffror","Staplar","Skript"
#define TR_GPSFORMAT                   "DMS","NMEA"

#define TR_TEMPLATE_CLEAR_MIXES        "Nolla mixar"
#define TR_TEMPLATE_SIMPLE_4CH         "Enkel 4-kanal"
#define TR_TEMPLATE_STICKY_TCUT        "Gasklippning"
#define TR_TEMPLATE_VTAIL              "V-stjärt"
#define TR_TEMPLATE_DELTA              "Deltavinge"
#define TR_TEMPLATE_ECCPM              "eCCPM"
#define TR_TEMPLATE_HELI               "Helikopter"
#define TR_TEMPLATE_SERVO_TEST         "Servotest"

#define TR_VSWASHTYPE                  "---","120","120X","140","90"

#define TR_STICKS_VSRCRAW              STR_CHAR_STICK "Rod", STR_CHAR_STICK "Hjd", STR_CHAR_STICK "Gas", STR_CHAR_STICK "Ske"

#if defined(PCBHORUS)
  #define TR_TRIMS_VSRCRAW             STR_CHAR_TRIM "Rod",STR_CHAR_TRIM "Hjd",STR_CHAR_TRIM "Gas",STR_CHAR_TRIM "Ske",STR_CHAR_TRIM "T5",STR_CHAR_TRIM "T6"
#else
  #define TR_TRIMS_VSRCRAW             TR("TrmR",STR_CHAR_TRIM "Rod"),TR("TrmH",STR_CHAR_TRIM "Hjd"),TR("TrmG",STR_CHAR_TRIM "Gas"),TR("TrmS",STR_CHAR_TRIM "Ske")
#endif

#if defined(PCBHORUS)
  #define TR_TRIMS_SWITCHES            STR_CHAR_TRIM "Rv",STR_CHAR_TRIM "Rh",STR_CHAR_TRIM "Hn",STR_CHAR_TRIM "Hu",STR_CHAR_TRIM "Gn",STR_CHAR_TRIM "Gu", STR_CHAR_TRIM "Sv",STR_CHAR_TRIM "Sh",STR_CHAR_TRIM "5d",STR_CHAR_TRIM "5u",STR_CHAR_TRIM "6d",STR_CHAR_TRIM "6u"
#else
  #define TR_TRIMS_SWITCHES            TR("tRv",STR_CHAR_TRIM "Rv"),TR("tRh",STR_CHAR_TRIM "Rh"),TR("tHn",STR_CHAR_TRIM "Hn"),TR("tHu",STR_CHAR_TRIM "Hu"),TR("tGn", STR_CHAR_TRIM "Gn"),TR("tGu",STR_CHAR_TRIM "Gu"),TR("tSv",STR_CHAR_TRIM "Sv"),TR("tSh",STR_CHAR_TRIM "Sh")
#endif

#define TR_ROTARY_ENCODERS
#define TR_ROTENC_SWITCHES

#define TR_ON_ONE_SWITCHES              "PÅ","Ett"

#if defined(IMU)
  #define TR_IMU_VSRCRAW                "TltX","TltY",
#else
  #define TR_IMU_VSRCRAW
#endif

#if defined(HELI)
  #define TR_CYC_VSRCRAW                "CYK1","CYK2","CYK3"
#else
  #define TR_CYC_VSRCRAW                "[C1]","[C2]","[C3]"
#endif

#define TR_RESERVE_VSRCRAW              "[--]"
#define TR_EXTRA_VSRCRAW                "Batt","Tid","GPS",TR_RESERVE_VSRCRAW,TR_RESERVE_VSRCRAW,TR_RESERVE_VSRCRAW,TR_RESERVE_VSRCRAW,"Tmr1","Tmr2","Tmr3"

#define TR_VTMRMODES                    "Av","På","GAs","GA%","GAt"
#define TR_VTRAINER_MASTER_OFF          "Av"
#define TR_VTRAINER_MASTER_JACK         "Lärare/Uttag"
#define TR_VTRAINER_SLAVE_JACK          "Elev/Uttag"
#define TR_VTRAINER_MASTER_SBUS_MODULE  "Lärare/SBUS-modul"
#define TR_VTRAINER_MASTER_CPPM_MODULE  "Lärare/CPPM-modul"
#define TR_VTRAINER_MASTER_BATTERY      "Lärare/Seriell"
#define TR_VTRAINER_BLUETOOTH           TR("Lärare/BT","Lärare/Blåtand"),TR("Elev/BT","Elev/Blåtand")
#define TR_VTRAINER_MULTI               "Lärare/Multi"

#define TR_VFAILSAFE                    "Ej def.","Lås servo","Anpassat","Pulsfritt","Mottagare"
#define TR_VSENSORTYPES                 "Egen","Beräknad"
#define TR_VFORMULAS                    "Addera","Medel","Min","Max","Multipl.","Totalsumma","Cell","Förbrukning","Sträcka"
#define TR_VPREC                        "0.--","0.0","0.00"
#define TR_VCELLINDEX                   "Lägsta","1","2","3","4","5","6","Högsta","Skillnad"
#define TR_GYROS                        "GyrX","GyrY"
#define TR_SUBTRIMMODES                 STR_CHAR_DELTA " (center only)","= (symetrical)"

// ZERO TERMINATED STRINGS
#if defined(COLORLCD)
  #define INDENT
  #define LEN_INDENT                    3
  #define INDENT_WIDTH                  12
  #define BREAKSPACE                    "\036"
#else
  #define INDENT                        "\001"
  #define LEN_INDENT                    1
  #define INDENT_WIDTH                  (FW/2)
  #define BREAKSPACE                    " "
#endif

#if defined(PCBFRSKY)
  #define TR_ENTER                      "[ENTER]"
#elif defined(PCBNV14)
  #define TR_ENTER                      "[NEXT]"
#else
  #define TR_ENTER                      "[MENU]"
#endif

#if defined(PCBHORUS)
  #define TR_EXIT                       "RTN"
  #define TR_OK                         TR_ENTER
#else
  #define TR_EXIT                       "EXIT"
  #define TR_OK                         "\010" "\010" "\010" TR("[OK]", "\010" "\010" "[OK]")
#endif

#if defined(PCBTARANIS)
  #define TR_POPUPS_ENTER_EXIT          TR(TR_EXIT "\010" TR_ENTER, TR_EXIT "\010" "\010" "\010" "\010" TR_ENTER)
#else
  #define TR_POPUPS_ENTER_EXIT          TR_ENTER "\010" TR_EXIT
#endif

#define TR_MENUWHENDONE                 CENTER "\006" TR_ENTER " AVSLUTAR"
#define TR_FREE                         "kvar"
#define TR_YES                          "Yes"
#define TR_NO                           "No"
#define TR_DELETEMODEL                  "RADERA" BREAKSPACE "MODELL"
#define TR_COPYINGMODEL                 "Kopierar..."
#define TR_MOVINGMODEL                  "Flyttar..."
#define TR_LOADINGMODEL                 "Laddar..."
#define TR_NAME                         "Namn"
#define TR_MODELNAME                    "Modellnamn"
#define TR_PHASENAME                    "Lägesnamn"
#define TR_MIXNAME                      TR("Namn","Mixernamn")
#define TR_INPUTNAME                    TR("Input","Inputnamn")
#define TR_EXPONAME                     TR("Namn","Radnamn")
#define TR_BITMAP                       "Modellikon"
#define TR_TIMER                        TR("Timer","Timer ")
#define TR_START                        "Start"
#define TR_ELIMITS                      TR("Gränser++","Utökade gränser")
#define TR_ETRIMS                       TR("Trimmar++","Utökade trimmar")
#define TR_TRIMINC                      TR("Trimning","Trimökning")
#define TR_DISPLAY_TRIMS                "Visa trimmar"
#define TR_TTRACE                       TR("Följ gas", INDENT "Följ gas")
#define TR_TTRIM                        TR("Gastrim", INDENT "Gastrim")
#define TR_TTRIM_SW                     TR("T-Trim-Sw", INDENT "Trim switch")
#define TR_BEEPCTR                      TR("Cent.pip", "Centerpip")
#define TR_USE_GLOBAL_FUNCS             TR("Glob.funk.", "Anv. globala funk.")

#define TR_PROTOCOL                     TR("Proto.", "Protokoll")
#define TR_PPMFRAME                     INDENT "PPM-paket"
#define TR_REFRESHRATE                  TR(INDENT "Refresh", INDENT "Refresh rate")
#define STR_WARN_BATTVOLTAGE            TR(INDENT "Output is VBAT: ", INDENT "VARNING: Output level is VBAT: ")
#define TR_WARN_5VOLTS                  "Warning: output level is 5 volts"
#define TR_MS                           "ms"
#define TR_FREQUENCY                    INDENT "Frekvens"
#define TR_SWITCH                       "Brytare"
#define TR_TRIMS                        "Trimmar"
#define TR_FADEIN                       "Tona in"
#define TR_FADEOUT                      "Tona ut"
#define TR_DEFAULT                      "Standard"
#define TR_CHECKTRIMS                   "\006Kolla\012trimmar"
#define OFS_CHECKTRIMS                  (9*FW)
#define TR_SWASHTYPE                    "Swashtyp"
#define TR_COLLECTIVE                   "Kollektiv"
#define TR_AILERON                      "Skevroder-källa"
#define TR_ELEVATOR                     "Höjdroder-källa"
#define TR_SWASHRING                    "Swashring"
#define TR_ELEDIRECTION                 "HöJD riktning"
#define TR_AILDIRECTION                 "SKEV riktning"
#define TR_COLDIRECTION                 TR("PITCH riktn.","PITCH riktning")
#define TR_MODE                         "Läge"
#define TR_SUBTYPE                      INDENT "Subtyp"
#define TR_NOFREEEXPO                   "Ingen ledig expo!"
#define TR_NOFREEMIXER                  "Ingen ledig mixer!"
#define TR_SOURCE                       "Källa"
#define TR_WEIGHT                       "Vikt"
#define TR_EXPO                         TR("Expo","Exponentiell")
#define TR_SIDE                         "Sida"
#define TR_DIFFERENTIAL                 "Diff"
#define TR_OFFSET                       "Offset"
#define TR_TRIM                         "Trim"
#define TR_DREX                         "DRex"
#define DREX_CHBOX_OFFSET               30
#define TR_CURVE                        "Kurva"
#define TR_FLMODE                       TR("Läge","Flyglägen")
#define TR_MIXWARNING                   "Varning"
#define TR_OFF                          "AV"
#define TR_ANTENNA                      "Antenn"
#define TR_NO_INFORMATION               TR("Ingen info", "Ingen information")
#define TR_MULTPX                       "Multiplex"
#define TR_DELAYDOWN                    TR("Dröj ned","Fördröj ned")
#define TR_DELAYUP                      TR("Dröj upp","Fördröj upp")
#define TR_SLOWDOWN                     "Trög ned"
#define TR_SLOWUP                       "Trög upp"
#define TR_MIXES                        "MIXAR"
#define TR_CV                           "KU"

#if defined(PCBNV14)
  #define TR_GV                           "GV"
#else
  #define TR_GV                           TR("G","GV")
#endif

#define TR_ACHANNEL                     "A"
#define TR_RANGE                        INDENT "MinMax"
#define TR_CENTER                       INDENT "Center"
#define TR_BAR                          "Data"
#define TR_ALARM                        "Alarm"
#define TR_USRDATA                      TR("Anv.data","Användardata")
#define TR_BLADES                       "Blad"
#define TR_SCREEN                       "Skärm"
#define TR_SOUND_LABEL                  "Ljud"
#define TR_LENGTH                       "Tid"
#define TR_BEEP_LENGTH                  "Pip-längd"
#define TR_BEEP_PITCH                   "Pip-ton"
#define TR_HAPTIC_LABEL                 "Vibrator"
#define TR_STRENGTH                     "Styrka"
#define TR_GYRO_LABEL                   "Gyro"
#define TR_GYRO_OFFSET                  "Offset"
#define TR_GYRO_MAX                     "Max"
#define TR_CONTRAST                     "Kontrast"
#define TR_ALARMS_LABEL                 "Alarm"
#define TR_BATTERY_RANGE                "Batteri-MinMax"
#define TR_BATTERYCHARGING              "Laddar..."
#define TR_BATTERYFULL                  "Batteri fullt"
#define TR_BATTERYNONE                  "None!"
#define TR_BATTERYWARNING               "Batteri"
#define TR_INACTIVITYALARM              "Inaktivitet"
#define TR_MEMORYWARNING                "Lite minne"
#define TR_ALARMWARNING                 "Ljud av"
#define TR_RSSI_SHUTDOWN_ALARM          TR("RSSI shutdown", "Check RSSI on shutdown")
#define TR_FLYSKY_TELEMETRY             TR("FlySky RSSI #", "Use FlySky RSSI value without rescalling")
#define TR_MODEL_STILL_POWERED          TR("Modell på","Modell fortfarande på")
#define TR_USB_STILL_CONNECTED          "USB fortfarande ansluten"
#define TR_MODEL_SHUTDOWN               "Stänga av?"
#define TR_PRESS_ENTER_TO_CONFIRM       "Tryck [ENTER] för att bekräfta"
#define TR_THROTTLE_LABEL               "Gas"
#define TR_THROTTLEREVERSE              TR("Inv. gas", INDENT "Inverterad gas")
#define TR_MINUTEBEEP                   "Minutpip"
#define TR_BEEPCOUNTDOWN                INDENT "Nedräkning"
#define TR_PERSISTENT                   TR(INDENT "Persist.", INDENT "Alltid på")
#define TR_BACKLIGHT_LABEL              "Belysning"
#define TR_GHOST_MENU_LABEL             "GHOST MENU"
#define TR_BLDELAY                      INDENT "Av efter"
#define TR_BLONBRIGHTNESS               INDENT "Ljusstyrka PÅ"
#define TR_BLOFFBRIGHTNESS              INDENT "Ljusstyrka AV"
#define TR_KEYS_BACKLIGHT               "Keys backlight"
#define TR_SPLASHSCREEN                 "Startbild"
#define TR_PWR_ON_DELAY                 "Pwr On delay"
#define TR_PWR_OFF_DELAY                "Pwr Off delay"
#define TR_BLCOLOR                      "Färg"
#define TR_THROTTLE_WARNING             "Gasvarning"
#define TR_CUSTOM_THROTTLE_WARNING      TR(INDENT INDENT INDENT INDENT "Cust-Pos", INDENT INDENT INDENT INDENT "Custom position?")
#define TR_CUSTOM_THROTTLE_WARNING_VAL  TR("Pos. %", "Position %")
#define TR_SWITCHWARNING                TR(INDENT "Bryt.varn.", INDENT "Brytarvarning")
#define TR_POTWARNINGSTATE              TR(INDENT "Pot&Slid.", INDENT "Pots & sliders")
#define TR_SLIDERWARNING                TR(INDENT "Slid. pos.", INDENT "Slider positions")
#define TR_POTWARNING                   TR(INDENT "Pot warn.", INDENT "Pot positions")
#define TR_TIMEZONE                     "Tidszon"
#define TR_ADJUST_RTC                   "Ändra RTC"
#define TR_GPS                          "GPS"
#define TR_RXCHANNELORD                 TR("Kanalordn. RX","Kanalordning i RX")
#define TR_STICKS                       "Spakar"
#define TR_POTS                         "Reglage"
#define TR_SWITCHES                     "Brytare"
#define TR_SWITCHES_DELAY               "Brytarfördröjning"
#define TR_SLAVE                        "Elev"
#define TR_MODESRC                      "Läge\006% Källa"
#define TR_MULTIPLIER                   "Styrka"
#define TR_CAL                          "Kal."
#define TR_CALIBRATION                  "Kalibrering"
#define TR_VTRIM                        "Trim- +"
#define TR_BG                           "BG:"
#define TR_CALIB_DONE                   "Kalibrering färdig"
#if defined(PCBHORUS)
  #define TR_MENUTOSTART                "Tryck [Enter] för att börja"
  #define TR_SETMIDPOINT                "Centrera spakar/rattar/reglage och tryck [Enter]"
  #define TR_MOVESTICKSPOTS             "Rör spakar/rattar/reglage och tryck [Enter]"
#elif defined(COLORLCD)
  #define TR_MENUTOSTART                TR_ENTER " FÖR ATT STARTA"
  #define TR_SETMIDPOINT                "CENTRERA ALLT"
  #define TR_MOVESTICKSPOTS             "RÖR SPAKAR/REGLAGE"
#else
  #define TR_MENUTOSTART                CENTER"\006" TR_ENTER " FÖR ATT BÖRJA"
  #define TR_SETMIDPOINT                CENTER"\010CENTRERA ALLT"
  #define TR_MOVESTICKSPOTS             CENTER"\004RÖR SPAKAR/REGLAGE"
#endif
#define TR_RXBATT                       "RX batt:"
#define TR_TXnRX                        "TX:\0RX:"
#define OFS_RX                          4
#define TR_ACCEL                        "Acc:"
#define TR_NODATA                       CENTER "DATA SAKNAS"
#define TR_US                           "us"
#define TR_HZ                           "Hz"
#define TR_TMR1LATMINUS                 "Tmr1Lat min\037\124us"

#define TR_TMIXMAXMS                    "Tmix max"
#define TR_FREE_STACK                   "Free stack"
#define TR_INT_GPS_LABEL                "Internal GPS"
#define TR_HEARTBEAT_LABEL              "Heartbeat"
#define TR_LUA_SCRIPTS_LABEL            "Lua-skript"
#define TR_FREE_MEM_LABEL               "Free mem"
#define TR_TIMER_LABEL                  "Timer"
#define TR_THROTTLE_PERCENT_LABEL       "Throttle %"
#define TR_BATT_LABEL                   "Batteri"
#define TR_SESSION                      "Session"
#define TR_MENUTORESET                  TR_ENTER " nollar"
#define TR_PPM_TRAINER                  "TR"
#define TR_CH                           "KN"
#define TR_MODEL                        "MODELL"
#define TR_FM                           "FL"
#define TR_MIX                          "MIX"
#define TR_EEPROMLOWMEM                 "Minnesbrist"
#define TR_PRESS_ANY_KEY_TO_SKIP        "Tryck ned en knapp"
#define TR_THROTTLE_NOT_IDLE            "Gasen är på!"
#define TR_ALARMSDISABLED               "Alarmen avstängda!"
#define TR_PRESSANYKEY                  "Tryck ned en knapp"
#define TR_BADEEPROMDATA                "Minnet kan inte tolkas"
#define TR_BAD_RADIO_DATA               "Data från radion kan inte tolkas"
#define TR_EEPROMFORMATTING             "Minnet formateras"
#define TR_STORAGE_FORMAT               "SD-Lagring förbereds"
#define TR_EEPROMOVERFLOW               "Minnesfel"
#define TR_RADIO_SETUP                  "INSTÄLLNINGAR"
#define TR_MENUDATEANDTIME              "DAG OCH TID"
#define TR_MENUTRAINER                  "TRAINER"
#define TR_MENUSPECIALFUNCS             "GLOBALA FUNKTIONER"
#define TR_MENUVERSION                  "VERSION"
#define TR_MENU_RADIO_SWITCHES          TR("BRYTARE","TEST AV BRYTARE")
#define TR_MENU_RADIO_ANALOGS           "ANALOGA VÄRDEN"
#define TR_MENU_RADIO_ANALOGS_CALIB     "CALIBRATED ANALOGS"
#define TR_MENU_RADIO_ANALOGS_RAWLOWFPS "RAW ANALOGS (5 Hz)"
#define TR_MENUCALIBRATION              "KALIBRERING"
#if defined(COLORLCD)
  #define TR_TRIMS2OFFSETS              "[Spara trimvärden]"
#else
  #define TR_TRIMS2OFFSETS              "\006[Spara trimvärden]"
#endif
#define TR_CHANNELS2FAILSAFE            "Channels=>Failsafe"
#define TR_CHANNEL2FAILSAFE             "Channel=>Failsafe"
#define TR_MENUMODELSEL                 TR("MODELL","VÄLJ MODELL")
#define TR_MENU_MODEL_SETUP             TR("MODELLINST.","MODELLINSTÄLLNINGAR")
#define TR_MENUFLIGHTMODE               "FLYGLÄGE"
#define TR_MENUFLIGHTMODES              "FLYGLÄGEN"
#define TR_MENUHELISETUP                "HELIKOPTER"

#define TR_MENUINPUTS                   "INPUT"
#define TR_MENULIMITS                   "SERVON"
#define TR_MENUCURVES                   "KURVOR"
#define TR_MENUCURVE                    "KURVA"
#define TR_MENULOGICALSWITCH            "LOGISK BRYTARE"
#define TR_MENULOGICALSWITCHES          "LOGISKA BRYTARE"
#define TR_MENUCUSTOMFUNC               "BRYTARFUNKTIONER"
#define TR_MENUCUSTOMSCRIPTS            "SPECIALKOD"
#define TR_MENUTELEMETRY                "TELEMETRI"
#define TR_MENUTEMPLATES                "MALLAR"
#define TR_MENUSTAT                     "STATISTIK"
#define TR_MENUDEBUG                    "DEBUG"
#define TR_MONITOR_CHANNELS1            "CHANNELS MONITOR 1-8"
#define TR_MONITOR_CHANNELS2            "CHANNELS MONITOR 9-16"
#define TR_MONITOR_SWITCHES             "LOGICAL SWITCHES MONITOR"
#define TR_MONITOR_CHANNELS3            "CHANNELS MONITOR 17-24"
#define TR_MONITOR_CHANNELS4            "CHANNELS MONITOR 25-32"
#define TR_MONITOR_OUTPUT_DESC          "Outputs"
#define TR_MONITOR_MIXER_DESC           "Mixers"
#define TR_RECEIVER_NUM                 TR("RxNum","Mottagare nr.")
#define TR_RECEIVER                     "Mottagare"
#define TR_SYNCMENU                     "Synk [MENU]"
#define TR_MULTI_RFTUNE                 TR("Freq tune", "Finjustera radiofrekvens")
#define TR_MULTI_RFPOWER                "RF styrka"
#define TR_MULTI_WBUS                   "Output"
#define TR_MULTI_TELEMETRY              "Telemetri"
#define TR_MULTI_VIDFREQ                TR("Vid.frek", "Videofrekvens")
#define TR_RF_POWER                     "RF styrka"
#define TR_MULTI_FIXEDID                TR("FixedID", "Fixed ID")
#define TR_MULTI_OPTION                 TR("Option", "Option value")
#define TR_MULTI_AUTOBIND               TR(INDENT "Bind Ch.",INDENT "Bind on channel")
#define TR_DISABLE_CH_MAP               TR("No Ch. map", "Disable Ch. map")
#define TR_DISABLE_TELEM                TR("No Telem", "Disable Telemetry")
#define TR_MULTI_DSM_AUTODTECT          TR(INDENT "Autodetect", INDENT "Autodetect format")
#define TR_MULTI_LOWPOWER               TR(INDENT "Låg effekt", INDENT "Lågeffektläge")
#define TR_MULTI_LNA_DISABLE            INDENT "LNA disable"
#define TR_MODULE_TELEMETRY             TR(INDENT "S.Port", INDENT "S.Port link")
#define TR_MODULE_TELEM_ON              TR("PÅ", "Aktiverad")
#define TR_DISABLE_INTERNAL             TR("Disable int. RF", "Disable internal RF")
#define TR_MODULE_NO_SERIAL_MODE        TR("!seriellt läge", "Ej i seriellt läge")
#define TR_MODULE_NO_INPUT              TR("Ingen input", "Ingen seriell input")
#define TR_MODULE_NO_TELEMETRY          TR3("No telemetry", "No MULTI_TELEMETRY", "No MULTI_TELEMETRY detected")
#define TR_MODULE_WAITFORBIND           "Bind to load protocol"
#define TR_MODULE_BINDING               "Binding"
#define TR_MODULE_UPGRADE_ALERT         TR3("Uppdat. nödv", "Modulen måste uppdateras", "Modulen\nbehöver uppdateras")
#define TR_MODULE_UPGRADE               TR("Uppdat. rekomm", "Moduluppdatering rekommenderas")
#define TR_REBIND                       "Rebinding required"
#define TR_REG_OK                       "Registrering ok"
#define TR_BIND_OK                      "Bind successful"
#define TR_BINDING_CH1_8_TELEM_ON       "Ch1-8 Telem PÅ"
#define TR_BINDING_CH1_8_TELEM_OFF      "Ch1-8 Telem AV"
#define TR_BINDING_CH9_16_TELEM_ON      "Ch9-16 Telem PÅ"
#define TR_BINDING_CH9_16_TELEM_OFF     "Ch9-16 Telem AV"
#define TR_PROTOCOL_INVALID             TR("Prot ogiltigt", "Ogiltigt protokoll")
#define TR_MODULE_STATUS                TR(INDENT "Status", INDENT "Modulstatus")
#define TR_MODULE_SYNC                  TR(INDENT "Sync", INDENT "Proto Sync Status")
#define TR_MULTI_SERVOFREQ              TR("Servo rate", "Servo update rate")
#define TR_MULTI_MAX_THROW              TR("Max. Throw", "Enable max. throw")
#define TR_MULTI_RFCHAN                 TR("RF Channel", "Select RF channel")
#define TR_LIMIT                        INDENT "Nivå"
#define TR_MINRSSI                      "Min RSSI"
#define TR_FLYSKY_TELEMETRY             TR("FlySky RSSI #", "Use FlySky RSSI value without rescalling")
#define TR_LATITUDE                     "Breddgrad"
#define TR_LONGITUDE                    "Längdgrad"
#define TR_GPS_COORDS_FORMAT            TR("GPS-Koordinater", "GPS-koordinatsystem")
#define TR_VARIO                        TR("Vario", "Variometer")
#define TR_PITCH_AT_ZERO                "Ton vid noll"
#define TR_PITCH_AT_MAX                 "Ton vid max"
#define TR_REPEAT_AT_ZERO               "Repetera vid noll"
#define TR_SHUTDOWN                     "STÄNGER AV"
#define TR_SAVE_MODEL                   "Spara modellinställn."
#define TR_BATT_CALIB                   "Kalib. Batteri"
#define TR_CURRENT_CALIB                "Kalib. Ström"
#define TR_VOLTAGE                      INDENT"Volt"
#define TR_CURRENT                      INDENT"Ampere"
#define TR_SELECT_MODEL                 "Välj Modell"
#define TR_MODEL_CATEGORIES             "Model Categories"
#define TR_MODELS                       "Models"
#define TR_SELECT_MODE                  "Select mode"
#define TR_CREATE_CATEGORY              "Skapa kategori"
#define TR_RENAME_CATEGORY              "Byt kat.namn"
#define TR_DELETE_CATEGORY              "Ta bort kategori"
#define TR_CREATE_MODEL                 "Skapa modell"
#define TR_DUPLICATE_MODEL              "Dupl. modell"
#define TR_COPY_MODEL                   "Kopiera modell"
#define TR_MOVE_MODEL                   "Flytta modell"
#define TR_BACKUP_MODEL                 "Modell-backup"
#define TR_DELETE_MODEL                 "Ta bort modell"
#define TR_RESTORE_MODEL                "Återställ modell"
#define TR_DELETE_ERROR                 "Delete error"
#define TR_CAT_NOT_EMPTY                "Category is not empty"
#define TR_SDCARD_ERROR                 "SD-kortfel"
#define TR_SDCARD                       "SD-kort"
#define TR_NO_FILES_ON_SD               "No files on SD!"
#define TR_NO_SDCARD                    "SD-kort saknas"
#define TR_WAITING_FOR_RX               "Waiting for RX..."
#define TR_WAITING_FOR_TX               "Waiting for TX.."
#define TR_WAITING_FOR_MODULE           TR("Awaiting module", "Waiting for module...")
#define TR_NO_TOOLS                     "No tools available"
#define TR_NORMAL                       "Normal"
#define TR_NOT_INVERTED                 "Not inv"
#define TR_NOT_CONNECTED                "!Connected"
#define TR_CONNECTED                    "Connected"
#define TR_FLEX_915                     "Flex 915MHz"
#define TR_FLEX_868                     "Flex 868MHz"
#define TR_16CH_WITHOUT_TELEMETRY       TR("16CH without telem.", "16CH without telemetry")
#define TR_16CH_WITH_TELEMETRY          TR("16CH with telem.", "16CH with telemetry")
#define TR_8CH_WITH_TELEMETRY           TR("8CH with telem.", "8CH with telemetry")
#define TR_EXT_ANTENNA                  "Ext. antenn"
#define TR_PIN                          "Pin"
#define TR_UPDATE_RX_OPTIONS            "Update RX options?"
#define TR_UPDATE_TX_OPTIONS            "Update TX options?"
#define TR_MODULES_RX_VERSION           "Modules / RX version"
#define TR_MENU_MODULES_RX_VERSION      "MODULES / RX VERSION"
#define TR_MENU_FIRM_OPTIONS            "FIRMWARE OPTIONS"
#define TR_GYRO                         "Gyro"
#define TR_STICKS_POTS_SLIDERS          "Sticks/Pots/Sliders"
#define TR_PWM_STICKS_POTS_SLIDERS      "PWM Sticks/Pots/Sliders"
#define TR_RF_PROTOCOL                  "RF Protocol"
#define TR_MODULE_OPTIONS               "Module options"
#define TR_POWER                        "Power"
#define TR_NO_TX_OPTIONS                "No Tx options"
#define TR_RTC_BATT                     "RTC Batt"
#define TR_POWER_METER_EXT              "Power Meter (EXT)"
#define TR_POWER_METER_INT              "Power Meter (INT)"
#define TR_SPECTRUM_ANALYSER_EXT        "Spektrum (EXT)"
#define TR_SPECTRUM_ANALYSER_INT        "Spektrum (INT)"
#define TR_SDCARD_FULL                  "SD-kort fullt"
#define TR_NEEDS_FILE                   "NEEDS FILE"
#define TR_EXT_MULTI_SPEC               "opentx-inv"
#define TR_INT_MULTI_SPEC               "stm-opentx-noinv"
#define TR_INCOMPATIBLE                 "Inkompatibel"
#define TR_WARNING                      "VARNING"
#define TR_EEPROMWARN                   "EEPROM"
#define TR_STORAGE_WARNING              "LAGRING"
#define TR_EEPROM_CONVERTING            "EEPROM Konvertering"
#define TR_SDCARD_CONVERSION_REQUIRE    "SD card conversion required"
#define TR_CONVERTING                   "Converting: "
#define TR_THROTTLE_UPPERCASE           "GAS"
#define TR_ALARMSWARN                   "ALARM"
#define TR_SWITCHWARN                   "BRYTARE"
#define TR_FAILSAFEWARN                 "FAILSAFE"
#define TR_TEST_WARNING                 TR("TESTING", "TEST BUILD")
#define TR_TEST_NOTSAFE                 "Use for tests only"
#define TR_SDCARDVERSIONWARN            "SD Card Check"
#define TR_WRONG_SDCARDVERSION          TR("Expected ver: ","Expected version: ")
#define TR_WARN_RTC_BATTERY_LOW         "RTC Battery low"
#define TR_WARN_MULTI_LOWPOWER          "Low power mode"
#define TR_BATTERY                      "BATTERY"
#define TR_WRONG_PCBREV                 "Wrong PCB detected"
#define TR_EMERGENCY_MODE               "EMERGENCY MODE"
#define TR_PCBREV_ERROR                 "PCB error"
#define TR_NO_FAILSAFE                  "Failsafe ej angiven"
#define TR_KEYSTUCK                     "Knapp-fel"
#define TR_INVERT_THR                   TR("Invert.gas?", "Invertera gasen?")
#define TR_VOLUME                       "Volym"
#define TR_LCD                          "LCD"
#define TR_BRIGHTNESS                   "Ljusstyrka"
#define TR_CPU_TEMP                     "CPU temp.\016>"
#define TR_CPU_CURRENT                  "Ström\022>"
#define TR_CPU_MAH                      "Förbrukn."
#define TR_COPROC                       "CoProc."
#define TR_COPROC_TEMP                  "MB temp. \016>"
#define TR_CAPAWARNING                  INDENT "Låg kapacitet"
#define TR_TEMPWARNING                  TR(INDENT "Hög temp ", INDENT "Hög temperatur")
#define TR_TTL_WARNING                  "Warning: use 3.3V logic levels"
#define TR_FUNC                         "Funktion"
#define TR_V1                           "V1"
#define TR_V2                           "V2"
#define TR_DURATION                     "Tidlängd"
#define TR_DELAY                        "Fördröj"
#define TR_SD_CARD                      "SD-kort"
#define TR_SDHC_CARD                    "SD/HC-kort"
#define TR_NO_SOUNDS_ON_SD              "Inga ljud i SD"
#define TR_NO_MODELS_ON_SD              "Ingen modell i SD"
#define TR_NO_BITMAPS_ON_SD             "Ikoner saknas på SD"
#define TR_NO_SCRIPTS_ON_SD             "Programkod saknas på SD"
#define TR_SCRIPT_SYNTAX_ERROR          TR("Syntaxfel", "Skriptsyntaxfel")
#define TR_SCRIPT_PANIC                 "Script panic"
#define TR_SCRIPT_KILLED                "Script killed"
#define TR_SCRIPT_ERROR                 "Okänt fel"
#define TR_PLAY_FILE                    "Spela"
#define TR_DELETE_FILE                  "Radera"
#define TR_COPY_FILE                    "Kopia"
#define TR_RENAME_FILE                  "Byt namn"
#define TR_ASSIGN_BITMAP                "Tilldela ikon"
#define TR_ASSIGN_SPLASH                "Startbild"
#define TR_EXECUTE_FILE                 "Utför"
#define TR_REMOVED                      " raderad"
#define TR_SD_INFO                      "Information"
#define TR_SD_FORMAT                    "Formatera"
#define TR_NA                           "ET."
#define TR_HARDWARE                     "Hårdvara"
#define TR_FORMATTING                   "Formaterar..."
#define TR_TEMP_CALIB                   "Temp. kalib."
#define TR_TIME                         "Tid"
#define TR_MAXBAUDRATE                  "Max bauds"
#define TR_SAMPLE_MODE                  "Sample Mode"
#define TR_SAMPLE_MODES                 "Normal","OneBit"

#define TR_BLUETOOTH                    "Blåtand"
#define TR_BLUETOOTH_DISC               "Upptäck"
#define TR_BLUETOOTH_INIT               "Init"
#define TR_BLUETOOTH_DIST_ADDR          "Dist addr"
#define TR_BLUETOOTH_LOCAL_ADDR         "Lokal addr"
#define TR_BLUETOOTH_PIN_CODE           "PIN-kod"
#define TR_BLUETOOTH_NODEVICES          "No Devices Found"
#define TR_BLUETOOTH_SCANNING           "Scanning..."
#define TR_BAUDRATE                     "BT baudrate"
#if defined(PCBX9E)
  #define TR_BLUETOOTH_MODES            "---","Enabled"
#else
  #define TR_BLUETOOTH_MODES            "---","Telemetri","Trainer"
#endif
#define TR_SD_INFO_TITLE                "SD INFO"
#define TR_SD_TYPE                      "Typ: "
#define TR_SD_SPEED                     "Hastighet:"
#define TR_SD_SECTORS                   "Sektorer:"
#define TR_SD_SIZE                      "Strl:"
#define TR_TYPE                         INDENT "Typ"
#define TR_GLOBAL_VARS                  "Globala variabler"
#define TR_GVARS                        "GLOBAL V."
#define TR_GLOBAL_VAR                   "Global variabel"
#define TR_MENU_GLOBAL_VARS             "GLOBALA VARIABLER"
#define TR_OWN                          "Egen"
#define TR_DATE                         "Datum"
#define TR_MONTHS                       { "Jan", "Feb", "Mar", "Apr", "Maj", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dec" }
#define TR_ROTARY_ENCODER               "R.Enks"
#define TR_CHANNELS_MONITOR             "Kanalöversikt"
#define TR_MIXERS_MONITOR               "MIXERSKÄRM"
#define TR_PATH_TOO_LONG                "För lång sökväg"
#define TR_VIEW_TEXT                    "Visa text"

#define TR_FLASH_BOOTLOADER             "Skriv bootloader"
#define TR_FLASH_DEVICE                 TR("Flash device","Flash device")
#define TR_FLASH_EXTERNAL_DEVICE        "Flash External Device"
#define TR_FLASH_RECEIVER_OTA           "Flash receiver OTA"
#define TR_FLASH_RECEIVER_BY_EXTERNAL_MODULE_OTA          "Flash RX by ext. OTA"
#define TR_FLASH_RECEIVER_BY_INTERNAL_MODULE_OTA          "Flash RX by int. OTA"
#define TR_FLASH_FLIGHT_CONTROLLER_BY_EXTERNAL_MODULE_OTA "Flash FC by ext. OTA"
#define TR_FLASH_FLIGHT_CONTROLLER_BY_INTERNAL_MODULE_OTA "Flash FC by int. OTA"
#define TR_FLASH_BLUETOOTH_MODULE       TR("Flash BT module", "Flash Bluetooth module")
#define TR_FLASH_POWER_MANAGEMENT_UNIT  "Flash pwr mngt unit"
#define TR_DEVICE_NO_RESPONSE           TR("Device not responding", "Device not responding")
#define TR_DEVICE_FILE_ERROR            TR("Device file prob.", "Device file prob.")
#define TR_DEVICE_DATA_REFUSED          TR("Device data refused", "Device data refused")
#define TR_DEVICE_WRONG_REQUEST         TR("Device access problem", "Device access problem")
#define TR_DEVICE_FILE_REJECTED         TR("Device file refused", "Device file refused")
#define TR_DEVICE_FILE_WRONG_SIG        TR("Device file sig.", "Device file sig.")
#define TR_CURRENT_VERSION              TR("Current vers. ", "Current version: ")
#define TR_FLASH_INTERNAL_MODULE        "Flash Internal Module"
#define TR_FLASH_INTERNAL_MULTI         TR("Flash Int. Multi", "Flash Internal Multi")
#define TR_FLASH_EXTERNAL_MODULE        "Flash external module"
#define TR_FLASH_EXTERNAL_MULTI         TR("Flash Ext. Multi", "Flash External Multi")
#define TR_FLASH_EXTERNAL_ELRS          TR("Flash Ext. ELRS", "Flash External ELRS")

#define TR_FIRMWARE_UPDATE_ERROR        TR("FW update Error","Firmware update error")
#define TR_FIRMWARE_UPDATE_SUCCESS      "Flash successful"
#define TR_WRITING                      "Skriver..."
#define TR_CONFIRM_FORMAT               "Formatera minnet?"
#define TR_INTERNALRF                   "Intern radio"
#define TR_INTERNAL_MODULE              TR("Int. modul","Intern modul")
#define TR_EXTERNAL_MODULE              TR("Ext. modul","Extern modul")
#define TR_OPENTX_UPGRADE_REQUIRED      "EdgeTX upgrade required"
#define TR_TELEMETRY_DISABLED           "Telem. disabled"
#define TR_MORE_OPTIONS_AVAILABLE       "More options available"
#define TR_NO_MODULE_INFORMATION        "No module information"
#define TR_EXTERNALRF                   "Extern radiomodul"
#define TR_FAILSAFE                     TR(INDENT "Failsafe", INDENT "Failsafeläge")
#define TR_FAILSAFESET                  "Failsafeinställning"
#define TR_REG_ID                       "Reg. ID"
#define TR_OWNER_ID                     "Owner ID"
#define TR_PINMAPSET                    "PINMAP"
#define TR_HOLD                         "Hold"
#define TR_HOLD_UPPERCASE               "HOLD"
#define TR_NONE                         "None"
#define TR_NONE_UPPERCASE               "NONE"
#define TR_MENUSENSOR                   "SENSOR"
#define TR_POWERMETER_PEAK              "Peak"
#define TR_POWERMETER_POWER             "Power"
#define TR_POWERMETER_ATTN              "Attn"
#define TR_POWERMETER_FREQ              "Freq."
#define TR_MENUTOOLS                    "TOOLS"
#define TR_TURN_OFF_RECEIVER            "Turn off receiver"
#define TR_STOPPING                     "Stopping..."
#define TR_MENU_SPECTRUM_ANALYSER       "SPECTRUM ANALYSER"
#define TR_MENU_POWER_METER             "POWER METER"
#define TR_SENSOR                       "SENSOR"
#define TR_COUNTRY_CODE                 "Landskod"
#define TR_USBMODE                      "USB-läge"
#define TR_JACK_MODE                    "Jack Mode"
#define TR_VOICE_LANGUAGE               "Röstspråk"
#define TR_UNITS_SYSTEM                 "Enheter"
#define TR_EDIT                         "Redigera"
#define TR_INSERT_BEFORE                "Addera före"
#define TR_INSERT_AFTER                 "Addera efter"
#define TR_COPY                         "Kopiera"
#define TR_MOVE                         "Flytta"
#define TR_PASTE                        "Infoga"
#define TR_PASTE_AFTER                  "Klistra in efter"
#define TR_PASTE_BEFORE                 "Klistra in före"
#define TR_DELETE                       "Radera"
#define TR_INSERT                       "Addera"
#define TR_RESET_FLIGHT                 "Nollställ flygning"
#define TR_RESET_TIMER1                 "Nollställ timer1"
#define TR_RESET_TIMER2                 "Nollställ timer2"
#define TR_RESET_TIMER3                 "Nollställ timer3"
#define TR_RESET_TELEMETRY              "Nollställ telemetri"
#define TR_STATISTICS                   "Statistik"
#define TR_ABOUT_US                     "Om Oss"
#define TR_USB_JOYSTICK                 "USB Joystick (HID)"
#define TR_USB_MASS_STORAGE             "USB Storage (SD)"
#define TR_USB_SERIAL                   "USB Serial (Debug)"
#define TR_SETUP_SCREENS                "Setup screens"
#define TR_MONITOR_SCREENS              "Monitors"
#define TR_AND_SWITCH                   "OCH Brytare"
#define TR_SF                           "BF"
#define TR_GF                           "GF"
#define TR_ANADIAGS_CALIB               "Calibrated analogs"
#define TR_ANADIAGS_FILTRAWDEV          "Filtered raw analogs with deviation"
#define TR_ANADIAGS_UNFILTRAW           "Unfiltered raw analogs"
#define TR_ANADIAGS_MINMAX              "Min., max. and range"
#define TR_ANADIAGS_MOVE                "Move analogs to their extremes!"
#define TR_SPEAKER                      INDENT"Högtalare"
#define TR_BUZZER                       INDENT"Summer"
#define TR_BYTES                        "byte"
#define TR_MODULE_BIND                  TR("[Bnd]", "[Bind]")
#define TR_POWERMETER_ATTN_NEEDED       "Attenuator needed"
#define TR_PXX2_SELECT_RX               "Select RX"
#define TR_PXX2_DEFAULT                 "<default>"
#define TR_BT_SELECT_DEVICE             "Select device"
#define TR_DISCOVER                     "Discover"
#define TR_BUTTON_INIT                  BUTTON("Init")
#define TR_WAITING                      "Waiting..."
#define TR_RECEIVER_DELETE              "Delete receiver?"
#define TR_RECEIVER_RESET               "Reset receiver?"
#define TR_SHARE                        "Share"
#define TR_BIND                         "Bind"
#define TR_REGISTER                     TR("Reg", "Register")
#define TR_MODULE_RANGE                 TR("[Tst]", "[Testa]")
#define TR_RECEIVER_OPTIONS             TR("REC. OPTIONS", "RECEIVER OPTIONS")
#define TR_DEL_BUTTON                   BUTTON(TR("Del", "Delete"))
#define TR_RESET_BTN                    "[Nollställ]"
#define TR_DEBUG                        "Debug"
#define TR_KEYS_BTN                     BUTTON(TR("SW","Switches"))
#define TR_ANALOGS_BTN                  BUTTON(TR("Analog","Analogs"))
#define TR_TOUCH_NOTFOUND               "Touch hardware not found"
#define TR_TOUCH_EXIT                   "Touch screen to exit"
#define TR_SET                          "[Spara]"
#define TR_TRAINER                      "Instruktör"
#define TR_CHANS                        "Kan"
#define TR_ANTENNAPROBLEM               CENTER "Fel på TX-antennen"
#define TR_MODELIDUSED                  TR("ID finns redan","Modell-ID används redan")
#define TR_MODULE                       "Modul"
#define TR_RX_NAME                      "RX Name"
#define TR_TELEMETRY_TYPE               "Telemetrityp"
#define TR_TELEMETRY_SENSORS            "Sensorer"
#define TR_VALUE                        "Värde"
#define TR_REPEAT                       "Upprepa"
#define TR_ENABLE                       "Aktivera"
#define TR_TOPLCDTIMER                  "Top LCD Timer"
#define TR_UNIT                         "Enhet"
#define TR_TELEMETRY_NEWSENSOR          INDENT "Lägg till sensor..."
#define TR_CHANNELRANGE                 INDENT "Kanalområde"
#define TR_RXFREQUENCY                  TR("RX Freqency", "RX Servo Frequency")
#define TR_AFHDS3_RX_FREQ               TR("RX freq.", "RX frequency")
#define TR_AFHDS3_ONE_TO_ONE_TELEMETRY  TR("Unicast/Tel.", "Unicast/Telemetry")
#define TR_AFHDS3_ONE_TO_MANY           "Multicast"
#define TR_AFHDS3_ACTUAL_POWER          TR("Act. pow", "Actual power")
#define TR_AFHDS3_POWER_SOURCE          TR("Power src.", "Power source")
#define TR_ANTENNACONFIRM1              "EXT. ANTENN"

#if defined(PCBX12S)
  #define TR_ANTENNA_MODES              "Intern","Fråga","Per modell","Intern + Extern"
#else
  #define TR_ANTENNA_MODES              "Intern","Fråga","Per modell","Extern"
#endif

#define TR_USE_INTERNAL_ANTENNA         TR("Anv int. antenn", "Använd intern antenn")
#define TR_USE_EXTERNAL_ANTENNA         TR("Anv ext. antenn", "Använd extern antenn")
#define TR_ANTENNACONFIRM2              TR("Kontr. antenn", "Kontrollera att antennen är installerad!")
#define TR_MODULE_PROTOCOL_FLEX_WARN_LINE1        "Requires non"
#define TR_MODULE_PROTOCOL_FCC_WARN_LINE1         "Requires FCC"
#define TR_MODULE_PROTOCOL_EU_WARN_LINE1          "Requires EU"
#define TR_MODULE_PROTOCOL_WARN_LINE2             "certified firmware"
#define TR_LOWALARM                     INDENT "Låg-alarm"
#define TR_CRITICALALARM                INDENT "Kritiskt alarm"
#define TR_RSSIALARM_WARN               TR("RSSI","TELEMETRI RSSI")
#define TR_NO_RSSIALARM                 TR(INDENT "Alarm avaktiverade", INDENT "Telemetrialarm inaktiverade")
#define TR_DISABLE_ALARM                TR(INDENT "Inaktivera alarm", INDENT "Inaktivera telemetrialarm")
#define TR_ENABLE_POPUP                 "Slå på dialog"
#define TR_DISABLE_POPUP                "Slå av dialog"
#define TR_POPUP                        "Popup"
#define TR_MIN                          "Min"
#define TR_MAX                          "Max"
#define TR_CURVE_PRESET                 "Lutning..."
#define TR_PRESET                       "Lutning"
#define TR_MIRROR                       "Spegla"
#define TR_CLEAR                        "Töm"
#define TR_RESET                        "Nollställ"
#define TR_RESET_SUBMENU                "Nollställ..."
#define TR_COUNT                        "Antal"
#define TR_PT                           "pt"
#define TR_PTS                          "pkt"
#define TR_SMOOTH                       "Mjuk"
#define TR_COPY_STICKS_TO_OFS           TR("Cpy stick->subtrim","Spara spakar som subtrim")
#define TR_COPY_MIN_MAX_TO_OUTPUTS      TR("Cpy min/max to all","Copy min/max/center to all outputs")
#define TR_COPY_TRIMS_TO_OFS            TR("Cpy trim->subtrim","Spara trimmar som subtrim")
#define TR_INCDEC                       "Inkr/Dekrement"
#define TR_GLOBALVAR                    "Globala var"
#define TR_MIXSOURCE                    "Mixerkälla"
#define TR_CONSTANT                     "Konstant"
#define TR_PERSISTENT_MAH               INDENT "Lagra mAh"
#define TR_PREFLIGHT                    "Startkontroller"
#define TR_CHECKLIST                    TR(INDENT "Checklista", INDENT "Visa checklista")
#define TR_FAS_OFFSET                   TR(INDENT "FAS Ofs", INDENT "FAS Offset")
#define TR_AUX_SERIAL_MODE              "Serieport"
#define TR_AUX2_SERIAL_MODE             "Serieport 2"
#define TR_AUX_SERIAL_PORT_POWER        "Port power"
#define TR_SCRIPT                       "Programkod"
#define TR_INPUTS                       "Input"
#define TR_OUTPUTS                      "Outputs"
#define STR_EEBACKUP                    "Säkerhetskopiera EEPROM"
#define STR_FACTORYRESET                "Fabriksåterställning"
#define TR_CONFIRMRESET                 "Radera ALLA modeller och inställningar?"
#define TR_TOO_MANY_LUA_SCRIPTS         "För många Lua-skript!"
#define TR_SPORT_UPDATE_POWER_MODE      "SP Power"
#define TR_SPORT_UPDATE_POWER_MODES     "AUTO","ON"
#define TR_NO_TELEMETRY_SCREENS         "Ingen telemetriskärm"
#define TR_TOUCH_PANEL                  "Pekskärm:"
#define TR_FILE_SIZE                    "File size"
#define TR_FILE_OPEN                    "Open anyway?"

// Horus and Taranis column headers
#define TR_PHASES_HEADERS_NAME          "Namn"
#define TR_PHASES_HEADERS_SW            "Brytare"
#define TR_PHASES_HEADERS_RUD_TRIM      "Rodertrim"
#define TR_PHASES_HEADERS_ELE_TRIM      "Höjdrodertrim"
#define TR_PHASES_HEADERS_THT_TRIM      "Gastrim"
#define TR_PHASES_HEADERS_AIL_TRIM      "Skevrodertrim"
#define TR_PHASES_HEADERS_CH5_TRIM      "Trim 5"
#define TR_PHASES_HEADERS_CH6_TRIM      "Trim 6"
#define TR_PHASES_HEADERS_FAD_IN        "Tona upp"
#define TR_PHASES_HEADERS_FAD_OUT       "Tona ned"

#define TR_LIMITS_HEADERS_NAME          "Namn"
#define TR_LIMITS_HEADERS_SUBTRIM       "Subtrim"
#define TR_LIMITS_HEADERS_MIN           "Min"
#define TR_LIMITS_HEADERS_MAX           "Max"
#define TR_LIMITS_HEADERS_DIRECTION     "Riktning"
#define TR_LIMITS_HEADERS_CURVE         "Kurva"
#define TR_LIMITS_HEADERS_PPMCENTER     "PPM-center"
#define TR_LIMITS_HEADERS_SUBTRIMMODE   "Subtrim-läge"
#define TR_INVERTED                     "Inverterad"

#define TR_LSW_HEADERS_FUNCTION         "Funktion"
#define TR_LSW_HEADERS_V1               "V1"
#define TR_LSW_HEADERS_V2               "V2"
#define TR_LSW_HEADERS_ANDSW            "OCH-brytare"
#define TR_LSW_HEADERS_DURATION         "Tidslängd"
#define TR_LSW_HEADERS_DELAY            "Fördröj"

#define TR_GVAR_HEADERS_NAME            "Namn"
#define TR_GVAR_HEADERS_FM0             "Value on FM0"
#define TR_GVAR_HEADERS_FM1             "Value on FM1"
#define TR_GVAR_HEADERS_FM2             "Value on FM2"
#define TR_GVAR_HEADERS_FM3             "Value on FM3"
#define TR_GVAR_HEADERS_FM4             "Value on FM4"
#define TR_GVAR_HEADERS_FM5             "Value on FM5"
#define TR_GVAR_HEADERS_FM6             "Value on FM6"
#define TR_GVAR_HEADERS_FM7             "Value on FM7"
#define TR_GVAR_HEADERS_FM8             "Value on FM8"

// Horus footer descriptions
#define TR_LSW_DESCRIPTIONS             { "Comparison type or function", "First variable", "Second variable or constant", "Second variable or constant", "Additional condition for line to be enabled", "Minimum ON duration of the logical switch", "Minimum TRUE duration for the switch to become ON" }

// Horus layouts and widgets
#define TR_FIRST_CHANNEL                "First channel"
#define TR_FILL_BACKGROUND              "Fill background?"
#define TR_BG_COLOR                     "BG Color"
#define TR_SLIDERS_TRIMS                "Sliders+Trims"
#define TR_SLIDERS                      "Sliders"
#define TR_FLIGHT_MODE                  "Flight mode"
#define TR_INVALID_FILE                 "Invalid File"
#define TR_TIMER_SOURCE                 "Timer source"
#define TR_SIZE                         "Size"
#define TR_SHADOW                       "Shadow"
#define TR_TEXT                         "Text"
#define TR_COLOR                        "Color"
#define TR_MAIN_VIEW_X                  "Main view X"
#define TR_PANEL1_BACKGROUND            "Panel1 background"
#define TR_PANEL2_BACKGROUND            "Panel2 background"

// About screen
#define TR_ABOUTUS                      "Om oss"

#define TR_CHR_SHORT                    's'
#define TR_CHR_LONG                     'l'
#define TR_CHR_TOGGLE                   't'
#define TR_CHR_HOUR                     'h'
#define TR_CHR_INPUT                    'I'   // Values between A-I will work

#define TR_BEEP_VOLUME                  "Volym Pip"
#define TR_WAV_VOLUME                   "Volym Wav"
#define TR_BG_VOLUME                    "Volym Bg"

#define TR_TOP_BAR                      "Titelrad"
#define TR_FLASH_ERASE                  "Flash erase..."
#define TR_FLASH_WRITE                  "Flash write..."
#define TR_OTA_UPDATE                   "OTA update..."
#define TR_MODULE_RESET                 "Module reset..."
#define TR_UNKNOWN_RX                   "Okänd RX"
#define TR_UNSUPPORTED_RX               "RX stöds ej"
#define TR_OTA_UPDATE_ERROR             "OTA update error"
#define TR_DEVICE_RESET                 "Device reset..."
#define TR_ALTITUDE                     INDENT "Höjd"
#define TR_SCALE                        "Skala"
#define TR_VIEW_CHANNELS                "Visa kanaler"
#define TR_VIEW_NOTES                   "Visa anteckningar"
#define TR_MODEL_SELECT                 "Välj modell"
#define TR_MODS_FORBIDDEN               "Modifikationer förbjudna!"
#define TR_UNLOCKED                     "Olåst"
#define TR_ID                           "ID"
#define TR_PRECISION                    "Precision"
#define TR_RATIO                        "Ratio"
#define TR_FORMULA                      "Formel"
#define TR_CELLINDEX                    "Cell index"
#define TR_LOGS                         "Loggar"
#define TR_OPTIONS                      "Options"
#define TR_FIRMWARE_OPTIONS             "Firmware options"

#define TR_ALTSENSOR                    "Höjdsensor"
#define TR_CELLSENSOR                   "Cellsensor"
#define TR_GPSSENSOR                    "GPS-sensor"
#define TR_CURRENTSENSOR                "Sensor"
#define TR_AUTOOFFSET                   "Auto Offset"
#define TR_ONLYPOSITIVE                 "Positiv"
#define TR_FILTER                       "Filter"
#define TR_TELEMETRYFULL                "Alla telemetriplatser upptagna!"
#define TR_SERVOS_OK                    "Servon OK"
#define TR_SERVOS_KO                    "Servon KO"

#define TR_INVERTED_SERIAL              INDENT "Invert"
#define TR_IGNORE_INSTANCE              TR(INDENT "Inst.fel", INDENT "Hantera instansfel")
#define TR_DISCOVER_SENSORS             "Sök nya sensorer"
#define TR_STOP_DISCOVER_SENSORS        "Avbryt sökning"
#define TR_DELETE_ALL_SENSORS           "Ta bort alla sensorer"
#define TR_CONFIRMDELETE                "Ta bort alla?"
#define TR_SELECT_WIDGET                "Välj widget"
#define TR_REMOVE_WIDGET                "Ta bort widget"
#define TR_WIDGET_SETTINGS              "Widgetinställningar"
#define TR_REMOVE_SCREEN                "Ta bort skärm"
#define TR_SETUP_WIDGETS                "Konfigurera widgets"
#define TR_USER_INTERFACE               "Användargränssnitt"
#define TR_THEME                        "Tema"
#define TR_SETUP                        "Konfigurera"
#define TR_LAYOUT                       "Layout"
#define TR_ADD_MAIN_VIEW                "Lägg till huvudvy"
#define TR_BACKGROUND_COLOR             "Bakgrundsfärg"
#define TR_MAIN_COLOR                   "Huvudfärg"
#define TR_BAR2_COLOR                   "Sekundär stapelfärg"
#define TR_BAR1_COLOR                   "Primär stapelfärg"
#define TR_TEXT_COLOR                   "Textfärg"
#define TR_TEXT_VIEWER                  "Textgranskare"

#define TR_MENU_INPUTS                  STR_CHAR_INPUT "Indata"
#define TR_MENU_LUA                     STR_CHAR_LUA "Lua-skript"
#define TR_MENU_STICKS                  STR_CHAR_STICK "Spakar"
#define TR_MENU_POTS                    STR_CHAR_POT "Vred"
#define TR_MENU_MAX                     STR_CHAR_FUNCTION "MAX"
#define TR_MENU_HELI                    STR_CHAR_CYC "Cyklisk"
#define TR_MENU_TRIMS                   STR_CHAR_TRIM "Trimm"
#define TR_MENU_SWITCHES                STR_CHAR_SWITCH "Brytare"
#define TR_MENU_LOGICAL_SWITCHES        STR_CHAR_SWITCH "Logiska brytare"
#define TR_MENU_TRAINER                 STR_CHAR_TRAINER "Instruktör"
#define TR_MENU_CHANNELS                STR_CHAR_CHANNEL "Servon"
#define TR_MENU_GVARS                   STR_CHAR_SLIDER "GVars"
#define TR_MENU_TELEMETRY               STR_CHAR_TELEMETRY "Telemetri"
#define TR_MENU_DISPLAY                 "DISPLAY"
#define TR_MENU_OTHER                   "Övrigt"
#define TR_MENU_INVERT                  "Invertera"
#define TR_JITTER_FILTER                "ADC Filter"
#define TR_RTC_CHECK                    TR("Kolla RTC", "Kolla RTC-batteriet")
#define TR_AUTH_FAILURE                 "Auth-failure"
#define TR_RACING_MODE                  "Tävlingsläge"

#define STR_VFR                         "VFR"
#define STR_RSSI                        "RSSI"
#define STR_R9PW                        "R9PW"
#define STR_RAS                         "SWR"
#define STR_A1                          "A1"
#define STR_A2                          "A2"
#define STR_A3                          "A3"
#define STR_A4                          "A4"
#define STR_BATT                        "RxBt"
#define STR_ALT                         "Alt"
#define STR_TEMP1                       "Tmp1"
#define STR_TEMP2                       "Tmp2"
#define STR_TEMP3                       "Tmp3"
#define STR_TEMP4                       "Tmp4"
#define STR_RPM2                        "RPM2"
#define STR_PRES                        "Pres"
#define STR_ODO1                        "Odo1"
#define STR_ODO2                        "Odo2"
#define STR_TXV                         "TX_V"
#define STR_CURR_SERVO1                 "CSv1"
#define STR_CURR_SERVO2                 "CSv2"
#define STR_CURR_SERVO3                 "CSv3"
#define STR_CURR_SERVO4                 "CSv4"
#define STR_DIST                        "Dist"
#define STR_ARM                         "Arm"
#define STR_C50                         "C50"
#define STR_C200                        "C200"
#define STR_RPM                         "RPM"
#define STR_FUEL                        "Fuel"
#define STR_VSPD                        "VSpd"
#define STR_ACCX                        "AccX"
#define STR_ACCY                        "AccY"
#define STR_ACCZ                        "AccZ"
#define STR_GYROX                       "GYRX"
#define STR_GYROY                       "GYRY"
#define STR_GYROZ                       "GYRZ"
#define STR_CURR                        "Curr"
#define STR_CAPACITY                    "Capa"
#define STR_VFAS                        "VFAS"
#define STR_BATT_PERCENT                "Bat%"
#define STR_ASPD                        "ASpd"
#define STR_GSPD                        "GSpd"
#define STR_HDG                         "Hdg"
#define STR_SATELLITES                  "Sats"
#define STR_CELLS                       "Cels"
#define STR_GPSALT                      "GAlt"
#define STR_GPSDATETIME                 "Date"
#define STR_BATT1_VOLTAGE               "RB1V"
#define STR_BATT2_VOLTAGE               "RB2V"
#define STR_BATT1_CURRENT               "RB1A"
#define STR_BATT2_CURRENT               "RB2A"
#define STR_BATT1_CONSUMPTION           "RB1C"
#define STR_BATT2_CONSUMPTION           "RB2C"
#define STR_BATT1_TEMP                  "RB1T"
#define STR_BATT2_TEMP                  "RB2T"
#define STR_RB_STATE                    "RBS"
#define STR_CHANS_STATE                 "RBCS"
#define STR_RX_RSSI1                    "1RSS"
#define STR_RX_RSSI2                    "2RSS"
#define STR_RX_QUALITY                  "RQly"
#define STR_RX_SNR                      "RSNR"
#define STR_RX_NOISE                    "RNse"
#define STR_RF_MODE                     "RFMD"
#define STR_TX_POWER                    "TPWR"
#define STR_TX_RSSI                     "TRSS"
#define STR_TX_QUALITY                  "TQly"
#define STR_TX_SNR                      "TSNR"
#define STR_TX_NOISE                    "TNse"
#define STR_PITCH                       "Ptch"
#define STR_ROLL                        "Roll"
#define STR_YAW                         "Yaw"
#define STR_THROTTLE                    "Thr"
#define STR_QOS_A                       "FdeA"
#define STR_QOS_B                       "FdeB"
#define STR_QOS_L                       "FdeL"
#define STR_QOS_R                       "FdeR"
#define STR_QOS_F                       "FLss"
#define STR_QOS_H                       "Hold"
#define STR_LAP_NUMBER                  "Lap "
#define STR_GATE_NUMBER                 "Gate"
#define STR_LAP_TIME                    "LapT"
#define STR_GATE_TIME                   "GteT"
#define STR_ESC_VOLTAGE                 "EscV"
#define STR_ESC_CURRENT                 "EscA"
#define STR_ESC_RPM                     "Erpm"
#define STR_ESC_CONSUMPTION             "EscC"
#define STR_ESC_TEMP                    "EscT"
#define STR_SD1_CHANNEL                 "Chan"
#define STR_GASSUIT_TEMP1               "GTp1"
#define STR_GASSUIT_TEMP2               "GTp2"
#define STR_GASSUIT_RPM                 "GRPM"
#define STR_GASSUIT_FLOW                "GFlo"
#define STR_GASSUIT_CONS                "GFue"
#define STR_GASSUIT_RES_VOL             "GRVl"
#define STR_GASSUIT_RES_PERC            "GRPc"
#define STR_GASSUIT_MAX_FLOW            "GMFl"
#define STR_GASSUIT_AVG_FLOW            "GAFl"
#define STR_SBEC_VOLTAGE                "BecV"
#define STR_SBEC_CURRENT                "BecA"
#define STR_RB3040_EXTRA_STATE          "RBES"
#define STR_RB3040_CHANNEL1             "CH1A"
#define STR_RB3040_CHANNEL2             "CH2A"
#define STR_RB3040_CHANNEL3             "CH3A"
#define STR_RB3040_CHANNEL4             "CH4A"
#define STR_RB3040_CHANNEL5             "CH5A"
#define STR_RB3040_CHANNEL6             "CH6A"
#define STR_RB3040_CHANNEL7             "CH7A"
#define STR_RB3040_CHANNEL8             "CH8A"
#define STR_ESC_VIN                     "EVIN"
#define STR_ESC_TFET                    "TFET"
#define STR_ESC_CUR                     "ECUR"
#define STR_ESC_TBEC                    "TBEC"
#define STR_ESC_BCUR                    "CBEC"
#define STR_ESC_VBEC                    "VBEC"
#define STR_ESC_THR                     "ETHR"
#define STR_ESC_POUT                    "EOUT"
#define STR_SMART_BAT_BTMP              "BTmp"
#define STR_SMART_BAT_BCUR              "BCur"
#define STR_SMART_BAT_BCAP              "BUse"
#define STR_SMART_BAT_MIN_CEL           "CLMi"
#define STR_SMART_BAT_MAX_CEL           "CLMa"
#define STR_SMART_BAT_CYCLES            "Cycl"
#define STR_SMART_BAT_CAPACITY          "BCpT"
#define STR_CL01                        "Cel1"
#define STR_CL02                        "Cel2"
#define STR_CL03                        "Cel3"
#define STR_CL04                        "Cel4"
#define STR_CL05                        "Cel5"
#define STR_CL06                        "Cel6"
#define STR_CL07                        "Cel7"
#define STR_CL08                        "Cel8"
#define STR_CL09                        "Cel9"
#define STR_CL10                        "Cl10"
#define STR_CL11                        "Cl11"
#define STR_CL12                        "Cl12"
#define STR_CL13                        "Cl13"
#define STR_CL14                        "Cl14"
#define STR_CL15                        "Cl15"
#define STR_CL16                        "Cl16"
#define STR_CL17                        "Cl17"
#define STR_CL18                        "Cl18"
#define STR_FRAME_RATE                  "FRat"
#define STR_TOTAL_LATENCY               "TLat"
#define STR_VTX_FREQ                    "VFrq"
#define STR_VTX_PWR                     "VPwr"
#define STR_VTX_CHAN                    "VChn"
#define STR_VTX_BAND                    "VBan"
#define STR_SERVO_CURRENT               "SrvA"
#define STR_SERVO_VOLTAGE               "SrvV"
#define STR_SERVO_TEMPERATURE           "SrvT"
#define STR_SERVO_STATUS                "SrvS"
#define STR_LOSS                        "Loss"
#define STR_SPEED                       "Spd "
#define STR_FLOW                        "Flow"

#define TR_ADD_ALL_TRIMS_TO_SUBTRIMS    "Addera alla trimmar till subtrimmar"

#define TR_USE_THEME_COLOR              "Använd temafärg"
#define TR_DUPLICATE                    "Duplicera"
#define TR_ACTIVATE                     "Aktivera"
#define TR_RED                          "Röd"
#define TR_BLUE                         "Blå"
#define TR_GREEN                        "Grön"
#define TR_COLOR_PICKER                 "Färgväljare"
#define TR_EDIT_THEME_DETAILS           "Ändra temadetaljer"
#define TR_AUTHOR                       "Författare"
#define TR_DESCRIPTION                  "Beskrivning"
#define TR_SAVE                         "Spara"
#define TR_CANCEL                       "Avbryt"
#define TR_EDIT_THEME                   "ÄNDRA TEMA"
#define TR_DETAILS                      "Detaljer"
#define TR_THEME_EDITOR                 "TEMAN"

// Main menu
#define TR_MAIN_MENU_SELECT_MODEL       "Välj\nmodell"
#define TR_MAIN_MENU_MODEL_NOTES        "Modell-\nanteckningar"
#define TR_MAIN_MENU_CHANNEL_MONITOR    "Channel\nMonitor"
#define TR_MAIN_MENU_MODEL_SETTINGS     "Modell-\ninställningar"
#define TR_MAIN_MENU_RADIO_SETTINGS     "Radio-\ninställningar"
#define TR_MAIN_MENU_SCREEN_SETTINGS    "Skärm-\ninställningar"
#define TR_MAIN_MENU_RESET_TELEMETRY    "Återställ\ntelemetri"
#define TR_MAIN_MENU_STATISTICS         "Statistik"
#define TR_MAIN_MENU_ABOUT_EDGETX       "Om\nEdgeTX"
// End Main menu
