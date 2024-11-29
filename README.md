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
The *sockaddr_in* structure is used to specify the socket's address properties, such as IP address, port, and address family.

To define and initialize the sockaddr_in structure:
```C
struct sockaddr_in server_addr;

memset(&server_addr, 0, sizeof(server_addr)); //This clears the structure
// Before initializing the structure, clear its memory to avoid leftover garbage values that might cause undefined behavior

server_addr.sin_family = AF_INET;            // IPv4
server_addr.sin_port = htons(PORT);          // Port number (use htons for network byte order)

// To Bind to a Specific IP Address
// server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

// To Bind to All Available Interfaces
server_addr.sin_addr.s_addr = INADDR_ANY;    // IP address (localhost in this case)
// INADDR_ANY allows the socket to listen on all available network interfaces 
// (e.g., 127.0.0.1 for localhost and any other assigned IP addresses).

```
