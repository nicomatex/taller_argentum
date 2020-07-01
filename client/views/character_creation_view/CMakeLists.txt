add_library(char_creation_view
    character_creation_view.cpp
)


target_link_libraries(char_creation_view
  sdlutil
  view_util
  engine
)
