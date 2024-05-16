#include "avl.h"

Avl *cria_avl()
{

    Avl *nova = (Avl *)malloc(sizeof(Avl));
    nova->altura = nova->qtde_chaves = 0;
    nova->raiz = NULL;
    return nova;
}
No_avl *cria_no_avl(int chave)
{
    No_avl *novo = (No_avl *)malloc(sizeof(No_avl));
    novo->dir = novo->esq = novo->pai = NULL;
    novo->chave = chave;
    novo->fb = 0;
    novo->qtd_chaves_dir = 0;
    novo->qtd_chaves_esq = 0;
    return novo;
}
Avl *insercao_avl(Avl *t, int chave)
{
    No_avl *candidato = NULL;
    // criar a arvore se necessário
    if (t == NULL)
    {
        t = cria_avl();
        t->raiz = cria_no_avl(chave);
        t->altura++;
        t->qtde_chaves++;
        return t;
    }
    else
    {
        candidato = colocar_no_avl(t->raiz, chave);
        recalcular_fb(candidato, chave);
        if (candidato->fb == -2 || candidato->fb == +2)
        {
            if (t->raiz == candidato)
                t->raiz = rotacao_geral(candidato);
            else if (candidato->pai->esq == candidato)
                candidato->pai->esq = rotacao_geral(candidato);
            else
                candidato->pai->dir = rotacao_geral(candidato);
        }
    }
    // colocar o nó na arvore corretamente
    // recalcular o fb
    // verifica desbalanceamento
    // balancear (rotacionar)
    // recalcular o fb
    return t;
}

No_avl *colocar_no_avl(No_avl *raiz, int chave)
{
    No_avl *aux = raiz;
    No_avl *candidato = raiz;
    No_avl *pai = NULL;
    No_avl *novo = cria_no_avl(chave);
    while (aux != NULL)
    {
        if (aux->fb != 0)
            candidato = aux;
        pai = aux;
        if (chave < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    if (chave < pai->chave)
        pai->esq = novo;
    else
        pai->dir = novo;
    novo->pai = pai;
    return candidato;
}
void recalcular_fb(No_avl *candidato, int chave)
{
    No_avl *aux = candidato;
    while (aux->chave != chave)
    {
        if (chave < aux->chave)
        {
            aux->fb++;
            aux = aux->esq;
        }
        else
        {
            aux->fb--;
            aux = aux->dir;
        }
    }
}

No_avl *rotacao_geral(No_avl *candidato)
{
    No_avl *nova_raiz;
    if (candidato->fb == -2)
    {
        if (candidato->dir->fb == +1)
            nova_raiz = rotacao_dir_esq(candidato);
        else
            nova_raiz = rotacao_esq(candidato);
    }
    else //+2
    {
        if (candidato->esq->fb == -1)
            nova_raiz = rotacao_esq_dir(candidato);
        else
            nova_raiz = rotacao_dir(candidato);
    }
    return nova_raiz;
}

No_avl *rotacao_dir(No_avl *candidato)
{
    No_avl *filho = candidato->esq;
    No_avl *neto = filho->dir;

    filho->dir = candidato;
    candidato->esq = neto;

    if (neto != NULL)
        neto->pai = candidato;

    filho->pai = candidato->pai;
    candidato->pai = filho;

    candidato->fb = filho->fb = 0;

    return filho;
}

No_avl *rotacao_esq(No_avl *candidato)
{

    No_avl *filho = candidato->dir;
    No_avl *neto = filho->esq;

    filho->esq = candidato;
    candidato->dir = neto;

    if (neto != NULL)
        neto->pai = candidato;

    filho->pai = candidato->pai;
    candidato->pai = filho;

    candidato->fb = filho->fb = 0;

    return filho;
}

No_avl *rotacao_esq_dir(No_avl *candidato)
{

    No_avl *filho = candidato->esq;
    No_avl *neto = filho->dir;

    candidato->esq = rotacao_esq(filho);
    filho = rotacao_dir(candidato);

    if (neto->fb == 1)
    {
        candidato->fb = -1;
        filho->fb = neto->fb = 0;
    }
    else
    {
        if (neto->fb == -1)
        {
            candidato->fb = neto->fb = 0;
            filho->fb = 1;
        }
        else // neto->fb ==0
        {
            candidato->fb = neto->fb = filho->fb = 0;
        }
    }

    return filho;
}

No_avl *rotacao_dir_esq(No_avl *candidato)
{

    No_avl *filho = candidato->dir;
    No_avl *neto = filho->esq;

    candidato->dir = rotacao_dir(filho);
    filho = rotacao_esq(candidato);
    if (neto->fb == 1)
    {
        candidato->fb = -1;
        filho->fb = neto->fb = 0;
    }
    else
    {
        if (neto->fb == -1)
        {
            candidato->fb = neto->fb = 0;
            filho->fb = 1;
        }
        else // neto->fb ==0
        {
            candidato->fb = neto->fb = filho->fb = 0;
        }
    }

    return filho;
}

void em_ordem_avl(Avl *T)
{
    if (T != NULL)
        em_ordem_no_avl(T->raiz);
}

void em_ordem_no_avl(No_avl *raiz)
{
    if (raiz != NULL)
    {

        em_ordem_no_avl(raiz->esq);
        printf("%d ", raiz->chave);
       // printf("%d (%d)", raiz->chave, raiz->fb);
       
        em_ordem_no_avl(raiz->dir);
    }
}

void libera_avl(No_avl* raiz)
{
    if (raiz != NULL)
    {
        libera_avl(raiz->esq);
        libera_avl(raiz->dir);
        free(raiz);
    }
}

void verificar_nos(Avl *T) {
    if (T != NULL) {
        nos(T->raiz);
    }
}

void nos(No_avl *raiz) {
    if (raiz != NULL) {
        qtd_nos_lados(raiz);
        nos(raiz->esq);
        printf("[%d]%d(%d) ", raiz->qtd_chaves_esq, raiz->chave, raiz->qtd_chaves_dir);
        nos(raiz->dir);
    }
}

int qtd_nos_lados(No_avl* raiz) {
    if (raiz == NULL) return 0;

    raiz->qtd_chaves_esq = qtd_nos_lados(raiz->esq);
    raiz->qtd_chaves_dir = qtd_nos_lados(raiz->dir);

    return raiz->qtd_chaves_esq + raiz->qtd_chaves_dir + 1;
}