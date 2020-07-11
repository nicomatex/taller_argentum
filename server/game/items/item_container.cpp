#include "item_container.h"

#include "../../server_manager.h"

// Temp
#include <iomanip>
#include <iostream>

const char* FullItemContainerException::what() const throw() {
    return "ItemContainer is full!";
}

const char* EmptySlotException::what() const throw() {
    return "Slot is empty!";
}

ItemContainer::ItemContainer(unsigned int slots_amount) {
    item_container.resize(slots_amount);
}

ItemContainer::ItemContainer(const nlohmann::json& inv_json)
    : ItemContainer(INV_SIZE) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    inventory_t inventory = inv_json;
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        ItemId item_id = inventory.items_ids[slot_id];
        if (item_id == 0)
            continue;  // El 0 es un id invalido (ausencia)
        uint32_t stack = inventory.items_stacks[slot_id];
        this->add(item_factory.create(item_id, stack));
    }
    gold = static_cast<Gold*>(item_factory.create(500, inv_json["curr_gold"]));
}

ItemContainer::~ItemContainer() {
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        delete item_container[slot_id];
    }
    delete gold;
}

void ItemContainer::add(Item* item) {
    ItemId item_id = item->get_id();
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        item_container[slot_id] = item;
        item_id_to_slot[item_id] = slot_id;
    } else {
        item_container[slot_id]->increase_stack(item->get_stack());
        item->set_stack(0);
        delete item;  //?
    }
}

void ItemContainer::add(Item* item, uint32_t stack) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    ItemId item_id = item->get_id();
    if (item->get_stack() <= stack)
        return add(item);  // estoy agregando todo el item
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        item_container[slot_id] = item_factory.create(item_id, stack);
        item_id_to_slot[item_id] = slot_id;
    } else {
        item_container[slot_id]->increase_stack(stack);
    }
    item->decrease_stack(stack);
}

Item* ItemContainer::remove(SlotId slot_id) {
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    Item* item = item_container[slot_id];
    item_container[slot_id] = nullptr;
    item_id_to_slot.erase(item->get_id());
    return item;
}

Item* ItemContainer::remove(SlotId slot_id, uint32_t stack) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    Item* item = item_container[slot_id];
    if (item->stack_difference(stack) <= 0)
        return remove(slot_id);
    item->decrease_stack(stack);
    return item_factory.create(item->get_id(), stack);
}

std::vector<Item*> ItemContainer::remove_all() {
    std::vector<Item*> items;
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        if (!slot_is_free(slot_id))
            items.push_back(remove(slot_id));
    }
    return items;
}

nlohmann::json ItemContainer::get_data() const {
    nlohmann::json json_inv;
    json_inv["items"] = nlohmann::json::array();
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        if (slot_is_free(slot_id)) {
            json_inv["items"].push_back({{"type", TYPE_INVALID}});
        } else {
            json_inv["items"].push_back(get_item(slot_id).get_data());
        }
    }
    json_inv["curr_gold"] = gold->get_stack();
    return json_inv;
}

nlohmann::json ItemContainer::get_persist_data() const {
    nlohmann::json json_inv;
    inventory_t inventory = {};
    Item item;
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        if (slot_is_free(slot_id)) {
            inventory.items_ids[slot_id] = 0;
            inventory.items_stacks[slot_id] = 0;
        } else {
            item = get_item(slot_id);
            inventory.items_ids[slot_id] = item.get_id();
            inventory.items_stacks[slot_id] = item.get_stack();
        }
    }
    inventory.current_gold = gold->get_stack();
    json_inv = inventory;
    return json_inv;
}

bool ItemContainer::slot_is_free(SlotId slot_id) const {
    return (item_container[slot_id] == nullptr) ? true : false;
}

bool ItemContainer::has_item(ItemId item_id) {
    return item_id_to_slot.count(item_id);
}

const Item& ItemContainer::get_item(SlotId slot_id) const {
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    return *item_container[slot_id];
}

SlotId ItemContainer::get_available_slot(ItemId item_id) {
    if (has_item(item_id))
        return item_id_to_slot.at(item_id);
    for (SlotId slot_id = 0; slot_id < item_container.size(); slot_id++) {
        if (slot_is_free(slot_id)) {
            return slot_id;
        }
    }
    throw FullItemContainerException();
}

void ItemContainer::add_gold(Gold* other_gold) {
    gold->increase_stack(other_gold->get_stack());
    other_gold->set_stack(0);
}

void ItemContainer::add_gold(Gold* other_gold, uint32_t stack) {
    if (other_gold->get_stack() <= stack) {
        add_gold(other_gold);
    } else {
        gold->increase_stack(stack);
        other_gold->decrease_stack(stack);
    }
}
unsigned int ItemContainer::get_gold_stack() const {
    return gold->get_stack();
}

Gold* ItemContainer::remove_gold() {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    Gold* new_gold = static_cast<Gold*>(
        item_factory.create(gold->get_id(), gold->get_stack()));
    gold->set_stack(0);
    return new_gold;
}

Gold* ItemContainer::remove_gold(uint32_t stack) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    if (gold->stack_difference(stack) <= 0)
        return remove_gold();
    gold->decrease_stack(stack);
    return static_cast<Gold*>(item_factory.create(gold->get_id(), stack));
}
