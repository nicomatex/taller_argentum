cmake_minimum_required(VERSION 2.8)

project(aoclient)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")

add_subdirectory(engine)

add_subdirectory(engine/SDL)

add_subdirectory(engine/ECS)

add_subdirectory(engine/components)

add_subdirectory(engine/UI)

add_subdirectory(../include/network inc_network)

add_subdirectory(views)

add_subdirectory(network)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(game
  game_client.cpp
  map_change_buffer.cpp
  chat_buffer.cpp
  game_state_monitor.cpp
)

target_link_libraries(game
  engine
  game_view
  login_view
  char_creation_view
  inc_network
  client_network
)

add_executable (aoclient
  main.cpp
)

target_link_libraries(aoclient game)

install(DIRECTORY assets ind DESTINATION ${CMAKE_BINARY_DIR})
install(FILES config.json DESTINATION ${CMAKE_BINARY_DIR})