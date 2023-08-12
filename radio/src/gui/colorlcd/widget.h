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

#include <list>
#include <string.h>
#include "button.h"
#include "widgets_container.h"
#include "debug.h"

// YAML_GENERATOR defs
#if !defined(USE_IDX)
#define USE_IDX
#endif

class WidgetFactory;

class Widget : public Button
{
  public:

    typedef WidgetPersistentData PersistentData;

    Widget(const WidgetFactory *factory, Window* parent, const rect_t &rect,
           WidgetPersistentData *persistentData);

    ~Widget() override = default;

    inline const WidgetFactory * getFactory() const
    {
        return factory;
    }

    inline const ZoneOption * getOptions() const;

    virtual const char * getErrorMessage() const
    {
      return nullptr;
    }

    inline ZoneOptionValue * getOptionValue(unsigned int index) const
    {
      return &persistentData->options[index].value;
    }

    // 
    // TODO: for some reason, this one crashes on the radio...
    //
    // inline void setOptionValue(unsigned int index, const ZoneOptionValue& value)
    // {
    //   persistentData->options[index].value = value;
    // }

    inline PersistentData * getPersistentData()
    {
      return persistentData;
    }

#if defined(DEBUG_WINDOWS)
    std::string getName() const override
    {
      return "Widget";
    }
#endif

    // Window interface
#if defined(HARDWARE_KEYS)
    void onEvent(event_t event) override;
#endif
    void paint(BitmapBuffer * dc) override;

    // Widget interface

    // Set/unset fullscreen mode
    void setFullscreen(bool enable);

    // Disable setting fullscreen mode
    void disableFullscreen();
    bool isFullscreenAllowed() { return fsAllowed; }
  
    // Called when the widget options have changed
    virtual void update();

    // Called when the widget should redraw
    virtual void refresh(BitmapBuffer* dc) = 0;

    // Called at regular time interval, even if the widget cannot be seen
    virtual void background() {}

    // Update widget 'zone' data (for Lua widgets)
    virtual void updateZoneRect(rect_t rect) {}

  protected:
    const WidgetFactory * factory;
    PersistentData * persistentData;
    uint32_t focusGainedTS = 0;
    bool fullscreen = false;
    bool fsAllowed = true;

    void onCancel() override;
    void onLongPress() override;

    virtual void onFullscreen(bool enable) {}
    void openMenu();
};

void registerWidget(const WidgetFactory * factory);
void unregisterWidget(const WidgetFactory * factory);

class WidgetFactory
{
  public:
    explicit WidgetFactory(const char * name, const ZoneOption * options = nullptr, const char * displayName = nullptr):
      name(name),
      displayName(displayName),
      options(options)
    {
      registerWidget(this);
    }

    virtual ~WidgetFactory() {}

    inline const char * getName() const
    {
        return name;
    }

    inline const ZoneOption * getOptions() const
    {
      return options;
    }

    inline const char * getDisplayName() const
    {
        if (displayName)
          return displayName;
        else
          return name;
    }

    void initPersistentData(Widget::PersistentData * persistentData, bool setDefault) const
    {
      if (setDefault) {
        memset(persistentData, 0, sizeof(Widget::PersistentData));
      }
      if (options) {
        int i = 0;
        for (const ZoneOption * option = options; option->name; option++, i++) {
          TRACE("WidgetFactory::initPersistentData() setting option '%s'", option->name);
          // TODO compiler bug? The CPU freezes ... persistentData->options[i++] = option->deflt;
          auto optVal = &persistentData->options[i];
          auto optType = zoneValueEnumFromType(option->type);
          if (setDefault || optVal->type != optType) {
            // reset to default value
            memcpy(&optVal->value, &option->deflt, sizeof(ZoneOptionValue));
            optVal->type = optType;
          }
        }
      }
    }

    virtual Widget * create(Window* parent, const rect_t & rect, Widget::PersistentData * persistentData, bool init = true) const = 0;

  protected:
    const char * name;
    const char * displayName;
    const ZoneOption * options;
};

inline const ZoneOption * Widget::getOptions() const
{
  return getFactory()->getOptions();
}

Widget * loadWidget(const char * name, Window* parent, const rect_t & rect, Widget::PersistentData * persistentData);

std::list<const WidgetFactory *> & getRegisteredWidgets();
