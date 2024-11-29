/**
 * @brief Accepts an incoming client connection and returns a new socket.
 * 
 * This function accepts an incoming connection request from a client and 
 * returns a new socket descriptor that represents the communication channel 
 * with the connected client. The server socket remains open for additional 
 * client connections.
 * 
 * @param server_fd      The server socket file descriptor created by socket().
 * @param address        A pointer to the sockaddr structure containing client information.
 * 
 * @return int           Returns the new socket descriptor for the accepted connection.
 */

int accept_connections(int server_fd, struct sockaddr *address){
    int new_socket;
    socklen_t address_len = sizeof(*address);  // Length of the address structure

    // Accept the connection
    new_socket = accept(server_fd, address, &address_len);
    if(new_socket < 0){
        perror("accept");
        printf("file descriptro : %d\n", server_fd);
        exit(EXIT_FAILURE);
    }

    printf("New connection Established : %d\n", new_socket);
    return new_socket;
}