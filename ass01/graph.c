// TODO: Add any extra #includes that you need

#include "graph.h"
#include "pagerank.h"
#include "pqueue.h"
#include "stack.h"
#include "dijkstra.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNDEFINED -1

// TODO: Add your data structure definitions

typedef struct Vertex {
    string            dat;
    int               idx;
    weight            w;
    struct Vertex    *next;
} Vertex, *Edge;

typedef struct GraphRepr { 
    string           *vertices;
    Edge             *edges; 
    int               nV, nE;
    weight           *oRank, *pRank, *dist;
    int              *prev;
} GraphRepr;

typedef struct PageRank {
    string            url;
    weight            pRank;
} PageRank, *Ranking;

// TODO: Fill in these function stubs

graph graph_create(void) {
    graph g = malloc(sizeof(GraphRepr));
    g->vertices = NULL;
    g->edges = NULL;
    g->nV = g->nE = 0;
    g->oRank = g->pRank = g->dist = NULL;
    g->prev = NULL;
    return g;
}

void graph_destroy(graph g) {
    if (g != NULL) {
        for (int i = 0; i < g->nV; i++) {
            Edge head = g->edges[i];
            while (head != NULL) {
                Edge tmp = head;
                head = head->next;
                free(tmp->dat);
                free(tmp);
            }
            free(g->vertices[i]);
        }
        free(g->vertices);
        free(g->edges);
        free(g->oRank);
        free(g->pRank);
        free(g->dist);
        free(g->prev);
        free(g);
    }
}

void graph_add_vertex(graph g, string v) {
    if (!graph_has_vertex(g, v)) {
        g->vertices = realloc(g->vertices, sizeof(string) * (g->nV + 1));
        g->vertices[g->nV] = malloc(strlen(v) + 1);
        g->edges = realloc(g->edges, sizeof(Edge) * (g->nV + 1));
        g->edges[g->nV] = NULL;
        strcpy(g->vertices[g->nV], v);
        g->oRank = realloc(g->oRank, sizeof(weight) * (g->nV + 1));
        g->pRank = realloc(g->pRank, sizeof(weight) * (g->nV + 1));
        g->dist = realloc(g->dist, sizeof(weight) * (g->nV + 1));
        g->prev = realloc(g->prev, sizeof(int) * (g->nV + 1));
        g->nV++;
    }
}

int vertices_get_index(graph g, string v) {
    for (int i = 0; i < g->nV; i++) {
        if (strcmp(g->vertices[i], v) == 0) {
            return i;
        }
    }
    return -1;
}

bool graph_has_vertex(graph g, string v) {
    if (vertices_get_index(g, v) != -1) {
        return true;
    }
    return false;
}

size_t graph_vertices_count(graph g) {
    return g->nV;
}

void graph_add_edge(graph g, string v1, string v2, weight w) {
    graph_add_vertex(g, v1); // wont be added if v1 exists
    graph_add_vertex(g, v2); // wont be added if v2 exists
    if (!graph_has_edge(g, v1, v2)) {
        int src_idx = vertices_get_index(g, v1);
        int dest_idx = vertices_get_index(g, v2);
        Edge v = malloc(sizeof(Vertex));
        v->dat = malloc(strlen(v2) + 1);
        strcpy(v->dat, v2);
        v->idx = dest_idx;
        v->w = w;
        v->next = NULL;
        if (g->edges[src_idx] == NULL) {
            g->edges[src_idx] = v;
        }
        else {
            Edge p = g->edges[src_idx];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = v;
        }
        g->nE++;
    }
}

bool graph_has_edge(graph g, string v1, string v2) {
    int src_idx = vertices_get_index(g, v1);
    if (src_idx != -1) {
        Edge p = g->edges[src_idx];
        while (p != NULL) {
            if (strcmp(p->dat, v2) == 0) {
                return true;
            }
            p = p->next;
        }
    }
    return false;
}

void graph_update_edge(graph g, string v1, string v2, weight w) {
    if (!graph_has_edge(g, v1, v2)) {
        graph_add_edge(g, v1, v2, w);
    }
    else {
        int src_idx = vertices_get_index(g, v1);
        int dest_idx = vertices_get_index(g, v2);
        Edge p = g->edges[src_idx];
        while (p != NULL) {
            if (p->idx == dest_idx) {
                p->w = w;
            }
            p = p->next;
        }
    }
}

weight graph_get_edge(graph g, string v1, string v2) {
    double w = 0.0;
    int src_idx = vertices_get_index(g, v1);
    if (src_idx != -1) {
        Edge p = g->edges[src_idx];
        while (p != NULL) {
            if (strcmp(p->dat, v2) == 0) {
                w = p->w;
                break;
            }
            p = p->next;
        }
    }
    return w;
}

size_t graph_outgoing_edges_count(graph g, string v) {
    int nE = 0;
    for (int i = 0; i < g->nV; i++) {
        if (graph_has_edge(g, v, g->vertices[i])) {
            nE++;
        }
    }
    return nE;
}

size_t graph_incoming_edges_count(graph g, string v) {
    int nE = 0;
    for (int i = 0; i < g->nV; i++) {
        if (graph_has_edge(g, g->vertices[i], v)) {
            nE++;
        }
    }
    return nE;
}

size_t graph_edges_count(graph g, string v) {
    return graph_outgoing_edges_count(g, v) + graph_incoming_edges_count(g, v);
}

