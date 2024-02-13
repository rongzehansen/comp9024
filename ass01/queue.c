// TODO: Add any extra #includes that you need

#include "queue.h"
#include <stdlib.h>
#include <string.h>

// TODO: Add your data structure definitions

typedef struct QueueNode {
    string            dat;
    struct QueueNode *next;
} QueueNode, *Node;

typedef struct QueueRepr {
    Node              head;
    Node              tail;
    size_t            size;
} QueueRepr;

// TODO: Fill in these function stubs


queue queue_create() {
    queue q = (QueueRepr *) malloc(sizeof(QueueRepr));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void queue_destroy(queue q) {
    if (q != NULL) {
        while (q->head != NULL) {
            Node tmp = q->head;
            q->head = q->head->next;
            free(tmp->dat);
            free(tmp);
        }
        free(q);
    }
}

void queue_enqueue(queue q, string dat) {
    if (q == NULL || dat == NULL) return;
    Node new = malloc(sizeof(QueueNode));
    if (new == NULL) return;
    new->dat = malloc(strlen(dat) + 1);
    strcpy(new->dat, dat);
    new->next = NULL;
    if (q->tail != NULL) {
        q->tail->next = new;
    }
    q->tail = new;
    if (q->head == NULL) {
        q->head = new;
    }
    q->size++;
}

string queue_dequeue(queue q) {
    if (q == NULL || q->head == NULL) return NULL;
    Node node = q->head;
    string dat = node->dat;
    q->head = node->next;
    if (q->tail == node) {
        q->tail = NULL;
    }
    free(node);
    q->size--;
    return dat;
}

string queue_peek(queue q) {
    if (q == NULL || q->head == NULL) return NULL;
    return q->head->dat;
}

bool queue_empty(queue q) {
    return (q == NULL || q->head == NULL);
}
