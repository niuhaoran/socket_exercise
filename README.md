



The included file <netinet/in.h> defines sockaddr_in as:

```cpp
struct sockaddr_in {
	short			sin_family;		// e.g. AF_INET
	unsigned short	sin_port;		// e.g. htons(3490)
	struct in_addr	sin_addr;		// see struct in_addr, below
	char			sin_zero[8];	// zero this if you want to
};

/* Internet address. */
struct in_addr {
	unsigned long s_addr;	// load with inet_aton()
							// address in network byte order
}
```

sin_falimuly is always set to AF_INET.


`struct hostent` is used to represent an entry in the hosts data base.
```cpp
sturct hostent {
	char *h_name		// name of the host.
	char **h_aliases	// alternative names for the host
	int h_addrtype 		// host address type; in practice, its value is always
						// either AF_INET or AF_INET6, with the latter being
						// used for IPv6 hosts.
	int h_length		// length in bytes of each address.
	char **h_addr_list	// vector of addresses for the host. The vector is 
						// terminated by a null pointer.
	char *h_addrtype 	// a synonym for h_addr_list[0]
}
```

## Reference
* Using `exit(EXIT_FAILURE)` makes the code more portable than `exit(1)`
* `reinterpret_cast<char*>` is just type conversion.
* socklen_t is an unsigned opaque integral type of length of at least 32 bits
* The constant INADDR_ANY is the so-called IPv4 wildcard address. The wildcard IP address is useful for applications that bind Internet domain sockets on multihomed hosts. When INADDR_ANY is specified in the bind call,
       the socket will be bound to all local interfaces. 

```cpp
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
```

The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.
The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.

* `in_addr_t inet_addr(const char *cp);`
