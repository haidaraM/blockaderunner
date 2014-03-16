/**
* @file fichier d'implementation du module Ecran
* @brief
*/
#include "Ecran.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



void ecranInit(Ecran *ecran, int largeur, int hauteur, char *titre, int mode)
{
	SDL_Rect **modes;
	int i;

	int imgFlags, imgRes;
	assert( ecran != NULL && largeur > 0 && hauteur > 0 );

	#ifdef JEU_VERBOSE
		printf("Ecran :\n    initialisation ...\n");
	#endif

	ecran->surface		= 0;
	ecran->largeur 		= 0;
	ecran->hauteur		= 0;
	ecran->titre		= ECRAN_TITRE_DEFAUT;
	ecran->mode 		= ECRAN_MODE_FENETRE;

	#ifdef JEU_VERBOSE
	/* Evaluation des modes video disponibles */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
	/* verifie s'il ya plusieurs modes disponibles */
	if(modes == (SDL_Rect **)0){
		printf("    No VIDEO modes available!\n");
  		exit(-1);
	}

	/* Verifie si la resolution est limitee */
	if(modes == (SDL_Rect **)-1){
		printf("    VIDEO : All resolutions available.\n");
	}
	else{
	  	/* Affiche les modes valides */
	  	printf("    Available Modes\n");
	  	for(i=0;modes[i];++i)
	    	printf("      %d x %d\n", modes[i]->w, modes[i]->h);
	}
	/*free(modes);*/
	#endif

	/* Initialisation fenetre principale (SDL) */
	ecran->surface 		= SDL_SetVideoMode( largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
	assert( ecran->surface != NULL );

	/* Initialise la surface accessible (par blit..) à toute la surface ecran : toute opération en dehors de ces limites sera tronquée automatiquement. */
	SDL_SetClipRect(ecran->surface, NULL);

	ecran->couleurFond	= SDL_MapRGB( ecran->surface->format, 0x00, 0x00, 0x00 );
	ecranEfface(ecran);
	ecran->largeur		= largeur;
	ecran->hauteur 		= hauteur;
	if (titre != NULL)
	{
		SDL_WM_SetCaption( titre, NULL );
		ecran->titre 	= titre;
	} else
		SDL_WM_SetCaption( ecran->titre, NULL);

	/* Initialisation de SDL_image */
	imgFlags			= IMG_INIT_JPG | IMG_INIT_PNG;
	imgRes				= IMG_Init(imgFlags);
	if((imgRes & imgFlags) != imgFlags)
	{
   	 	printf("IMG_Init: Impossible d'initialiser SDL_image avec support PNG et JPEG.\n");
   	 	printf("IMG_Init: %s\n", IMG_GetError());
	}

	#ifdef JEU_VERBOSE
		printf("    initialisation OK.\n");
	#endif
}

void ecranLibere(Ecran *ecran)
{
	/* SDL_image */
	IMG_Quit();
}

void ecranRaffraichit(Ecran *ecran)
{
	assert( SDL_Flip( ecran->surface ) !=-1 );
}

void ecranSetTitre(Ecran *ecran, char *titre)
{
	if (titre != NULL)
	{
		SDL_WM_SetCaption( titre, NULL);
		ecran->titre 	= titre;
	}
}

void ecranEfface(Ecran *ecran)
{
	SDL_FillRect( ecran->surface, &ecran->surface->clip_rect, ecran->couleurFond );
}

void ecranAfficheImage(Ecran *ecran, SDL_Surface* image, int x, int y )
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit la surface */
	SDL_BlitSurface( image, NULL, ecran->surface, &offset );
}

