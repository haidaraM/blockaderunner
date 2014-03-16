/**
* @file Sprite.c
* @brief
*/
#include "Sprite.h"
#include <stdio.h>
#include <assert.h>





void spriteInit(Sprite *sprite, SDL_Surface *surface, Ecran *ecran)
{
	assert( sprite != NULL && ecran != NULL );

	sprite->type			= -1;
	sprite->x 				= 0;
	sprite->y				= 0;
	sprite->largeur 		= 0;
	sprite->hauteur 		= 0;
	sprite->largeurEcran	= ecran->largeur;
	sprite->hauteurEcran	= ecran->hauteur;
	sprite->visible 		= 0;
	sprite->surface 		= surface;

	if (surface != NULL)
	{
		sprite->largeur 	= sprite->surface->w;
		sprite->hauteur 	= sprite->surface->h;
	}
}

void spriteLibere(Sprite *sprite)
{}



int spriteVisible(Sprite *sprite)
{
	return sprite->visible;
}

int spriteGetX(Sprite *sprite)
{
	return sprite->x;
}

int spriteGetY(Sprite *sprite)
{
	return sprite->y;
}

void spriteSetPosition(Sprite *sprite, int x, int y)
{
	sprite->x	= x;
	sprite->y	= y;

	if (x < (-sprite->largeur) || y < (-sprite->hauteur) || x > sprite->largeurEcran || y > sprite->hauteurEcran)
			sprite->visible = 0;
	else	sprite->visible = 1;
}

SDL_Surface* spriteGetSDLSurface(Sprite *sprite)
{
	return sprite->surface;
}




