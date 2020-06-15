cmake_minimum_required(VERSION 2.8)

project(aoclient)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")

add_subdirectory(engine)

add_subdirectory(engine/SDL)

add_subdirectory(engine/ECS)

add_subdirectory(engine/components)

add_subdirectory(../include build)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(game
  event_factory.cpp
  game_client.cpp
  receive_handler.cpp
)

target_link_libraries(game
  engine
)

add_executable (aoclient
  main.cpp
)

target_link_libraries(aoclient game)

install(DIRECTORY assets ind DESTINATION ${CMAKE_BINARY_DIR})
install(FILES config.json DESTINATION ${CMAKE_BINARY_DIR})