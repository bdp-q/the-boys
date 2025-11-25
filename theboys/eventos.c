#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "entidades.h"
#include "fila.h"
#include "fprio.h"
#include "funcExtras.h"
void evento_chega(struct mundo *w, struct evento *ev)
{
    int espera;

    w->herois[ev->id_1]->base = ev->id_2;
    if ((cjto_card(w->bases[ev->id_2]->h_presentes) < w->bases[ev->id_2]->n_max)
    && (fila_tamanho(w->bases[ev->id_2]->f_espera) == 0))
        espera = 1;
    else
        espera = (w->herois[ev->id_1]->paciencia) > (10 * fila_tamanho(w->bases[ev->id_2]->f_espera));
    
    if (espera)
    {    
        fprio_insere(w->lef,ev,EV_ESPERA,ev->tempo);
        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n",ev->tempo,ev->id_1,
        ev->id_2,cjto_card(w->bases[ev->id_2]->h_presentes),w->bases[ev->id_2]->n_max);
    }
    else
    {
        fprio_insere(w->lef,ev,EV_DESISTE,ev->tempo);
        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n",ev->tempo,ev->id_1,
        ev->id_2,cjto_card(w->bases[ev->id_2]->h_presentes),w->bases[ev->id_2]->n_max);
    }
    
    return; //boto ou nao :( perguntar castilho
}

void evento_espera(struct mundo *w, struct evento *ev)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",ev->tempo,ev->id_1,
    ev->id_2,fila_tamanho(w->bases[ev->id_2]->f_espera));
    
    fila_insere(w->bases[ev->id_2]->f_espera,ev->id_1);   
    fprio_insere(w->lef,ev,EV_AVISA,ev->tempo);
}

void evento_desiste(struct mundo *w, struct evento *ev)
{
    printf("%6d: DESIST HEROI %2d BASE %d\n",ev->tempo,ev->id_1,ev->id_2);
    ev->id_2 = aleat(0,w->n_bases-1);
    fprio_insere(w->lef,ev,EV_VIAJA,ev->tempo);    
}

void evento_avisa(struct mundo *w, struct evento *ev)
{
    int id_primeiro_da_fila;

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ",ev->tempo,
    ev->id_2,cjto_card(w->bases[ev->id_2]->h_presentes),w->bases[ev->id_2]->n_max);
    fila_imprime(w->bases[ev->id_2]->f_espera);
    printf(" ]\n");
    while (cjto_card(w->bases[ev->id_2]->h_presentes) < w->bases[ev->id_2]->n_max 
    && fila_tamanho(w->bases[ev->id_2]->f_espera) != 0)
    {
        struct evento *novo_ev;

        fila_retira(w->bases[ev->id_2]->f_espera,&id_primeiro_da_fila);
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",ev->tempo,ev->id_2,id_primeiro_da_fila);
        
        //cria novo evento dado que entrou um evento na funcao, mas podem sair varios.
        if(!(novo_ev = malloc(sizeof(struct evento))))
            return;
        novo_ev->tempo = ev->tempo;
        novo_ev->id_1 = id_primeiro_da_fila;
        novo_ev->id_2 = ev->id_2;

        fprio_insere(w->lef,novo_ev,EV_ENTRA,novo_ev->tempo);
    }
    // libera o ev antigo que acabou
    free(ev);
}

void evento_entra(struct mundo *w, struct evento *ev)
{
    printf("entrei\n");
    free(ev);
}

void evento_sai(struct mundo *w, struct evento *ev)
{
    printf("sai");
}

void evento_viaja(struct mundo *w, struct evento *ev)
{
    printf("viajei");
    free(ev);
}

void evento_morre(struct mundo *w, struct evento *ev)
{
    printf("morri");
}

void evento_missao(struct mundo *w, struct evento *ev)
{
   // printf("missao criada\n");
   free(ev);
}

void evento_fim(struct mundo *w, struct evento *ev)
{
    printf("cabo");
    free(ev);
}

