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

#include <vector>
#include <functional>
#include <utility>
#include <memory>

#include "modal_window.h"
#include "table.h"

class Menu;
class MenuWindowContent;

struct lvobj_delete {
  constexpr lvobj_delete() = default;
  void operator()(lv_obj_t* obj) const {
    lv_obj_del(obj);
  }
};

class MenuBody: public TableField
{
  friend class MenuWindowContent;
  friend class Menu;

  enum MENU_DIRECTION
  {
    DIRECTION_UP = 1,
    DIRECTION_DOWN = -1
  };

  class MenuLine
  {
    friend class MenuBody;

   public:
    MenuLine(const std::string& text, std::function<void()> onPress, std::function<bool()> isChecked,
             lv_obj_t *icon) :
        text(text), onPress(std::move(onPress)), isChecked(std::move(isChecked)), icon(icon)
    {
    }

    MenuLine(MenuLine &) = delete;
    MenuLine(MenuLine &&) = default;

    lv_obj_t* getIcon() { return icon.get(); }
    
   protected:
    std::string text;
    std::function<void()> onPress;
    std::function<bool()> isChecked;
    std::unique_ptr<lv_obj_t, lvobj_delete> icon;
  };

  public:
    MenuBody(Window * parent, const rect_t & rect);

#if defined(DEBUG_WINDOWS)
    std::string getName() const override
    {
      return "MenuBody";
    }
#endif

    void setIndex(int index);

    int selection() const
    {
      return selectedIndex;
    }

    int count() const
    {
      return lines.size();
    }

    void onEvent(event_t event) override;
    void onCancel() override;

    void addLine(const std::string &text, std::function<void()> onPress,
                 std::function<bool()> isChecked, bool update = true);

    void addLine(const uint8_t *icon_mask, const std::string &text,
                 std::function<void()> onPress,
                 std::function<bool()> isChecked,
                 bool update = true);

    void updateLines();

    void removeLines();

    void setCancelHandler(std::function<void()> handler)
    {
      _onCancel = std::move(handler);
    }

    coord_t getContentHeight();

    void onPress(size_t index);
  
  protected:
    void onPress(uint16_t row, uint16_t col) override;
    void onDrawBegin(uint16_t row, uint16_t col, lv_obj_draw_part_dsc_t* dsc) override;
    void onDrawEnd(uint16_t row, uint16_t col, lv_obj_draw_part_dsc_t* dsc) override;

    void selectNext(MENU_DIRECTION direction);
    int rangeCheck(int);

    std::vector<MenuLine> lines;
    int selectedIndex = 0;
    std::function<void()> _onCancel;

    inline Menu * getParentMenu();
};

class MenuWindowContent: public ModalWindowContent
{
  friend class Menu;

  public:
    explicit MenuWindowContent(Menu * parent);

    coord_t getHeaderHeight() const;

    void deleteLater(bool detach = true, bool trash = true) override;

#if defined(DEBUG_WINDOWS)
    std::string getName() const override
    {
      return "MenuWindowContent";
    }
#endif

  protected:
    MenuBody body;
};

class Menu: public ModalWindow
{
  friend class MenuBody;

  public:
    explicit Menu(Window * parent, bool multiple = false);

#if defined(DEBUG_WINDOWS)
    std::string getName() const override
    {
      return "Menu";
    }
#endif
    
    void setCancelHandler(std::function<void()> handler)
    {
      content->body.setCancelHandler(std::move(handler));
    }

    void setWaitHandler(std::function<void()> handler)
    {
      waitHandler = std::move(handler);
    }

    void setToolbar(Window* window);

    void setTitle(std::string text);

    void addLine(const std::string &text, std::function<void()> onPress,
                 std::function<bool()> isChecked = nullptr);

    void addLine(const uint8_t *icon_mask, const std::string &text,
                 std::function<void()> onPress,
                 std::function<bool()> isChecked = nullptr);

    void addLineBuffered(const std::string &text, std::function<void()> onPress,
                 std::function<bool()> isChecked = nullptr);

    void addLineBuffered(const uint8_t *icon_mask, const std::string &text,
                 std::function<void()> onPress,
                 std::function<bool()> isChecked = nullptr);

    void updateLines();

    void addSeparator();

    void removeLines();

    unsigned count() const
    {
      return content->body.count();
    }

    int selection() const
    {
      return content->body.selection();
    }

    void select(int index)
    {
      content->body.setIndex(index);
    }

    void onEvent(event_t event) override;
    void onCancel() override;

    void checkEvents() override
    {
      ModalWindow::checkEvents();
      if (waitHandler) {
        waitHandler();
      }
    }

  protected:
    MenuWindowContent* content;
    bool multiple;
    Window * toolbar = nullptr;
    std::function<void()> waitHandler;
    void updatePosition();

    void setOutline(Window* obj);
};

Menu * MenuBody::getParentMenu()
{
  return static_cast<Menu *>(getParent()->getParent());
}

