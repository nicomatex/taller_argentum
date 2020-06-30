add_library(ui_widgets
  text_box.cpp
  text_input.cpp
  stat_bar.cpp
  icon_grid.cpp
  button.cpp
)


target_link_libraries(ui_widgets
  sdlutil
)
