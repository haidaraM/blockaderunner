/**
* @file Scene.c
* @brief
*/
#include "Scene.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>



void sceneInit(Scene *scene, Ecran *ecran, Ressource *res)
{
	int i;
	Sprite *sprite		= NULL;

	assert( scene != NULL && ecran != NULL && res != NULL );

	scene->ecran		= ecran;
	scene->ressource 	= res;
	scene->numSprites 	= 1;
	scene->sprites 		= 0;

	scene->sprites		= (Sprite**)malloc(scene->numSprites * sizeof(Sprite*));
	assert( scene->sprites != NULL);

	for (i=0; i< scene->numSprites; i++)
		scene->sprites[i] = 0;


	/* TEST : initialisation sprite du vaisseau joueur */
	sprite 				= (Sprite*)malloc(sizeof(Sprite));
	assert( sprite != NULL);
	spriteInit(sprite, 0, RESS_VAISSEAU_JOUEUR, ressourceGetLargeurImage(res, RESS_VAISSEAU_JOUEUR), ressourceGetHauteurImage(res, RESS_VAISSEAU_JOUEUR), ecran->largeur, ecran->hauteur);
	sprite->type 		= SPRITE_TYPE_VAISSEAU_JOUEUR;
	spriteSetPosition(sprite, 32, (ecran->hauteur - sprite->hauteur)/2);
	scene->sprites[0]	= sprite;
}

void sceneLibere(Scene *scene)
{
	int i;
	assert( scene != NULL);

	for (i=0; i<scene->numSprites; i++)
	{
		if (scene->sprites[i] != NULL)
		{
			spriteLibere(scene->sprites[i]);
			free(scene->sprites[i]);
		}
	}

	free(scene->sprites);
	scene->numSprites = 0;
}



void sceneAffiche(Scene *scene)
{
	int i;
	for (i=0; i< scene->numSprites; i++)
	{
		if (scene->sprites[i] != NULL && spriteVisible(scene->sprites[i]) == 1)
		{
			/*printf("OK. ");*/
			ecranAfficheImage( scene->ecran, ressourceGetImage(scene->ressource, spriteGetIndexImage(scene->sprites[i])), spriteGetX(scene->sprites[i]), spriteGetY(scene->sprites[i]) );
		}
	}
}

Sprite* sceneCreerSprite(Scene *scene, int type)
{
	/* To Do */
	return NULL;
}



void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
{
	Sprite *vaiss				= scene->sprites[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dy						= -(int)(tempsSecondes * vitesseDeplacement);
	int y 						= spriteGetY( vaiss );

	/* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
	if ( (y + dy) < 0)
		dy 						= -y;

	spriteSetPosition( vaiss, spriteGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
{
	Sprite *vaiss				= scene->sprites[0];
	float vitesseDeplacement 	= 768.0f/0.88f;
	int dy						= (int)(tempsSecondes * vitesseDeplacement);
	int y 						= spriteGetY( vaiss );

	/* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
	if ( (y + dy) > (vaiss->hauteurEcran - vaiss->hauteur))
		dy 						= (vaiss->hauteurEcran - vaiss->hauteur) - y;

	spriteSetPosition( vaiss, spriteGetX( vaiss ), y + dy );
}




