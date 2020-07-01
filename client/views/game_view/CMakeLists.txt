add_library(game_view
    game_view.cpp
    chat.cpp
    ui_event_handler.cpp
    hud.cpp
    cast_button.cpp
)


target_link_libraries(game_view
  sdlutil
  view_util
  engine
)
