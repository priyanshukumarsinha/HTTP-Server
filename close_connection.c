/**
 * @brief Closes the given socket connection.
 * 
 * This function attempts to close the specified socket, releasing the resources 
 * associated with the socket. It checks whether the `close()` system call was 
 * successful and prints an appropriate message.
 * 
 * @param socket_fd    The file descriptor of the socket to be closed.
 * 
 * @return int        Returns 0 if successful, or -1 if there is an error.
 */

int close_connection(int socket_fd) {
    if (close(socket_fd) < 0) {
        perror("Error closing socketn\n");
        return -1;
    } else {
        printf("Connection closed.\n");
        return 0;
    }
}