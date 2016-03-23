#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

static const char * data = "Hello World";

int main(int argc, char *argv[]) {
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
	server.sin_port = htons(port); // host to network short);

	/*-----------------------------------------------------------------------*/

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(
			sock, // file descripter
			(sockaddr*) &server, // the strcture defines the IO and the port
			sizeof(server) // the size of the structure
		) == -1) {
		cerr << "connecting stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	while (1) {
		string message;
		getline(cin, message);
		send (
			sock, // socket file descripter
			message.c_str(),
			message.size(),
			0 // flags
		);
	}
}

