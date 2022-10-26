#pragma once
#include <stdlib.h>
#include <stddef.h>

typedef struct queue_node {
    struct queue_node *next;
    void *data;
} queue_node;

typedef struct{
    queue_node *head;
    queue_node *tail;
    int size;
}queue;

queue *queue_create();
void queue_free(queue *queue);

void queue_enqueue(queue *queue, void *data);
void *queue_dequeue(queue *queue);

int queue_is_empty(queue *queue);
