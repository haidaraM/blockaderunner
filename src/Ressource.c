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
	int i;

	/* initialisation des tableaux */

	res->images 			= (char**)malloc(RESS_NUM_IMAGES * sizeof(char*));
	res->dimensionImages 	= (Rectangle*)malloc(RESS_NUM_IMAGES * sizeof(Rectangle));
	assert( res->images != NULL  &&  res->dimensionImages != NULL );

	for (i=0; i< RESS_NUM_IMAGES; i++)
	{
		res->images[i]		= NULL;
		res->dimensionImages[i].largeur = 0;
		res->dimensionImages[i].hauteur = 0;
	}

	/* données */

	res->images[RESS_IMG_VAISSEAU_JOUEUR] 							= RESS_IMG_FICHIER_VAISSEAU_JOUEUR;
	res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].largeur 			= RESS_IMG_LARGEUR_VAISSEAU_JOUEUR;
	res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].hauteur 			= RESS_IMG_HAUTEUR_VAISSEAU_JOUEUR;

	res->images[RESS_IMG_SPLASH]		 							= RESS_IMG_FICHIER_SPLASH;
	res->dimensionImages[RESS_IMG_SPLASH].largeur 					= RESS_IMG_LARGEUR_SPLASH;
	res->dimensionImages[RESS_IMG_SPLASH].hauteur 					= RESS_IMG_HAUTEUR_SPLASH;

	res->images[RESS_IMG_FOND_MENU] 								= RESS_IMG_FICHIER_FOND_MENU;
	res->dimensionImages[RESS_IMG_FOND_MENU].largeur 				= RESS_IMG_LARGEUR_FOND_MENU;
	res->dimensionImages[RESS_IMG_FOND_MENU].hauteur 				= RESS_IMG_HAUTEUR_FOND_MENU;

	res->images[RESS_IMG_FOND_NIVEAU_0] 							= RESS_IMG_FICHIER_FOND_NIVEAU_0;
	res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].largeur 			= RESS_IMG_LARGEUR_FOND_NIVEAU_0;
	res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].hauteur 			= RESS_IMG_HAUTEUR_FOND_NIVEAU_0;
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



