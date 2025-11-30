// Arquivo que define os structs que formam as entidades do the boys
#ifndef ENTIDADES
#define ENTIDADES
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

// descreve o heroi e seus atributos
struct heroi 
{
    int id;                         // identificador do heroi
    struct cjto_t *habilidades;     // conjunto de habilidades que o herói tem
    int paciencia;                  // indicador de paciência do herói
    int velocidade;                 // indicador de velocidade do herói
    int xp;                         // indicador de números de missões (experiência) do herói
    int base;                       // identificador da base atual em que o herói está
    int morto;                      // bool que identifica se esta vivo (0) ou morto (1)
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
    int n_max;                      // lotação maxima de heróis na base
    int f_max;                      // quantidade maxima de herois que ja estiveram na fila
    int missoes;                    // quantidade de missoes que essa base participou
    struct cjto_t *h_presentes;     // conjunto de heróis presentes na base
    struct fila_t *f_espera;        // fila de espera de heróis tentando entrar na base
    struct localizacao local_base;  // coordenadas da base no mundo                      
};

// descreve cada missão
struct missao 
{
    int id;                             // identificador da missão
    struct cjto_t *habilidades;         // conjunto de habilidades necessárias para concluir essa missão
    struct localizacao local_missao;    // coordenadas do local da missão no mundo
    int tentativas;                     // tentativas feitas de concluir a missao
};

// descreve o mundo e as informações dele
struct mundo
{
    int n_herois;                       // quantidade de heróis no mundo                  
    struct heroi **herois;              // vetor que contém os heróis

    int n_bases;                        // quantidade de bases no mundo
    struct base **bases;                // vetor que contém as bases

    int n_missoes;                      // quantidade de missões da simulação
    int n_missoes_concluidas;           // quantidade de missoes concluidas na simulacao
    int tent_max;                       // quantidade de tentativas da missao ha mais tempo
    int tent_min;                       // missao concluida com menor quantidade de tentativas
    int total_tent;                     // total de tentativas de missoes;
    struct missao **missoes;            // vetor com as missões

    int n_habilidades;                  // quantidade de habilidades que existem no mundo
    int n_compostos_v;                  // quantidade de compostos v disponíveis
    int ev_tratados;                    // quantidade de eventos tratados durante a simulacao

    struct localizacao tam_mundo;       // definição do tamanho do mundo
    int min_atual;                      // inteiro que define o minuto atual que estamos na simulação

    struct fprio_t *lef;                // lista de eventos futuros a qual a ordem dos eventos eh guardada
};

#endif