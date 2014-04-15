/**
* @file ElementScene.c
* @brief
*/
#include "ElementScene.h"
#include <stdio.h>
#include <assert.h>





void elementInit(ElementScene *element, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran)
{
	assert( element != NULL );

	element->type			= type;
	element->destructible  	= 0;
	element->x 				= 0;
	element->y				= 0;
	element->largeur 		= largeur;
	element->hauteur 		= hauteur;
	element->largeurSceneVisible	= largeurEcran;
	element->hauteurSceneVisible	= hauteurEcran;
	element->visible 		= 0;
	element->indexImage 		= indexImage;

}

void elementLibere(ElementScene *element)
{}


void elementSetType(ElementScene *element, int type)
{
	assert(element != NULL);
	element->type = type;
	switch (type)
	{
		case SPRITE_TYPE_VAISSEAU_JOUEUR:
			element->destructible = 1;
		default:
			element->destructible = 0;
	}
}

int elementVisible(const ElementScene *element)
{
	return element->visible;
}

int elementDestructible(const ElementScene *element)
{
	return element->destructible;
}

int elementGetX(const ElementScene *element)
{
	return element->x;
}

int elementGetY(const ElementScene *element)
{
	return element->y;
}

void elementSetPosition(ElementScene *element, int x, int y)
{
	element->x	= x;
	element->y	= y;

	if (x < (-element->largeur) || y < (-element->hauteur) || x > element->largeurSceneVisible || y > element->hauteurSceneVisible)
			element->visible = 0;
	else	element->visible = 1;
}

int elementGetImageIndex(const ElementScene *element)
{
	return element->indexImage;
}




