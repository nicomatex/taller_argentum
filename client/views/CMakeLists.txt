add_subdirectory(game_view)
add_subdirectory(login_view)
add_subdirectory(character_creation_view)

add_library(view_util
  	responsive_scaler.cpp
)

target_link_libraries(view_util
  sdlutil
)


