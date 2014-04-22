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

	/* element->type			= type; */
	element->destructible  	= 0;
	element->x 				= 0;
	element->y				= 0;
	element->largeur 		= largeur;
	element->hauteur 		= hauteur;
	element->largeurSceneVisible	= largeurEcran;
	element->hauteurSceneVisible	= hauteurEcran;
	element->visible 		= 0;
	element->indexImage 		= indexImage;
	elementSetType(element, type);

}

void elementLibere(ElementScene *element)
{}


void elementSetType(ElementScene *element, int type)
{
	assert(element != NULL);
	element->type = type;
	switch (type)
	{
		case ELEMENT_TYPE_VAISSEAU_JOUEUR:
			element->destructible = 1;
			break;
		default:
			element->destructible = 0;
			break;
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

int elementGetType(const ElementScene * element)
{
    return element->type;
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

void elementSceneTestDeRegression()
{
    ElementScene eS;
    printf("Test de regression du module elementScene \n");

    printf("------------- Test de elementInit --------------\n");
    elementInit(&eS, ELEMENT_TYPE_LASER, 1, 40, 40, 1366,768);
    assert(eS.type==ELEMENT_TYPE_LASER && eS.indexImage==1 && eS.hauteur== 40 && eS.hauteur==40);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf("------------ Test de elementSetType ----------\n");
    elementSetType(&eS, ELEMENT_TYPE_MISSILE);
    assert(eS.type== ELEMENT_TYPE_MISSILE);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf("------------- Test de elementGetType ----------- \n");
    assert(elementGetType(&eS)==ELEMENT_TYPE_MISSILE);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf(" ----------- Test de elementSetPosition ---------- \n");
    elementSetPosition(&eS, 40, 50);
    assert(eS.x==40 && eS.y==50);
    printf("===========> Resultat : OK! \n");
    printf("\n");


}



