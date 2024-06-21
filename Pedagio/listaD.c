#include "listaD.h"

ListaD *criar_listad() {
    ListaD *lista = (ListaD*)malloc(sizeof(ListaD));
    lista->inicio = lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

NoD *criar_no (int vertice) {
    NoD *novo = (NoD*)malloc(sizeof(NoD));
    novo->vertice = vertice;
    novo->prox = novo->ant = NULL;
    return novo;
}

void inserir_no_fila (ListaD *fila, int vertice) {
    NoD *novo = criar_no(vertice);

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = novo;
    } else {
        NoD *aux = fila->inicio;
        while (aux->prox != NULL && vertice > aux->prox->vertice) {
            aux = aux->prox;
        }
        novo->ant = aux;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    fila->tamanho++;
}

void remover_no_fila (ListaD *fila) {
    if (fila->inicio != NULL) {
        NoD *aux = fila->inicio;
        aux->prox->ant = NULL;
        fila->inicio = aux->prox;
        aux->prox = NULL;
        free(aux);
    }
}

void inserir_no_pilha (ListaD *pilha, int vertice) {
    NoD *novo = criar_no(vertice);

    if (pilha->inicio == NULL) {
        pilha->inicio = pilha->fim = novo;
    } else {
        novo->prox = pilha->inicio;
        pilha->inicio->ant = novo;
        pilha->inicio = novo;
    }
    pilha->tamanho++;
}

void remover_no_pilha (ListaD *pilha) {
    if (pilha->inicio != NULL) {
        NoD *aux = pilha->inicio;
        
        aux->prox->ant = NULL;
        pilha->inicio = aux->prox;
        aux->prox = NULL;
        free(aux);
    }
}