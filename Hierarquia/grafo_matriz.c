#include "grafo_matriz.h"
#include "listaD.h"

Grafo *cria_grafo(int ordem) {
    Grafo *novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    novo_grafo->ordem = ordem;
    novo_grafo->matriz = (int**)malloc(sizeof(int*)*ordem);
    for (int i = 0; i < ordem; i++) {
        novo_grafo->matriz[i] = (int*)malloc(sizeof(int)*ordem);
    }

    novo_grafo->visitados = (int*)malloc(sizeof(int)*ordem);
    for (int i = 0; i < ordem; i++) {
        novo_grafo->visitados[i] = 0;
    }

    return novo_grafo;
}

void preenche_aresta(Grafo *g, int ini, int fim) {
    g->matriz[ini][fim] = 1;
}

void mostra(Grafo *g) {
    for (int i = 0; i < g->ordem; i++) {
        for (int j = 0; j < g->ordem; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

void limpa (Grafo *g) {
    for (int i = 0; i < g->ordem; i++) {
        for (int j = 0; j < g->ordem; j++) {
            g->matriz[i][j] = 0;
            g->visitados[i] = 0;
        }
    }
    free(g->matriz);
    free(g->visitados);
    free(g);
}

//dado um vértice retorne o grau, se não direcionado
//se direcionado grau de entrada e grau de saída do vértice

void busca_em_profundidade (Grafo *g, ListaD *p) {
    for (int i = 0; i < g->ordem; i++) {
        if (g->visitados[i] == 0) {
            inserir_no_pilha(p, i);
            profundidade(g, p, i, 1);
            printf("\n");
        }
    }
}

void profundidade (Grafo *g, ListaD *p, int u, int prof) {
    //"u" será a posição do vértice
    g->visitados[u] = 1; //visitou
    int i = u;
    for (int j = 0; j < g->ordem; j++) {
        if (g->matriz[i][j] == 1) { // contém aresta
            inserir_no_pilha(p, j);
            if (g->visitados[u] && g->visitados[j])
                printf("%d-%d\n", i, j); //caso de retorno no msm vértice, ele printa diferente
            if (g->visitados[j] == 0) { // vértice não visitado
                for (int k = 0; k <= prof; k++) {
                    printf(" ");
                }
                if (!g->visitados[u] || !g->visitados[j]) //printa caso nao visitados um dos dois
                    printf("%d-%d pathR(G, %d)\n", i, j, j);
                remover_no_pilha(p);
                profundidade(g, p, j, prof + 2);
            }
        }
    }
}

// void profundidade (Grafo *g, ListaD *p, int u) {
//     //"u" será a posição do vértice
//     g->visitados[u] = 1; //visitou
//     for (int i = u; i < g->ordem; i++) {
//         for (int j = 0; j < g->ordem; j++) {
//             if (g->matriz[i][j] == 1) { //contém aresta
//                 if (g->visitados[j] == 0) { //vértice não visitado
//                     for (int k = 0; k < i; k++) {
//                         printf(" ");
//                     }
//                     printf("%d-%d pathR(G, %d)\n", i, j, j);
//                     profundidade(g, p, j); //g, p, j
//                 }
//             }
//         }
//     }
// }