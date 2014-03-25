/**
* @file Ressource.c
* @brief
*/
#include "Ressource.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



void creeListeImages(Ressource *res)
{
	res->images 			= (char**)malloc(RESS_NUM_IMAGES * sizeof(char*));
	res->dimensionImages 	= (Rectangle*)malloc(RESS_NUM_IMAGES * sizeof(Rectangle));
	assert( res->images != NULL  &&  res->dimensionImages != NULL );

	/* Vaisseau : Joueur */
	res->images[RESS_VAISSEAU_JOUEUR] 							= RESS_FICHIER_VAISSEAU_JOUEUR;
	res->dimensionImages[RESS_VAISSEAU_JOUEUR].largeur 			= 128;
	res->dimensionImages[RESS_VAISSEAU_JOUEUR].hauteur 			= 52;
}

void creeListeSons(Ressource *res)
{}

void creeListePolices(Ressource *res)
{}



/* INTERFACE */

void ressourceInit(Ressource *res)
{

	creeListeImages(res);
	creeListeSons(res);
	creeListePolices(res);
}

void ressourceLibere(Ressource *res)
{
	free(res->images);
	free(res->dimensionImages);
}


int ressourceGetLargeurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->dimensionImages[nomRessource].largeur;
}

int ressourceGetHauteurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->dimensionImages[nomRessource].hauteur;
}



