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

#include "model_logical_switches.h"
#include "opentx.h"
#include "libopenui.h"
#include "switches.h"

#define SET_DIRTY()     storageDirty(EE_MODEL)

void putsEdgeDelayParam(BitmapBuffer * dc, coord_t x, coord_t y, LogicalSwitchData * ls, LcdFlags flags = 0)
{
  coord_t lcdNextPos = 0;
  lcdNextPos = dc->drawText(x, y, "[", flags);
  lcdNextPos = dc->drawNumber(lcdNextPos+2, y, lswTimerValue(ls->v2), LEFT | PREC1 | flags);
  lcdNextPos = dc->drawText(lcdNextPos, y, ":", flags);
  if (ls->v3 < 0)
    lcdNextPos = dc->drawText(lcdNextPos+3, y, "<<", flags);
  else if (ls->v3 == 0)
    lcdNextPos = dc->drawText(lcdNextPos+3, y, "--", flags);
  else
    lcdNextPos = dc->drawNumber(lcdNextPos+3, y, lswTimerValue(ls->v2+ls->v3), LEFT | PREC1 | flags);
  dc->drawText(lcdNextPos, y, "]", flags);
}

class LogicalSwitchEditPage: public Page
{
  public:
    explicit LogicalSwitchEditPage(uint8_t index):
      Page(ICON_MODEL_LOGICAL_SWITCHES),
      index(index)
    {
      buildHeader(&header);
      buildBody(&body);
    }

  protected:
    uint8_t index;
    bool active = false;
    FormGroup * logicalSwitchOneWindow = nullptr;
    StaticText * headerSwitchName = nullptr;
    NumberEdit * v2Edit = nullptr;

    bool isActive() const
    {
      return getSwitch(SWSRC_FIRST_LOGICAL_SWITCH + index);
    }

    void checkEvents() override
    {
      Page::checkEvents();
      if (active != isActive()) {
        invalidate();
        headerSwitchName->setTextFlags(isActive() ? FONT(BOLD) | COLOR_THEME_ACTIVE : COLOR_THEME_PRIMARY2);
        active = !active;
      }
    }

    void buildHeader(Window * window)
    {
      new StaticText(window,
                     {PAGE_TITLE_LEFT, PAGE_TITLE_TOP, LCD_W - PAGE_TITLE_LEFT,
                      PAGE_LINE_HEIGHT},
                     STR_MENULOGICALSWITCHES, 0, COLOR_THEME_PRIMARY2);
      headerSwitchName = new StaticText(
          window,
          {PAGE_TITLE_LEFT, PAGE_TITLE_TOP + PAGE_LINE_HEIGHT,
           LCD_W - PAGE_TITLE_LEFT, PAGE_LINE_HEIGHT},
          getSwitchPositionName(SWSRC_SW1 + index), 0, COLOR_THEME_PRIMARY2);
    }

