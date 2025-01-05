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
#include <queue.h>

#include "HTTP_Server.h"
#include "Response.h"
#include "Routes.h"

// Thread pool size
#define THREAD_POOL_SIZE 4

// Struct to pass data to threads
typedef struct {
    int client_socket;
    struct Route *route;
} ThreadArgs;

// Task queue and synchronization
Queue task_queue;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

// Worker thread function
void *worker_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&queue_mutex);

        // Wait for tasks in the queue
        while (is_queue_empty(&task_queue)) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        // Get a task from the queue
        ThreadArgs *task = (ThreadArgs *)dequeue(&task_queue);

        pthread_mutex_unlock(&queue_mutex);

        // Handle the client
        int client_socket = task->client_socket;
        struct Route *route = task->route;

        // Read client message
        char client_msg[1024];
        read(client_socket, client_msg, sizeof(client_msg));
        printf("Client: %s\n", client_msg);

        // Parse HTTP method and route
        char *method = NULL, *urlRoute = NULL;
        char *client_http_header = strtok(client_msg, "\n");
        printf("\n%s\n", client_http_header);

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

        // Determine the response template
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

        // Send the response
        char *response_data = render_static_file(template);
        char http_header[4096] = "HTTP/1.1 200 OK\r\n";
        strcat(http_header, "Content-Type: text/html\r\n\r\n");
        strcat(http_header, response_data);
        strcat(http_header, "\r\n\r\n");

        send(client_socket, http_header, strlen(http_header), 0);
        printf("Response sent successfully: %s\n", http_header);

        close(client_socket);
        free(response_data);
        free(task);
    }
    return NULL;
}


int main() {

    // Create a thread pool
    pthread_t thread_pool[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        if (pthread_create(&thread_pool[i], NULL, worker_thread, NULL) != 0) {
            perror("Error creating thread");
            return 1;
        }
    }

    // initialize the task queue
    init_queue(&task_queue);


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

        // Add the client socket to the task queue
        pthread_mutex_lock(&queue_mutex);
        // task_queue.push(args);
        enqueue(&task_queue, args);
        pthread_cond_signal(&queue_cond);
        pthread_mutex_unlock(&queue_mutex);
    }

    return 0;
}
