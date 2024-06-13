#include "grafo_matriz.h"

int main () {

    int n;
    scanf("%d", &n);

    int ordem, arestas;
    int ini, fim;

    ListaD *p = criar_listad();

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &ordem, &arestas);

        Grafo *g = cria_grafo(ordem);
        
        for (int j = 0; j < arestas; j++) {
            scanf("%d %d", &ini, &fim);
            preenche_aresta(g, ini, fim);
        }
        printf("Caso %d:\n", i);
        busca_em_profundidade(g, p);
        limpa(g);
    }

    return 0;
}