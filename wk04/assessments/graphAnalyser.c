/** Algorithm & Complexity Analysis
 *
 * showMinMaxDegInfo(G):
 *
 * Input:  graph G with n vertices
 * Output: 
 *
 * Statement                                           
 * ----------------------------------------------------
 * create empty array with the size of n int as degs
 * initialize the whole array to 0
 * for each vertice in g as i do
 *   tmp=0
 *   for each vertice in g as j do
 *     if i is adjacent to j and i is not j then
 *       tmp++
 *     end if
 *     degs[i]=tmp
 *   end for
 *   if i=0 then
 *     minDeg=degs[i], maxDeg=degs[i];
 *   end if
 *   if degs[i]<minDeg then
 *     minDeg=degs[i]
 *   if degs[i]>maxDeg then
 *     maxDeg=degs[i]
 * end for
 * ----------------------------------------------------
 * Time complexity: O(n^2)
 *
 *
 * showTrngleFormation(G, n):
 *
 * Input:  graph G with n vertices
 * Output: 
 *
 * Statement                                           
 * ----------------------------------------------------
 * for each vertice in g as i do
 *   for each vertice after i in g as j do
 *     if i is adjacent to j then
 *       for each vertice after j in g as k do
 *         if i is adjacent to k and j is also adjacent to k then
 *           print i-j-k
 *         end if
 *       end for
 *     end if
 *   end for
 * end for
 * ----------------------------------------------------
 * Time complexity: O(n^3)
 *
 **/
#include "Graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showNodesWDeg(int deg, int *degs, int size) {
  for (int i = 0; i < size; i++) {
    if (deg == degs[i])
      printf("%d\n", i);
  }
}

void showMinMaxDegInfo(Graph g, int size) {
  int *degs = malloc(sizeof(int) * size);
  memset(degs, 0, sizeof(int) * size);
  int minDeg = 0, maxDeg = 0;
  for (int i = 0; i < size; i++) {
    int tmp = 0;
    for (int j = 0; j < size; j++) {
      if (i != j && adjacent(g, i, j)) {
        tmp++;
      }
      degs[i] = tmp;
    }
    if (i == 0) {
      minDeg = degs[i], maxDeg = degs[i];
    }
    if (degs[i] < minDeg) {
      minDeg = degs[i];
    } else if (degs[i] > maxDeg) {
      maxDeg = degs[i];
    }
  }
  printf("Minimum degree: %d\n", minDeg);
  printf("Maximum degree: %d\n", maxDeg);
  printf("Nodes of minimum degree:\n");
  showNodesWDeg(minDeg, degs, size);
  printf("Nodes of maximum degree:\n");
  showNodesWDeg(maxDeg, degs, size);
}

void showTrngleFormation(Graph g, int size) {
  printf("Triangles:\n");
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (adjacent(g, i, j)) {
        for (int k = j + 1; k < size; k++) {
          if (adjacent(g, i, k) && adjacent(g, j, k))
            printf("%d-%d-%d\n", i, j, k);
        }
      }
    }
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
        insertEdge(g, e);
      } else {
        break;
      }
    } else {
      break;
    };
  }
  printf("Done.\n");
  showMinMaxDegInfo(g, V);
  showTrngleFormation(g, V);
  return 0;
}
