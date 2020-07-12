#include "inventory.h"

#include "item_factory.h"

const char* FullItemContainerException::what() const throw() {
    return "ItemContainer is full!";
}

ItemContainer::ItemContainer() {
    inventory = {};
}

ItemContainer::ItemContainer(const nlohmann::json& inv_json) : ItemContainer() {
    // ItemFactory& item_factory = server_manager.get_item_factory();
    ItemFactory item_factory(
        "items.json");  // en realidad se lo pide al server_manager!!!!
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
        delete inventory[slot_id];
    }
}

void ItemContainer::add(Item* item) {
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

void ItemContainer::add(Item* item, uint32_t stack) {
    ItemId item_id = item->get_id();
    if (item->get_stack() <= stack)
        add(item);  // estoy agregando todo el item
    SlotId slot_id = get_available_slot(item_id);
    if (!has_item(item_id)) {
        Item* new_item = new Item(*item);
        new_item->set_stack(stack);
        inventory[slot_id] = new_item;
        item_id_to_slot[item_id] = slot_id;
    } else {
        inventory[slot_id]->increase_stack(stack);
    }
    item->decrease_stack(stack);
}

/*
    No es posible tener varios stacks del mismo item spliteados en el inventario
*/
void ItemContainer::add(Item* item, SlotId slot_id) {
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

Item* ItemContainer::remove(SlotId slot_id) {
    if (slot_is_free(slot_id))
        throw std::exception();
    Item* item = inventory[slot_id];
    inventory[slot_id] = nullptr;
    item_id_to_slot.erase(item->get_id());
    return item;
}

Item* ItemContainer::remove(SlotId slot_id, uint32_t stack) {
    // ItemFactory& item_factory = server_manager.get_item_factory();
    ItemFactory item_factory(
        "items.json");  // en realidad se lo pide al server_manager!!!!
    if (slot_is_free(slot_id))
        throw std::exception();
    Item* item = inventory[slot_id];
    if (item->stack_difference(stack) <= 0)
        return remove(slot_id);
    item->decrease_stack(stack);
    Item* new_item = new Item(*item);
    new_item->set_stack(stack);
    return new_item;
}

nlohmann::json ItemContainer::get_data() {
    nlohmann::json json_inv;
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id))
            continue;
        json_inv["inventory"][slot_id] = {slot_id,
                                          inventory[slot_id]->get_data()};
    }
    return json_inv;
}

nlohmann::json ItemContainer::get_persist_data() {
    nlohmann::json json_inv;
    inventory_t inventory = {};
    ItemId item_id;
    Item* item;
    uint32_t stack;
    for (SlotId slot_id = 0; slot_id < INV_SIZE; slot_id++) {
        if (slot_is_free(slot_id)) {
            item_id = 0;
            stack = 0;
        } else {
            item = get_item(slot_id);
            item_id = item->get_id();
            stack = item->get_stack();
        }
        inventory.items_ids[slot_id] = item_id;
        inventory.items_stacks[slot_id] = stack;
    }
    json_inv = inventory;
    return json_inv;
}

bool ItemContainer::slot_is_free(SlotId slot_id) {
    return (inventory[slot_id] == nullptr) ? true : false;
}

bool ItemContainer::has_item(ItemId item_id) {
    return item_id_to_slot.count(item_id);
}

Item* ItemContainer::get_item(SlotId slot_id) {
    if (slot_is_free(slot_id))
        return nullptr;
    return inventory[slot_id];
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
