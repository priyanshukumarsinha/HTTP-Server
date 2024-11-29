#include <sys/socket.h>  // For socket(), connect(), bind(), listen(), accept()
#include <stdio.h>       // For printf(), perror()
#include <netinet/in.h>  // For struct sockaddr_in, htons, INADDR_ANY
#include <string.h>       // For memset
#include <arpa/inet.h>    // For INADDR_ANY
#include <stdlib.h>
#include <unistd.h> // For close()

#include "create_socket.c"
#include "add_str.c"
#include "bind_socket.c"
#include "listen_PORT.c"
#include "accept_connections.c"
#include "read_data_from_client.c"

const int PORT = 8080;
const int backlog = 3;
const int BUFFER_SIZE = 1024;

int main(){

    // Create the socket (IPv4, TCP)
    int sockfd = createSocket(AF_INET, SOCK_STREAM, 0);

    // Define the server address structure
    struct sockaddr_in server_addr = defineAddress(AF_INET, PORT, INADDR_ANY);

     // Bind the socket to the address
    bind_socket(sockfd, PORT, (struct sockaddr *)&server_addr);

    // Start listening for incoming connections
    listen_PORT(PORT, sockfd, backlog);

    // The server can accept incoming connections here 
    int new_socket = accept_connections(sockfd, (struct sockaddr *)&server_addr);

    // read data from the client
    read_data_from_client(new_socket, BUFFER_SIZE);

    // Close the socket after testing
    printf("Closing the Server ...\n");
    close(sockfd);
    
    return 0;

}