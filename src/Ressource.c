/**
* @file Ressource.c
* @brief
*/
#include "Ressource.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



/* FONCTIONS INTERNES */

SDL_Surface* ressourceChargeImage(char* nomFichier)
{
	SDL_Surface *image;
	char file[64], dir[64];

	strcpy(file, nomFichier);
	strcpy(dir, RESS_DIR_IMAGES);

	image 					= IMG_Load(strcat(dir, file));
	if (image == NULL)
	{
		printf("ERREUR : Ressources : impossible de charger l'image %s dans %s.\n   %s\n", nomFichier, RESS_DIR_IMAGES, IMG_GetError());
	}

	assert( image != NULL );
	return image;
}


void chargeImages(Ressource *res)
{
	/* Vaisseau : Joueur */
	res->images[RESS_VAISSEAU_JOUEUR] 			= ressourceChargeImage(RESS_FICHIER_VAISSEAU_JOUEUR);
}

void chargeSons(Ressource *res)
{}

void chargePolices(Ressource *res)
{}



/* INTERFACE */

void ressourceInit(Ressource *res)
{
	int i;

	#ifdef JEU_VERBOSE
		printf("Ressources :\n    initialisation ...\n");
	#endif
	res->images 		= (SDL_Surface**)malloc(RESS_NUM_IMAGES*sizeof(SDL_Surface*));
	if (res->images == NULL)
	{
		printf("ERREUR : Ressources : impossible d'allouer la memoire pour les images.\n");
	}
	assert( res->images != NULL);
	for (i=0; i< RESS_NUM_IMAGES; i++)
		res->images[i] 		= 0;


	chargeImages(res);
	chargeSons(res);
	chargePolices(res);

	#ifdef JEU_VERBOSE
		printf("    initialisation OK.\n");
	#endif
}

void ressourceLibere(Ressource *res)
{
	int i;
	for (i=0; i< RESS_NUM_IMAGES; i++)
		if (res->images[i] != NULL)
			SDL_FreeSurface(res->images[i]);

	free(res->images);
}



SDL_Surface* ressourceGetImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->images[nomRessource];
}

int ressourceGetLargeurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->images[nomRessource]->w;
}

int ressourceGetHauteurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->images[nomRessource]->h;
}



