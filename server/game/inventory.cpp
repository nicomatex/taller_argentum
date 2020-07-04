#include "inventory.h"
#include <iomanip>
#include "../server_manager.h"

const char* FullInventoryException::what() const throw() {
    return "Inventory is full!";
}

const char* EmptySlotException::what() const throw() {
    return "Slot is empty!";
}

Inventory::Inventory() {
    inventory = {};
}

Inventory::Inventory(const nlohmann::json& inv_json) : Inventory() {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    inventory_t inventory = inv_json;
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        ItemId item_id = inventory.items_ids[slot_id];
        if (item_id == 0)
            continue;  // El 0 es un id invalido (ausencia)
        uint32_t stack = inventory.items_stacks[slot_id];
        this->add(item_factory.create(item_id, stack));
    }
}

Inventory::~Inventory() {
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        delete inventory[slot_id];
    }
}

void Inventory::add(Item* item) {
    ItemId item_id = item->get_id();
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        inventory[slot_id] = item;
        item_id_to_slot[item_id] = slot_id;
    } else {
        inventory[slot_id]->increase_stack(item->get_stack());
        item->set_stack(0);
        delete item;  //?
    }
}

void Inventory::add(Item* item, uint32_t stack) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    ItemId item_id = item->get_id();
    if (item->get_stack() <= stack)
        add(item);  // estoy agregando todo el item
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        inventory[slot_id] = item_factory.create(item_id, stack);
        item_id_to_slot[item_id] = slot_id;
    } else {
        inventory[slot_id]->increase_stack(stack);
    }
    item->decrease_stack(stack);
}

/*
    No es posible tener varios stacks del mismo item spliteados en el inventario

void Inventory::add(Item* item, SlotId slot_id) {
    ItemId item_id = item->get_id();
    if (slot_is_free(slot_id)) {
        inventory[slot_id] = item;
        item_id_to_slot[item_id] = slot_id;
    } else {
        if (item_id != inventory[slot_id]->get_id())
            throw std::exception();
        inventory[slot_id]->increase_stack(item->get_stack());
        item->set_stack(0);
        delete item;  //?
    }
}
*/
Item* Inventory::remove(SlotId slot_id) {
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    Item* item = inventory[slot_id];
    inventory[slot_id] = nullptr;
    item_id_to_slot.erase(item->get_id());
    return item;
}

Item* Inventory::remove(SlotId slot_id, uint32_t stack) {
    ServerManager& server_manager = ServerManager::get_instance();
    ItemFactory& item_factory = server_manager.get_item_factory();
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    Item* item = inventory[slot_id];
    if (item->stack_difference(stack) <= 0)
        return remove(slot_id);
    item->decrease_stack(stack);
    return item_factory.create(item->get_id(), stack);
}

nlohmann::json Inventory::get_data() const {
    nlohmann::json json_inv;
    json_inv["items"] = nlohmann::json::array();
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id)) {
            json_inv["items"].push_back({{"type", TYPE_INVALID}});
        } else {
            json_inv["items"].push_back(get_item(slot_id).get_data());
        }
    }
    return json_inv;
}

nlohmann::json Inventory::get_persist_data() const {
    nlohmann::json json_inv;
    inventory_t inventory = {};
    Item item;
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id)) {
            inventory.items_ids[slot_id] = 0;
            inventory.items_stacks[slot_id] = 0;
        } else {
            item = get_item(slot_id);
            inventory.items_ids[slot_id] = item.get_id();
            inventory.items_stacks[slot_id] = item.get_stack();
        }
    }
    json_inv = inventory;
    return json_inv;
}

bool Inventory::slot_is_free(SlotId slot_id) const {
    return (inventory[slot_id] == nullptr) ? true : false;
}

bool Inventory::has_item(ItemId item_id) {
    return item_id_to_slot.count(item_id);
}

const Item& Inventory::get_item(SlotId slot_id) const {
    if (slot_is_free(slot_id))
        throw EmptySlotException();
    return *inventory[slot_id];
}

SlotId Inventory::get_available_slot(ItemId item_id) {
    if (has_item(item_id))
        return item_id_to_slot.at(item_id);
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id)) {
            return slot_id;
        }
    }
    throw FullInventoryException();
}
