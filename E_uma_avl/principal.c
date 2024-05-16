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

struct no_avl
{
    int chave;
    struct no_avl *esq, *dir, *pai;
    int fb;
};
typedef struct no_avl No_avl;

struct avl
{
    No_avl *raiz;
    int altura;
    int qtde_chaves;
};
typedef struct avl Avl;

//PROTÓTIPOS
Abb* criar_abb();
No_Abb* criar_noabb(int valor);
void inserir_no_abb(Abb* T, int valor);


No_avl *cria_no_avl(int chave);
Avl *cria_avl();
Avl *insercao_avl(Avl *t, int chave);
No_avl *colocar_no_avl(No_avl *raiz, int chave);
void recalcular_fb(No_avl *candidato, int chave);
No_avl *rotacao_geral(No_avl *candidato);

No_avl *rotacao_dir(No_avl *candidato);
No_avl *rotacao_esq(No_avl *candidato);
No_avl *rotacao_dir_esq(No_avl *candidato);
No_avl *rotacao_esq_dir(No_avl *candidato);

void verifica_e_avl (Abb *arvore, Avl *t);
int verificacao(No_Abb* raiz_abb, No_avl *raiz_avl);

void libera_avl(No_avl *raiz);
void libera_abb(No_Abb *raiz);

void pre_ordem_abb(Abb *T);
void pre_ordem_no_abb(No_Abb *raiz);

void pre_ordem_avl(Avl *T);
void pre_ordem_no_avl(No_avl *raiz);

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

void libera_avl(No_avl *raiz)
{
    if (raiz != NULL)
    {
        libera_avl(raiz->esq);
        libera_avl(raiz->dir);
        free(raiz);
    }
}

void libera_abb(No_Abb *raiz)
{
    if (raiz != NULL)
    {
        libera_abb(raiz->esq);
        libera_abb(raiz->dir);
        free(raiz);
    }
}

void pre_ordem_abb(Abb *T)
{
    if (T != NULL)
    {
        pre_ordem_no_abb(T->raiz);
    }
}

void pre_ordem_no_abb(No_Abb *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        pre_ordem_no_abb(raiz->esq);
        pre_ordem_no_abb(raiz->dir);
    }
}

void pre_ordem_avl(Avl *T)
{
    if (T != NULL)
    {
        pre_ordem_no_avl(T->raiz);
    }
}

void pre_ordem_no_avl(No_avl *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->chave);
        pre_ordem_no_avl(raiz->esq);
        pre_ordem_no_avl(raiz->dir);
    }
}

void verifica_e_avl (Abb *arvore, Avl *t) {
    int resultado = verificacao(arvore->raiz, t->raiz);
    if (resultado == 1)
        printf("sim\n");
    else
        printf("nao\n");

}

int verificacao(No_Abb* raiz_abb, No_avl *raiz_avl) {
    if (raiz_abb == NULL && raiz_avl == NULL) {
        return 1;
    }
    if (raiz_abb == NULL || raiz_avl == NULL) {
        return 0;
    }
    if(raiz_abb->valor != raiz_avl->chave){
        return 0;
    }
    return verificacao(raiz_abb->esq, raiz_avl->esq) && verificacao(raiz_abb->dir, raiz_avl->dir);
}

int main()
{

    int i = 0;
    int n;
    scanf("%d", &n);
    int valor = 0; 

    for (i = 0; i < n; i++)
    {
        Avl *t = NULL;
        Abb *arvore = criar_abb();
        while (scanf("%d", &valor), valor != -1)
        {
            t = insercao_avl(t, valor);
            inserir_no_abb(arvore, valor);
        }

        verifica_e_avl(arvore, t);
        libera_avl(t->raiz);
        libera_abb(arvore->raiz);
        
        free(t);
        free(arvore);
    }
    return 0;
}