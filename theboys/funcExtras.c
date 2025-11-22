//arquivo com funções extras

#include <stdlib.h>

int aleat(int min, int max)
{
    return min + rand() % (max - min + 1);
}
