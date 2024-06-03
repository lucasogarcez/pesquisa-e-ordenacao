#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grafo {
    int ordem;
    int eh_valorado;
    int eh_direcionado;
    int **matriz;
    char **vertices;
}Grafo;

Grafo *cria_grafo(int ordem, int eh_direcionado, int eh_valorado);
void preenche_vertices(Grafo *g);
void preenche_aresta(Grafo *g);
void mostra(Grafo *g);
int retorna_grau (Grafo *g);

Grafo *cria_grafo(int ordem, int eh_direcionado, int eh_valorado) {
    Grafo *novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    novo_grafo->ordem = ordem;
    novo_grafo->eh_direcionado = eh_direcionado;
    novo_grafo->eh_valorado = eh_valorado;
    novo_grafo->matriz = (int**)malloc(sizeof(int*)*ordem);
    for (int i = 0; i < ordem; i++) {
        novo_grafo->matriz[i] = (int*)malloc(sizeof(int)*ordem);
    }

    return novo_grafo;
}

void mostra(Grafo *g) {
    for (int i = 0; i < g->ordem; i++) {
        for (int j = 0; j < g->ordem; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

//dado um vértice retorne o grau, se não direcionado
//se direcionado grau de entrada e grau de saída do vértice

int retorna_grau (Grafo *g) {

    int cont_entrada = 0;
    int cont_total = 0;

    for (int k = 0; k < g->ordem; k++) { //geral
        for (int i = 0; i < g->ordem; i++) { //rodando matriz
            cont_entrada = 0;
            for (int j = 0; j < g->ordem; j++)
            {
                if (g->matriz[i][j] >= 0)
                {
                    cont_entrada++;
                }
            }
            if (i == 0) {
                cont_total = cont_entrada;
            }
            if (cont_total != cont_entrada) {
                return 0;
            }
        }
    }
    return 1;
}

int main () {
    int ordem;
    scanf("%d", &ordem);

    Grafo *grafo = cria_grafo(ordem, 0, 1);

    for (int i = 0; i < ordem; i++) { //preenche grafo
        for (int j = 0; j < ordem; j++) {
            scanf("%d", &grafo->matriz[i][j]);
        }
    }

    int resp = retorna_grau(grafo);

    if (resp) {
        printf("sim\n");
    } else {
        printf("nao\n");
    }

    return 0;
}