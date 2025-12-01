// Arquivo que descreve as funcoes que criam a lógica dos eventos
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

    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

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
}

void evento_espera(struct mundo *w, struct evento *ev)
{
    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",ev->tempo,ev->id_1,
    ev->id_2,fila_tamanho(w->bases[ev->id_2]->f_espera));
    
    fila_insere(w->bases[ev->id_2]->f_espera,ev->id_1);

    /*  checa se alcancou o maior tamanho de fila da base.
        como o evento espera sempre insere apenas uma pessoa, podemos garantir que sempre sera + 1
        o novo recorde. */
    if (fila_tamanho(w->bases[ev->id_2]->f_espera) > w->bases[ev->id_2]->f_max)
        w->bases[ev->id_2]->f_max++;
    
    fprio_insere(w->lef,ev,EV_AVISA,ev->tempo);
}

void evento_desiste(struct mundo *w, struct evento *ev)
{

    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

    printf("%6d: DESIST HEROI %2d BASE %d\n",ev->tempo,ev->id_1,ev->id_2);
    ev->id_2 = aleat(0,w->n_bases-1);
    fprio_insere(w->lef,ev,EV_VIAJA,ev->tempo);    
}

void evento_avisa(struct mundo *w, struct evento *ev)
{
    int id_primeiro_da_fila;

    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

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
    // libera o ev antigo que nao consegue mais ser reutilizado
    free(ev);
}

