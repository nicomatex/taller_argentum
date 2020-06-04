cmake_minimum_required(VERSION 2.8)

project(aoclient)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_library(sdlutil
  sdl_window.cpp
  sdl_area.cpp
  sdl_texture.cpp
  sdl_error.cpp
  sdl_timer.cpp
  sdl_animated_sprite.cpp
  sdl_text.cpp
  sdl_texture_loader.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (aoclient
  main.cpp  
)

target_link_libraries(aoclient sdlutil SDL2 SDL2_image SDL2_ttf)
