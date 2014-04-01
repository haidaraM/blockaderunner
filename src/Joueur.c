/**
* @file Joueur.c
* @brief fichier d'implementation du module Joueur
*/

#include "Joueur.h"
#include "Vaisseau.h"

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

    vaisseauJoueurInit(&joueur->vaisseau, pointS, pointE, nbArmes);
}

void joueurLibere(Joueur * joueur)
{
    vaisseauLibere(&joueur->vaisseau);
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
    printf("nom : %s \nScore : %d \nNiveau : %d \n", j.nom, j.score, j.progression );
    assert(strcmp(j.nom, nom)==0 && j.vaisseau.armes!=NULL);
    printf("nbArmes : %d \n", j.vaisseau.nbArmes);
    printf("PointS : %d \n", j.vaisseau.pointStructure);
    printf("PointE : %d \n", j.vaisseau.pointEcran);
    printf("Types Arme :  %d\n", j.vaisseau.armes[0].typeArme );
    printf("Munitions :  %d\n", j.vaisseau.armes[0].munitions );
    printf("degatEcran :  %d\n", j.vaisseau.armes[0].degatEcran );
    printf("degatStructure :  %d\n", j.vaisseau.armes[0].degatStructure );
    printf("=========> Resultat : OK!\n");
    printf("\n");

    printf("---------- Test joueurGetProgression ---------\n");
    assert(joueurGetProgression(&j)==5);
    printf("=========> Resultat : OK!\n");
    printf("\n");

    printf("---------- Test joueurGetScore ----------\n");
    assert(joueurGetScore(&j)==9000);
    printf("=========> Resultat : OK!\n");
    printf("\n");

    joueurLibere(&j);
}

