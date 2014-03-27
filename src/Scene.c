/**
* @file Scene.c
* @brief
*/
#include "Scene.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>



void sceneInit(Scene *scene, Ressource *res, int largeurGraphique, int hauteurGraphique)
{
	int i;
	ElementScene *element	= NULL;

	assert( scene != NULL && res != NULL );

	scene->largeurAffichage = largeurGraphique;
	scene->hauteurAffichage = hauteurGraphique;
	scene->niveau 		= 0;
	scene->ressource 	= res;
	scene->numElements 	= 1;
	scene->elements		= (ElementScene**)malloc(scene->numElements * sizeof(ElementScene*));
	assert( scene->elements != NULL);
	for (i=0; i< scene->numElements; i++)
		scene->elements[i] = 0;


	/* TEST : initialisation element du vaisseau joueur */
	element 				= (ElementScene*)malloc(sizeof(ElementScene));
	assert( element != NULL);
	elementInit(element, 0, RESS_IMG_VAISSEAU_JOUEUR,
				ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_JOUEUR), ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_JOUEUR), scene->largeurAffichage, scene->hauteurAffichage);
	element->type 		= SPRITE_TYPE_VAISSEAU_JOUEUR;
	elementSetPosition(element, 32, (hauteurGraphique - element->hauteur)/2);
	scene->elements[0]	= element;
}

void sceneLibere(Scene *scene)
{
	int i;
	assert( scene != NULL);

	for (i=0; i<scene->numElements; i++)
	{
		if (scene->elements[i] != NULL)
		{
			elementLibere(scene->elements[i]);
			free(scene->elements[i]);
		}
	}

	free(scene->elements);
	scene->numElements = 0;
}

ElementScene* sceneCreerElementScene(Scene *scene, int type)
{
	/* To Do */
	return NULL;
}

void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
{
	ElementScene *vaiss			= scene->elements[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dy						= -(int)(tempsSecondes * vitesseDeplacement);
	int y 						= elementGetY( vaiss );

	/* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
	if ( (y + dy) < 0)
		dy 						= -y;

	elementSetPosition( vaiss, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
{
	ElementScene *vaiss			= scene->elements[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dy						= (int)(tempsSecondes * vitesseDeplacement);
	int y 						= elementGetY( vaiss );

	/* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
	if ( (y + dy) > (vaiss->hauteurSceneVisible - vaiss->hauteur))
		dy 						= (vaiss->hauteurSceneVisible - vaiss->hauteur) - y;

	elementSetPosition( vaiss, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->elements[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dx						= (int)(tempsSecondes * vitesseDeplacement);
	int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ((x+dx) >(vaiss->largeurSceneVisible - vaiss ->largeur))
        dx                      =(vaiss->largeurSceneVisible - vaiss ->largeur) -x;
    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}

void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->elements[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dx						= -(int)(tempsSecondes * vitesseDeplacement);
	int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
	if ( (x + dx) < 0)
		dx						= -x;

    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}