void graph_show(graph g, FILE *output) {
    FILE *f = output;
    if (output == NULL) {
        f = stdout;
    }
    for (int i = 0; i < g->nV; i++) {
        fprintf(f, "%s\n", g->vertices[i]);
    }
    for (int j = 0; j < g->nV; j++) {
        Edge p = g->edges[j];
        while (p != NULL) {
            fprintf(f, "%s %s %.3f\n", g->vertices[j], p->dat, p->w);
            p = p->next;
        }
    }
}

bool vertices_any_gt_epsilon(graph g, double delta) {
    for (int i = 0; i < g->nV; i++) {
        if (fabs(g->pRank[i] - g->oRank[i]) > delta) {
            return true;
        }
    }
    return false;
}

void graph_pagerank(graph g, double damping, double delta) {
    int nV = g->nV;
    for (int i = 0; i < nV; i++) {
        g->oRank[i] = 0;
        g->pRank[i] = 1.0 / nV;
    }
    while (vertices_any_gt_epsilon(g, delta)) {
        for (int j = 0; j < nV; j++) {
            g->oRank[j] = g->pRank[j];
        }
        double sRank = 0.0;
        for (int k = 0; k < nV; k++) {
            if (g->edges[k] == NULL) {
                sRank += (damping * (g->oRank[k] / nV));
            }
        }
        for (int m = 0; m < nV; m++) {
            g->pRank[m] = sRank + ((1 - damping) / nV);
            for (int n = 0; n < nV; n++) {
                if (graph_has_edge(g, g->vertices[n], g->vertices[m])) {
                    g->pRank[m] += ((damping * g->oRank[n]) / graph_outgoing_edges_count(g, g->vertices[n]));
                }
            }
        }
    }
}

Ranking *ranking_create(graph g) {
    Ranking *rankings = malloc(sizeof(rankings) * g->nV);
    for (int i = 0; i < g->nV; i++) {
        rankings[i] = malloc(sizeof(PageRank));
        rankings[i]->url = malloc(strlen(g->vertices[i]) + 1);
        strcpy(rankings[i]->url, g->vertices[i]);
        rankings[i]->pRank = g->pRank[i];
    }
    return rankings;
}

void ranking_destroy(Ranking *rankings, int nV) {
    for (int i = 0; i < nV; i++) {
        free(rankings[i]->url);
    }
    free(rankings);
}

int compare(const void *a, const void *b) {
    Ranking x = *(Ranking *)a;
    Ranking y = *(Ranking *)b;
    if (y->pRank != x->pRank) {
        return (y->pRank > x->pRank) ? 1 : -1;
    } else {
        return strcmp(x->url, y->url);
    }
}

void graph_show_pagerank(graph g, FILE *file) {
    FILE *f = file;
    if (file == NULL) {
        f = stdout;
    }
    Ranking *rankings = ranking_create(g);
    qsort(rankings, g->nV, sizeof(Ranking), compare);
    for (int i = 0; i < g->nV; i++) {
        fprintf(f, "%s (%.3f)\n", rankings[i]->url, rankings[i]->pRank);
    }
    ranking_destroy(rankings, g->nV);
}

void graph_worst_path(graph g, string source, double damping, double delta) {
    graph_pagerank(g, damping, delta);
    int src_idx = vertices_get_index(g, source);
    g->dist[src_idx] = 0.0;
    g->prev[src_idx] = UNDEFINED;
    pqueue pq = pqueue_create();
    for (int i = 0; i < g->nV; i++) {
        if (i != src_idx) {
            g->dist[i] = INFINITY;
            g->prev[i] = UNDEFINED;
        }
        pqueue_join(pq, g->vertices[i], g->prev[i]);
    }
    while (!pqueue_empty(pq)) {
        string u = pqueue_leave(pq);
        for (int j = 0; j < g->nV; j++) {
            if (graph_has_edge(g, u, g->vertices[j])) {
                int u_idx = vertices_get_index(g, u);
                weight alt = g->dist[u_idx] + g->pRank[u_idx];
                if (alt < g->dist[j]) {
                    g->dist[j] = alt;
                    g->prev[j] = u_idx;
                    pqueue_join(pq, g->vertices[j], alt);
                }
            }
        }
        free(u);
    }
    pqueue_destroy(pq);
}

void graph_show_path(graph g, string destination) {
    /*
    for (int i = 0; i < g->nV; i++) {
        printf("%d %f %d\n", i, g->dist[i], (int)g->prev[i]);
    }
    */
    int dest_idx = vertices_get_index(g, destination);
    //printf("dest idx is %d\n", dest_idx);
    stack s = stack_create();
    if (g->prev[dest_idx] == UNDEFINED) {
        printf("No path found.\n");
        return;
    }
    stack_push(s, destination);
    int prev_idx = g->prev[dest_idx];
    while (true) {
        if (g->prev[prev_idx] == UNDEFINED) {
            stack_push(s, g->vertices[prev_idx]);
            break;
        }
        stack_push(s, g->vertices[prev_idx]);
        //printf("-> %s\n", g->vertices[prev_idx]);
        prev_idx = g->prev[prev_idx];
    }
    string ele = stack_pop(s);
    printf("%s\n", ele);
    free(ele);
    while (!stack_empty(s)) {
        ele = stack_pop(s);
        printf("-> %s\n", ele);
        free(ele);
    }
    stack_destroy(s);
}
