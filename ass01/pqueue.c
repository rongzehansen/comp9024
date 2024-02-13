// TODO: Add any extra #includes that you need

#include "pqueue.h"
#include <stdlib.h>
#include <string.h>

// TODO: Add your data structure definitions

typedef struct PQueueNode {
    string              dat;
    priority            prio;
    struct PQueueNode  *next;
} PQueueNode, *Node;

struct PriorityQueueRepr {
    Node                head;
};

// TODO: Fill in these function stubs


pqueue pqueue_create() {
    pqueue pq = malloc(sizeof(struct PriorityQueueRepr));
    pq->head = NULL;
    return pq;
}

void pqueue_destroy(pqueue pq) {
    Node curr = pq->head;
    while (curr != NULL) {
        Node next = curr->next;
        free(curr->dat);
        free(curr);
        curr = next;
    }
    free(pq);
}

bool pqueue_contains(pqueue pq, string dat) {
    Node curr = pq->head;
    while (curr != NULL) {
        if (strcmp(curr->dat, dat) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void pqueue_update_priority(pqueue pq, string dat, priority prio) {
    Node curr = pq->head;
    while (curr != NULL) {
        if (strcmp(curr->dat, dat) == 0) {
            curr->prio = prio;
            break;
        }
        curr = curr->next;
    }
}

void pqueue_join(pqueue pq, string dat, priority prio) {
    if (pqueue_contains(pq, dat)) {
        pqueue_update_priority(pq, dat, prio);
    }
    Node new = malloc(sizeof(PQueueNode));
    new->dat = malloc(strlen(dat) + 1);
    strcpy(new->dat, dat);
    new->prio = prio;
    new->next = NULL;

    if (pq->head == NULL || prio < pq->head->prio) {
        new->next = pq->head;
        pq->head = new;
    } else {
        Node curr = pq->head;
        while (curr->next != NULL && curr->next->prio <= prio) {
            curr = curr->next;
        }
        new->next = curr->next;
        curr->next = new;
    }
}

string pqueue_leave(pqueue pq) {
    if (pq->head == NULL) {
        return NULL;
    }
    Node head = pq->head;
    string dat = head->dat;
    pq->head = pq->head->next;
    free(head);
    return dat;
}

string pqueue_peek(pqueue pq) {
    if (pq->head == NULL) {
        return NULL;
    }
    return pq->head->dat;
}

bool pqueue_empty(pqueue pq) {
    return pq->head == NULL;
}
