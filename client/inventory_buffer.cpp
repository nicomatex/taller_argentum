#include "inventory_buffer.h"


InventoryBuffer::InventoryBuffer(){}

InventoryBuffer::~InventoryBuffer(){}

void InventoryBuffer::push(nlohmann::json new_inventory_data){
    std::unique_lock<std::mutex> l(m);
    inventory_data = new_inventory_data;
}


nlohmann::json InventoryBuffer::get_inventory_data(){
    std::unique_lock<std::mutex> l(m);
    return inventory_data;
}