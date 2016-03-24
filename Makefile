.PHONY: all clean

all: server client

server: server.cc
	g++ server.cc -std=c++11 -o server

client: server.cc
	g++ client.cc -std=c++11 -o client

clean:
	rm  -f server client out*