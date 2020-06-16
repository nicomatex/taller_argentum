
# Agregar -Werror -pedantic-errors
FLAGS = -std=c++11 -ggdb -Wall -pedantic 
LDFLAGS = -pthread

INCLUDE = ../include/my_exception.cpp ../include/thread.cpp \
../include/socket.cpp  ../include/socket_exception.cpp \
../include/protocol.cpp ../include/translator.cpp \
../include/th_event_handler.cpp ../include/socket_manager.cpp \
../include/th_socket_sender.cpp ../include/th_socket_receiver.cpp 


include_client = $(INCLUDE) test_client.cpp
include_server = $(INCLUDE) test_server.cpp ../server/th_broadcaster.cpp \
../server/th_client_accepter.cpp ../server/session.cpp \
../server/client_id_set.cpp

ocxx := $(CXX)

CXX = @echo "  CXX $@"; $(ocxx)

LD = $(CXX)


all: client server

client:
	g++ $(FLAGS) $(include_client) -o test_client $(LDFLAGS)

server:
	g++ $(FLAGS) $(include_server) -o test_server $(LDFLAGS)
