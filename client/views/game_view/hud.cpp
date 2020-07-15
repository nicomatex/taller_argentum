#include "hud.h"

#include <string>
#include <unordered_map>

#include "../../../include/types.h"
#include "../../client_config.h"
#include "../../engine/components/stats_component.h"
#include "../../engine/components/visual_character_component.h"
#include "../../engine/resource_manager.h"
#include "../responsive_scaler.h"

Hud::Hud(ResponsiveScaler& scaler, SDLWindow& window, ChatBuffer& chat_buffer,
         InventoryBuffer& inventory_buffer,
         PlayerInfoMonitor& player_info_monitor, Entity& player,
         SocketManager& socket_manager)
    : scaler(scaler),
      window(window),
      player(player),
      chat_buffer(chat_buffer),
      inventory_buffer(inventory_buffer),
      player_info_monitor(player_info_monitor),
      chat(scaler.scale(AREA_CHAT), CHAT_LINES, window.get_renderer(),
           ResourceManager::get_instance().get_font(CHAT_FONT_ID)),
      mana_bar(scaler.scale(MP_BAR_AREA),
               ResourceManager::get_instance().get_font(STAT_FONT_ID),
               window.get_renderer(), 999, MP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      health_bar(scaler.scale(HP_BAR_AREA),
                 ResourceManager::get_instance().get_font(STAT_FONT_ID),
                 window.get_renderer(), 999, HP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      experience_bar(scaler.scale(XP_BAR_AREA),
                     ResourceManager::get_instance().get_font(STAT_FONT_ID),
                     window.get_renderer(), 999, XP_BAR_COLOR,
                     STAT_BAR_FONT_COLOR),
      equipment(scaler.scale(EQUIPPED_ITEMS_AREA),
                scaler.scale(VIEWPORT_SIDE_PANEL), window.get_renderer(),
                socket_manager),
      inventory(
          scaler.scale(INVENTORY_AREA), scaler.scale(VIEWPORT_SIDE_PANEL),
          INVENTORY_ROWS, INVENTORY_COLS,
          ResourceManager::get_instance().get_font(INVENTORY_QTIES_FONT_ID),
          window.get_renderer(), socket_manager),
      attempting_cast(false),
      render_help(false),
      cast_button(scaler.scale(CAST_BUTTON_AREA),
                  scaler.scale(VIEWPORT_SIDE_PANEL), window.get_renderer(),
                  attempting_cast),
      side_panel_background(
          ResourceManager::get_instance().get_texture("interface", 1)),
      help_panel(ResourceManager::get_instance().get_texture("interface", 23)),
      gold_text("9999", ResourceManager::get_instance().get_font(1),
                GOLD_TEXT_COLOR, window.get_renderer()),
      level_text("99", ResourceManager::get_instance().get_font(1),
                 LEVEL_TEXT_COLOR, window.get_renderer()),
      spell_name_text("Nothing", ResourceManager::get_instance().get_font(1),
                      INFO_TEXT_COLOR, window.get_renderer()),
      attack_points_text("152", ResourceManager::get_instance().get_font(1),
                         INFO_TEXT_COLOR, window.get_renderer()),
      defense_points_text("245", ResourceManager::get_instance().get_font(1),
                          INFO_TEXT_COLOR, window.get_renderer()) {}

Hud::~Hud() {}

void Hud::_update_inventory() {
    nlohmann::json inventory_data = inventory_buffer.get_inventory_data();
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        nlohmann::json slot_info = inventory_data["items"][i];
        SDLTexture* icon = NULL;
        int quantity = 0;
        switch (int(slot_info["type"])) {
            case TYPE_INVALID:
                icon = NULL;
                quantity = 0;
                break;
            case TYPE_WEAPON:
                icon = &ResourceManager::get_instance().get_texture(
                    "weapon_icons", slot_info["item_id"]);
                quantity = slot_info["actual_stack"];
                break;
            case TYPE_ARMOR:
                switch (int(slot_info["armor_info"]["slot_info"])) {
                    case 0:
                        icon = &ResourceManager::get_instance().get_texture(
                            "helmet_icons", slot_info["item_id"]);
                        quantity = slot_info["actual_stack"];
                        break;
                    case 1:
                        icon = &ResourceManager::get_instance().get_texture(
                            "armor_icons", slot_info["item_id"]);
                        quantity = slot_info["actual_stack"];
                        break;
                    case 2:
                        icon = &ResourceManager::get_instance().get_texture(
                            "shield_icons", slot_info["item_id"]);
                        quantity = slot_info["actual_stack"];
                        break;
                }
                break;
            case TYPE_POTION:
                icon = &ResourceManager::get_instance().get_texture(
                    "potion_icons", slot_info["item_id"]);
                quantity = slot_info["actual_stack"];
                break;
        }
        inventory.set_item(i, icon, quantity);
    }
    gold_text.update_text(std::to_string(int(inventory_data["curr_gold"])));
}

void Hud::_update_equipment() {
    VisualCharacterComponent& character_visuals =
        player.get_component<VisualCharacterComponent>();

    SDLTexture* helmet_icon = NULL;
    int helmet_id = character_visuals.get_part_id("helmet");
    if (helmet_id != 0) {
        helmet_icon = &(ResourceManager::get_instance().get_texture(
            "helmet_icons", helmet_id));
    }

    SDLTexture* armor_icon = NULL;
    int armor_id = character_visuals.get_part_id("armor");
    if (armor_id != 0) {
        armor_icon = &(ResourceManager::get_instance().get_texture(
            "armor_icons", armor_id));
    }

    SDLTexture* shield_icon = NULL;
    int shield_id = character_visuals.get_part_id("shield");
    if (shield_id != 0) {
        shield_icon = &(ResourceManager::get_instance().get_texture(
            "shield_icons", shield_id));
    }

    SDLTexture* weapon_icon = NULL;
    int weapon_id = character_visuals.get_part_id("weapon");
    if (weapon_id != 0) {
        weapon_icon = &(ResourceManager::get_instance().get_texture(
            "weapon_icons", weapon_id));
    }
    equipment.set_item(POS_HELMET, helmet_icon);
    equipment.set_item(POS_ARMOR, armor_icon);
    equipment.set_item(POS_SHIELD, shield_icon);
    equipment.set_item(POS_WEAPON, weapon_icon);
}

void Hud::_update_stats() {
    StatsComponent& player_stats = player.get_component<StatsComponent>();

    health_bar.set_max_value(player_stats.get_stat_max_value("hp"));
    health_bar.set_current_value(player_stats.get_stat_current_value("hp"));

    mana_bar.set_max_value(player_stats.get_stat_max_value("mp"));
    mana_bar.set_current_value(player_stats.get_stat_current_value("mp"));

    experience_bar.set_max_value(player_stats.get_stat_max_value("xp"));
    experience_bar.set_current_value(player_stats.get_stat_current_value("xp"));

    level_text.update_text(std::to_string(player_stats.get_level()));
}

void Hud::_update_player_info() {
    StatsComponent& player_stats = player.get_component<StatsComponent>();
    player_stats.get_ability_name();
    spell_name_text.update_text(player_stats.get_ability_name());
    int min_attack = player_stats.get_stat_current_value("att");
    int max_attack = player_stats.get_stat_max_value("att");
    std::string attack = std::to_string(min_attack) + " - " + std::to_string(max_attack);
    attack_points_text.update_text(attack);

    int min_defense = player_stats.get_stat_current_value("def");
    int max_defense = player_stats.get_stat_max_value("def");
    std::string defense = std::to_string(min_defense) + " - " + std::to_string(max_defense);
    defense_points_text.update_text(defense);
}

SDL_Rect Hud::_get_scaled_dest(SDLText& text, SDL_Rect dest) {
    SDL_Rect scaled_dest = scaler.scale(dest);
    float scale_factor = (float)scaled_dest.h / (float)text.get_height();
    scaled_dest.w = text.get_width() * scale_factor;
    return scaled_dest;
}

void Hud::_render_gold_amount() {
    gold_text.render(_get_scaled_dest(gold_text, GOLD_TEXT_AREA));
}

void Hud::_render_level() {
    SDL_Rect scaled_dest = _get_scaled_dest(level_text, LEVEL_TEXT_AREA);
    scaled_dest.x -= scaled_dest.w / 2;  // Centrado del texto
    level_text.render(scaled_dest);
}

void Hud::_render_player_info() {
    spell_name_text.render(_get_scaled_dest(spell_name_text, SPELL_TEXT_AREA));
    attack_points_text.render(
        _get_scaled_dest(attack_points_text, ATT_PTS_TEXT_AREA));
    defense_points_text.render(
        _get_scaled_dest(defense_points_text, DEF_PTS_TEXT_AREA));
}

void Hud::_render_help_panel() {
    if (render_help) {
        help_panel.render(scaler.scale(HELP_PANEL_AREA));
    }
}

void Hud::update() {
    _update_stats();
    _update_equipment();
    _update_inventory();
    _update_player_info();
    chat_buffer.flush(chat);
}

void Hud::render() {
    window.set_viewport(scaler.scale(AREA_CHAT));
    chat.render();
    window.set_viewport(scaler.scale(VIEWPORT_SIDE_PANEL));
    side_panel_background.render(scaler.scale(AREA_SIDE_PANEL));
    health_bar.render();
    mana_bar.render();
    experience_bar.render();
    equipment.render();
    inventory.render();
    _render_gold_amount();
    _render_level();
    _render_player_info();
    window.reset_viewport();
    _render_help_panel();
}

void Hud::handle_event(SDL_Event& e) {
    cast_button.handle_event(e);
    inventory.handle_event(e);
    equipment.handle_event(e);
}