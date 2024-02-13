#include "Graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dfsCycleCheck(Graph g, Vertex v, Vertex n, int *visited) {
  visited[v] = 1;
  for (int w = 0; w < numOfVertices(g); w++) {
    if (w != n && adjacent(g, v, w)) {
      if (visited[w]) {
        return true;
      } else if (dfsCycleCheck(g, w, v, visited)) {
        return true;
      }
    }
  }
  return false;
}

bool hasCycle(Graph g) {
  int *visited = malloc(numOfVertices(g) * sizeof(int));
  for (int i = 0; i < numOfVertices(g); i++) {
    memset(visited, 0, numOfVertices(g) * sizeof(int));
    if (dfsCycleCheck(g, i, -1, visited)) {
      return true;
    }
  }
  return false;
}

int main(void) {
  int V = 0;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);
  Graph g = newGraph(V);
  while (true) {
    int v = 0, w = 0;
    printf("Enter an edge (from): ");
    if (scanf("%d", &v) > 0) {
      printf("Enter an edge (to): ");
      if (scanf("%d", &w) > 0) {
        Edge e;
        e.v = v;
        e.w = w;
        insertEdge(g, e);
      } else {
        break;
      }
    } else {
      break;
    };
  }
  printf("Done.\n");
  if (hasCycle(g)) {
    printf("The graph has a cycle.\n");
  } else {
    printf("The graph is acyclic.\n");
  }
  return 0;
}
