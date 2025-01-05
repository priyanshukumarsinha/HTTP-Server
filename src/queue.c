#include "queue.h"

// Initialize the queue
void init_queue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Check if the queue is empty
int is_queue_empty(Queue *q) {
    return q->size == 0;
}

// Enqueue an element into the queue
void enqueue(Queue *q, void *data) {
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    new_node->data = data;
    new_node->next = NULL;

    if (q->rear != NULL) {
        q->rear->next = new_node;
    }
    q->rear = new_node;

    if (q->front == NULL) {
        q->front = new_node;
    }

    q->size++;
}

// Dequeue an element from the queue
void *dequeue(Queue *q) {
    if (is_queue_empty(q)) {
        return NULL;
    }

    QueueNode *temp = q->front;
    void *data = temp->data;
    q->front = temp->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return data;
}
