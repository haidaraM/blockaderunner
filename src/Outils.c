#include "Outils.h"
#include <assert.h>
#include <stdlib.h>



int randomInt(int borneInf, int borneSup)
{
    return rand()%(borneSup-borneInf) +borneInf;
}

unsigned char rectangleContient(Rectangle *rect, int x, int y)
{
	if ( x >= rect->x && y >= rect->y && x <= (rect->x + rect->largeur) && y <= (rect->y + rect->hauteur))
		return 1;
	return 0;
}




void tabDynInit(TabDyn *t)
{
	assert(t != NULL);
	
	t->tab = (void**)malloc(1*sizeof(void*));
	assert(t->tab != NULL);
	
	t->capacite = 1;
	t->taille   = 0;
}

void tabDynLibere(TabDyn *t)
{
	assert(t != NULL);
		
	free(t->tab);
	t->tab = NULL;
	t->capacite = -1;
	t->taille = 0;
}

void tabDynAjoute(TabDyn *t, void* element)
{
	int i;
	void **T;
	if (t->taille == t->capacite)
	{
		T = (void**)malloc(t->capacite * 2 * sizeof(void*));
		assert(T != NULL);
		for (i=0; i< t->taille; i++)
			T[i] = t->tab[i];
		free(t->tab);
		t->tab = T;
		t->capacite *= 2;
	}

	t->tab[t->taille] = element;
	t->taille++;
}

void* tabDynGetElement(TabDyn *t, int index)
{
	assert(t != NULL && index < t->taille);
	return t->tab[index];
}

/*
CelluleListe* celluleListeCreer(void *data)
{
	CelluleListe *cell = (CelluleListe*)malloc(sizeof(CelluleListe));
	cell->suiv = NULL;
	cell->data = data;
	
	return cell;
}

Liste* listeCreer()
{
	Liste* liste;
	liste = (Liste*)malloc(sizeof(Liste));
	assert(liste != NULL);

	listeInit(liste);
	return liste;
}

void listeDetruire(Liste *liste)
{
	listeLibere(liste);
	free(liste);
	liste = NULL;
}

void listeInit(Liste *liste)
{	
	assert(liste != NULL);
	
	liste->prem = NULL;
}

void listeLibere(Liste *liste)
{
	CelluleListe *cell, *suiv;

	assert(liste != NULL);
	cell = liste->prem;

	while (cell != NULL)
	{
		suiv = cell->suiv;
		free(cell);
		cell = suiv;
	}
}

void listeAjouteTete(Liste *liste, void *data)
{
	CelluleListe *cell, *nw;
	assert(liste != NULL);

	cell = liste->prem;
	if (cell == NULL)
	{
		liste->prem = celluleListeCreer(data);
		return;
	}

	nw = celluleListeCreer(data);
	nw->suiv = liste->prem;
	liste->prem = nw;
}

void listeAjouteQueue(Liste *liste, void *data)
{
	CelluleListe *nw, cell;
	assert(liste != NULL);

	cell = liste->prem;
	if (cell = NULL)
	{
		liste->prem = celluleListeCreer(data);
		return;
	}

	while(cell->suiv != NULL)
		cell = cell->suiv;
	
	cell->suiv = celluleListeCreer(data);
}

int listeGetIndex(Liste *liste, void *data)
{
	int index = 0;
	CelluleListe *cell;
	assert(liste != NULL);

	cell = liste->prem;
	while (cell != NULL)
	{
		if (data == cell->data)
			return index;
		index++;
	}
	
	return  -1;
}

void listeSupprime(Liste *liste, void *data)
{
	CelluleListe *cell, *prec;
	assert(liste !=NULL);

	cell = liste->prem;
	if (cell == NULL)
		return;

	if (data == cell->data)
	{
		liste->prem = cell->suiv;
		free(cell);
		return;
	}
	
	while (cell !=NULL)
	{
		prec = cell;
		cell = cell->suiv;
		if (data == cell->data)
		{
			prec->suiv = cell->suiv;
			free(cell);
		}
	}
}
*/


