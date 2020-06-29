add_library(engine
  actor.cpp
  animation_pack.cpp
  camera.cpp
  decoration.cpp
  entity_factory.cpp
  map.cpp
  renderizable_object.cpp
  resource_manager.cpp
  engine_error.cpp
)


target_link_libraries(engine
  components
  sdlutil
  ecs
  ui_widgets
)
