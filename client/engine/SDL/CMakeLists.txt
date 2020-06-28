add_library(sdlutil
  sdl_window.cpp
  sdl_texture.cpp
  sdl_error.cpp
  sdl_timer.cpp
  sdl_animated_sprite.cpp
  sdl_text.cpp
  sdl_texture_loader.cpp
  sdl_music.cpp
  sdl_sfx.cpp
)


target_link_libraries(sdlutil
  SDL2
  SDL2_image
  SDL2_ttf
  SDL2_mixer
)
