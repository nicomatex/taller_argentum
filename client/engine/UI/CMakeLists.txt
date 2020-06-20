add_library(ui_widgets
  text_box.cpp
  text_input.cpp
)


target_link_libraries(ui_widgets
  sdlutil
)
