#include "creation_handler.h"

#include "../game/position.h"
#include "../game/race_graphics_manager.h"
#include "../server_manager.h"
#include "event_factory.h"

CreationHandler::CreationHandler() : BlockingThEventHandler() {
    std::cerr << "CreationHandler: starting.." << std::endl;
}

void CreationHandler::handle(Event& event) {
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json create_info = event.get_json();
    ClientId client_id = create_info["client_id"];
    try {
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        std::string player_name = create_info["name"];
        if (character_manager.character_exists(player_name))
            throw DuplicatedPlayerException(player_name);
        nlohmann::json player_info = {
            {"name", player_name},
            {"map_id", 0},
            {"pos", position_t{25, 25}},
            {"head_id",
             RaceGraphicsManager::get_race_head(create_info["race_type"])},
            {"body_id",
             RaceGraphicsManager::get_race_body(create_info["race_type"])},
            {"helmet_id", 0},
            {"armor_id", 0},
            {"shield_id", 0},
            {"weapon_id", 0},
            {"curr_hp", 5},
            {"curr_mp", 0},
            {"class_type", create_info["class_type"]},
            {"race_type", create_info["race_type"]},
            {"curr_level", 1},
            {"curr_exp", 0},
            {"alive", true}};
        player_info["inventory"] = R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;
        player_info["vault"] = R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "curr_gold":0})"_json;
        character_manager.add_character(player_info);
        server_manager.add_player(client_id, player_info);
        std::cerr << "ClientInitializerHandler: Created player: " << player_name
                  << std::endl;
    } catch (const DuplicatedPlayerException& e) {
        server_manager.send_to(client_id, EventFactory::name_taken());
    }
}