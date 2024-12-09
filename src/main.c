#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "HTTP_Server.h"
#include "Response.h"
#include "Routes.h"

// Struct to pass data to threads
typedef struct {
    int client_socket;
    struct Route *route;
} ThreadArgs;

// Thread function to handle each client
void *handle_client(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    int client_socket = thread_args->client_socket;
    struct Route *route = thread_args->route;

    // Read data from client
    char client_msg[1024];
    read(client_socket, client_msg, sizeof(client_msg));
    printf("Client: %s\n", client_msg);

    // Parse client socket header to get HTTP method and route
    char *method = NULL;
    char *urlRoute = NULL;
    char *client_http_header = strtok(client_msg, "\n");

    printf("\n\n%s\n\n", client_http_header);

    char *header_token = strtok(client_http_header, " ");
    int header_parse_counter = 0;

    while (header_token != NULL) {
        switch (header_parse_counter) {
            case 0:
                method = header_token;
                break;
            case 1:
                urlRoute = header_token;
                break;
        }
        header_token = strtok(NULL, " ");
        header_parse_counter++;
    }

    printf("The method is %s\n", method);
    printf("The route is %s\n", urlRoute);

    // Template
    char template[100] = "";
    if (strstr(urlRoute, "/static/") != NULL) {
        strcat(template, "static/index.css");
    } else {
        struct Route *destination = search(route, urlRoute);
        strcat(template, "templates/");

        if (destination == NULL) {
            strcat(template, "404.html");
        } else {
            strcat(template, destination->value);
        }
    }

    char *response_data = render_static_file(template);
    char http_header[4096] = "HTTP/1.1 200 OK\r\n";
    strcat(http_header, "Content-Type: text/html\r\n\r\n");
    strcat(http_header, response_data);
    strcat(http_header, "\r\n\r\n");

    // Respond to client
    send(client_socket, http_header, strlen(http_header), 0);
    printf("Response sent successfully: %s\n", http_header);

    close(client_socket);
    free(response_data);
    free(thread_args);

    return NULL;
}

int main() {
    // Initiate HTTP_Server
    HTTP_Server http_server;
    init_server(&http_server, 6969);

    // Registering Routes
    struct Route *route = initRoute("/", "index.html");
    addRoute(route, "/about", "about.html");

    printf("\n====================================\n");
    printf("=========ALL AVAILABLE ROUTES========\n");
    inorder(route);

    while (1) {
        // Accept a new client connection
        int client_socket = accept(http_server.socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Error accepting client");
            continue;
        }

        // Allocate memory for thread arguments
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args->client_socket = client_socket;
        args->route = route;

        // Create a new thread to handle the client
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, args) != 0) {
            perror("Error creating thread");
            close(client_socket);
            free(args);
            continue;
        }

        // Detach the thread so its resources are cleaned up automatically
        pthread_detach(thread_id);
    }

    return 0;
}
