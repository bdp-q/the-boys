// Arquivo que inicializa e destrói o Universo e suas entidades do the Boys

#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "funcExtras.h"
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_DO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)


// função que define os atributos de um herói
void inicializa_heroi(struct heroi *h, int i)
{
    int qnt_habilidades;

    h->id = i;
    h->xp = 0;
    h->paciencia = aleat(0,100); 
    h->velocidade = aleat(50,5000);
    qnt_habilidades = aleat(1,3);
    h->habilidades = cjto_aleat(qnt_habilidades,3);

}

// função que define as características de uma base
void inicializa_base(struct base *b, int i)
{
    b->id = i;
    b->local_base.x = aleat(0,N_TAMANHO_DO_MUNDO-1);
    b->local_base.y = aleat(0,N_TAMANHO_DO_MUNDO-1);
    b->n_max = aleat(3,10);
    b->h_presentes = cjto_cria(b->n_max);
    b->f_espera = fila_cria();
}

// função que define as especificações da missão
void inicializa_missao(struct missao *m, int i)
{
    int qnt_habilidades;

    m->id = i;
    m->local_missao.x = aleat(0,N_TAMANHO_DO_MUNDO-1);
    m->local_missao.y = aleat(0,N_TAMANHO_DO_MUNDO-1);
    qnt_habilidades = aleat(6,10);
    m->habilidades = cjto_aleat(qnt_habilidades,N_HABILIDADES);

}

struct mundo *inicializa_mundo()
{
    struct mundo *w;
    if(!(w = malloc(sizeof(struct mundo))))
		return NULL;

    w->min_atual = T_INICIO;
    w->tam_mundo.x = N_TAMANHO_DO_MUNDO;
    w->tam_mundo.y = N_TAMANHO_DO_MUNDO;
    w->n_compostos_v = N_COMPOSTOS_V;
    w->n_habilidades = N_HABILIDADES;

    // cria os heróis
    w->n_herois = N_HEROIS;
    if(!(w->herois = malloc(w->n_herois * sizeof(struct heroi*))))
        return NULL;
    
    for(int i = 0; i < w->n_herois; i++)
    {
        if(!(w->herois[i] = malloc(sizeof(struct heroi))))
            return NULL;
        inicializa_heroi(w->herois[i],i);
    }

    // cria as bases
    w->n_bases = N_BASES;
    if(!(w->bases = malloc(w->n_bases * sizeof(struct base*))))
        return NULL;
    
    for(int i = 0; i < w->n_bases; i++)
    {
        if(!(w->bases[i] = malloc(sizeof(struct base))))
            return NULL;
        inicializa_base(w->bases[i],i);
    }

    //cria as missões
    w->n_missoes = N_MISSOES;
    if(!(w->missoes = malloc(w->n_missoes * sizeof(struct missao*))))
        return NULL;
    
    for(int i = 0; i < w->n_missoes; i++)
    {
        if(!(w->missoes[i] = malloc(sizeof(struct missao))))
            return NULL;
        inicializa_missao(w->missoes[i],i);
    }

    return w;
}

struct mundo *destroi_mundo(struct mundo *w)
{
    
    // liberando os heróis
    for(int i = 0; i < w->n_herois; i++)
    {
        cjto_destroi(w->herois[i]->habilidades);
        free(w->herois[i]);
    }
    free(w->herois);

    // liberando as bases  
    for(int i = 0; i < w->n_bases; i++)
    {
        fila_destroi(w->bases[i]->f_espera);
        cjto_destroi(w->bases[i]->h_presentes);
        free(w->bases[i]);
    }
    free(w->bases);

    // liberando as missoes
    for(int i = 0; i < w->n_missoes; i++)
    {
        cjto_destroi(w->missoes[i]->habilidades);
        free(w->missoes[i]);
    }
    free(w->missoes);

    free(w);
    return NULL;
}

