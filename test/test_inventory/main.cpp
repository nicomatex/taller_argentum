#include <exception>
#include <fstream>
#include <iostream>
#include <map>

#include "armor.h"
#include "gold.h"
#include "inventory.h"
#include "item_factory.h"
#include "json.h"
#include "potion.h"
#include "weapon.h"

int main(int argc, char const* argv[]) {
    ItemFactory item_factory("items.json");
    ItemContainer inventory;
    Gold* gold = static_cast<Gold*>(item_factory.create(500, 2000));
    inventory.add(gold);
    Potion* potion = static_cast<Potion*>(item_factory.create(401, 1000));
    inventory.add(potion);
    Potion* potion2 = static_cast<Potion*>(item_factory.create(401, 3000));
    inventory.add(potion2);
    Weapon* weapon = static_cast<Weapon*>(item_factory.create(300, 1));
    inventory.add(weapon);
    std::cout << inventory.get_data() << std::endl;
    std::cout << inventory.get_persist_data() << std::endl;
    std::cout << "\n";
    nlohmann::json inv_json = inventory.get_persist_data();

    ItemContainer inv_from_json(inv_json);
    std::cout << inv_from_json.get_data() << std::endl;
    std::cout << inv_from_json.get_persist_data() << std::endl;
    std::cout << "\n";
    Gold* gold_withdraw = (Gold*)inv_from_json.remove(0, 250);
    std::cout << gold_withdraw->get_data() << std::endl;
    delete gold_withdraw;
    std::cout << inv_from_json.get_data() << std::endl;
    std::cout << inv_from_json.get_persist_data() << std::endl;
    std::cout << "\n";
    Gold* gold_to_add = static_cast<Gold*>(item_factory.create(500, 750));
    inv_from_json.add(gold_to_add, uint32_t(300));
    std::cout << gold_to_add->get_data() << std::endl;
    delete gold_to_add;
    std::cout << inv_from_json.get_data() << std::endl;
    std::cout << inv_from_json.get_persist_data() << std::endl;
    return 0;
}
