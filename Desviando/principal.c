#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct grafo {
    int ordem;
    int **matriz;
    int *visitados;
    int *precedente;
    int *estimativa;

    int nulo;
}Grafo;

Grafo *cria_grafo(int ordem);
void preenche_aresta(Grafo *g, int ini, int fim, int pedagio);
void mostra(Grafo *g);
void limpa (Grafo *g);
void dijkstra (Grafo *g, int s, int cidade_dest);

Grafo *cria_grafo(int ordem) {
    Grafo *novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    novo_grafo->ordem = ordem;
    novo_grafo->matriz = (int**)malloc(sizeof(int*)*ordem);
    for (int i = 0; i < ordem; i++) {
        novo_grafo->matriz[i] = (int*)malloc(sizeof(int)*ordem);
    }

    novo_grafo->visitados = (int*)malloc(sizeof(int)*ordem);
    novo_grafo->estimativa = (int*)malloc(sizeof(int)*ordem);
    novo_grafo->precedente = (int*)malloc(sizeof(int)*ordem);

    for (int i = 0; i < ordem; i++) {
        novo_grafo->visitados[i] = 0; //0 == não
        for (int j = 0; j < ordem; j++) {
            novo_grafo->matriz[i][j] = -1;
        }
    }

    novo_grafo->nulo = -1;

    return novo_grafo;
}

void preenche_aresta(Grafo *g, int ini, int fim, int pedagio) {
    g->matriz[ini][fim] = pedagio;
    g->matriz[fim][ini] = pedagio;
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
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g->visitados);
    free(g->estimativa);
    free(g->precedente);
    g->ordem = 0;
    free(g);
}

int vertice_aberto_menor_estimativa(Grafo *g)
{
    int i,pos_menor = -1, menor = INT_MAX;
    for(i=0; i<g->ordem; i++)
    {
        if (!g->visitados[i])
        {
            if (g->estimativa[i] < menor)
            {
                pos_menor = i;
                menor = g->estimativa[i];
            }
        }
    }
    return pos_menor;
}


void dijkstra (Grafo *g, int s, int cidade_dest)
{
    int i,j,k,soma, flag = 1;
    int nro_vertices_abertos = g->ordem;
    for (i = 0; i< g->ordem; i++)
    {
        g->estimativa[i] = INT_MAX;
        g->precedente[i] = -1;
    }
    g->estimativa[s] = 0;
    
    while (nro_vertices_abertos > 0)
    {
        k = vertice_aberto_menor_estimativa(g);
        if (k == -1)
            nro_vertices_abertos = 0;
        else {
            g->visitados[k] = 1;
            nro_vertices_abertos--;
            for(j=0; j<g->ordem; j++)
            {
                if (g->matriz[k][j] != g->nulo)
                {
                    if (!g->visitados[j])
                    {
                        flag = 1;
                        if (j != k + 1 && cidade_dest > k)
                            flag = 0;
                        if (flag == 1) {
                            soma = g->estimativa[k] + g->matriz[k][j];
                            if (soma < g->estimativa[j])
                            {
                                g->estimativa[j] = soma;
                                g->precedente[j] = k;
                            }                    
                        }
                    }
                }
            }
        }
    }
}

int main () {

    
    int n_cidades, n_estradas, cidade_dest, cidade_conserto;
    int ini, fim, pedagio;
    int flag = 1;

    while (flag == 1) {
        scanf("%d %d %d %d", &n_cidades, &n_estradas, &cidade_dest, &cidade_conserto);
        cidade_dest = cidade_dest-1;
        if (n_cidades == 0) {
            flag = 0;
        } else{
            Grafo *g = cria_grafo(n_cidades);

            for (int i = 0; i < n_estradas; i++) {
                scanf("%d %d %d", &ini, &fim, &pedagio);
                preenche_aresta(g, ini, fim, pedagio);
            }
            dijkstra(g, cidade_conserto, cidade_dest+1);
            printf("%d\n", g->estimativa[cidade_dest]);
            limpa(g);
        }
    }

    return 0;
}