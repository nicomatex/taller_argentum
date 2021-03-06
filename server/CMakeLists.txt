cmake_minimum_required(VERSION 2.8)

project(aoserver)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Werror -Wall -pedantic -g -pthread")

add_subdirectory(network)
add_subdirectory(events)

add_subdirectory(../include/network inc_network)


# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(server
  character_manager.cpp
  clients_names_monitor.cpp
  game_server.cpp
  map_changer.cpp
  server_manager.cpp
  session.cpp
  th_dispatcher.cpp
  th_observer.cpp
)

target_link_libraries(server
  server_network
  game
  events
  inc_network
)

add_executable (aoserver
  main.cpp
)

target_link_libraries(aoserver server)

install(DIRECTORY assets ind database DESTINATION ${CMAKE_BINARY_DIR})
