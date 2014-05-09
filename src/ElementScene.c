/**
* @file ElementScene.c
* @brief Fichier d'implementation du module ElementScene
*/
#include "ElementScene.h"
#include "Vaisseau.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>





void elementInit(ElementScene *element, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran)
{
	assert( element != NULL );

	/* element->type			= type; */
	element->x 				= 0;
	element->y				= 0;
	element->largeur 		= largeur;
	element->hauteur 		= hauteur;
	element->largeurSceneVisible	= largeurEcran;
	element->hauteurSceneVisible	= hauteurEcran;
	element->visible 		= 0;
	element->indexImage 		= indexImage;
	element->data=NULL;
	elementSetType(element, type);

}

void elementLibere(ElementScene *element)
{
    assert(element!=NULL);
    if(element->data !=NULL)
    {
        free(element->data);
    }
}


void elementSetType(ElementScene *element, int type)
{
	assert(element != NULL);
	element->type = type;
	switch (type)
	{
		case ELEMENT_TYPE_ECLAIREUR:
            element->data=(Vaisseau *) malloc(sizeof(Vaisseau));
            vaisseauInit(element->data, VAISSEAU_ENNEMI_TYPE, ENNEMI_POINTSTRUCTURE, ENNEMI_POINTECRAN, 1);
			break;
		case ELEMENT_TYPE_CHASSEUR:
            element->data=(Vaisseau *) malloc(sizeof(Vaisseau));
            vaisseauInit(element->data, VAISSEAU_ENNEMI_TYPE, ENNEMI_POINTSTRUCTURE, ENNEMI_POINTECRAN, 1);
			break;
		case ELEMENT_TYPE_CROISEUR:
            element->data=(Vaisseau *) malloc(sizeof(Vaisseau));
            vaisseauInit(element->data, VAISSEAU_ENNEMI_TYPE, ENNEMI_POINTSTRUCTURE, ENNEMI_POINTECRAN, 1);
			break;

		default:
			break;
	}
}

int elementVisible(const ElementScene *element)
{
    assert(element!=NULL);
	return element->visible;
}

int elementGetX(const ElementScene *element)
{
    assert(element!=NULL);
	return element->x;
}

int elementGetY(const ElementScene *element)
{
    assert(element!=NULL);
	return element->y;
}

int elementGetType(const ElementScene * element)
{
    assert(element!=NULL);
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

int elementTestDeCollision(ElementScene * e1, ElementScene *e2)
{
    int x1, x2, y1, y2;
    x1=elementGetX(e1);
    x2=elementGetX(e2);
    y1=elementGetY(e1);
    y2=elementGetY(e2);

    if((x2 >= x1 + e1->largeur)      /* trop à droite */
	|| (x2 + e2->largeur <= x1)  /* trop à gauche */
	|| (y2 >= y1 + e1->hauteur)  /*trop en bas */
	|| (y2 + e2->hauteur <= y1))  /* trop en haut */
          return 0;
   else
          return 1;
}

void elementSceneTestDeRegression()
{
    ElementScene eS;
    printf("Test de regression du module elementScene \n");

    printf("------------- Test de elementInit --------------\n");
    elementInit(&eS, ELEMENT_TYPE_LASER_JOUEUR, 1, 40, 40, 1366,768);
    assert(eS.type==ELEMENT_TYPE_LASER_JOUEUR && eS.indexImage==1 && eS.hauteur== 40 && eS.hauteur==40);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf("------------ Test de elementSetType ----------\n");
    elementSetType(&eS, ELEMENT_TYPE_MISSILE_JOUEUR);
    assert(eS.type== ELEMENT_TYPE_MISSILE_JOUEUR);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf("------------- Test de elementGetType ----------- \n");
    assert(elementGetType(&eS)==ELEMENT_TYPE_MISSILE_JOUEUR);
    printf("===========> Resultat : OK! \n");
    printf("\n");

    printf(" ----------- Test de elementSetPosition ---------- \n");
    elementSetPosition(&eS, 40, 50);
    assert(eS.x==40 && eS.y==50);
    printf("===========> Resultat : OK! \n");
    printf("\n");


}



