/**
 * @brief Sends a response message to the connected client.
 * 
 * This function sends the provided message to the client over the specified socket.
 * It uses the `send()` system call and prints a confirmation message if successful.
 * If an error occurs during the sending process, it prints an error message.
 * 
 * @param new_socket  The socket file descriptor for the connected client.
 * @param msg         The message to be sent to the client.
 * 
 * @return int        Returns 0 if successful, or -1 if there is an error.
 */



int respond(int new_socket, char* msg, int req){
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s<h1>%s</h1>", response, msg);

    ssize_t bytes_sent = send(new_socket, response, strlen(response), 0);

    // Our server can either respond back with 200 or 500
    // Since for now we are not returning any data which will not be found

    if (bytes_sent < 0) {
        perror("Error sending response");
        return -1;  
    }

    printf("Response sent successfully: %s\n", response);
    return 0;
}