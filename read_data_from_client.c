/**
 * @brief Reads data from the client and prints it to the console.
 * 
 * This function reads up to `BUFFER_SIZE - 1` bytes of data from the connected client
 * socket (`new_socket`). The data is null-terminated to safely print it as a string.
 * If an error occurs during reading, it prints an error message.
 * 
 * @param new_socket    The socket descriptor of the connected client (from accept()).
 * @param BUFFER_SIZE   The size of the buffer used for reading data.
 * 
 * @return int          Returns 0 if data was read successfully, or -1 on error.
 */

int read_data_from_client(int new_socket, int BUFFER_SIZE){
    ssize_t valread;
    char buffer[BUFFER_SIZE]; // Buffer to hold incoming data
    memset(buffer, 0, sizeof(buffer)); // Initialize the buffer to 0

    // Read data from the client
    valread = read(new_socket, buffer, sizeof(buffer) - 1); 
    if (valread < 0) {
        perror("Error reading from socket");
        return -1;
    }

    buffer[valread] = '\0'; // Null-terminate the string to safely print it
    printf("Data Read from Client : \n%s\n", buffer);
    return 0;
}