#include <stdio.h>
#include <stdlib.h>

typedef struct No_Abb {
    int valor;
    struct No_Abb *esq, *dir;
    int nivel;
}No_Abb;

typedef struct Abb {
    int tamanho;
    No_Abb *raiz;
}Abb;

Abb* criar_abb();
No_Abb* criar_noabb(int valor);
void inserir_no_abb(Abb* T, int valor);
void imprimir_abb(Abb* T);
void imprimir_largura(No_Abb* raiz, int nivel);

Abb* criar_abb() {
    Abb* T = (Abb*)malloc(sizeof(Abb));
    T->raiz = NULL;
    T->tamanho = 0;
    return T;
}

No_Abb* criar_noabb(int valor) {
    No_Abb *novo = (No_Abb*)malloc(sizeof(No_Abb));
    novo->esq = novo->dir = NULL;
    novo->valor = valor;
    return novo;
}

void inserir_no_abb(Abb* T, int valor) {
    No_Abb *novo = criar_noabb(valor);

    if (valor != -1) {
        if (T != NULL) {
            if (T->raiz != NULL) {
                No_Abb *aux = T->raiz;
                No_Abb *pai_aux = NULL;
                int cont = 0;
                int alt = 0;

                while (aux != NULL) {
                    pai_aux = aux;
                    if (valor > aux->valor) {
                        aux = aux->dir;
                        alt++;
                        cont++;
                    } else {
                        if (valor < aux->valor) {
                            aux = aux->esq;
                            alt++;
                            cont++;
                        }else {
                            aux = NULL;
                        }
                    }
                }
                if(valor > pai_aux->valor) {
                    pai_aux->dir = novo;
                    if (alt > T->tamanho)
                        T->tamanho++;
                } else {
                    pai_aux->esq = novo;
                    if (alt > T->tamanho)
                        T->tamanho++;
                }

                novo->nivel = cont;
            } else {
                T->raiz = criar_noabb(valor);
                T->tamanho++;
            }
        }
    }
}

void imprimir_abb(Abb* T) {
    for(int i = 0; i <= T->tamanho; i++) {
        imprimir_largura(T->raiz, i);
        printf("\n");
    }
}

void imprimir_largura(No_Abb* raiz, int nivel) {
	if (raiz == NULL) {
		return;
	}
	if (nivel == raiz->nivel) {
		printf("%d ", raiz->valor);
	} else if(nivel > 0){
		imprimir_largura(raiz->esq, nivel);
        imprimir_largura(raiz->dir, nivel);
	}
	/*
    if (nivel == 0) {
        printf("%d ", raiz->valor);
    }else {
        imprimir_largura(raiz->esq, nivel--);
        imprimir_largura(raiz->dir, nivel--);
    }
    */
}

int main () {
    Abb* T = criar_abb();

    int valor = 0;
    while (valor != -1) {
        scanf("%d", &valor);
        inserir_no_abb(T, valor);
    }
    
    imprimir_abb(T);

    return 0;
}