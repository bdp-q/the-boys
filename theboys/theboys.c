// programa principal do projeto "The Boys - 2025/2"
// Autor: Breno Demio Padilha, GRR 20252088

// seus #includes vão aqui
#include <stdlib.h>
#include "entidades.h"
#include "universo.h"
#include "simulacao.h"
// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
  // iniciar o mundo
  struct mundo *w;
  
  srand(11231321);
  w = inicializa_mundo();
  // executar o laço de simulação
  simula_mundo(w);
  // destruir o mundo
  w = destroi_mundo(w);
  return (0) ;
}

