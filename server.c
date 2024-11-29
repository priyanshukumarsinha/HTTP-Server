/**
 * @brief Main entry point for the server application.
 * 
 * This function implements a simple TCP server that performs the following actions:
 * - Creates a socket (IPv4, TCP).
 * - Defines and binds the server address to the socket.
 * - Listens for incoming client connections.
 * - Accepts client connections and reads data from the client.
 * - Responds to the client with a message.
 * - Closes the connection after each communication.
 * 
 * The server continuously accepts new connections, reads data from clients, 
 * responds with a message, and then closes the connection.
 * 
 * @return int Returns 0 if the program exits successfully. 
 * 
 * Future improvements may include:
 * - Handling multiple connections simultaneously (e.g., using `fork()` or multi-threading).
 * - Using proper error handling and logging mechanisms.
 * - Implementing more secure communication using SSL/TLS.
 * - Adding better memory management and optimization.
 * - Implementing a more advanced protocol for communication (e.g., HTTP, custom protocol).
 * - Refactoring the server into a modular structure for better scalability.
 */

#include "headers.c"

int main(){

    // Create the socket (IPv4, TCP)
    int sockfd = createSocket(AF_INET, SOCK_STREAM, 0);

    // Define the server address structure
    struct sockaddr_in server_addr = defineAddress(AF_INET, PORT, INADDR_ANY);

     // Bind the socket to the address
    bind_socket(sockfd, PORT, (struct sockaddr *)&server_addr);

    // Start listening for incoming connections
    listen_PORT(PORT, sockfd, backlog);

    while(1){
        // The server can accept incoming connections here 
        int new_socket = accept_connections(sockfd, (struct sockaddr *)&server_addr);

        // read data from the client
        read_data_from_client(new_socket, BUFFER_SIZE);

        // Respond
        char* msg = "Hello from server";
        respond(new_socket, msg);

        // Close the socket after testing
        printf("Closing the Server ...\n");
        close_connection(sockfd);
    }

    // closing the listening socket
    close(sockfd);
    return 0;

}