#include <stdlib.h>
#include "eventos.h"
#include "simulacao.h"
#include "fprio.h"

void simula_mundo(struct mundo *w)
{
    struct evento *ev_atual;
    int id_evento;
    int tempo;

    int fim = 0;
    while (!fim)
    { 
        ev_atual = fprio_retira(w->lef,&id_evento,&tempo);
        
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

}