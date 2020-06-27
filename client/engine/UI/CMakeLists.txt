add_library(ui_widgets
  text_box.cpp
  text_input.cpp
  stat_bar.cpp
)


target_link_libraries(ui_widgets
  sdlutil
)
