# HTTP-Server

HTTP (Hypertext Transfer Protocol) is the foundation of data communication on the World Wide Web. It is an application layer protocol that allows web clients (such as browsers) and servers to communicate with each other. HTTP is a stateless protocol, meaning each request from a client to the server is independent and contains all the necessary information for the server to understand it.

---

## Objectives

1. Understand the core concepts of HTTP and socket programming.
2. Implement an HTTP server in C using sockets.
3. Provide clear examples to demonstrate each step of socket programming.
4. Enable multithreading to handle concurrent client requests.
5. Design the code to be modular and reusable for future scalability.

---

## Steps to Cover for Socket Programming:

1. Create a socket
2. Bind the socket to an address
3. Listen on the address
4. Block on `accept()` until a connection is made
5. Read on the connected socket
6. Figure out how to respond
7. Write back on the connected socket
8. Close the connection
9. Go back to blocking on `accept()`

---

## Step 1: How to Create a Socket in C

### What is a "Socket"?

A socket is like a "doorway" for communication between processes or devices. It can be created using the `sys/socket.h` header file.

To create a socket in C, use the following function:

```c
int sockfd = socket(domain, type, protocol);
```

### Parameters:

- **`sockfd`**: A file descriptor that acts as a label for the socket.
- **`domain`**: Determines the communication domain:
  - `AF_LOCAL`: Communication between processes on the same computer.
  - `AF_INET`: Communication using IPv4.
  - `AF_INET6`: Communication using IPv6.
- **`type`**: Specifies how data is sent:
  - `SOCK_STREAM`: Uses TCP, ensuring data arrives in order and without errors.
  - `SOCK_DGRAM`: Uses UDP, which is faster but doesn’t guarantee reliability.
- **`protocol`**: Typically set to `0`, allowing the default protocol for the specified domain and type to be used.

---

## Step 2: Binding the Socket to an Address

Binding a socket associates it with a specific IP address and port so it can send and receive data. This step is crucial for server sockets, as clients need to know where to connect.

### Address Structure:

The `sockaddr_in` structure specifies the socket's address properties for IPv4.

```c
struct sockaddr_in server_addr;

memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure

server_addr.sin_family = AF_INET;            // IPv4
server_addr.sin_port = htons(PORT);          // Port number (convert to network byte order)
server_addr.sin_addr.s_addr = INADDR_ANY;    // Bind to all available interfaces
```

---

## Step 3: Listen on the Address

Prepare the socket to accept incoming connections using the `listen()` function:

```c
int listen(int sockfd, int backlog);
```

---

## Step 4: Block on Accept Until a Connection is Made

When the server calls the `accept()` function, it enters a waiting state (blocks) until a client connects.

---

## Step 5: Read on the Connected Socket

After establishing the connection, use the `read()` function to read data sent by the client.

---

## Step 6: Figure Out How to Respond

Decide on the server’s response based on the data received.

---

## Step 7: Write Back on the Connected Socket

Use the `send()` function to send data back to the client.

---

## Step 8: Close the Connection

Close the connection using the `close()` function to release resources.

---

## Step 9: Go Back to Blocking on Accept

After closing the connection, return to `accept()` to handle new client connections.

---

## HTTP Implementation

HTTP follows a request-response model where the client sends a request, and the server responds. Each HTTP request/response consists of headers, a body, and sometimes status codes.

### HTTP Methods:

- **GET**: Retrieve data.
- **POST**: Send data to create/modify resources.

---

## Multithreading for Concurrent Requests

To handle multiple client requests concurrently, implement multithreading using `pthread` in C.

---

## Installation

To set up and run the HTTP server on your system, follow these steps:

### Prerequisites:

1. **Operating System**: Any Unix-based system (Linux/MacOS) or Windows with a compatible compiler.
2. **Compiler**: GCC or any C compiler installed.
3. **Libraries**: Ensure the `pthread` library is available.

### Steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/HTTP-Server.git
   cd HTTP-Server
   ```

2. Compile the server code:

   ```bash
   gcc -o http_server server.c -lpthread
   ```

3. Run the server:

   ```bash
   ./http_server
   ```

4. Test the server:

   ```bash
   curl http://localhost:8080/home
   ```

---

## Contributing

We welcome contributions to improve the HTTP Server! Please follow the guidelines below:

### How to Contribute:

1. Fork the repository.
2. Clone your fork locally.
3. Create a new branch for your changes.
4. Make your changes and commit them.
5. Push to your fork and create a pull request.

### Contribution Guidelines:

- Follow a consistent coding style.
- Ensure that your code compiles without warnings or errors.
- Test your changes thoroughly before submitting.

---

## Future Improvements

1. **Enhance Multithreading**: Use a thread pool for better performance.
2. **Add HTTPS Support**: Integrate SSL/TLS for secure communication.
3. **Implement Unit Testing**: Add unit tests for core HTTP server functionalities.
4. **Improve Route Handling**: Use dynamic routing tables or configurations.

---
