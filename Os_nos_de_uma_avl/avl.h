#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include <stdio.h>
#include <stdlib.h>

struct no_avl
{
    int chave;
    struct no_avl *esq,*dir, *pai;
    int fb;
    int qtd_chaves_dir;
    int qtd_chaves_esq;
};
typedef struct no_avl No_avl;

struct avl
{
    No_avl *raiz;
    int altura;
    int qtde_chaves;
};
typedef struct avl Avl;

No_avl* cria_no_avl(int chave);
Avl* cria_avl();
void em_ordem_avl(Avl *t);
Avl* insercao_avl(Avl *t, int chave);
No_avl *colocar_no_avl(No_avl *raiz, int chave);
void recalcular_fb(No_avl *candidato, int chave);
No_avl* rotacao_geral(No_avl *candidato);

No_avl* rotacao_dir(No_avl* candidato);
No_avl* rotacao_esq(No_avl* candidato);
No_avl* rotacao_dir_esq(No_avl* candidato);
No_avl* rotacao_esq_dir(No_avl* candidato);
void em_ordem_avl(Avl *T);
void em_ordem_no_avl(No_avl *raiz);

void libera_avl(No_avl* raiz);

void verificar_nos(Avl *T);
void nos(No_avl *raiz);
int qtd_nos_lados(No_avl* raiz);

#endif