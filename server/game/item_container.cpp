#include "item_container.h"
#include <iomanip>
#include "../server_manager.h"

const char* FullItemContainerException::what() const throw() {
    return "ItemContainer is full!";
}

const char* EmptySlotException::what() const throw() {
    return "Slot is empty!";
}

ItemContainer::ItemContainer() {
    item_container = {};
}

ItemContainer::ItemContainer(const nlohmann::json& inv_json) : ItemContainer() {
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

ItemContainer::~ItemContainer() {
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        delete item_container[slot_id];
    }
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
        add(item);  // estoy agregando todo el item
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        item_container[slot_id] = item_factory.create(item_id, stack);
        item_id_to_slot[item_id] = slot_id;
    } else {
        item_container[slot_id]->increase_stack(stack);
    }
    item->decrease_stack(stack);
}

/*
    No es posible tener varios stacks del mismo item spliteados en el inventario

void ItemContainer::add(Item* item, SlotId slot_id) {
    ItemId item_id = item->get_id();
    if (slot_is_free(slot_id)) {
        item_container[slot_id] = item;
        item_id_to_slot[item_id] = slot_id;
    } else {
        if (item_id != item_container[slot_id]->get_id())
            throw std::exception();
        item_container[slot_id]->increase_stack(item->get_stack());
        item->set_stack(0);
        delete item;  //?
    }
}
*/
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

nlohmann::json ItemContainer::get_data() const {
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

nlohmann::json ItemContainer::get_persist_data() const {
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
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id)) {
            return slot_id;
        }
    }
    throw FullItemContainerException();
}
