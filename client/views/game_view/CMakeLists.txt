add_library(game_view
    game_view.cpp
    chat.cpp
    ui_event_handler.cpp
    hud.cpp
    cast_button.cpp
    inventory.cpp
    item_qty_grid.cpp
    item_button.cpp
    item_button_grid.cpp
)


target_link_libraries(game_view
  sdlutil
  view_util
  engine
)
