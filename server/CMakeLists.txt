cmake_minimum_required(VERSION 2.8)

project(aoserver)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")

add_subdirectory(../include build)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(server
  client_id_set.cpp
  client_initializer_handler.cpp
  entity.cpp
  game_server.cpp
  game_loop.cpp
  map_manager.cpp
  map.cpp
  movement_handler.cpp
  player.cpp
  server_manager.cpp
  session.cpp
  th_broadcaster.cpp
  th_client_accepter.cpp
  th_dispatcher.cpp
  th_observer.cpp
  action_move.cpp
  map_monitor.cpp
  command_handler.cpp
  event_factory.cpp
  client_drop_handler.cpp
  character_manager.cpp
  clients_monitor.cpp
  th_event_handler.cpp
  map_changer.cpp
  change_map_handler.cpp
)

target_link_libraries(server
  network
)

add_executable (aoserver
  main.cpp
)

target_link_libraries(aoserver server)

install(DIRECTORY assets DESTINATION ${CMAKE_BINARY_DIR})
install(DIRECTORY database DESTINATION ${CMAKE_BINARY_DIR})