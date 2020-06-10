cmake_minimum_required(VERSION 2.8)

project(aoclient)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_subdirectory(engine)

add_subdirectory(engine/SDL)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(game
  game_client.cpp
)

target_link_libraries(game 
  sdlutil
  engine
)

add_executable (aoclient
  main.cpp
)

target_link_libraries(aoclient game SDL2 SDL2_image SDL2_ttf)

install(DIRECTORY assets ind DESTINATION ${CMAKE_BINARY_DIR})
