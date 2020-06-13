add_library(engine
  actor.cpp
  animation_pack.cpp
  camera.cpp
  decoration.cpp
  entity_factory.cpp
  map.cpp
  renderizable_object.cpp
  resource_manager.cpp
)


target_link_libraries(engine
  components
  sdlutil
  ecs
  network
)
