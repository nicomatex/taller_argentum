cmake_minimum_required(VERSION 2.8)

project(aoserver)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")

add_subdirectory(../include build)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(server
  client_monitor.cpp
  session.cpp
  th_broadcaster.cpp
  th_client_accepter.cpp
  game_server.cpp
)

target_link_libraries(server
  network
)

add_executable (aoserver
  main.cpp
)

target_link_libraries(aoserver game)

