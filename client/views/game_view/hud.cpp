#include "hud.h"

#include <unordered_map>

#include "../../client_config.h"
#include "../../engine/components/stats_component.h"
#include "../../engine/components/visual_character_component.h"
#include "../../engine/resource_manager.h"
#include "../responsive_scaler.h"
#include "../../../include/types.h"

Hud::Hud(ResponsiveScaler& scaler, SDLWindow& window, ChatBuffer& chat_buffer,
         InventoryBuffer& inventory_buffer, Entity& player,
         SocketManager& socket_manager)
    : scaler(scaler),
      window(window),
      player(player),
      chat_buffer(chat_buffer),
      inventory_buffer(inventory_buffer),
      chat(scaler.scale(AREA_CHAT), CHAT_LINES, window.get_renderer(),
           ResourceManager::get_instance().get_font(CHAT_FONT_ID)),
      mana_bar(scaler.scale(MP_BAR_AREA),
               ResourceManager::get_instance().get_font(STAT_FONT_ID),
               window.get_renderer(), 999, MP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      health_bar(scaler.scale(HP_BAR_AREA),
                 ResourceManager::get_instance().get_font(STAT_FONT_ID),
                 window.get_renderer(), 999, HP_BAR_COLOR, STAT_BAR_FONT_COLOR),
      equipped_items(scaler.scale(EQUIPPED_ITEMS_AREA), window.get_renderer(),
                     4, 1, 1),
      inventory(
          scaler.scale(INVENTORY_AREA), scaler.scale(VIEWPORT_SIDE_PANEL),
          INVENTORY_ROWS, INVENTORY_COLS,
          ResourceManager::get_instance().get_font(INVENTORY_QTIES_FONT_ID),
          window.get_renderer(), socket_manager),
      cast_button(scaler.scale(CAST_BUTTON_AREA),
                  scaler.scale(VIEWPORT_SIDE_PANEL), window.get_renderer()),
      side_panel_background(
          ResourceManager::get_instance().get_texture("interface", 1)),
      gold_text("9999", ResourceManager::get_instance().get_font(1),
                GOLD_TEXT_COLOR, window.get_renderer()) {}

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
        }
        inventory.set_item(i,icon,quantity);
    }
}

void Hud::_update_equipped_items() {
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
    equipped_items.set_icon(POS_HELMET, helmet_icon);
    equipped_items.set_icon(POS_ARMOR, armor_icon);
    equipped_items.set_icon(POS_SHIELD, shield_icon);
    equipped_items.set_icon(POS_WEAPON, weapon_icon);
}

void Hud::_update_stat_bars() {
    StatsComponent& player_stats = player.get_component<StatsComponent>();

    health_bar.set_max_value(player_stats.get_stat_max_value("hp"));
    health_bar.set_current_value(player_stats.get_stat_current_value("hp"));

    mana_bar.set_max_value(player_stats.get_stat_max_value("mp"));
    mana_bar.set_current_value(player_stats.get_stat_current_value("mp"));
}

void Hud::_render_gold_amount() {
    SDL_Rect dest = scaler.scale(GOLD_TEXT_AREA);
    float scale_factor = (float)dest.h / (float)gold_text.get_height();
    dest.w = gold_text.get_width() * scale_factor;
    gold_text.render(dest);
}

void Hud::update() {
    _update_stat_bars();
    _update_equipped_items();
    _update_inventory();
    chat_buffer.flush(chat);
}

void Hud::render() {
    window.set_viewport(scaler.scale(AREA_CHAT));
    chat.render();
    window.set_viewport(scaler.scale(VIEWPORT_SIDE_PANEL));
    side_panel_background.render(scaler.scale(AREA_SIDE_PANEL));
    health_bar.render();
    mana_bar.render();
    equipped_items.render();
    inventory.render();
    _render_gold_amount();
}

void Hud::handle_event(SDL_Event& e) {
    cast_button.handle_event(e);
    inventory.handle_event(e);
}