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



int elementVisible(const ElementScene *element)
{
	return element->visible;
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




