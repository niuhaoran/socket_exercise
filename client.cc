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

const char ACK = 0x6; //this is the Acknowledge byte in ASCII

int main(int argc, char *argv[]) {
	/*
	 * Create a socket by opening a TCP connection (SOCK_STREAM)
	 * over the internet (AF_INET)
	 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cerr << "opening stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	sockaddr_in server;
	server.sin_family = AF_INET;

	/*-----------------------------------------------------------------------*/

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	u_short port_num;
	cout << "Connect to port: ";
	cin >> port_num;
	server.sin_port = htons(port_num);

	string junk;
	getline(cin, junk); // throw away the newline so we do not send it later

	if (connect(
			sock, // file descripter
			(sockaddr*) &server, // the strcture defines the IO and the port
			sizeof(server) // the size of the structure
		) == -1) {
		cerr << "connecting stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	/*-----------------------------------------------------------------------*/
	while (1) {
		string message;
		getline(cin, message);
		send (
			sock, // socket file descripter
			message.c_str(),
			message.size(),
			0 // flags
		);

		char val;
		recv(sock, &val, sizeof(val), 0);
		if (val == ACK)
			cout << "Message received!" << endl;
	}
}

