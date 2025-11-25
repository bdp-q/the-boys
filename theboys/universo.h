#ifndef UNIVERSO
#define UNIVERSO

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_DO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)

// inicializa o universo e define suas entidades, características e eventos iniciais
// retorna um ponteiro para esse universo.
struct mundo *inicializa_mundo();

// acaba o mundo e destrói suas entidades
// retorna NULL.
struct mundo * destroi_mundo(struct mundo *w);

#endif