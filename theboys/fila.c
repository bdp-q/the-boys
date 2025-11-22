// TAD Fila 
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria ()
{
	struct fila_t *f;

	if (!(f = malloc(sizeof(struct fila_t))))
		return NULL;

	f->prim = NULL;
	f->ult = NULL;
	f->num = 0;
	return f;

}

struct fila_t *fila_destroi (struct fila_t *f)
{
	struct fila_nodo_t *aux, *aux_prox;

	aux_prox = f->prim;
	while (aux_prox != NULL)
	{
		aux = aux_prox;
		aux_prox = aux_prox->prox;
		free(aux);
	}

	free(f);

	return NULL;
}

int fila_vazia (struct fila_t *f)
{
	if(f->prim == NULL)
		return 1;
	return 0;
}

int fila_insere (struct fila_t *f, int item)
{
	struct fila_nodo_t *novo_nodo;
	if (!(novo_nodo = malloc(sizeof(struct fila_nodo_t))))
		return 0;
    /* se a fila não for vazia coloca no fim, senão coloca no primeiro lugar da fila*/
	if(!fila_vazia(f))
		f->ult->prox = novo_nodo;

	else
		f->prim = novo_nodo;

	novo_nodo->item = item;
	novo_nodo->prox = NULL;
	f->num++;
	return 1;
}

int fila_retira (struct fila_t *f, int *item)
{
	struct fila_nodo_t *aux;

	if (fila_vazia(f))
		return 0;

	*item = f->prim->item;
	aux = f->prim;
	f->prim = f->prim->prox;
	free(aux);
	f->num--;
	return 1;
}

int fila_tamanho (struct fila_t *f)
{
	if (!f)
		return -1;
	return f->num;
}

void fila_imprime (struct fila_t *f)
{
	 struct fila_nodo_t *aux_prox;

	aux_prox = f->prim;


	/* checa se tem algo a imprimir*/
	if (!f || !f->prim)
		return;

	while (aux_prox->prox != NULL)
	{
		printf("%d ",aux_prox->item);
		aux_prox = aux_prox->prox;
	}
	printf("%d",aux_prox->item);
	return;
}