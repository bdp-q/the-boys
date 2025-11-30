#ifndef FUNCEXTRAS
#define FUNCEXTRAS

#include "entidades.h"

// retorna um número aleatório entre min e max
int aleat(int min, int max);

// retorna a distancia cartesiana entre dois pontos de um plano cartesiano
double distancia_cartesiana(struct localizacao p1, struct localizacao p2);

#endif