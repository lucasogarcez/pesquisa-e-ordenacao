#include "grafo_matriz.h"
#include "listaD.h"

Grafo *cria_grafo(int ordem) {
    Grafo *novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    novo_grafo->ordem = ordem;
    novo_grafo->matriz = (int**)malloc(sizeof(int*)*ordem+1);
    for (int i = 1; i <= ordem; i++) {
        novo_grafo->matriz[i] = (int*)malloc(sizeof(int)*ordem+1);
    }

    novo_grafo->visitados = (int*)malloc(sizeof(int)*ordem+1);

    for (int i = 1; i <= ordem; i++) {
        novo_grafo->visitados[i] = 0; //0 == não
        for (int j = 1; j <= ordem; j++) {
            novo_grafo->matriz[i][j] = 0;
        }
    }


    return novo_grafo;
}

void preenche_aresta(Grafo *g, int ini, int fim) {
    g->matriz[ini][fim] = 1;
    g->matriz[fim][ini] = 1;
}

void mostra(ListaD *fila) {
    NoD *aux = fila->inicio;
    while (aux != NULL) {
        printf("%d ", aux->vertice);
        aux = aux->prox;
    }
}

void limpa (Grafo *g, ListaD *fila) {
    for (int i = 1; i <= g->ordem; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g->visitados);
    g->ordem = 0;
    free(g);

    NoD *aux1 = fila->inicio;
    NoD *aux2;

    while(aux1 != NULL){
        aux2 = aux1->prox;
        free(aux1);
        aux1 = aux2;
    }

    fila->inicio = fila->fim = NULL;
    free(fila);
}

//dado um vértice retorne o grau, se não direcionado
//se direcionado grau de entrada e grau de saída do vértice

void busca_em_profundidade (Grafo *g, int cidade_atual, int prof, ListaD *fila) {
    for (int i = 1; i <= prof; i++) {
        if (g->visitados[i] == 0) {
            profundidade(g, cidade_atual, 1, prof, fila);
        }
    }
}

void profundidade (Grafo *g, int u, int prof_atual, int prof_max, ListaD *fila) {
    //"u" será a posição do vértice
    g->visitados[u] = 1; //visitou
    int i = u;
    for (int j = 1; j <= g->ordem; j++) {
        if (g->matriz[i][j] == 1) { // contém aresta
            if (g->visitados[j] == 0) { // vértice não visitado
                if (!g->visitados[u] || !g->visitados[j]) //printa caso nao visitados um dos dois
                    inserir_no_fila(fila, j);
                if (prof_atual < prof_max)
                    profundidade(g, j, prof_atual + 1, prof_max, fila);
            }
        }
    }
}