void evento_entra(struct mundo *w, struct evento *ev)
{
    int tpb;

    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

    w->herois[ev->id_1]->base = ev->id_2;
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

    if(w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

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

    if(w->herois[ev->id_1]->base < 0 || w->herois[ev->id_1]->morto == 1)
    {
        free(ev);
        return;
    }

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
    printf("%6d: MORRE  HEROI %2d MISSAO %d\n",ev->tempo,ev->id_1,ev->id_2);

    w->herois[ev->id_1]->morto = 1;
    if (w->herois[ev->id_1]->base < 0)
    {
        free(ev);
        return;
    }
    ev->id_2 = w->herois[ev->id_1]->base;
    cjto_retira(w->bases[ev->id_2]->h_presentes,ev->id_1);
    fprio_insere(w->lef,ev,EV_AVISA,ev->tempo);
    w->herois[ev->id_1]->base = -1;
}

void evento_missao(struct mundo *w, struct evento *ev)
{
    struct cjto_t *habilidades_b = NULL;
    struct cjto_t *aux = NULL;
    struct cjto_t *habilidades_b_vencedora = NULL;
    int distancia_m,menor_distancia,menor_distancia_com_hab;
    int bmp = -1;              
    int bmp_com_habilidades = -1; 

    menor_distancia = N_TAMANHO_DO_MUNDO * N_TAMANHO_DO_MUNDO;
    menor_distancia_com_hab = menor_distancia;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", ev->tempo, ev->id_1, w->missoes[ev->id_1]->tentativas);
    cjto_imprime(w->missoes[ev->id_1]->habilidades);
    printf(" ]\n");

    w->total_tent++;
    w->missoes[ev->id_1]->tentativas++;
    if (w->missoes[ev->id_1]->tentativas > w->tent_max)
        w->tent_max = w->missoes[ev->id_1]->tentativas;

    // faz o calculo das distancias e habilidades das bases de todos os lados
    for (int i = 0; i < w->n_bases; i++)
    {
        if (cjto_card(w->bases[i]->h_presentes) == 0)
            continue;

        distancia_m = distancia_cartesiana(w->missoes[ev->id_1]->local_missao, w->bases[i]->local_base);

        // descobre a menor distancia geral
        if (distancia_m < menor_distancia) {
            menor_distancia = distancia_m;
            bmp = i;
        }

        habilidades_b = cjto_cria(N_HABILIDADES);
        for (int j = 0; j < w->n_herois; j++)
        {
            if (cjto_pertence(w->bases[i]->h_presentes, j)) {
                aux = cjto_uniao(habilidades_b, w->herois[j]->habilidades);
                cjto_destroi(habilidades_b);
                habilidades_b = aux;
            }
        }

        if (cjto_contem(habilidades_b, w->missoes[ev->id_1]->habilidades) && distancia_m < menor_distancia_com_hab) {
            menor_distancia_com_hab = distancia_m;

            if (habilidades_b_vencedora)
                cjto_destroi(habilidades_b_vencedora);
            habilidades_b_vencedora = cjto_copia(habilidades_b);

            bmp_com_habilidades = i;
        }

        cjto_destroi(habilidades_b);
    }

    // caso que tem uma base com as habilidades da missao
    if (bmp_com_habilidades >= 0)
    {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",
               ev->tempo, ev->id_1, bmp_com_habilidades);
        cjto_imprime(habilidades_b_vencedora);
        printf(" ]\n");

        for (int i = 0; i < w->n_herois; i++) {
            if (w->herois[i]->base == bmp_com_habilidades)
                w->herois[i]->xp++;
        }

        w->bases[bmp_com_habilidades]->missoes++;
        w->n_missoes_concluidas++;

        if (w->missoes[ev->id_1]->tentativas < w->tent_min)
            w->tent_min = w->missoes[ev->id_1]->tentativas;

        cjto_destroi(habilidades_b_vencedora);
        free(ev);
        return;
    }

    // caso em que nao ha base mas da para usar o composto v
    if (w->n_compostos_v > 0 && (ev->tempo % 2500 == 0) && bmp >= 0)
    {
        struct heroi *heroi_morto = NULL;
        int maior_xp = -1;

        // acha o heroi com maior experiencia
        for (int i = 0; i < w->n_herois; i++) {
            if (w->herois[i]->base == bmp) {
                if (w->herois[i]->xp > maior_xp) {
                    heroi_morto = w->herois[i];
                    maior_xp = w->herois[i]->xp;
                }
            }
        }

        if (heroi_morto) {
            w->n_compostos_v--;
            w->bases[bmp]->missoes++;
            w->n_missoes_concluidas++;

            if (w->missoes[ev->id_1]->tentativas < w->tent_min)
                w->tent_min = w->missoes[ev->id_1]->tentativas;

            heroi_morto->xp++;

            // em id_2 vai a missao e em id 1 o heroi que morrera
            ev->id_2 = ev->id_1;         
            ev->id_1 = heroi_morto->id; 
            
            fprio_insere(w->lef, ev, EV_MORRE, ev->tempo);
            if (habilidades_b_vencedora) cjto_destroi(habilidades_b_vencedora);
                return;
        }
    }

    // caso que nao conseguiu concluir a missao, entao adia 24 horas
    printf("%6d: MISSAO %d IMPOSSIVEL\n", ev->tempo, ev->id_1);
    ev->tempo = ev->tempo + (24 * 60);
    fprio_insere(w->lef, ev, EV_MISSAO, ev->tempo);

    if (habilidades_b_vencedora) cjto_destroi(habilidades_b_vencedora);
}

void evento_fim(struct mundo *w, struct evento *ev)
{
    struct heroi *h;
    struct base *b;
    double porcentagem_missoes;
    int qnt_mortos = 0;
    printf("%6d: FIM\n",ev->tempo);
    
    //imprime estatisticas dos herois
    for(int i=0; i < w->n_herois; i++)
    {
        h = w->herois[i];
        if(h->morto)
        {
            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ",h->id,h->paciencia,h->velocidade,h->xp);
            qnt_mortos++;
        }
        else
            printf("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ",h->id,h->paciencia,h->velocidade,h->xp);
        cjto_imprime(h->habilidades);
        printf(" ]\n");
    }

    //imprime estatisticas das bases
    for(int i=0; i < w->n_bases; i++)
    {
        b = w->bases[i];
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",b->id,b->n_max,b->f_max,b->missoes);
    }
    printf("EVENTOS TRATADOS: %d\n",w->ev_tratados);
    porcentagem_missoes = ((float)w->n_missoes_concluidas/w->n_missoes) * 100;
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",w->n_missoes_concluidas,w->n_missoes,porcentagem_missoes);
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",w->tent_min,w->tent_max,(float)w->total_tent / w->n_missoes);
    printf("TAXA MORTALIDADE: %.1f%%\n",((float) qnt_mortos / w->n_herois) * 100);
    free(ev);
}

