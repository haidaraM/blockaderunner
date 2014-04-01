#include "Niveau.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>



void niveauInit(Niveau *niveau, int numero)
{
	assert(niveau != NULL);
	
	niveau->numero = numero;
	niveau->description = NULL;
	niveau->imageFond = 0; /* vide */
}

void niveauLibere(Niveau *niveau)
{
	assert(niveau != NULL);
}

void niveauSetImageFond(Niveau *niveau, int indexImage)
{
	assert(niveau != NULL);
	niveau->imageFond = indexImage;
}

