cmake_minimum_required(VERSION 2.8)

project(aoclient)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_subdirectory(include/SDL)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(game
  animation_pack.cpp
  visual_component.cpp
  actor.cpp
  camera.cpp
  decoration.cpp
)

add_executable (aoclient
  test.cpp  
)

target_link_libraries(aoclient sdlutil game SDL2 SDL2_image SDL2_ttf)
