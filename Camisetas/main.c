#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Camisa {
    char nome[100];
    int tamanho;
    struct Camisa *prox;
}Camisa;

typedef struct No {
    char cor[10];
    Camisa *info;
    struct No *prox;
}No;

typedef struct Lista {
    No *inicio, *fim;
}Lista;

Lista *cria_lista();
No *cria_no (char cor[]);
void insere_cores (Lista *lista);
Camisa *cria_camisa (char nome[], char tamanho);
void insere_camisa (Lista *lista, char nome[], char cor[], int tamanho);
void mostrar_camisa (Lista *lista);
void limpa (Lista *lista);

Lista *cria_lista() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = lista->fim = NULL;
    return lista;
}

No *cria_no (char cor[]) {
    No *novo = (No*)malloc(sizeof(No));
    strcpy(novo->cor, cor);
    novo->info = NULL;
    novo->prox = NULL;
    return novo;
}

void insere_cores (Lista *lista) {
    No *novo = cria_no("branco");
    lista->inicio = lista->fim = novo;
    No *novo2 = cria_no("vermelho");
    lista->fim->prox = novo2;
    lista->fim = novo2;
}

Camisa *cria_camisa (char nome[], char tamanho) {
    Camisa *nova_camisa = (Camisa*)malloc(sizeof(Camisa));
    strcpy(nova_camisa->nome, nome);
    nova_camisa->tamanho = tamanho;
    nova_camisa->prox = NULL;
    return nova_camisa;
}

void insere_camisa (Lista *lista, char nome[], char cor[], int tamanho) {
    Camisa *camisa = cria_camisa(nome, tamanho);
    
    if (strcmp(cor, "branco") == 0) {
        No *aux = lista->inicio; //branco - primeiro elemento
        if (aux->info == NULL) {
            aux->info = camisa;
        } else if (camisa->tamanho >= aux->info->tamanho && strcmp(camisa->nome, aux->info->nome) < 0){ //inicio
            camisa->prox = aux->info;
            aux->info = camisa;
        } else { //meio ou fim
            Camisa *aux2 = aux->info;
            while (aux2->prox != NULL && aux2->prox->tamanho > camisa->tamanho) {
                aux2 = aux2->prox;
            }

            while (aux2->prox != NULL && camisa->tamanho == aux2->prox->tamanho) { //caso haja mais de uma do mesmo tamanho
                aux2 = aux2->prox;
            }
            camisa->prox = aux2->prox;
            aux2->prox = camisa;
        }
    } else {
        No *aux = lista->fim; //vermelho
        if (aux->info == NULL) {
            aux->info = camisa;
        } else if (camisa->tamanho > aux->info->tamanho || strcmp(camisa->nome, aux->info->nome) < 0){ //inicio
            camisa->prox = aux->info;
            aux->info = camisa;
        } else { //meio ou fim
            Camisa *aux2 = aux->info;
            while (aux2->prox != NULL && aux2->prox->tamanho > camisa->tamanho) {
                aux2 = aux2->prox;
            }
            
            while (aux2->prox != NULL && camisa->tamanho == aux2->prox->tamanho) { //caso haja mais de uma do mesmo tamanho
                aux2 = aux2->prox;
            }
            camisa->prox = aux2->prox;
            aux2->prox = camisa;
        }
    }
}

void mostrar_camisa (Lista *lista) {
     No *aux = lista->inicio;

    while (aux != NULL) {
        Camisa *aux2 = aux->info;
        while (aux2 != NULL) {
            printf("%s", aux->cor);
            printf(" %c", aux2->tamanho);
            printf(" %s\n", aux2->nome);
            aux2 = aux2->prox;
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

    lista->inicio = lista->fim = NULL;
}


int main () {

    int n;
    Lista *lista = cria_lista();

    while (scanf("%d", &n), n != 0) {
        insere_cores(lista);
        char nome[100];
        char cor[10];
        char tamanho;
        for (int i = 0; i < n; i++) {
            getchar();
            scanf(" %[^\n]s", nome);
            getchar();
            scanf("%s", cor);
            getchar();
            scanf("%c", &tamanho);
            insere_camisa(lista, nome, cor, tamanho);
        }
        mostrar_camisa(lista);
        limpa(lista);
    }




    return 0;
}