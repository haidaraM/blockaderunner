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


