/**
* @file Sprite.c
* @brief
*/
#include "Sprite.h"
#include <stdio.h>
#include <assert.h>





void spriteInit(Sprite *sprite, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran)
{
	assert( sprite != NULL );

	sprite->type			= type;
	sprite->x 				= 0;
	sprite->y				= 0;
	sprite->largeur 		= largeur;
	sprite->hauteur 		= hauteur;
	sprite->largeurEcran	= largeurEcran;
	sprite->hauteurEcran	= hauteurEcran;
	sprite->visible 		= 0;
	sprite->indexImage 		= indexImage;

}

void spriteLibere(Sprite *sprite)
{}



int spriteVisible(const Sprite *sprite)
{
	return sprite->visible;
}

int spriteGetX(const Sprite *sprite)
{
	return sprite->x;
}

int spriteGetY(const Sprite *sprite)
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

int spriteGetIndexImage(const Sprite *sprite)
{
	return sprite->indexImage;
}




