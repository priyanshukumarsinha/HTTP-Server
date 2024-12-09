#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

typedef struct HTTP_Server {
	int socket;
	int port;	
} HTTP_Server;

// Function declaration
void init_server(HTTP_Server* http_server, int port);
// This function is defined in the HTTP_Server.c file
// This function uses the above struct to create a socket and bind it to the port
// similar to what is done in the server.c file

#endif