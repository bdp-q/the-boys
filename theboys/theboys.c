// programa principal do projeto "The Boys - 2025/2"
// Autor: Breno Demio Padilha, GRR 20252088

// seus #includes vão aqui
#include <stdlib.h>
#include <time.h>
// seus #defines vão aqui
#include "entidades.h"
#include "universo.h"
#include "simulacao.h"
#include "fprio.h"
#include "eventos.h"
// minimize o uso de variáveis globais

// programa principal
int main ()
{
  // iniciar o mundo
  struct mundo *w;
  struct evento *ev_atual;
  int id_evento;
  int tempo;
  srand(time(NULL));

  w = inicializa_mundo();
  // executar o laço de simulação
  
  int fim = 0;
  while (!fim)
  { 
    ev_atual = fprio_retira(w->lef,&id_evento,&tempo);
    w->ev_tratados++;
    switch (id_evento)
      {
      case EV_CHEGA:
          evento_chega(w,ev_atual);
          break;
      
      case EV_ESPERA:
          evento_espera(w,ev_atual);
          break;

      case EV_DESISTE:
          evento_desiste(w,ev_atual);
          break;

      case EV_AVISA:
          evento_avisa(w,ev_atual);
          break;

      case EV_ENTRA:
          evento_entra(w,ev_atual);
          break;

      case EV_SAI:
          evento_sai(w,ev_atual);
          break;

      case EV_VIAJA:
          evento_viaja(w,ev_atual);
          break;

      case EV_MORRE:
          evento_morre(w,ev_atual);
          break;
      
      
      case EV_MISSAO:
          evento_missao(w,ev_atual);
          break;

      case EV_FIM:
          evento_fim(w,ev_atual);
          fim = 1;
          break;
      }        
  }
  
  // destruir o mundo
  w = destroi_mundo(w);
  return (0) ;
}

