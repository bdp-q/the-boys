#ifndef EVENTOS
#define EVENTOS

#include "universo.h"

#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MORRE 8
#define EV_MISSAO 9
#define EV_FIM 10

// struct que guarda informacoes importantes de um evento
struct evento {
    int tempo;  // o momento em que o evento ira acontecer
    int id_1;   // um id ou do heroi ou da missao ou da base que esta atrelado a esse evento
    int id_2;   // outro id igual ao anterior para eventos que usam duas entidades
};

// chama o evento do heroi chegando a uma base e decide se ele ira tentar entrar ou ir embora.
void evento_chega(struct mundo *w, struct evento *ev);

// chama o evento de espera, insere o heroi no fim da fila e avisa o porteiro de sua chegada 
void evento_espera(struct mundo *w, struct evento *ev);

// chama o evento em que o heroi desiste e aleatoriamente escolhe outra base para viajar
void evento_desiste(struct mundo *w, struct evento *ev);

// chama o evento em que o porteiro eh avisado e deixa entrar os herois da fila ate a lotacao maxima
void evento_avisa(struct mundo *w, struct evento *ev);

void evento_entra(struct mundo *w, struct evento *ev);

void evento_sai(struct mundo *w, struct evento *ev);

void evento_viaja(struct mundo *w, struct evento *ev);

void evento_morre(struct mundo *w, struct evento *ev);

void evento_missao(struct mundo *w, struct evento *ev);

void evento_fim(struct mundo *w, struct evento *ev);


#endif