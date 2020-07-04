add_library(char_creation_view
    character_creation_view.cpp
    creation_ui_event_handler.cpp
    race_and_class_selector.cpp
    go_back_button.cpp
    request_char_creation_button.cpp
)


target_link_libraries(char_creation_view
  sdlutil
  view_util
  engine
)
