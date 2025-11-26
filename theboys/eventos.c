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
        cjto_insere(w->bases[ev->id_2]->h_presentes,id_primeiro_da_fila);
        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",ev->tempo,ev->id_2,id_primeiro_da_fila);
        
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
    int tpb;

    tpb = 15 + w->herois[ev->id_1]->paciencia * aleat(1,20);
    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",ev->tempo,ev->id_1,
        ev->id_2,cjto_card(w->bases[ev->id_2]->h_presentes),w->bases[ev->id_2]->n_max,
        ev->tempo + tpb);
    
    ev->tempo = ev->tempo + tpb; 
    fprio_insere(w->lef,ev,EV_SAI,ev->tempo);
}

void evento_sai(struct mundo *w, struct evento *ev)
{
    struct evento *novo_ev;
    int nova_base;

    cjto_retira(w->bases[ev->id_2]->h_presentes,ev->id_1);
    nova_base = aleat(0,w->n_bases-1);

    if(!(novo_ev = malloc(sizeof(struct evento))))
            return;
    novo_ev->tempo = ev->tempo;
    novo_ev->id_1 = ev->id_1;
    novo_ev->id_2 = nova_base;
    fprio_insere(w->lef,novo_ev,EV_VIAJA,novo_ev->tempo);

    fprio_insere(w->lef,ev,EV_AVISA,ev->tempo);

    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",ev->tempo,ev->id_1,
        ev->id_2,cjto_card(w->bases[ev->id_2]->h_presentes),w->bases[ev->id_2]->n_max);
}

void evento_viaja(struct mundo *w, struct evento *ev)
{
    int distancia_b;
    int t_duracao;
    
    distancia_b = distancia_cartesiana(w->bases[w->herois[ev->id_1]->base]->local_base,
        w->bases[ev->id_2]->local_base);
    t_duracao = distancia_b/w->herois[ev->id_1]->velocidade;
    
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",ev->tempo,
        ev->id_1,w->herois[ev->id_1]->base,ev->id_2,distancia_b,w->herois[ev->id_1]->velocidade,
        ev->tempo + t_duracao);

    ev->tempo = ev->tempo + t_duracao;
    fprio_insere(w->lef,ev,EV_CHEGA,ev->tempo);
}

void evento_morre(struct mundo *w, struct evento *ev)
{
    printf("morri");
}

void evento_missao(struct mundo *w, struct evento *ev)
{
    struct cjto_t *habilidades_b;
    int distancia_m, menor_distancia;
    int bmp = -1;

    menor_distancia = N_TAMANHO_DO_MUNDO; 
    for (int i = 0; i < w->n_bases; i++)
    {
        distancia_m = distancia_cartesiana(w->missoes[ev->id_1]->local_missao,w->bases[i]->local_base);
        
        habilidades_b = cjto_cria(N_HABILIDADES);
        for(int j = 0; j < N_HEROIS; j++)
        {
            if (w->herois[j]->base == i)
                cjto_uniao(w->herois[j]->habilidades,habilidades_b);
        }

        if (cjto_contem(habilidades_b,w->missoes[ev->id_1]->habilidades) && distancia_m < menor_distancia)
        {
            bmp = i;
            menor_distancia = distancia_m;
        }
        
        if(bmp >= 0)
            printf("possivel");

        else
            printf("impossivel");

    }
        
    free(ev);
}

void evento_fim(struct mundo *w, struct evento *ev)
{
    printf("cabo");
    free(ev);
}

