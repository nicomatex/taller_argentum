#include "hud.h"

#include "client_config.h"
#include "engine/components/stats_component.h"
#include "engine/resource_manager.h"

Hud::Hud(SDLWindow& window, ChatBuffer& chat_buffer,
         StatsComponent& player_stats)
    : window(window),
      player_stats(player_stats),
      chat_buffer(chat_buffer),
      chat(AREA_CHAT, CHAT_LINES, window.get_renderer(),
           ResourceManager::get_instance().get_font(CHAT_FONT_ID)),
      mana_bar(MP_BAR_AREA,
               ResourceManager::get_instance().get_font(STAT_FONT_ID),
               window.get_renderer(), player_stats.get_stat_max_value("mp"),
               MP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      health_bar(HP_BAR_AREA,
                 ResourceManager::get_instance().get_font(STAT_FONT_ID),
                 window.get_renderer(), player_stats.get_stat_max_value("hp"),
                 HP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      side_panel_background(
          ResourceManager::get_instance().get_texture("interface", 1)) {}

Hud::~Hud() {}

void Hud::update() { 
    health_bar.set_max_value(player_stats.get_stat_max_value("hp"));
    health_bar.set_current_value(player_stats.get_stat_current_value("hp"));

    mana_bar.set_max_value(player_stats.get_stat_max_value("mp"));
    mana_bar.set_current_value(player_stats.get_stat_current_value("mp"));
    
    chat_buffer.flush(chat); 
}

void Hud::render() {
    window.set_viewport(AREA_CHAT);
    chat.render();
    window.set_viewport(VIEWPORT_SIDE_PANEL);
    side_panel_background.render(AREA_SIDE_PANEL);
    health_bar.render();
    mana_bar.render();
}