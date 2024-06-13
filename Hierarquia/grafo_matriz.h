#ifndef GRAFO_MATRIZ
#define GRAFO_MATRIZ

#include "listaD.h"

typedef struct grafo {
    int ordem;
    int **matriz;
    int *visitados;
}Grafo;

Grafo *cria_grafo(int ordem);
void preenche_aresta(Grafo *g, int ini, int fim);
void mostra(Grafo *g);
void busca_em_profundidade (Grafo *g, ListaD *p);
void profundidade (Grafo *g, ListaD *p, int u, int prof);
void limpa (Grafo *g);

#endif