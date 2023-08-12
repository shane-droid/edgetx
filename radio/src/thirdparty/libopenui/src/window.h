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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <string>
#include <utility>
#include <functional>

#include "bitmapbuffer.h"
#include "libopenui_defines.h"
#include "opentx_helpers.h"

#include "widgets/etx_obj_create.h"

#include "LvglWrapper.h"

typedef uint32_t WindowFlags;

#if !defined(_GNUC_)
  #undef OPAQUE
  #undef TRANSPARENT
#endif

constexpr WindowFlags OPAQUE =                1u << 0u;
constexpr WindowFlags TRANSPARENT =           1u << 1u;
constexpr WindowFlags NO_FOCUS =              1u << 2u;
constexpr WindowFlags REFRESH_ALWAYS =        1u << 3u;
constexpr WindowFlags WINDOW_FLAGS_LAST =  REFRESH_ALWAYS;

typedef lv_obj_t *(*LvglCreate)(lv_obj_t *);
extern "C" void window_event_cb(lv_event_t * e);

class Window
{
    friend void window_event_cb(lv_event_t * e);

  public:
    Window(Window *parent, const rect_t &rect, WindowFlags windowFlags = 0,
           LcdFlags textFlags = 0, LvglCreate objConstruct = nullptr);

    Window(Window *parent, lv_obj_t* lvobj);

    virtual ~Window();

#if defined(DEBUG_WINDOWS)
    virtual std::string getName() const;
    std::string getRectString() const;
    std::string getIndentString() const;
    std::string getWindowDebugString(const char * name = nullptr) const;
#endif

    Window *getParent() const { return parent; }

    Window *getFullScreenWindow();

    WindowFlags getWindowFlags() const { return windowFlags; }
    void setWindowFlags(WindowFlags flags);

    LcdFlags getTextFlags() const { return textFlags; }
    void setTextFlags(LcdFlags flags);

    typedef std::function<void()> CloseHandler;
    void setCloseHandler(CloseHandler h) { closeHandler = std::move(h); }

    typedef std::function<void(bool)> FocusHandler;
    void setFocusHandler(FocusHandler h) { focusHandler = std::move(h); }

    void clear();
    virtual void deleteLater(bool detach = true, bool trash = true);

    bool hasFocus() const;

    void setRect(rect_t value)
    {
      rect = value;
      lv_obj_enable_style_refresh(false);
      lv_obj_set_pos(lvobj, rect.x, rect.y);
      lv_obj_set_size(lvobj, rect.w, rect.h);
      lv_obj_enable_style_refresh(true);
      lv_obj_refresh_style(lvobj, LV_PART_ANY, LV_STYLE_PROP_ANY);
    }

    void setWidth(coord_t value)
    {
      rect.w = value;
      lv_obj_set_width(lvobj, rect.w);
    }

    void setHeight(coord_t value)
    {
      rect.h = value;
      lv_obj_set_height(lvobj, rect.h);
    }

    void setLeft(coord_t x)
    {
      rect.x = x;
      lv_obj_set_pos(lvobj, rect.x, rect.y);
    }

    void setTop(coord_t y)
    {
      rect.y = y;
      lv_obj_set_pos(lvobj, rect.x, rect.y);
    }

    coord_t left() const
    {
      return rect.x;
    }

    coord_t right() const
    {
      return rect.x + rect.w;
    }

    coord_t top() const
    {
      return rect.y;
    }

    coord_t bottom() const
    {
      return rect.y + rect.h;
    }

    coord_t width() const
    {
      return rect.w;
    }

    coord_t height() const
    {
      return rect.h;
    }

    rect_t getRect() const
    {
      return rect;
    }

    void padLeft(coord_t pad);
    void padRight(coord_t pad);
    void padTop(coord_t pad);
    void padBottom(coord_t pad);
    void padAll(coord_t pad);

    void padRow(coord_t pad);
    void padColumn(coord_t pad);

    virtual void onEvent(event_t event);
    virtual void onClicked();
    virtual void onCancel();

    virtual void updateSize();

    void invalidate()
    {
      invalidate({0, 0, rect.w, rect.h});
    }

    void bringToTop();

    virtual void checkEvents();

    void attach(Window * window);

    void detach();

    bool deleted() const
    {
      return _deleted;
    }

    virtual void paint(BitmapBuffer *) {}

#if defined(HARDWARE_TOUCH)
    virtual bool onTouchStart(coord_t x, coord_t y);
    virtual bool onTouchEnd(coord_t x, coord_t y);
#endif
  
    inline lv_obj_t *getLvObj() { return lvobj; }

  protected:
    static std::list<Window*> trash;

    rect_t rect;

    Window*   parent = nullptr;
    lv_obj_t* lvobj = nullptr;

    std::list<Window *> children;

    WindowFlags windowFlags = 0;
    LcdFlags    textFlags = 0;

    bool _deleted = false;

    std::function<void()> closeHandler;
    std::function<void(bool)> focusHandler;

    void deleteChildren();

    virtual void addChild(Window * window);
    void removeChild(Window * window);

    virtual void invalidate(const rect_t & rect);
};