    void updateLogicalSwitchOneWindow()
    {
      FormGridLayout grid;
      logicalSwitchOneWindow->clear();

      LogicalSwitchData * cs = lswAddress(index);
      uint8_t cstate = lswFamily(cs->func);

      if (cstate == LS_FAMILY_BOOL || cstate == LS_FAMILY_STICKY || cs->func == LS_FUNC_SAFE) {
        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V1, 0, COLOR_THEME_PRIMARY1);
        auto choice = new SwitchChoice(logicalSwitchOneWindow, grid.getFieldSlot(), SWSRC_FIRST_IN_LOGICAL_SWITCHES, SWSRC_LAST_IN_LOGICAL_SWITCHES, GET_SET_DEFAULT(cs->v1));
        choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
        grid.nextLine();

        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V2, 0, COLOR_THEME_PRIMARY1);
        choice = new SwitchChoice(logicalSwitchOneWindow, grid.getFieldSlot(), SWSRC_FIRST_IN_LOGICAL_SWITCHES, SWSRC_LAST_IN_LOGICAL_SWITCHES, GET_SET_DEFAULT(cs->v2));
        choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
        grid.nextLine();
      }
      else if (cstate == LS_FAMILY_EDGE) {
        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V1, 0, COLOR_THEME_PRIMARY1);
        auto choice = new SwitchChoice(logicalSwitchOneWindow, grid.getFieldSlot(), SWSRC_FIRST_IN_LOGICAL_SWITCHES, SWSRC_LAST_IN_LOGICAL_SWITCHES, GET_SET_DEFAULT(cs->v1));
        choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
        grid.nextLine();

        auto edit1 = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(2, 0), -129, 122, GET_DEFAULT(cs->v2));
        auto edit2 = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(2, 1), -1, 222 - cs->v2, GET_SET_DEFAULT(cs->v3));
        edit1->setSetValueHandler([=](int32_t newValue) {
          cs->v2 = newValue;
          cs->v3 = min<uint8_t>(cs->v3, 222 - cs->v2);
          SET_DIRTY();
          edit2->setMax(222 - cs->v2);
          edit2->invalidate();
        });
        edit1->setDisplayHandler([](int32_t value) {
          return formatNumberAsString(lswTimerValue(value), PREC1);
        });
        edit2->setDisplayHandler([cs](int32_t value) {
          if (value < 0)
            return std::string("<<");
          else if (value == 0)
            return std::string("--");
          else {
            return formatNumberAsString(lswTimerValue(cs->v2 + value), PREC1);
          }
        });
        grid.nextLine();
      }
      else if (cstate == LS_FAMILY_COMP) {
        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V1, 0, COLOR_THEME_PRIMARY1);
        new SourceChoice(logicalSwitchOneWindow, grid.getFieldSlot(), 0, MIXSRC_LAST_TELEM, GET_SET_DEFAULT(cs->v1));
        grid.nextLine();

        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V2, 0, COLOR_THEME_PRIMARY1);
        new SourceChoice(logicalSwitchOneWindow, grid.getFieldSlot(), 0, MIXSRC_LAST_TELEM, GET_SET_DEFAULT(cs->v2));
        grid.nextLine();
      }
      else if (cstate == LS_FAMILY_TIMER) {
        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V1, 0, COLOR_THEME_PRIMARY1);
        auto timer = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(), -128, 122, GET_SET_DEFAULT(cs->v1));
        timer->setDisplayHandler([](int32_t value) {
          return formatNumberAsString(lswTimerValue(value), PREC1);
        });
        grid.nextLine();

        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V2, 0, COLOR_THEME_PRIMARY1);
        timer = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(), -128, 122, GET_SET_DEFAULT(cs->v2));
        timer->setDisplayHandler([](int32_t value) {
          return std::to_string(lswTimerValue(value));
        });
        grid.nextLine();
      }
      else {
        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V1, 0, COLOR_THEME_PRIMARY1);
        new SourceChoice(logicalSwitchOneWindow, grid.getFieldSlot(), 0, MIXSRC_LAST_TELEM, GET_DEFAULT(cs->v1),
                         [=](int32_t newValue) {
                           cs->v1 = newValue;
                           if (v2Edit != nullptr)
                           {
                             int16_t v2_min = 0, v2_max = 0;
                             getMixSrcRange(cs->v1, v2_min, v2_max);
                             v2Edit->setMin(v2_min);
                             v2Edit->setMax(v2_max);
                             v2Edit->setValue(cs->v2);
                           }
                           SET_DIRTY();
                         });
        grid.nextLine();

        new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_V2, 0, COLOR_THEME_PRIMARY1);
        int16_t v2_min = 0, v2_max = 0;
        getMixSrcRange(cs->v1, v2_min, v2_max);
        v2Edit = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(),
                                v2_min, v2_max, GET_SET_DEFAULT(cs->v2));

        v2Edit->setDisplayHandler([=](int value) -> std::string {
          if (cs->v1 <= MIXSRC_LAST_CH) value = calc100toRESX(value);
          std::string txt = getSourceCustomValueString(cs->v1, value, 0);
          return txt;
        });
        grid.nextLine();
      }

      // AND switch
      if(cs->func != LS_FUNC_SAFE){
      new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_AND_SWITCH, 0, COLOR_THEME_PRIMARY1);
      auto choice = new SwitchChoice(logicalSwitchOneWindow, grid.getFieldSlot(), -MAX_LS_ANDSW, MAX_LS_ANDSW, GET_SET_DEFAULT(cs->andsw));
      choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
      grid.nextLine();
      }

      // Duration
      new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_DURATION, 0, COLOR_THEME_PRIMARY1);
      auto edit = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(), 0, MAX_LS_DURATION, GET_SET_DEFAULT(cs->duration), 0, PREC1);
      edit->setZeroText("---");
      grid.nextLine();

      // Delay
      new StaticText(logicalSwitchOneWindow, grid.getLabelSlot(), STR_DELAY, 0, COLOR_THEME_PRIMARY1);
      if (cstate == LS_FAMILY_EDGE) {
        new StaticText(logicalSwitchOneWindow, grid.getFieldSlot(), STR_NA, 0, COLOR_THEME_PRIMARY1);
      }
      else {
        auto edit = new NumberEdit(logicalSwitchOneWindow, grid.getFieldSlot(), 0, MAX_LS_DELAY, GET_SET_DEFAULT(cs->delay), 0, PREC1);
        edit->setZeroText("---");
      }
      grid.nextLine();
    }

    void buildBody(FormWindow * window)
    {
      FormGridLayout grid;
      grid.spacer(PAGE_PADDING);

      LogicalSwitchData * cs = lswAddress(index);

      // LS Func
      new StaticText(window, grid.getLabelSlot(), STR_FUNC, 0, COLOR_THEME_PRIMARY1);
      auto functionChoice = new Choice(window, grid.getFieldSlot(), STR_VCSWFUNC, 0, LS_FUNC_MAX, GET_DEFAULT(cs->func));
      functionChoice->setSetValueHandler([=](int32_t newValue) {
          cs->func = newValue;
          if (lswFamily(cs->func) == LS_FAMILY_TIMER) {
            cs->v1 = cs->v2 = 0;
          }
          else if (lswFamily(cs->func) == LS_FAMILY_EDGE) {
            cs->v1 = 0;
            cs->v2 = -129;
            cs->v3 = 0;
          }
          else {
            cs->v1 = cs->v2 = 0;
          }
          SET_DIRTY();
          updateLogicalSwitchOneWindow();
      });
      functionChoice->setAvailableHandler(isLogicalSwitchFunctionAvailable);
      grid.nextLine();

      logicalSwitchOneWindow = new FormGroup(window, { 0, grid.getWindowHeight(), LCD_W, 0 }// , FORM_FORWARD_FOCUS
                                             );
      updateLogicalSwitchOneWindow();
      grid.addWindow(logicalSwitchOneWindow);
    }
};

