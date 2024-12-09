#include <sys/socket.h>  // For socket(), connect(), bind(), listen(), accept()
#include <stdio.h>       // For printf(), perror()
#include <netinet/in.h>  // For struct sockaddr_in, htons, INADDR_ANY

#include <string.h>       // For memset
#include <arpa/inet.h>    // For INADDR_ANY
#include <stdlib.h>
#include <unistd.h> // For close()

// functionalities
#include "create_socket.c"
#include "add_str.c"
#include "bind_socket.c"
#include "listen_PORT.c"
#include "accept_connections.c"
#include "read_data_from_client.c"
#include "respond.c"    
#include "close_connection.c"
#include "constants.c"