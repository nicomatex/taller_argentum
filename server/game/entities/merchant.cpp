#include "merchant.h"

#include <sstream>

#include "../../server_manager.h"

Merchant::Merchant(EntityId entity_id, nlohmann::json npc_info, Map& map)
    : Npc(entity_id, npc_info, map), inventory(MERCH_SLOTS_INV) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    inventory.add(item_factory.create(400, 9000));
    inventory.add(item_factory.create(401, 9000));
    inventory.add(item_factory.create(2, 3));
    inventory.add(item_factory.create(101, 100));
    inventory.add(item_factory.create(201, 100));
    inventory.add(item_factory.create(308, 100));
    Gold* other_gold = (Gold*)item_factory.create(500, 99999999);
    inventory.add_gold(other_gold);
    delete other_gold;
}

Merchant::~Merchant() {}

const std::string Merchant::list_sale() const {
    std::stringstream ss;
    std::string greeting =
        "Bienvenido a mi tienda aventurero, tengo para vender:\n";
    ss << greeting;

    SlotId slot_id = 0;
    unsigned int counter = 0;
    nlohmann::json json_inv = inventory.get_data();
    for (auto& item : json_inv["items"]) {
        if (item["type"] != 0) {
            ss << "[" << std::to_string(slot_id) << "]"
               << " ";
            ss << "Name: " << item["name"] << ", ";
            ss << "stock: " << item["actual_stack"] << ", ";
            ss << "precio: $" << item["gold_value"] << "               ";
            counter++;
            if (counter == 2) {
                ss << "\n";
                counter = 0;
            }   
        }
        slot_id++;
    }
    std::string msg = ss.str();
    return msg;
}

void Merchant::sell(SlotId slot, uint32_t stack, Player* player) {
    Item *item = nullptr;
    try {
        item = player->remove_item(slot, stack);
        if (!item)
            return;
        uint32_t gold_total = item->get_stack() * item->get_gold_value();
        inventory.add(item);
        Gold* gold = inventory.remove_gold(gold_total);
        player->add_item(gold);
    } catch (const FullItemContainerException& e) {
        player->add_item(item);
    }
}

void Merchant::buy(SlotId slot, uint32_t stack, Player* player) {
    long int player_gold_stack = player->get_gold_stack();
    uint32_t purchasable = 0;
    uint32_t gold_value = inventory.get_item(slot).get_gold_value();
    while (purchasable != stack) {
        player_gold_stack -= gold_value;
        if (player_gold_stack >= 0)
            purchasable++;
        else
            break;
    }
    if (purchasable == 0)
        return;
    Item* item = inventory.remove(slot, purchasable);
    player->add_item(item);
    Gold* gold = player->remove_gold(item->get_stack() * gold_value);
    inventory.add_gold(gold);
    delete gold;
}