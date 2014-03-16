/**
* @file Ecran.h
* @brief fichier d'en-tête du module Ecran
* @author
*/
#ifndef _ECRAN_H
#define _ECRAN_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define ECRAN_MODE_FULLSCREEN 		0
#define ECRAN_MODE_FENETRE	 		1
#define ECRAN_TITRE_DEFAUT			"Blockade"



typedef struct
{
	int largeur, hauteur;
	int mode;
	Uint32 couleurFond;
	char *titre;
	SDL_Surface *surface;
} Ecran;



void ecranInit(Ecran *ecran, int largeur, int hauteur, char *titre, int mode);
void ecranLibere(Ecran *ecran);

void ecranRaffraichit(Ecran *ecran);
void ecranSetTitre(Ecran *ecran, char *titre);
void ecranEfface(Ecran *ecran);
void ecranAfficheImage(Ecran *ecran, SDL_Surface* image, int x, int y );

#endif

