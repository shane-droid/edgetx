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

#include "window.h"
#include "touch.h"
#include "mainwindow.h"

std::list<Window *> Window::trash;

extern lv_obj_t *virtual_kb;

extern "C" void window_event_cb(lv_event_t * e)
{
  lv_obj_t *target = lv_event_get_target(e);
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_SCROLL_BEGIN) {
    TRACE("SCROLL_BEGIN");
  } else if (code == LV_EVENT_SCROLL_END) {
    TRACE("SCROLL_END");
  } 

  Window* window = (Window *)lv_obj_get_user_data(target);
  if (!window) return;

  if(code == LV_EVENT_DELETE || window->deleted()) return;

  if (code == LV_EVENT_DRAW_MAIN) {

    lv_draw_ctx_t* draw_ctx = lv_event_get_draw_ctx(e);

    lv_area_t a, clipping, obj_coords;
    lv_area_copy(&a, draw_ctx->buf_area);
    lv_area_copy(&clipping, draw_ctx->clip_area);
    lv_obj_get_coords(target, &obj_coords);

    auto w = a.x2 - a.x1 + 1;
    auto h = a.y2 - a.y1 + 1;

    TRACE_WINDOWS("DRAW_MAIN %s", window->getWindowDebugString().c_str());

    BitmapBuffer buf = {BMP_RGB565, (uint16_t)w, (uint16_t)h,
                        (uint16_t *)draw_ctx->buf};

    buf.setDrawCtx(draw_ctx);
    
    buf.setOffset(obj_coords.x1 - a.x1, obj_coords.y1 - a.y1);
    buf.setClippingRect(clipping.x1 - a.x1, clipping.x2 + 1 - a.x1,
                        clipping.y1 - a.y1, clipping.y2 + 1 - a.y1);

    window->paint(&buf);

  }
#if defined(HARDWARE_TOUCH)
  else if (code == LV_EVENT_PRESSED || code == LV_EVENT_RELEASED) {
    TRACE_WINDOWS("PRESSED: %s", window->getWindowDebugString().c_str());

    lv_indev_t *click_source = (lv_indev_t *)lv_event_get_param(e);

    lv_area_t obj_coords;
    lv_obj_get_coords(target, &obj_coords);

    lv_point_t point_act;
    lv_indev_get_point(click_source, &point_act);

    // Ignore event from keypad
    if (point_act.x < 0 || point_act.y < 0) return;

    lv_point_t rel_pos;
    rel_pos.x = point_act.x - obj_coords.x1;
    rel_pos.y = point_act.y - obj_coords.y1;


    if (code == LV_EVENT_PRESSED) {
      TRACE("PRESSED[%d|%d]", rel_pos.x, rel_pos.y);
      window->onTouchStart(rel_pos.x, rel_pos.y);
    } else {
      lv_point_t vect_act;
      lv_indev_get_vect(click_source, &vect_act);

      TRACE("RELEASED[%d|%d] vect[%d|%d]", rel_pos.x, rel_pos.y, vect_act.x,
            vect_act.y, lv_indev_get_scroll_dir(click_source));

      if (vect_act.x != 0 || vect_act.y != 0) return;
      window->onTouchEnd(rel_pos.x, rel_pos.y);
    }
  }
#endif
  else if (code == LV_EVENT_SCROLL) {

    // exclude pointer based scrolling (only focus scrolling)
    if (!lv_obj_is_scrolling(target)) {
      lv_point_t* p = (lv_point_t*)lv_event_get_param(e);
      lv_coord_t scroll_bottom = lv_obj_get_scroll_bottom(target);

      lv_coord_t scroll_y = lv_obj_get_scroll_y(target);
      TRACE("SCROLL[x=%d;y=%d;top=%d;bottom=%d]", p->x, p->y,
             scroll_y, scroll_bottom);

      if (scroll_y <= 45 && p->y > 0) {
        lv_obj_scroll_by(target, 0, scroll_y, LV_ANIM_OFF);
      } else if (scroll_bottom <= 16 && p->y < 0) {
        lv_obj_scroll_by(target, 0, -scroll_bottom, LV_ANIM_OFF);
      }
    }
  }
  else if (code == LV_EVENT_CLICKED) {
    TRACE("CLICKED[%p]", window);
    window->onClicked();
  }
  else if (code == LV_EVENT_CANCEL) {
    TRACE("CANCEL[%p]", window);
    window->onCancel();
  } else if (code == LV_EVENT_FOCUSED) {
    if(window->focusHandler)
      window->focusHandler(true);
  } else if (code == LV_EVENT_DEFOCUSED) {
    if(window->focusHandler)
      window->focusHandler(false);
  }
}

