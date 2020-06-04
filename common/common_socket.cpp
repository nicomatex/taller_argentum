#include "common_socket.h"
#include <cstring>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <utility>

#define INVALID_FD -1

const int ACCEPT_QUEUE_LEN = 10;

void Socket::setHints(struct addrinfo *hints, const int ai_flags,
				      const int ai_family, const int ai_socktype) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = ai_family;
	hints->ai_socktype = ai_socktype;
	hints->ai_flags = ai_flags;
}

void Socket::iterateAddrinfo(struct addrinfo *res, const bool is_server) {
	struct addrinfo *rp;
	for (rp = res; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd == INVALID_FD) continue;
        if (is_server) {
        	int opt_val = 1;
        	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt_val,
        			   sizeof(opt_val));
        	if (::bind(fd, rp->ai_addr, rp->ai_addrlen) == 0) {
        		break;	
        	}  
        } else {
        	if (::connect(fd, rp->ai_addr, rp->ai_addrlen) == 0) {
        		break;	
        	}
        }
        ::close(fd);
    }
    freeaddrinfo(res);
	if (!rp) throw std::exception();
}

void Socket::getWorkingSocket(const char *node, const char *service,
					     		  const bool is_server) {
	struct addrinfo hints;
	struct addrinfo *res;
	int status;
	setHints(&hints, is_server ? AI_PASSIVE : 0, AF_INET, SOCK_STREAM);
	status = getaddrinfo(node, service, &hints, &res);
	if (status != 0) throw std::exception();
	iterateAddrinfo(res, is_server);
}

Socket::Socket(): fd(INVALID_FD) {}

Socket::Socket(const int fd): fd(fd) {}

Socket::~Socket() {
	if (fd != INVALID_FD) {
		::close(fd);
	}
	fd = INVALID_FD;
}

Socket::Socket(Socket &&other) noexcept: fd(other.fd) {
	other.fd = INVALID_FD;
}

Socket& Socket::operator=(Socket &&other) {
	if (fd != INVALID_FD) {
		throw std::exception();	
	}
    fd = other.fd;
    other.fd = INVALID_FD;
    return *this;
}

size_t Socket::send(const char *buffer, const size_t length) const {
	size_t tot_sent = 0;
	int actual_sent;
	while (tot_sent != length) {
 		actual_sent = ::send(fd, buffer + tot_sent, length - tot_sent,
 						     MSG_NOSIGNAL);
 		if (actual_sent == -1) throw std::exception();
 		tot_sent += actual_sent;
 	}
 	return tot_sent;
}

size_t Socket::receive(char *buffer, const size_t length) const {
	size_t tot_recv = 0;
	int actual_recv;
	while (tot_recv != length) {
    	actual_recv = ::recv(fd, buffer + tot_recv, length - tot_recv, 0);
    	if (actual_recv == 0) break;
 		if (actual_recv == -1) throw std::exception();
    	tot_recv += actual_recv;
   }
   return tot_recv;
}

void Socket::bindAndListen(const char *service) {
	getWorkingSocket(nullptr, service, true);
	if (::listen(fd, ACCEPT_QUEUE_LEN) == -1) throw std::exception();
}

void Socket::connect(const char *host_name, const char *service) {
	getWorkingSocket(host_name, service, false);
}

Socket Socket::accept() {
	int fd = ::accept(this->fd, nullptr, nullptr);
	if (fd == INVALID_FD) throw std::exception();
	return std::move(Socket(fd));
}

void Socket::shutdown(const int channel) {
	if (fd != INVALID_FD) ::shutdown(fd, channel);
}
