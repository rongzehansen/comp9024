// TODO: Add any extra #includes that you need

#include "set.h"
#include <stdlib.h>
#include <string.h>

// TODO: Add your data structure definitions

typedef struct SetNode {
    string          dat;
    struct SetNode *next;
} SetNode, *Node;

typedef struct SetRepr {
    Node            head;
    size_t          size;
} SetRepr;

// TODO: Fill in these function stubs

set set_create() {
    set s = malloc(sizeof(SetRepr));
    if (s == NULL) {
        return NULL;
    }
    s->head = NULL;
    s->size = 0;
    return s;
}

void set_destroy_helper(Node node) {
    if (node != NULL) {
        set_destroy_helper(node->next);
        free(node->dat);
        free(node);
    }
}

void set_destroy(set s) {
    if (s != NULL) {
        set_destroy_helper(s->head);
        free(s);
    }
}

void set_insert(set s, string dat) {
    if (!set_contains(s, dat)) {
        Node new = malloc(sizeof(SetNode));
        if (new == NULL) {
            return;
        }
        new->dat = malloc(strlen(dat) + 1);
        strcpy(new->dat, dat);
        new->next = s->head;
        s->head = new;
        s->size++;
    }
}

void set_remove(set s, string dat) {
    Node *curr = &s->head;
    while (*curr != NULL) {
        if (strcmp((*curr)->dat, dat) == 0) {
            Node temp = *curr;
            *curr = (*curr)->next;
            free(temp->dat);
            free(temp);
            s->size--;
            return;
        }
        curr = &(*curr)->next;
    }
}

bool set_contains(set s, string dat) {
    Node curr = s->head;
    while (curr != NULL) {
        if (strcmp(curr->dat, dat) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}
