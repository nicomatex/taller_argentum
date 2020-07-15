#include "character_creation_view.h"

#include "../../client_config.h"
#include "../../engine/resource_manager.h"
#include "../../engine/sound_system.h"
CharacterCreationView::CharacterCreationView(
    SDLWindow &window, ResponsiveScaler &scaler,
    GameStateMonitor &game_state_monitor, SocketManager &socket_manager)
    : window(window),
      scaler(scaler),
      background(ResourceManager::get_instance().get_texture("interface", 3)),
      game_state_monitor(game_state_monitor),
      character_name_input(
          scaler.scale(CHAR_CREATION_NAME_AREA), window.get_renderer(),
          USERNAME_INPUT_FONT_COLOR, CHAR_CREATION_NAME_BG_COLOR,
          ResourceManager::get_instance().get_font(USERNAME_INPUT_FONT_ID), 15),
      race_and_class_selector(scaler, window.get_renderer()),
      go_back_button(scaler.scale(GO_BACK_BUTTON_AREA),
                     scaler.scale(CHAR_CREATION_VIEWPORT),
                     window.get_renderer(), game_state_monitor),
      req_char_creation_button(scaler.scale(REQ_CHAR_CREATION_BUTTON_AREA),
                               scaler.scale(CHAR_CREATION_VIEWPORT),
                               window.get_renderer(), socket_manager,
                               character_name_input, race_and_class_selector,
                               game_state_monitor),
      ui_event_handler(character_name_input, race_and_class_selector,
                       go_back_button, req_char_creation_button,
                       game_state_monitor) {
    window.set_viewport(scaler.scale(CHAR_CREATION_VIEWPORT));
    character_name_input.toggle();
}

CharacterCreationView::~CharacterCreationView() {}

void CharacterCreationView::render_selected_race_info() {
    switch (race_and_class_selector.get_selected_race()) {
        case HUMAN:
            ResourceManager::get_instance()
                .get_texture("interface", HUMAN_INFO_TEX_ID)
                .render(scaler.scale(RACE_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", HUMAN_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case GNOME:
            ResourceManager::get_instance()
                .get_texture("interface", GNOME_INFO_TEX_ID)
                .render(scaler.scale(RACE_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", GNOME_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case ELF:
            ResourceManager::get_instance()
                .get_texture("interface", ELF_INFO_TEX_ID)
                .render(scaler.scale(RACE_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", ELF_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case DWARF:
            ResourceManager::get_instance()
                .get_texture("interface", DWARF_INFO_TEX_ID)
                .render(scaler.scale(RACE_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", DWARF_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
    }
}

void CharacterCreationView::render_selected_class_info() {
    switch (race_and_class_selector.get_selected_class()) {
        case MAGE:
            ResourceManager::get_instance()
                .get_texture("interface", MAGE_INFO_TEX_ID)
                .render(scaler.scale(CLASS_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", MAGE_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case PALADIN:
            ResourceManager::get_instance()
                .get_texture("interface", PALADIN_INFO_TEX_ID)
                .render(scaler.scale(CLASS_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", PALADIN_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case PRIEST:
            ResourceManager::get_instance()
                .get_texture("interface", PRIEST_INFO_TEX_ID)
                .render(scaler.scale(CLASS_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", PRIEST_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
        case WARRIOR:
            ResourceManager::get_instance()
                .get_texture("interface", WARRIOR_INFO_TEX_ID)
                .render(scaler.scale(CLASS_DESCRIPTION_AREA));
            ResourceManager::get_instance()
                .get_texture("interface", WARRIOR_PREVIEW_TEX_ID)
                .render(scaler.scale(CHAR_PREVIEW_AREA));
            break;
    }
}

void CharacterCreationView::render_creation_alert() {
    switch (game_state_monitor.get_char_creation_state()) {
        case FIRST_TRY:
            return;
        case NAME_TAKEN:
            ResourceManager::get_instance()
                .get_texture("interface", ALERT_ID_NAME_TAKEN)
                .render(scaler.scale(CREATION_ALERT_AREA));
            break;
    }
}

void CharacterCreationView::run(int fps) {
    int frame_duration = 1000 / fps;
    SDLTimer frame_timer;

    while (game_state_monitor.get_game_state() == CREATING_CHARACTER) {
        frame_timer.start();

        window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        background.render(scaler.scale(CHAR_CREATION_BACKGROUND_AREA));
        character_name_input.render();
        render_selected_race_info();
        render_selected_class_info();
        render_creation_alert();
        window.render();

        int frame_time_remaining = frame_duration - frame_timer.get_ticks();
        if (frame_time_remaining > 0) SDL_Delay(frame_time_remaining);
    }
}