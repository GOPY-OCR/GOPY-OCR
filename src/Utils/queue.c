#include "queue.h"

queue *queue_create(){
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void queue_free(queue *queue){
    while(!queue_is_empty(queue)){
        free(queue_dequeue(queue));
    }
    free(queue);
}

void queue_enqueue(queue *queue, void *data){
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    node->data = data;
    node->next = NULL;
    if (queue->size == 0){
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
}
void *queue_dequeue(queue *queue){
    if (queue->size == 0){
        return NULL;
    }
    queue_node *node = queue->head;
    void *data = node->data;
    queue->head = node->next;
    free(node);
    queue->size--;
    return data;
}

int queue_is_empty(queue *queue){
    return queue->size == 0;
}
