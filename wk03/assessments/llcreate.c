#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int data;
  struct node *next;
} NodeT;

void showLL(NodeT *list) {
  NodeT *p;
  if (list) {
    printf("List is ");
    for (p = list; p != NULL; p = p->next) {
      printf("%d", p->data);
      if (p->next) {
        printf("-->");
      }
    }
  }
}

NodeT *joinLL(NodeT *list, int v) {
  NodeT *curr = list;
  NodeT *new = malloc(sizeof(NodeT));
  assert(new != NULL);
  new->data = v;
  new->next = NULL;
  if (list == NULL) {
    list = new;
  } else {
    while (curr->next)
      curr = curr->next;
    curr->next = new;
  }
  return list;
}

int main(void) {
  NodeT *all = NULL;
  int x = 0;
  while (true) {
    printf("Enter an integer: ");
    if (scanf("%d", &x) > 0) {
      all = joinLL(all, x);
    } else {
      break;
    }
  }
  printf("Done. ");
  showLL(all);
  return 0;
}
