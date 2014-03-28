/**
* @file Joueur.c
* @brief fichier d'implementation du module Joueur
*/

#include "Joueur.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score)
{
    assert(joueur!=NULL);

    strcpy(joueur->nom, nom);
    joueur->score=score;
    joueur->progression=progression;
}

void joueurLibere(Joueur * joueur)
{}

unsigned int joueurGetProgression(const Joueur *joueur)
{
    assert(joueur!=NULL);
    return joueur->progression;
}

void joueurSetProgression(Joueur * joueur)
{
    assert(joueur!=NULL);
    joueur->progression++;
}

int joueurGetScore(const Joueur *joueur)
{
    assert(joueur!=NULL);
    return joueur->score;
}

void joueurSetScore(Joueur *joueur, int score)
{
	assert(joueur != NULL);
	joueur->score = score;
}

void joueurTestDeRegression()
{
    Joueur j;
    joueurInit(&j, "monJoueur", 0, 0);
}
