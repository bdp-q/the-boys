#ifndef ENTIDADES
#define ENTIDADES
#include "conjunto.h"
#include "fila.h"

// ----------------------- definição dos structs que formam as entidades --------------------------------


// descreve o heroi e seus atributos
struct heroi 
{
    int id;                         // identificador do heroi
    struct cjto_t *habilidades;     // conjunto de habilidades que o herói tem
    int paciencia;                  // indicador de paciência do herói
    int velocidade;                 // indicador de velocidade do herói
    int xp;                         // indicador de números de missões (experiência) do herói
    int base;                       // identificador da base atual em que o herói está

};

// descreve um par de coordenadas em um plano cartesiano
struct localizacao 
{
    int x;
    int y;
};

// descreve a base e suas características
struct base
{
    int id;                         // identificador da base
    int n_max;                      // lotação máxima de heróis na base
    struct cjto_t *h_presentes;     // conjunto de heróis presentes na base
    struct fila_t *f_espera;        // fila de espera de heróis tentando entrar na base
    struct localizacao local_base; // coordenadas da base no mundo
};

// descreve cada missão
struct missao 
{
    int id;                             // identificador da missão
    struct cjto_t *habilidades;         // conjunto de habilidades necessárias para concluir essa missão
    struct localizacao local_missao;   // coordenadas do local da missão no mundo
};

// descreve o mundo e as informações dele
struct mundo
{
    int n_herois;                       // quantidade de heróis no mundo                  
    struct heroi **herois;              // vetor que contém os heróis

    int n_bases;                        // quantidade de bases no mundo
    struct base **bases;                // vetor que contém as bases

    int n_missoes;                      // quantidade de missões da simulação
    struct missao **missoes;            // vetor com as missões

    int n_habilidades;                  // quantidade de habilidades que existem no mundo
    int n_compostos_v;                  // quantidade de compostos v disponíveis

    struct localizacao tam_mundo;        // definição do tamanho do mundo
    int min_atual;                      // inteiro que define o minuto atual que estamos na simulação
};

// -----------------------------------------------------------------------------------------------------

// inicializa o universo e define suas entidades e características
// retorna um ponteiro para esse universo.
struct mundo *inicializa_mundo();


// acaba o mundo e destrói suas entidades
// retorna NULL.
struct mundo * destroi_mundo(struct mundo *w);

#endif