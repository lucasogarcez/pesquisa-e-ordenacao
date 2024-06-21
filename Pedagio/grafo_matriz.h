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
void mostra(ListaD *fila);
void busca_em_profundidade (Grafo *g, int cidade_atual, int prof, ListaD *fila);
void profundidade (Grafo *g, int u, int prof_atual, int prof_max, ListaD *fila);
void limpa (Grafo *g, ListaD *fila);

#endif