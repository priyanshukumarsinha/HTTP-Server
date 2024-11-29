
/**
 * @brief Binds the given socket to the provided address and port.
 * 
 * This function binds a socket (identified by the sockfd) to a specific 
 * address and port. It uses the provided sockaddr structure to perform 
 * the binding.
 * 
 * @param sockfd         The socket file descriptor created using socket().
 * @param PORT           The port number to bind to.
 * @param server_addr    A pointer to a sockaddr structure (either IPv4 or IPv6).
 * 
 * @return int           Returns 0 if successful, or -1 if binding fails.
 */

int bind_socket(int sockfd, int PORT, const struct sockaddr *server_addr){

    // Bind the socket to the provided address and port
    if (bind(sockfd, server_addr, sizeof(*server_addr)) < 0) {
        perror("Bind failed");
        return -1;
    }
    else{
        printf("Socket successfully Bound to PORT : %d\n", PORT);
        return 0;
    }
}