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

![Socket Programming Steps](image-1.png)

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

### Example:

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
}
```

### Important Details:

- If the `socket()` call **succeeds**, `sockfd` will be a **positive integer** representing the socket’s file descriptor.
- If the `socket()` call **fails**, it returns `-1`. Check the global variable `errno` to diagnose the issue.

![Socket Protocol Details](image-2.png)

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

### Binding the Socket:

Use the `bind()` function to bind the socket to an address:

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

### Example:

```c
if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
}
```

### Parameters:

- **`sockfd`**: Socket file descriptor.
- **`addr`**: Pointer to a `struct sockaddr` containing the address.
- **`addrlen`**: Size of the address structure.

---

## Step 3: Listen on the Address

Prepare the socket to accept incoming connections using the `listen()` function:

```c
int listen(int sockfd, int backlog);
```

### Parameters:

- **`backlog`**: Maximum number of pending connections that can be queued.

### Example:

```c
if (listen(sockfd, 5) < 0) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
}
```

Calling `listen()` transitions the server socket into passive mode, waiting for connection requests.

---

## Step 4: Block on Accept Until a Connection is Made

When the server calls the `accept()` function, it enters a waiting state (blocks) until a client connects.

### Key Points:

- `accept()` returns a new socket descriptor representing the communication channel with the client.
- Use this new socket descriptor for data exchange with the client.

### Example:

```c
int new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
if (new_socket < 0) {
    perror("Accept failed");
    exit(EXIT_FAILURE);
}
```

---

## Step 5: Read on the Connected Socket

After establishing the connection, use the `read()` function to read data sent by the client:

```c
valread = read(new_socket, buffer, 1024 - 1);
printf("%s\n", buffer);
```

### Parameters:

- **`buffer`**: Character array to store the incoming data.
- **`1024-1`**: Ensures space for the null terminator (`\0`).
- **`read()`**: Returns the number of bytes read. A return value of `0` indicates the client has closed the connection.

### Example:

```c
char buffer[1024] = {0};
int valread = read(new_socket, buffer, sizeof(buffer));
printf("Client: %s\n", buffer);
```

---

## Step 6: Figure Out How to Respond

Decide on the server’s response based on the data received. This step varies depending on the application logic.

### Example:

If the server receives "Hello":

```c
if (strcmp(buffer, "Hello") == 0) {
    send(new_socket, "Hi there!", strlen("Hi there!"), 0);
}
```

---

## Step 7: Write Back on the Connected Socket

Use the `send()` function to send data back to the client:

```c
ssize_t send(int sockfd, const void *buffer, size_t len, int flags);
```

### Parameters:

- **`buffer`**: Data to send (e.g., a string).
- **`len`**: Length of the data.
- **`flags`**: Set to `0` for standard behavior.

### Example:

```c
send(new_socket, "HTTP/1.1 200 OK\r\n\r\nHello, World!", 40, 0);
```

![Send Flags](image-3.png)

---

## Step 8: Close the Connection

Close the connection using the `close()` function to release resources:

```c
close(new_socket);
```

### Key Points:

- Closing the connection signals the end of communication.
- The server can continue accepting new connections after closing the current one.

---

## Step 9: Go Back to Blocking on Accept

After closing the connection, return to `accept()` to handle new client connections.

---

## HTTP Implementation

HTTP follows a request-response model where the client sends a request, and the server responds. Each HTTP request/response consists of headers, a body, and sometimes status codes.

### Important Points:

1. The client sends a request for a resource.
2. The server processes the request and sends a response.
3. HTTP is stateless, meaning each request is independent.

### HTTP Methods:

- **GET**: Retrieve data.
- **POST**: Send data to create/modify resources.
- **PUT**: Replace resource data.
- **DELETE**: Remove resources.
- **HEAD**: Retrieve headers only.
- **OPTIONS**: Describe communication options.
- **PATCH**: Partially modify resources.

### HTTP Status Codes:

- **200 OK**: Request was successful.
- **404 Not Found**: Requested resource does not exist.
- **500 Internal Server Error**: Server encountered an error.

### Example:

Client sends:

```
GET /home HTTP/1.1
Host: localhost
```

Server responds:

```
HTTP/1.1 200 OK
Content-Type: text/plain

Welcome to the Home Page!
```

---

## Handling URL Routes and Methods

To handle different routes and HTTP methods dynamically:

1. **Parse the Request**: Extract the URL and method from the client request string.
2. **Route the Request**: Compare the extracted route and method against predefined routes.

### Example Code for Parsing:

```c
char *method = strtok(buffer, " ");
char *urlRoute = strtok(NULL, " ");

if (strcmp(method, "GET") == 0 && strcmp(urlRoute, "/home") == 0) {
    // Handle GET /home
    send(new_socket, "HTTP/1.1 200 OK\r\n\r\nHome Page", 28, 0);
} else {
    send(new_socket, "HTTP/1.1 404 Not Found\r\n\r\n", 28, 0);
}
```

### Key Points:

- Use `strcmp()` to compare the method and URL.
- Respond appropriately based on the matched route.

---

## Multithreading for Concurrent Requests

To handle multiple client requests concurrently, implement multithreading using `pthread` in C.

### Example:

```c
#include <pthread.h>

void *handle_request(void *socket_desc) {
    int new_socket = *(int *)socket_desc;
    char buffer[1024] = {0};

    read(new_socket, buffer, sizeof(buffer));
    printf("Request: %s\n", buffer);

    send(new_socket, "HTTP/1.1 200 OK\r\n\r\nHello, World!", 40, 0);
    close(new_socket);
    free(socket_desc);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Socket setup code here...

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        pthread_t thread_id;
        int *socket_desc = malloc(sizeof(int));
        *socket_desc = new_socket;
        pthread_create(&thread_id, NULL, handle_request, (void *)socket_desc);
        pthread_detach(thread_id);
    }

    return 0;
}
```

### Key Points:

- Use `pthread_create()` to spawn a new thread for each client.
- Use `pthread_detach()` to free thread resources upon completion.
- Ensure thread safety when accessing shared resources.

---

## Future Improvements

1. **Docker Integration**:

   - Create a Dockerfile to containerize the HTTP server application.
   - Ensure compatibility with different environments for easy deployment.

2. **Code Modularization**:

   - Refactor the code into reusable functions and modules.
   - Create a library for socket-based HTTP server functionalities.

3. **Logging and Monitoring**:

   - Implement logging for requests and errors.
   - Add monitoring for server performance and resource usage.

4. **HTTPS Support**:

   - Integrate SSL/TLS for secure communication.

5. **Scalability**:
   - Add load balancing for handling large numbers of concurrent requests.
   - Optimize thread pool management.
