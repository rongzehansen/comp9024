// TODO: Add any extra #includes that you need

#include "stack.h"
#include <stdlib.h>
#include <string.h>

// TODO: Add your data structure definitions

typedef struct StackNode {
    string               dat;
    struct StackNode    *next;
} StackNode, *Node;

typedef struct StackRepr {
    Node                 top;
} StackRepr;

// TODO: Fill in these function stubs


stack stack_create() {
    stack s = malloc(sizeof(StackRepr));
    if (s == NULL) {
        return NULL;
    }
    s->top = NULL;
    return s;
}

void stack_destroy(stack s) {
    while (s->top != NULL) {
        Node tmp = s->top;
        s->top = s->top->next;
        free(tmp->dat);
        free(tmp);
    }
    free(s);
}

void stack_push(stack s, string dat) {
    Node new = malloc(sizeof(StackNode));
    if (new == NULL) {
        return;
    }
    new->dat = malloc(strlen(dat) + 1);
    strcpy(new->dat, dat);
    new->next = s->top;
    s->top = new;
}

string stack_pop(stack s) {
    if (s->top == NULL) {
        return NULL;
    }
    Node tmp = s->top;
    s->top = s->top->next;
    string dat = tmp->dat;
    free(tmp);
    return dat;
}

string stack_peek(stack s) {
    if (s->top == NULL) {
        return NULL;
    }
    return s->top->dat;
}

bool stack_empty(stack s) {
    return (s->top == NULL);
}
