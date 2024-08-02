#include <stdio.h>
#include <stdlib.h>

typedef struct Indice {
    int valor;
    struct Indice *prox;
}Indice;

typedef struct No {
    int chave;
    Indice *inicio_indice;
    struct No *prox;
}No;

typedef struct Lista {
    int tamanho;
    No *inicio, *fim;
}Lista;

Lista *cria_lista () { //lista principal
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    lista->tamanho = 0;
    lista->inicio = lista->fim = NULL;

    return lista;
}

Indice *cria_indice (int valor) { //lista da lista
    Indice *nova_lista = (Indice*)malloc(sizeof(Indice));
    nova_lista->valor = valor;
    nova_lista->prox = NULL;
    return nova_lista;
}

No *cria_no (int valor) { //no da lista principal
    No *novo = (No*)malloc(sizeof(No));
    novo->chave = valor;
    novo->prox = NULL;
    novo->inicio_indice = NULL;

    return novo;
}

void insere_lista_principal (Lista *lista, int indice) {
    No *novo = cria_no(indice);

    if (lista->inicio == NULL) {
        lista->inicio = lista->fim = novo;
    } else {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    lista->tamanho++;
}

void insere_lista_lista (Lista *lista, int valor) {
    Indice *novo = cria_indice(valor);
    

    int resto = valor % lista->tamanho;
    No *aux = lista->inicio;
    while (aux->chave != resto) 
        aux = aux->prox;
    
    if (aux->inicio_indice == NULL) {
        aux->inicio_indice = novo;
    } else {
        Indice *aux2 = aux->inicio_indice;
        while (aux2->prox != NULL) {
            aux2 = aux2->prox;
        }
        aux2->prox = novo;
    }
}

void mostra (Lista *lista) {
    No *aux = lista->inicio;

    while (aux != NULL) {
        printf("%d ", aux->chave);
        Indice *aux2 = aux->inicio_indice;
        while (aux2 != NULL) {
            printf("-> %d ", aux2->valor);
            aux2 = aux2->prox;
        }
        if (aux2 == NULL) {
            printf("-> \\ \n");
        }
        aux = aux->prox;
    }
}

void limpa (Lista *lista) {
    No *aux = lista->inicio;
    No *aux2;

    while (aux != NULL) {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }

    lista->tamanho = 0;
    lista->inicio = lista->fim = NULL;
}

void mostra_lista(Lista *lista) {
    No *aux = lista->inicio;
    while (aux != NULL) {
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
}

int main () {
    int n;
    scanf("%d", &n);
    int qtd_enderecos, qtd_chaves, x;
    Lista *lista = cria_lista();

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &qtd_enderecos, &qtd_chaves);
        for (int j = 0; j < qtd_enderecos; j++) {
            insere_lista_principal(lista, j);
        }
        for (int k = 0; k < qtd_chaves; k++) {
            scanf("%d", &x);
            insere_lista_lista(lista, x);
        }
        mostra(lista);
        printf("\n");
        limpa(lista);
    }

    return 0;
}