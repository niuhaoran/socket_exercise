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

int main() {
	u_short port = 3778;
	int sock;
	struct sockaddr_in server; // this structure defines how do we connect

	/*
	 * Create a socket by opening a TCP connection (SOCK_STREAM)
	 * over the internet (AF_INET)
	 */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cerr << "opening stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port); // host to network short

	/*-----------------------------------------------------------------------*/

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

			
			buf[bytesWritten] = 0;
			cout << buf << endl;
		}
	}
}