#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int data;
  struct node *next;
} NodeT;

void splitLL(NodeT *list, NodeT **first, NodeT **second, int length) {
  if (length < 2) {
    *first = list;
    *second = NULL;
    return;
  }
  NodeT *curr = list;
  int nHop = (length - 1) / 2;
  for (int i = 0; i < nHop; i++) {
    curr = curr->next;
  }
  *first = list;
  *second = curr->next;
  curr->next = NULL;
}

void showLL(NodeT *list, int length) {
  NodeT *p;

  if (list) {
    printf("List is ");
    for (p = list; p != NULL; p = p->next) {
      printf("%d", p->data);
      if (p->next) {
        printf("-->");
      }
    }
    NodeT *first = NULL, *second = NULL;
    splitLL(list, &first, &second, length);
    printf("\nFirst part is ");
    for (p = first; p != NULL; p = p->next) {
      printf("%d", p->data);
      if (p->next) {
        printf("-->");
      }
    }
    if (second) {
      printf("\nSecond part is ");
      for (p = second; p != NULL; p = p->next) {
        printf("%d", p->data);
        if (p->next) {
          printf("-->");
        }
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
  int length = 0;
  while (true) {
    printf("Enter an integer: ");
    if (scanf("%d", &x) > 0) {
      all = joinLL(all, x);
      length++;
    } else {
      break;
    }
  }

  printf("Done. ");
  showLL(all, length);
  return 0;
}