static constexpr coord_t line1 = FIELD_PADDING_TOP;
static constexpr coord_t line2 = line1 + PAGE_LINE_HEIGHT;
static constexpr coord_t col1 = 20;
static constexpr coord_t col2 = (LCD_W - 100) / 3 + col1;
static constexpr coord_t col3 = ((LCD_W - 100) / 3) * 2 + col1;

class LogicalSwitchButton : public Button
{
 public:
  LogicalSwitchButton(FormGroup* parent, const rect_t& rect, int lsIndex) :
      Button(parent, rect, nullptr, 0, COLOR_THEME_PRIMARY1), lsIndex(lsIndex), active(isActive())
  {
    LogicalSwitchData* ls = lswAddress(lsIndex);
    if (ls->andsw != SWSRC_NONE || ls->duration != 0 || ls->delay != 0)
      setHeight(height() + 20);
  }

  bool isActive() const
  {
    return getSwitch(SWSRC_FIRST_LOGICAL_SWITCH + lsIndex);
  }

  void checkEvents() override
  {
    if (active != isActive()) {
      invalidate();
      active = !active;
    }

    Button::checkEvents();
  }

  void paintLogicalSwitchLine(BitmapBuffer* dc)
  {
    LogicalSwitchData* ls = lswAddress(lsIndex);
    uint8_t lsFamily = lswFamily(ls->func);

    // CSW func
    dc->drawTextAtIndex(col1, line1, STR_VCSWFUNC, ls->func, COLOR_THEME_SECONDARY1);

    // CSW params
    if (lsFamily == LS_FAMILY_BOOL || lsFamily == LS_FAMILY_STICKY || ls->func ==LS_FUNC_SAFE) {
      drawSwitch(dc, col2, line1, ls->v1, COLOR_THEME_SECONDARY1);
      drawSwitch(dc, col3, line1, ls->v2, COLOR_THEME_SECONDARY1);
    } else if (lsFamily == LS_FAMILY_EDGE) {
      drawSwitch(dc, col2, line1, ls->v1, COLOR_THEME_SECONDARY1);
      putsEdgeDelayParam(dc, col3, line1, ls, COLOR_THEME_SECONDARY1);
    } else if (lsFamily == LS_FAMILY_COMP) {
      drawSource(dc, col2, line1, ls->v1, COLOR_THEME_SECONDARY1);
      drawSource(dc, col3, line1, ls->v2, COLOR_THEME_SECONDARY1);
    } else if (lsFamily == LS_FAMILY_TIMER) {
      dc->drawNumber(col2, line1, lswTimerValue(ls->v1), COLOR_THEME_SECONDARY1 | LEFT | PREC1);
      dc->drawNumber(col3, line1, lswTimerValue(ls->v2), COLOR_THEME_SECONDARY1 | LEFT | PREC1);
    } else {
      drawSource(dc, col2, line1, ls->v1, COLOR_THEME_SECONDARY1);
      drawSourceCustomValue(dc, col3, line1, ls->v1,
          (ls->v1 <= MIXSRC_LAST_CH ? calc100toRESX(ls->v2) : ls->v2), COLOR_THEME_SECONDARY1);
    }

    // AND switch
    drawSwitch(dc, col1, line2, ls->andsw, COLOR_THEME_SECONDARY1);

    // CSW duration
    if (ls->duration > 0) {
      dc->drawNumber(col2, line2, ls->duration, COLOR_THEME_SECONDARY1 | PREC1 | LEFT);
    }

    // CSW delay
    if (lsFamily != LS_FAMILY_EDGE && ls->delay > 0) {
      dc->drawNumber(col3, line2, ls->delay, COLOR_THEME_SECONDARY1 | PREC1 | LEFT);
    }
  }

