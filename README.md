# HTTP-Server

Steps to cover : 
1. Create a socket
2. Bind the socket to an address
3. Listen on the address
4. Block on Accept until a connection is made
5. Read on the connected socket
6. Figure out how to respond
7. Write back on the connected socket
8. Close the connection
9. Go back to blocking on Accept

![alt text](image-1.png)

Let us move to **Step 1**
## How to Create a Socket in C

Before moving forward, let us understand what a "socket" is?
![alt text](image.png)


A socket is like a "doorway" for communication between processes or devices.

A socket can be created using sys/socket.h header file.

Let us start by initializing the socket first. To create a socket in C, you use the function:
```C
int sockfd = socket(domain, type, protocol)
```

Here,
- **sockfd**: This is a number (integer) that acts like a label for your socket. Think of it like a "file handle" for a file, but for communication instead of file operations.

- **domain**: integer,  This decides where the communication happens:

    - AF_LOCAL: Communication between processes on the same computer (POSIX standard).
    - AF_INET: Communication using IPv4 (e.g., between devices over a network).
    - AF_INET6: Communication using IPv6.

- **type**: This decides how data is sent:
    - SOCK_STREAM: Uses TCP, which ensures data arrives in order and without errors (reliable, connection-oriented).
    - SOCK_DGRAM: Uses UDP, which is faster but doesn’t guarantee reliability or order (unreliable, connectionless).
- **protocol**: Usually set to 0, it specifies the protocol used within the chosen domain. For example, in AF_INET, 0 defaults to IP.

### A little more on Sockets

The value of sockfd (the socket file descriptor) depends on the success or failure of the socket() function call:

- If the socket() function call is **successful**, sockfd will be a **positive integer**. It represents the file descriptor for the newly created socket. File descriptors typically start from 0 and increase, *but 0 is usually reserved for standard input (stdin)*, so a socket's file descriptor will generally be **1 or higher**.
- If the socket() function call **fails**, it **returns -1**. This indicates an error, and you should check errno (a global variable) to determine the reason for the failure.

More details about the Protocol part:
![alt text](image-2.png)

Now Let us move to **STEP 2** 
## Binding the socket to an address

Binding a socket to an address means associating it with a specific IP address and port so it can send and receive data. This is especially important for server sockets, as clients need to know where to connect.

So first we need to set up the address structure.
The *sockaddr_in* structure is used to specify the socket's address properties, such as IP address, port, and address family for IPv4.

For IPv6, the address structure is struct sockaddr_in6 instead of struct sockaddr_in. This structure is used to store IPv6 addresses and associated information.

To define and initialize the sockaddr_in structure:
```C
struct sockaddr_in server_addr;

memset(&server_addr, 0, sizeof(server_addr)); //This clears the structure
// Before initializing the structure, clear its memory to avoid leftover garbage values that might cause undefined behavior

server_addr.sin_family = AF_INET;            // IPv4
server_addr.sin_port = htons(PORT);          // Port number (use htons for network byte order)
// When you set the port number in sockaddr_in, remember to use htons() to ensure the port is in network byte order.

// To Bind to a Specific IP Address
// server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

// To Bind to All Available Interfaces
server_addr.sin_addr.s_addr = INADDR_ANY;    // IP address (localhost in this case)
// INADDR_ANY allows the socket to listen on all available network interfaces 
// (e.g., 127.0.0.1 for localhost and any other assigned IP addresses).

```



Once the socket is created and the address structure (sockaddr_in) is defined, the next step is to bind the socket to a specific address and port. This is done using the bind() function.

The function prototype is:
```C
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

```

Here,
- **sockfd**: The socket file descriptor returned from the socket() function. This identifies the socket you want to bind.
- **addr**: A pointer to a struct sockaddr (usually struct sockaddr_in for IPv4) that contains the address to bind the socket to. This structure typically includes the IP address and port number.
- **addrlen**: The size of the address structure (struct sockaddr_in), which is typically sizeof(struct sockaddr_in). This tells the bind() function how much memory to read when accessing the address information.

Now Lets Move to **STEP 3**
## Listen on the Address

Once a socket is bound to an address and port using the bind() function, the next step is to prepare the socket to accept incoming connections. This is done using the listen() function.

It can be done using:
```C
int listen(int sockfd, int backlog);
```
- It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. 

- The backlog, specifies the maximum number of pending connections that can be queued up before the system starts rejecting new connection requests. 

- If the queue reaches its limit and a new connection attempt is made, the client might receive an error such as ECONNREFUSED, which indicates that the server cannot accept any more connections at that time.

When a server calls listen(), it transitions the socket into a *passive mode*, which means that the server is no longer attempting to establish connections but instead is waiting for incoming connection requests from clients.

After calling listen(), the server is effectively saying, *"I'm ready to accept incoming connections."* It waits for clients to attempt to connect to the server.



Now we can test the server and start it to listen on the specified PORT.
So lets create a server.c file and add all these functionalities to the server file.


