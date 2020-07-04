#include "creation_handler.h"

#include "../game/map.h"
#include "../game/position.h"
#include "../server_manager.h"
#include "event_factory.h"

CreationHandler::CreationHandler() : BlockingThEventHandler() {
    std::cerr << "CreationHandler: starting.." << std::endl;
}

CreationHandler::~CreationHandler() {}

void CreationHandler::handle(Event& event) {
    try {
        ServerManager& server_manager = ServerManager::get_instance();
        nlohmann::json create_info = event.get_json();
        CharacterManager& character_manager =
            server_manager.get_character_manager();
        std::string player_name = create_info["name"];
        if (character_manager.character_exists(player_name))
            throw DuplicatedPlayerException(player_name);
        server_manager.add_name(create_info["client_id"], player_name);
        nlohmann::json player_info = {{"name", player_name},
                                      {"map_id", 0},
                                      {"pos", position_t{25, 25}},
                                      {"head_id", 1},
                                      {"body_id", 2},
                                      {"helmet_id", 0},
                                      {"armor_id", 0},
                                      {"shield_id", 0},
                                      {"weapon_id", 0},
                                      {"curr_hp", 1},
                                      {"curr_mp", 1},
                                      {"class_type", create_info["class_type"]},
                                      {"race_type", create_info["race_type"]},
                                      {"curr_level", 1},
                                      {"curr_exp", 0}};
        player_info["inventory"] = R"({"items_ids":[0,0,0,0,0,0,0,0,0,0,0,0],
                                 "items_stacks":[0,0,0,0,0,0,0,0,0,0,0,0]})"_json;
        character_manager.add_character(player_info);
        std::cout << "ClientInitializerHandler: Creating player: "
                  << player_name << std::endl;
        server_manager.add_player(create_info["client_id"], player_info);
    } catch (const DuplicatedPlayerException& e) {
        disconnect(event);
    }
}

void CreationHandler::disconnect(Event& event) const {
    // TODO: mejorar este handle
    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json create_info = event.get_json();
    server_manager.send_to(create_info["client_id"],
                           EventFactory::disconnect());
    std::cout << "Sending drop to " << create_info["client_id"] << std::endl;
    server_manager.rm_client(create_info["client_id"]);
}