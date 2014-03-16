/**
* @file Scene.h
* @brief
*/
#ifndef _SCENE_H
#define _SCENE_H

#include "Sprite.h"
#include "Ecran.h"
#include "Ressource.h"



typedef struct
{
	int numSprites;
	Sprite **sprites;
	Ecran *ecran;
	Ressource *ressource;
} Scene;



void sceneInit(Scene *scene, Ecran *ecran, Ressource *res);
void sceneLibere(Scene *scene);

void sceneAffiche(Scene *scene);
Sprite* sceneCreerSprite(Scene *scene, int type);

void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes);
void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes);

#endif

