add_subdirectory(../game game)

add_library(events
  command_handler.cpp
  event_factory.cpp
  client_drop_handler.cpp
  change_map_handler.cpp
  attack_handler.cpp
  movement_handler.cpp
  client_initializer_handler.cpp
  disconnect_handler.cpp
)

target_link_libraries(events
  game
)
