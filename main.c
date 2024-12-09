#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#include "HTTP_Server.h"
#include "Response.h"
#include "Routes.h"

int main() {
	// initiate HTTP_Server
	HTTP_Server http_server;
	init_server(&http_server, 6969);

	// accept connections
	int client_socket;

	// registering Routes
	struct Route * route = initRoute("/", "index.html"); 
	addRoute(route, "/about", "about.html");

	printf("\n====================================\n");
	printf("=========ALL VAILABLE ROUTES========\n");
	// display all available routes
	inorder(route);


	while (1) {
		client_socket = accept(http_server.socket, NULL, NULL);

		// read data from client
		char client_msg[1024];
		read(client_socket, client_msg, sizeof(client_msg)); 
		// returns the number of bytes read (0 if no data is read) or -1 if an error occurs
		// no use of the return value here

		printf("Client: %s\n", client_msg);


		// parsing client socket header to get HTTP method, route
		char *method = "";
		char *urlRoute = "";
		

		// template
		// stores the path to the file to be served
		// served means the file is sent to the client
		char template[100] = "";
		
		if (strstr(urlRoute, "/static/") != NULL) {
			//strcat(template, urlRoute+1);
			strcat(template, "static/index.css");
		}else {
			struct Route * destination = search(route, urlRoute);
			strcat(template, "templates/");

			if (destination == NULL) {
				strcat(template, "404.html");
			}else {
				strcat(template, destination->value);
			}
		}

		char * response_data = render_static_file(template);

		char http_header[4096] = "HTTP/1.1 200 OK\r\n";

		strcat(http_header, "Content-Type: text/html\r\n\r\n"); // Content type for HTML
		strcat(http_header, response_data);
		strcat(http_header, "\r\n\r\n");

		// respond to client
		send(client_socket, http_header, sizeof(http_header), 0);
		printf("Response sent successfully: %s\n", http_header);
		close(client_socket);
		printf("Reached Here");
		// free(response_data);

	}



    return 0;
}