cmake_minimum_required(VERSION 2.8)

project(aoserver)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_subdirectory(socket)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(game
  game_server.cpp
)

target_link_libraries(game
  engine
)

add_executable (aoserver
  main.cpp
)

target_link_libraries(aoserver game)

install(DIRECTORY assets ind DESTINATION ${CMAKE_BINARY_DIR})
