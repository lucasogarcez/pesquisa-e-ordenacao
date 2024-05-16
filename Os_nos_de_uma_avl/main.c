#include "avl.h"

int main()
{

  Avl *t = NULL;
  int i = 0;
  int n;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    t = NULL;
    int valor = 0;
    while (scanf("%d", &valor), valor != -1)
    {
      t = insercao_avl(t, valor);
    }
    verificar_nos(t);
    libera_avl(t->raiz);
  }

  return 0;
}
