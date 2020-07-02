add_library(login_view
    login_button.cpp
    login_view.cpp
    login_view_ui_handler.cpp
    create_character_button.cpp
)


target_link_libraries(login_view
  sdlutil
  view_util
  engine
)
