#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Define the structure for a queue node
typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

// Define the structure for the queue
typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

// Function declarations
void init_queue(Queue *q);
int is_queue_empty(Queue *q);
void enqueue(Queue *q, void *data);
void *dequeue(Queue *q);

#endif
