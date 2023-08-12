/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   libopenui - https://github.com/opentx/libopenui
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

#include "button.h"
#include "menu.h"

class Choice;

class MenuToolbarButton : public Button
{
 public:
  MenuToolbarButton(Window* parent, const rect_t& rect, const char* picto);
  void paint(BitmapBuffer* dc) override;

 protected:
  const char* picto;
};

class MenuToolbar : public Window
{
  // friend Menu;

 public:
  MenuToolbar(Choice* choice, Menu* menu);
  ~MenuToolbar();

  void resetFilter();
  void onEvent(event_t event) override;

 protected:
  Choice* choice;
  Menu* menu;

  lv_group_t* group;

  void addButton(const char* picto, int16_t filtermin, int16_t filtermax);
  bool filterMenu(MenuToolbarButton* btn, int16_t filtermin, int16_t filtermax);

  rect_t getButtonRect(size_t buttons);

  void onClicked() override;
};
