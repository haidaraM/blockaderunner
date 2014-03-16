/**
* @file Sprite.h
* @brief
*/
#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL/SDL.h>
#include "Ressource.h"
#include "Ecran.h"



#define SPRITE_TYPE_NON_DEFINI					-1
#define SPRITE_TYPE_VAISSEAU_JOUEUR				0



typedef struct
{
	int visible;
	int type;
	int x, y, largeur, hauteur;
	SDL_Surface *surface;
	int largeurEcran;
	int hauteurEcran;
} Sprite;



void spriteInit(Sprite *sprite, SDL_Surface *surface, Ecran *ecran);
void spriteLibere(Sprite *sprite);

int spriteVisible(Sprite *sprite);
int spriteGetX(Sprite *sprite);
int spriteGetY(Sprite *sprite);
void spriteSetPosition(Sprite *sprite, int x, int y);

SDL_Surface* spriteGetSDLSurface(Sprite *sprite);


#endif