Window::Window(Window *parent, const rect_t &rect, WindowFlags windowFlags,
               LcdFlags textFlags, LvglCreate objConstruct) :
    rect(rect),
    parent(parent),
    windowFlags(windowFlags),
    textFlags(textFlags)
{
  lv_obj_t* lv_parent = nullptr;
  if (parent) lv_parent = parent->lvobj;

  if (objConstruct != nullptr && objConstruct != window_create) {
    lvobj = objConstruct(lv_parent);
    lv_obj_add_event_cb(lvobj, window_event_cb, LV_EVENT_ALL, nullptr);
  } else {
    lvobj = window_create(lv_parent);
  }

  lv_obj_set_user_data(lvobj, this);

  if (rect.x || rect.y)
    lv_obj_set_pos(lvobj, rect.x, rect.y);
  if (rect.w)
    lv_obj_set_width(lvobj, rect.w);
  if (rect.h)
    lv_obj_set_height(lvobj, rect.h);

  if (windowFlags & OPAQUE) {
    lv_obj_set_style_bg_opa(lvobj, LV_OPA_MAX, LV_PART_MAIN);
  }

  lv_obj_set_scrollbar_mode(lvobj, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(lvobj, LV_OBJ_FLAG_SCROLL_ELASTIC);

  if (parent) {
    parent->addChild(this);
    if (!(windowFlags & TRANSPARENT)) {
      invalidate();
    }
  }

  // honor the no focus flag of libopenui
  if (this->windowFlags & NO_FOCUS) {
    lv_obj_clear_flag(lvobj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
  }
}

Window::Window(Window *parent, lv_obj_t* lvobj)
  : rect(nullRect),
    parent(parent),
    lvobj(lvobj)
{
  lv_obj_set_user_data(lvobj, this);

  if (windowFlags & OPAQUE) {
    lv_obj_set_style_bg_opa(lvobj, LV_OPA_MAX, LV_PART_MAIN);
  }

  lv_obj_set_scrollbar_mode(lvobj, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(lvobj, LV_OBJ_FLAG_SCROLL_ELASTIC);
  lv_obj_add_event_cb(lvobj, window_event_cb, LV_EVENT_ALL, this);

  if (parent) {
    parent->addChild(this);
    if (!(windowFlags & TRANSPARENT)) {
      invalidate();
    }
  }

  // honor the no focus flag of libopenui
  if (this->windowFlags & NO_FOCUS) {
    lv_obj_clear_flag(lvobj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
  }
}

Window::~Window()
{
  TRACE_WINDOWS("Destroy %p %s", this, getWindowDebugString().c_str());

  if (children.size() > 0) deleteChildren();

  if (lvobj != nullptr) {
    lv_obj_set_user_data(lvobj, nullptr);
    lv_obj_del(lvobj);
    lvobj = nullptr;
  }
}

#if defined(DEBUG_WINDOWS)
std::string Window::getName() const { return "Window"; }

std::string Window::getRectString() const
{
  char result[32];
  sprintf(result, "[%d, %d, %d, %d]", left(), top(), width(), height());
  return result;
}

std::string Window::getIndentString() const
{
  std::string result;
  auto tmp = parent;
  while (tmp) {
    result += "  ";
    tmp = tmp->getParent();
  }
  return result;
}

std::string Window::getWindowDebugString(const char *name) const
{
  return getName() + (name ? std::string(" [") + name + "] " : " ") +
         getRectString();
}
#endif

Window *Window::getFullScreenWindow()
{
  if (width() == LCD_W && height() == LCD_H) return this;
  if (parent) return parent->getFullScreenWindow();
  return nullptr;
}

void Window::setWindowFlags(WindowFlags flags)
{
  // TODO: check if LVGL flags need updating...
  windowFlags = flags;
}

void Window::setTextFlags(LcdFlags flags)
{
  textFlags = flags;
  if (!lvobj) return;

  // lv integration for colors
  lv_obj_set_style_text_color(lvobj, makeLvColor(textFlags), LV_PART_MAIN);
}

void Window::attach(Window *newParent)
{
  if (parent) detach();
  parent = newParent;
  if (newParent) {
    newParent->addChild(this);
  }
}

void Window::detach()
{
  if (parent) {
    parent->removeChild(this);
    parent = nullptr;
  }
}

void Window::deleteLater(bool detach, bool trash)
{
  if (_deleted)
    return;

  TRACE_WINDOWS("Delete %p %s", this, getWindowDebugString().c_str());

  _deleted = true;

  if (detach)
    this->detach();
  else
    parent = nullptr;

  if (trash) {
    Window::trash.push_back(this);
  }

  if (closeHandler) {
    closeHandler();
  }

  deleteChildren();

  if (lvobj != nullptr) {
    auto obj = lvobj;
    lvobj = nullptr;
    lv_obj_del(obj);
  }
}

void Window::clear()
{
  deleteChildren();
  if(lvobj != nullptr) {
    lv_obj_clean(lvobj);
  }
  invalidate();
}

void Window::deleteChildren()
{
  // prevent LVGL refocus while mass-deleting
  // inhibit_focus = true;
  for (auto window: children) {
    window->deleteLater(false);
  }
  // inhibit_focus = false;
  children.clear();
}

bool Window::hasFocus() const
{
  return lvobj && lv_obj_has_state(lvobj, LV_STATE_FOCUSED);
}

void Window::padLeft(coord_t pad)
{
  lv_obj_set_style_pad_left(lvobj, pad, 0);
}

void Window::padRight(coord_t pad)
{
  lv_obj_set_style_pad_right(lvobj, pad, 0);
}

void Window::padTop(coord_t pad)
{
  lv_obj_set_style_pad_top(lvobj, pad, 0);
}

void Window::padBottom(coord_t pad)
{
  lv_obj_set_style_pad_bottom(lvobj, pad, 0);
}

void Window::padAll(coord_t pad)
{
  lv_obj_set_style_pad_all(lvobj, pad, 0);
}

void Window::padRow(coord_t pad)
{
  lv_obj_set_style_pad_row(lvobj, pad, 0);
}

void Window::padColumn(coord_t pad)
{
  lv_obj_set_style_pad_column(lvobj, pad, 0);
}

void Window::bringToTop()
{
  attach(parent); // does a detach + attach
  if (lvobj && lv_obj_get_parent(lvobj)) lv_obj_move_foreground(lvobj);
}

void Window::checkEvents()
{
  auto copy = children;
  for (auto child: copy) {
    if (!child->deleted()) {
      child->checkEvents();
    }
  }

  if (windowFlags & REFRESH_ALWAYS) {
    invalidate();
  }
}

void Window::onEvent(event_t event)
{
  TRACE_WINDOWS("%s received event 0x%X", Window::getWindowDebugString("Window").c_str(), event);
  if (parent) { parent->onEvent(event); }
}

void Window::onClicked()
{
  if (parent && !(windowFlags & OPAQUE)) { parent->onClicked(); }
}

void Window::onCancel()
{
  if (parent) { parent->onCancel(); }
}


#if defined(HARDWARE_TOUCH)
bool Window::onTouchStart(coord_t x, coord_t y)
{
  if (parent && !(windowFlags & OPAQUE)) return parent->onTouchStart(x, y);
  return true;
}

bool Window::onTouchEnd(coord_t x, coord_t y)
{
  if (parent && !(windowFlags & OPAQUE)) return parent->onTouchEnd(x, y);
  return true;
}
#endif

void Window::updateSize()
{
  lv_obj_set_height(lvobj, LV_SIZE_CONTENT);
  lv_obj_update_layout(lvobj);

  rect.x = lv_obj_get_x(lvobj);
  rect.y = lv_obj_get_y(lvobj);
  rect.w = lv_obj_get_width(lvobj);
  rect.h = lv_obj_get_height(lvobj);
  invalidate();
}

void Window::addChild(Window* window)
{
  auto lv_parent = lv_obj_get_parent(window->lvobj);
  if (lv_parent && (lv_parent != lvobj)) {
    lv_obj_set_parent(window->lvobj, lvobj);
  }

  children.push_back(window);
}

void Window::removeChild(Window* window)
{
  children.remove(window);
  invalidate();
}

void Window::invalidate(const rect_t & rect)
{
  if (lvobj) lv_obj_invalidate(lvobj);
}
