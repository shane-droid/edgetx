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

#include "form.h"

constexpr WindowFlags BUTTON_CHECKED = WINDOW_FLAGS_LAST << 1u;

class Button : public FormField
{
 public:
  Button(Window* parent, const rect_t& rect,
         std::function<uint8_t(void)> pressHandler = nullptr,
         WindowFlags windowFlags = 0, LcdFlags textFlags = 0,
         LvglCreate objConstruct = nullptr);

#if defined(DEBUG_WINDOWS)
  std::string getName() const override { return "Button"; }
#endif

  virtual void onPress();
  virtual void onLongPress();

  void onClicked() override;
  void checkEvents() override;

  void check(bool checked = true);
  bool checked() const;

  void setPressHandler(std::function<uint8_t(void)> handler)
  {
    pressHandler = std::move(handler);
  }

  void setLongPressHandler(std::function<uint8_t(void)> handler)
  {
    longPressHandler = std::move(handler);
  }

  void setCheckHandler(std::function<void(void)> handler)
  {
    checkHandler = std::move(handler);
  }

#if defined(HARDWARE_TOUCH)
  bool onTouchEnd(coord_t x, coord_t y) override;
#endif

 protected:
  std::function<uint8_t(void)> pressHandler;
  std::function<uint8_t(void)> longPressHandler;
  std::function<void(void)> checkHandler;

  static void long_pressed(lv_event_t* e);
};

class TextButton: public Button
{
  public:
   TextButton(Window* parent, const rect_t& rect, std::string text,
              std::function<uint8_t(void)> pressHandler = nullptr,
              WindowFlags windowFlags = OPAQUE);
              
#if defined(DEBUG_WINDOWS)
   std::string getName() const override
   {
     return "TextButton \"" + text + "\"";
   }
#endif

   void setText(std::string value)
   {
     if (value != text) {
       text = std::move(value);
       lv_label_set_text(label, text.c_str());
     }
   }

   void setBgColorHandler(std::function<LcdFlags(void)> handler = nullptr)
   {
     bgColorHandler = std::move(handler);
   }

  protected:
    lv_obj_t * label = nullptr;

    std::string text;
    std::function<LcdFlags(void)> bgColorHandler = nullptr;
};
