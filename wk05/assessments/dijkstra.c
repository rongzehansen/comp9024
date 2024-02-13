#include "PQueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 999999
#define UNDEFINED -1

void dijkstra(Graph g, Vertex source) {
  int *dist = malloc(sizeof(int) * numOfVertices(g));
  memset(dist, 0, sizeof(int) * numOfVertices(g));
  int *prev = malloc(sizeof(int) * numOfVertices(g));
  memset(prev, 0, sizeof(int) * numOfVertices(g));

  dist[source] = 0;
  PQueueInit();

  for (int v = 0; v < numOfVertices(g); v++) {
    if (v != source) {
      dist[v] = INFINITY;
      prev[v] = UNDEFINED;
    }
    joinPQueue(v);
  }

  while (!PQueueIsEmpty()) {
    Vertex u = leavePQueue(dist);
    for (int v = 0; v < numOfVertices(g); v++) {
      if (adjacent(g, u, v)) {
        int alt = dist[u] + adjacent(g, u, v);
        if (alt < dist[v]) {
          dist[v] = alt;
          prev[v] = u;
        }
      } else if (adjacent(g, v, u)) {
        int alt = dist[u] + adjacent(g, v, u);
        if (alt < dist[v]) {
          dist[v] = alt;
          prev[v] = u;
        }
      }
    }
  }
  for (int i = 0; i < numOfVertices(g); i++) {
    // int *path = malloc(sizeof(int) * numOfVertices(g));
    char *path = calloc((numOfVertices(g) * (numOfVertices(g) + 1) / 2) + 1,
                        sizeof(char));
    int idx = 0;
    int j = i;
    path[idx++] = i + '0';
    while (j != source) {
      path[idx++] = '-';
      path[idx++] = prev[j] + '0';
      j = prev[j];
    }
    printf("%d: ", i);
    if (dist[i] != INFINITY) {
      printf("distance = %d, ", dist[i]);
      printf("shortest path : ");
      for (int k = strlen(path) - 1; k >= 0; k--) {
        printf("%c", path[k]);
      }
      printf("\n");

    } else {
      printf("no path\n");
    }
  }
}

int main(void) {
  int V, S = 0;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);
  printf("Enter the source node: ");
  scanf("%d", &S);
  Graph g = newGraph(V);
  while (true) {
    int v = 0, w = 0, weight = 0;
    printf("Enter an edge (from): ");
    if (scanf("%d", &v) > 0) {
      printf("Enter an edge (to): ");
      if (scanf("%d", &w) > 0) {
        printf("Enter the weight: ");
        if (scanf("%d", &weight) > 0) {
          Edge e;
          e.v = v;
          e.w = w;
          e.weight = weight;
          insertEdge(g, e);
        }
      } else {
        break;
      }
    } else {
      break;
    };
  }
  printf("Done.\n");
  dijkstra(g, S);
  return 0;
}
