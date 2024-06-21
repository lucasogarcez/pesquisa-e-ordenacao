#include "grafo_matriz.h"

int main () {

    
    int n_cidades, n_estradas, cidade_atual, max_pedagios;
    int ini, fim;
    int flag = 1, u = 1;

    while (flag == 1) {
        scanf("%d %d %d %d", &n_cidades, &n_estradas, &cidade_atual, &max_pedagios);
        if (n_cidades == 0) {
            flag = 0;
        } else{
            Grafo *g = cria_grafo(n_cidades);
            ListaD *fila = criar_listad();

            for (int i = 0; i < n_estradas; i++) {
                scanf("%d %d", &ini, &fim);
                preenche_aresta(g, ini, fim);
            }
            printf("Teste %d\n", u);
            busca_em_profundidade(g, cidade_atual, max_pedagios, fila);
            mostra(fila);
            printf("\n\n");
            limpa(g, fila);
            u++;
        }
    }

    return 0;
}