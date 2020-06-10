add_library(engine
  animation_pack.cpp
  visual_component.cpp
  actor.cpp
  camera.cpp
  decoration.cpp
  map.cpp
)

target_link_libraries(engine
  sdlutil
)
