/**
 * @brief Puts the server socket in a listening state.
 * 
 * This function puts the server socket (specified by the sockfd) into a 
 * listening state, allowing the server to accept incoming connection requests 
 * from clients. The function specifies the backlog, which defines the maximum 
 * number of pending connections allowed in the socket's queue.
 * 
 * @param PORT        The port number on which the server will listen.
 * @param sockfd      The socket file descriptor created using socket().
 * @param backlog     The maximum length of the queue for pending connections (default is 3).
 * 
 * @return int        Returns 0 if successful, or exits with failure if the listen() call fails.
 */

int listen_PORT(int PORT, int sockfd, int backlog){

    // Try to listen on the given socket with the specified backlog
    if (listen(sockfd, backlog) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("The Server is listening at PORT: %d\n", PORT);
    return 0;
}