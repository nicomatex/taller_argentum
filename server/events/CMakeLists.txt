add_subdirectory(../game game)

add_library(events
  command_handler.cpp
  event_factory.cpp
  client_drop_handler.cpp
  change_map_handler.cpp
  creation_handler.cpp
  attack_handler.cpp
  movement_handler.cpp
  client_initializer_handler.cpp
  disconnect_handler.cpp
  inventory_handler.cpp
  pickup_loot_handler.cpp
  drop_loot_handler.cpp
  resuscitate_handler.cpp
  unequip_handler.cpp
  heal_handler.cpp
  sell_handler.cpp
  buy_handler.cpp
  list_handler.cpp
  use_ability_handler.cpp
  deposit_item_handler.cpp
  withdraw_item_handler.cpp
  deposit_gold_handler.cpp
  withdraw_gold_handler.cpp
  meditate_handler.cpp
)

target_link_libraries(events
  game
)
