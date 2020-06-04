#ifndef SOCKET_H
#define SOCKET_H

#include <cstddef>
#include <exception>
#include <sys/socket.h>

class Socket {
private:
	int fd;
	explicit Socket(const int fd);
	void setHints(struct addrinfo *hints, const int ai_flags,
				  const int ai_family, const int ai_socktype);
	/*
		Itera las la lista de addrinfo hasta encontrar la dirreción que cumpla
		con los parametros de res, asignando el file descriptor a self.
    	En el caso del servidor hace un bind(), y en el caso del cliente
    	hace un connect().
    	Lanza std::exception() en caso de error.
	*/
	void iterateAddrinfo(struct addrinfo *res, const bool is_server);
	/*
		Encapsula y junta todos los llamados a funciones para obtener un socket
		en funcionamiento, ya sea un cliente o servidor.
		Lanza std::exception() en caso de error.
	*/
	void getWorkingSocket(const char *node, const char *service,
				     const bool is_server);
	
public:
	/*
		Inicializa el fd del socket en INVALID_FD.
	*/
	Socket();
	/*
		Hace close del fd (si es válido), y lo invalida dejándolo en INVALID_FD.
	*/
	~Socket();
	/*
		No copiar
	*/
	Socket(const Socket &copy) = delete;
	Socket& operator=(const Socket &copy) = delete;
	/*
		Movimiento
	*/
	Socket(Socket &&other) noexcept;
	Socket& operator=(Socket &&other);
		
	/*
	 	Asigna una dirección al socket y lo marca como socket pasivo
	 	(lado del servidor).
	 	Lanza std::exception() en caso de error.
	*/
	void bindAndListen(const char *service);
	/*	
		Acepta una conexión.
		Devuelve un socket por movimiento.
		Lanza std::exception() en caso de error.
	*/
	Socket accept();
	/*
		Se conecta a un servidor dada una dirección y un servicio o puerto
		(lado del cliente)
		Lanza std:exception en caso de error.
	*/
	void connect(const char *host_name, const char *service);
	/*
		Intenta enviar length bytes a traves del socket.
		Devuelve cantidad de bytes enviados.
		Lanza std:exception en caso de error.
	*/
	size_t send(const char *buffer, const size_t length) const;
	/*
		Intenta recibir length bytes a traves del socket.
		Devuelve cantidad de bytes recibidos.
		Lanza std:exception en caso de error.
		Lanza ClosedSocketException en caso de socket cerrado.
	*/
	size_t receive(char *buffer, const size_t length) const;
	/*
	 	Cierra los canales de lectura y/o escritura del socket.
	*/
	void shutdown(const int channel);
};

#endif // SOCKET_H
