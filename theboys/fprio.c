// TAD Fila de prioridades (FPRIO) genérica
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fprio_t *fprio_cria()
{
	struct fprio_t *f;

	if(!(f = malloc(sizeof(struct fprio_t))))
		return NULL;

	f->prim = NULL;
	f->num = 0;
	return f;
}

struct fprio_t *fprio_destroi (struct fprio_t *f)
{
	struct fpnodo_t *aux;
	struct fpnodo_t *aux_prox;

	aux_prox = f->prim;
	while (aux_prox != NULL)
	{
		aux = aux_prox;
		aux_prox = aux_prox->prox;
		free(aux->item);
		free(aux);
	}

	free(f);

	return NULL;
}
/* função para ver se não está sendo inserido o mesmo ponteiro duas vezes */
int checa_item(struct fprio_t *f, void *item)
{
	struct fpnodo_t *aux_prox;

	aux_prox = f->prim;
	while (!(aux_prox == NULL))
	{
		if (aux_prox->item == item)
			return 1;
		aux_prox = aux_prox->prox;
	}
	return 0;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
	struct fpnodo_t *novo_nodo;
	struct fpnodo_t *aux_prox;

	/* checa a validade dos parametros*/
	if((!f) || (!item))
		return -1;
		
	if (checa_item(f,item))
		return -1;

	if(!(novo_nodo = malloc(sizeof(struct fpnodo_t))))
		return -1;

	novo_nodo->item = item;
	novo_nodo->tipo = tipo;
	novo_nodo->prio = prio;

	aux_prox = f->prim;
	/* verifica o caso em que não existe o nodo inicial, para evitar segfault */
	if (aux_prox == NULL || prio < f->prim->prio)
	{
		novo_nodo->prox = f->prim;
		f->prim = novo_nodo;
	}

	else
	{
		while (!((aux_prox->prox == NULL || prio < aux_prox->prox->prio)))
 			aux_prox = aux_prox->prox;	

		novo_nodo->prox = aux_prox->prox;
		aux_prox->prox = novo_nodo;
	}

	f->num++;
	return f->num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
	struct fpnodo_t *aux;
	struct fpnodo_t *item;

	/* checa a validade dos parametros*/
	if (!tipo || !prio)
		return NULL;
	if (!f || f->prim == NULL)
		return NULL;

	*tipo = f->prim->tipo;
	*prio = f->prim->prio;
	item = f->prim->item;

	aux = f->prim;
	f->prim = f->prim->prox;
	free(aux);

	f->num--;
	return item;
}

int fprio_tamanho (struct fprio_t *f)
{
	if (!f)
		return -1;
	return f->num;
}

void fprio_imprime (struct fprio_t *f)
{
	 struct fpnodo_t *aux_prox;

	aux_prox = f->prim;


	/* checa se tem algo a imprimir*/
	if (!f || !f->prim)
		return;

	while (!((aux_prox->prox == NULL)))
	{
		printf("(%d %d) ",aux_prox->tipo, aux_prox->prio);
		aux_prox = aux_prox->prox;
	}
	printf("(%d %d)",aux_prox->tipo, aux_prox->prio);
	return;
}