/**
* @file Joueur.c
* @brief fichier d'implementation du module Joueur
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/

#include "Joueur.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score, int pointS, int pointE, int nbArmes)
{
    assert(joueur!=NULL && nom != NULL);

    strcpy(joueur->nom, nom);
    joueur->score=score;
    joueur->progression=progression;
    joueur->vaisseau=(Vaisseau *)malloc(sizeof(Vaisseau));
    assert(joueur->vaisseau!=NULL);

   vaisseauInit(joueur->vaisseau,VAISSEAU_JOUEUR_TYPE, pointS, pointE, nbArmes);
}

void joueurLibere(Joueur * joueur)
{
    vaisseauLibere(joueur->vaisseau);
    free(joueur->vaisseau);
    joueur->vaisseau=NULL;
}

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
    char nom[]="Superman";
    printf("Test de regression de Joueur\n");

    printf("---------- Test de joueurInit ------------\n");
    joueurInit(&j, nom, 5, 9000, 100, 5, 10);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("---- Test de joueurGetProgression ----\n");
    assert(joueurGetProgression(&j)==5);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("----- Test de joueurGetScore ----\n");
    assert(joueurGetScore(&j)==9000);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("----- Test de joueurSetProgression ------ \n");
    joueurSetProgression(&j);
    assert(joueurGetProgression(&j)==6);
    printf("=========> Resultat : OK \n");


    joueurLibere(&j);
}

