/**
* @file Joueur.c
* @brief fichier d'implementation du module Joueur
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Joueur.h"

void joueurInit(Joueur *joueur, char *nom, unsigned int progression)
{
    assert(joueur!=NULL);
    strcpy(joueur->nomJoueur, nom);
    joueur->score=0;
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

void joueurTestDeRegression()
{
    Joueur j;
    joueurInit(&j, "monJoueur", 0);
}
