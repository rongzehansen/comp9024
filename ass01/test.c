#include "graph.h"
#include "pagerank.h"
#include "pqueue.h"
#include "stack.h"
#include "dijkstra.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

graph g;

void graph_init_1() {
    g = graph_create();
    graph_add_vertex(g, "vertex1");
    graph_add_vertex(g, "vertex2");
    graph_add_vertex(g, "vertex3");
    graph_add_vertex(g, "vertex4");
    graph_add_vertex(g, "vertex5");
    graph_add_vertex(g, "vertex6");
    graph_add_edge(g, "vertex1", "vertex5", 1.0);
    graph_add_edge(g, "vertex2", "vertex4", 4.0);
    graph_add_edge(g, "vertex3", "vertex4", 1.0);
    graph_add_edge(g, "vertex4", "vertex5", 1.0);
    graph_add_edge(g, "vertex5", "vertex2", 0.5);
    graph_add_edge(g, "vertex6", "vertex2", 5.5);
}

void graph_init_2() {
    g = graph_create();
    graph_add_vertex(g, "vertex5");
    graph_add_vertex(g, "vertex2");
    graph_add_vertex(g, "vertex4");
    graph_add_vertex(g, "vertex6");
    graph_add_vertex(g, "vertex3");
    graph_add_vertex(g, "vertex1");
    graph_add_edge(g, "vertex1", "vertex5", 10.0);
    graph_add_edge(g, "vertex2", "vertex4", 6.6);
    graph_add_edge(g, "vertex3", "vertex4", 2.2);
    graph_add_edge(g, "vertex4", "vertex5", 4.0);
    graph_add_edge(g, "vertex5", "vertex2", 1.5);
    graph_add_edge(g, "vertex6", "vertex2", 2.5);
    graph_add_edge(g, "vertex2", "vertex6", 2.6);
    graph_add_edge(g, "vertex2", "vertex3", 1.3);
}

void graph_init_3() {
    g = graph_create();
    graph_add_vertex(g, "vertexxxxxxxxxxxxxxxx");
    graph_add_vertex(g, "vertexaaaaaaaaaaaaaaa");
    graph_add_vertex(g, "vertexzaaaaaaaaaaaaaa");
    graph_add_vertex(g, "vertex2");
    graph_add_vertex(g, "vertex5");
    graph_add_vertex(g, "vertex2");
    graph_add_vertex(g, "vertex4");
    graph_add_vertex(g, "vertex6");
    graph_add_vertex(g, "vertex3");
    graph_add_vertex(g, "vertex1");
    graph_add_edge(g, "vertex1", "vertex5", 10.0);
    graph_add_edge(g, "vertex2", "vertex4", 6.6);
    graph_add_edge(g, "vertex3", "vertex4", 2.2);
    graph_add_edge(g, "vertex4", "vertex5", 4.0);
    graph_add_edge(g, "vertex5", "vertex2", 1.5);
    graph_add_edge(g, "vertex6", "vertex2", 2.5);
    graph_add_edge(g, "vertex2", "vertex6", 2.6);
    graph_add_edge(g, "vertex2", "vertex3", 1.3);
    graph_add_edge(g, "vertexxxxxxxxxxxxxxxx", "vertexaaaaaaaaaaaaaaa", 99.1);
    graph_add_edge(g, "vertexzxxxxxxxxxxxxxx", "vertex2", 0.2);
    graph_add_edge(g, "vertexzxxxxxxxxxxxxxx", "vertex1", 0.01);
}

void graph_test() {
    FILE *fp = fopen("./wout.txt", "w");
    fprintf(fp,"output from graph_init_1():\n");
    graph_init_1();
    graph_show(g, fp);
    graph_pagerank(g, 0.85, 0.00001);
    graph_show_pagerank(g, fp);
    
    graph_worst_path(g, "vertex1", 0.85, 0.00001);
    graph_show_path(g, "vertex5");
    graph_show_path(g, "vertex2");
    graph_destroy(g);
    
    fprintf(fp,"output from graph_init_2():\n");
    graph_init_2();
    graph_show(g, fp);
    graph_pagerank(g, 0.85, 0.00001);
    graph_show_pagerank(g, fp);
    
    graph_worst_path(g, "vertex1", 0.85, 0.00001);
    graph_show_path(g, "vertex2");
    graph_show_path(g, "vertex4");
    graph_destroy(g);
    
    graph_init_3();
    graph_show(g, fp);
    graph_pagerank(g, 0.65, 0.00025);
    graph_show_pagerank(g, fp);
    
    graph_worst_path(g, "vertex1", 0.65, 0.00025);
    graph_show_path(g, "vertex1");
    graph_show_path(g, "vertex2");
    graph_show_path(g, "vertexxxxxxxxxxxxxxxx");
    graph_show_path(g, "vertexzxxxxxxxxxxxxxx");
    graph_destroy(g);
    fprintf(fp,"output from graph_show_path:\n");
}

int main(void) {
    graph_test();
    return 0;
}
