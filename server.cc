#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>

#include <array>
#include <iostream>

using namespace std;

const char ACK = 0x6; //this is the Acknowledge byte in ASCII

int main() {
	/*
	 * Create a socket by opening a TCP connection (SOCK_STREAM)
	 * over the internet (AF_INET)
	 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cerr << "opening stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	struct sockaddr_in server; // this structure defines how do we connect
	server.sin_family = AF_INET;

	/*-----------------------------------------------------------------------*/
	/*
	 * A port of zero request that the operating system pick its own port
	 */
	server.sin_port = htons(0);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	/*
	 * Request a port from the operating system
	 */
	if (::bind(
			sock, // the socket we want to listen over
			(sockaddr*) &server, // the structure that contains the port number
			sizeof(server) // the size of the structure
		) == -1) {
		cerr << "binding stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	/*
	 * Start acceptign connections.
	 */
	listen(sock, 0);

	/*
	 * Print the port
	 */
	sockaddr_in addr; // that addr struct where we specify the port and IP
	socklen_t len = sizeof(addr);
	getsockname(
		sock,				// the socket file descriptor
		(sockaddr*) &addr,	// the struct we want to put our info into
		&len 				// the amount of data the OS put into the struct
	);
	u_short port = ntohs(addr.sin_port); // Big-endian to Little-endian
	cout << "Server running on port " << port << endl;

	/*-----------------------------------------------------------------------*/
	while (1) {
		/*
		 * Wait for a client to connect on the socket
		 */
		int msgsock = accept(sock, 0, 0);
		char buf[4096];
		while (1) {
			size_t bytesWritten = recv(
				msgsock, // socket file descripter
				buf,
				sizeof(buf) - 1,
				0 // flags
			);

			if (buf == '\0')
				break;

			buf[bytesWritten] = 0;
			cout << buf << endl;

			send(msgsock, &ACK, 1, 0);
		}
	}
}