#include "WGraph.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int *idx_arr, double *pop_arr, int n) {
  int i;
  for (i = 1; i < n; i++) {
    double element = pop_arr[i]; // for this element ...
    int idx_ele = idx_arr[i];
    int j = i - 1;
    while (j >= 0 && pop_arr[j] < element) { // ... work down the ordered list
      pop_arr[j + 1] = pop_arr[j];           // ... moving elements up
      idx_arr[j + 1] = idx_arr[j];
      j--;
    }
    pop_arr[j + 1] = element; // and insert in correct position
    idx_arr[j + 1] = idx_ele;
  }
}

void showPopularityRank(Graph g) {
  double *inDegree = malloc(sizeof(double) * numOfVertices(g));
  memset(inDegree, 0, sizeof(double) * numOfVertices(g));
  double *outDegree = malloc(sizeof(double) * numOfVertices(g));
  memset(outDegree, 0, sizeof(double) * numOfVertices(g));
  double *popRanking = malloc(sizeof(double) * numOfVertices(g));
  memset(popRanking, 0, sizeof(double) * numOfVertices(g));
  int *idx = malloc(sizeof(int) * numOfVertices(g));
  memset(idx, 0, sizeof(int) * numOfVertices(g));
  for (int i = 0; i < numOfVertices(g); i++) {
    for (int j = 0; j < numOfVertices(g); j++) {
      if (adjacent(g, i, j)) {
        inDegree[j]++;
        outDegree[i]++;
      }
    }
  }
  for (int k = 0; k < numOfVertices(g); k++) {
    idx[k] = k;
    if (outDegree[k] == 0) {
      outDegree[k] = 0.5;
    }
    popRanking[k] = inDegree[k] / outDegree[k];
  }
  insertionSort(idx, popRanking, numOfVertices(g));
  printf("\nPopularity ranking:\n");
  for (int i = 0; i < numOfVertices(g); i++) {
    printf("%d %.1f\n", idx[i], popRanking[i]);
  }
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
        e.weight = 1;
        insertEdge(g, e);
      } else {
        break;
      }
    } else {
      break;
    };
  }
  printf("Done.\n");
  showPopularityRank(g);
  return 0;
}
