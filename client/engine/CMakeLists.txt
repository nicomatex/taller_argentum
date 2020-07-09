add_library(engine
  actor.cpp
  animation_pack.cpp
  camera.cpp
  decoration.cpp
  in_game_text.cpp
  entity_factory.cpp
  map.cpp
  renderizable_object.cpp
  resource_manager.cpp
  asset_loading_error.cpp
  sound_system.cpp
  engine_error.cpp
)


target_link_libraries(engine
  components
  sdlutil
  ecs
  ui_widgets
)
