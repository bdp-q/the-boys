//arquivo com funções extras

#include <stdlib.h>
#include <math.h>
#include "entidades.h"

int aleat(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int distancia_cartesiana (struct localizacao p1, struct localizacao p2)
{
    return sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
} 