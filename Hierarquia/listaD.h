#ifndef LISTA_D
#define LISTA_D

#include <stdio.h>
#include <stdlib.h>

typedef struct NoD {
    int vertice;
    struct NoD *prox, *ant;
}NoD;

typedef struct ListaD {
    NoD *inicio, *fim;
}ListaD;

ListaD *criar_listad();
NoD *criar_no (int vertice);
void inserir_no_pilha (ListaD *pilha, int vertice);
void remover_no_pilha (ListaD *pilha);

#endif