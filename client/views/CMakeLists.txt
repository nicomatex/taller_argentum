add_library(views
  	login_view.cpp
    login_view_ui_handler.cpp
    login_button.cpp
    game_view.cpp
    chat.cpp
    ui_event_handler.cpp
    responsive_scaler.cpp
    hud.cpp
    cast_button.cpp
)


target_link_libraries(views
  sdlutil
  engine
)
