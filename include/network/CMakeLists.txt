add_subdirectory(../ include)

add_library(inc_network
  protocol.cpp
  socket.cpp
  socket_exception.cpp
  socket_manager.cpp
  th_socket_receiver.cpp
  th_socket_sender.cpp
  translator.cpp
)

target_link_libraries(inc_network
  include
)
