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
    char nom[]="Superman", nom2[]="Supermmmmmmmmmmmmaaaaaaaaaaaaaaaaaaaaaaaann";
    printf("Test de regression de Joueur\n");

    printf("---------- Test de joueurInit ------------\n");
    joueurInit(&j, nom, 0, 0, 100, 5, 10);
    printf("nom : %s \nScore : %d \nNiveau : %d \n", j.nom, j.score, j.progression );
    assert(strcmp(j.nom, nom)==0 && j.score==0 && j.progression==0);
    printf("nbArmes : %d \n", j.vaisseau.nbArmes);
    printf("PointS : %d \n", j.vaisseau.pointStructure);
    printf("PointS : %d \n", j.vaisseau.pointEcran);
    printf("Munitions :  %d\n", j.vaisseau.armes[0].munitions );
    printf("=========> Resultat : OK!\n");
    printf("\n");

    printf("nbArmes : %d \n", j.vaisseau.nbArmes);

    printf("----------2e Test de joueurInit ------------\n");
    joueurInit(&j,  nom2, 1, 55555, 0,0 , 1);
    printf("nom : %s \nScore : %d \nNiveau : %d \n", j.nom, j.score,j.progression );
    assert(strcmp(j.nom, nom2)==0 );
    printf("=========> Resultat : OK!\n");
    printf("\n");

    printf("---------- Test joueurGetProgression ------------\n");
    assert(j.progression==1);
    printf("=========> Resultat : OK!\n");
    printf("\n");

    printf("---------- Test joueurGetScore ------------\n");
    assert(j.score==55555);
    printf("=========> Resultat : OK!\n");
    printf("\n");
}

