#include "hud.h"

#include "client_config.h"
#include "engine/resource_manager.h"

Hud::Hud(SDLWindow& window, ChatBuffer& chat_buffer, unsigned int max_xp,
         unsigned int max_mp)
    : chat(AREA_CHAT, CHAT_LINES, window.get_renderer(),
           ResourceManager::get_instance().get_font(CHAT_FONT_ID)),
      mana_bar(
          MP_BAR_AREA, ResourceManager::get_instance().get_font(STAT_FONT_ID),
          window.get_renderer(), max_mp, MP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      health_bar(
          HP_BAR_AREA, ResourceManager::get_instance().get_font(STAT_FONT_ID),
          window.get_renderer(), max_xp, HP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      chat_buffer(chat_buffer),
      window(window),
      side_panel_background(
          ResourceManager::get_instance().get_texture("interface", 1)) {}

Hud::~Hud() {}

void Hud::update() { chat_buffer.flush(chat); }

void Hud::render() {
    window.set_viewport(AREA_CHAT);
    chat.render();
    window.set_viewport(VIEWPORT_SIDE_PANEL);
    side_panel_background.render(AREA_SIDE_PANEL);
    health_bar.render();
    mana_bar.render();
}