  void paint(BitmapBuffer* dc) override
  {
    if (active)
      dc->drawSolidFilledRect(0, 0, rect.w, rect.h, COLOR_THEME_ACTIVE);
    else
      dc->drawSolidFilledRect(0, 0, rect.w, rect.h, COLOR_THEME_PRIMARY2);

    paintLogicalSwitchLine(dc);

    // The bounding rect
    if (hasFocus())
      dc->drawSolidRect(0, 0, rect.w, rect.h, 2, COLOR_THEME_FOCUS);
    else
      dc->drawSolidRect(0, 0, rect.w, rect.h, 1, COLOR_THEME_SECONDARY2);
  }

 protected:
  uint8_t lsIndex;
  bool active;
};

ModelLogicalSwitchesPage::ModelLogicalSwitchesPage():
  PageTab(STR_MENULOGICALSWITCHES, ICON_MODEL_LOGICAL_SWITCHES)
{
}

void ModelLogicalSwitchesPage::rebuild(FormWindow * window, int8_t focusIndex)
{
  auto scroll_y = lv_obj_get_scroll_y(window->getLvObj());
  window->clear();
  build(window, focusIndex);
  lv_obj_scroll_to_y(window->getLvObj(), scroll_y, LV_ANIM_OFF);
}

void ModelLogicalSwitchesPage::editLogicalSwitch(FormWindow * window, uint8_t lsIndex)
{
  Window * lsWindow = new LogicalSwitchEditPage(lsIndex);
  lsWindow->setCloseHandler([=]() {
    rebuild(window, lsIndex);
  });
}

void ModelLogicalSwitchesPage::build(FormWindow* window, int8_t focusIndex)
{
  FormGridLayout grid;
  grid.spacer(PAGE_PADDING);
  grid.setLabelWidth(66);
  window->padAll(0);

  for (uint8_t i = 0; i < MAX_LOGICAL_SWITCHES; i++) {
    LogicalSwitchData* ls = lswAddress(i);

    if (ls->func == LS_FUNC_NONE) {
      auto button = new TextButton(window, grid.getLabelSlot(),
                                   getSwitchPositionName(SWSRC_SW1 + i));
      button->setPressHandler([=]() {
        if (clipboard.type == CLIPBOARD_TYPE_CUSTOM_SWITCH) {
          Menu* menu = new Menu(window);
          menu->addLine(STR_EDIT, [=]() { editLogicalSwitch(window, i); });
          menu->addLine(STR_PASTE, [=]() {
            *ls = clipboard.data.csw;
            storageDirty(EE_MODEL);
            rebuild(window, i);
          });
        } else {
          editLogicalSwitch(window, i);
        }
        return 0;
      });
      
      grid.spacer(button->height() + 5);
    } else {
      auto txt = new StaticText(window, grid.getLabelSlot(),
                                getSwitchPositionName(SWSRC_SW1 + i),
                                BUTTON_BACKGROUND, COLOR_THEME_PRIMARY1 | CENTERED);

      auto button = new LogicalSwitchButton(window, grid.getFieldSlot(), i);
      button->setPressHandler([=]() {
        Menu* menu = new Menu(window);
        menu->addLine(STR_EDIT, [=]() { editLogicalSwitch(window, i); });
        if (ls->func)
          menu->addLine(STR_COPY, [=]() {
            clipboard.type = CLIPBOARD_TYPE_CUSTOM_SWITCH;
            clipboard.data.csw = *ls;
          });
        if (clipboard.type == CLIPBOARD_TYPE_CUSTOM_SWITCH)
          menu->addLine(STR_PASTE, [=]() {
            *ls = clipboard.data.csw;
            storageDirty(EE_MODEL);
            rebuild(window, i);
          });
        if (ls->func || ls->v1 || ls->v2 || ls->delay || ls->duration ||
            ls->andsw)
          menu->addLine(STR_CLEAR, [=]() {
            memset(ls, 0, sizeof(LogicalSwitchData));
            storageDirty(EE_MODEL);
            rebuild(window, i);
          });
        return 0;
      });
      button->setFocusHandler([=](bool focus) {
        if (focus) {
          txt->setBackgroundColor(COLOR_THEME_FOCUS);
          txt->setTextFlags(COLOR_THEME_PRIMARY2 | CENTERED);
        } else {
          txt->setBackgroundColor(COLOR_THEME_SECONDARY2);
          txt->setTextFlags(COLOR_THEME_PRIMARY1 | CENTERED);
        }
        txt->invalidate();
      });

      txt->setHeight(button->height());
      grid.spacer(button->height() + 5);
    }
  }

  grid.nextLine();

}
