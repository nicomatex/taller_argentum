add_library(components
  position_component.cpp
  visual_character_component.cpp
  stats_component.cpp
  sound_component.cpp
  visual_npc_component.cpp
)


target_link_libraries(components
  engine
  ecs
)
