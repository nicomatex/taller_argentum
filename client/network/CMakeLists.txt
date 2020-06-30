add_library(client_network
  	event_factory.cpp
  	receive_handler.cpp
)


target_link_libraries(client_network
  inc_network
  engine
)
