/**
* @file Joueur.c
* @brief fichier d'implementation du module Joueur
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Joueur.h"

/**
* @fn static Vaisseau * joueurGetVaisseau(const Joueur * joueur)
* @brief Renvoie le vaisseau du joueur
* @param [in] joueur : initialisé
* @return Pointeur sur vaisseau
*/
static Vaisseau * joueurGetVaisseau(const Joueur * joueur)
{
    assert(joueur!=NULL);
    return joueur->vaisseau;
}


void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score)
{
    assert(joueur!=NULL && nom != NULL);

    strcpy(joueur->nom, nom);
    joueur->score=score;
    joueur->progression=progression;
    joueur->vaisseau=(Vaisseau *)malloc(sizeof(Vaisseau));
    assert(joueur->vaisseau!=NULL);

    vaisseauInit(joueur->vaisseau,VAISSEAU_JOUEUR_TYPE);
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
	if (joueur->progression < 7)
	{
	    joueur->progression++;
		joueur->score += 10000; /* bonus de fin de niveau */
	}
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


int joueurGetNumArmeSelectionne(const Joueur * joueur)
{
    return joueurGetVaisseau(joueur)->numArmeSelectionne;
}

void joueurSetArmeSelectionne(Joueur * joueur, int numArme )
{
    Vaisseau * v;
    assert(joueur!=NULL);
    v=joueurGetVaisseau(joueur);
    v->numArmeSelectionne=numArme;
}

void joueurAjouteMissiles(Joueur *joueur, int numMissiles)
{
    Vaisseau *v;
    assert(joueur != NULL);
    v = joueurGetVaisseau(joueur);
    v->armes[ARME_MISSILE].munitions += numMissiles;
    if (v->armes[ARME_MISSILE].munitions > JOUEUR_MAX_MISSILES)
        v->armes[ARME_MISSILE].munitions = JOUEUR_MAX_MISSILES;
}

Joueur * joueurCopieJoueur(Joueur * j)
{
    Joueur * nouveauJoueur=NULL;
    assert(j!=NULL);
    nouveauJoueur=(Joueur*)malloc(sizeof(Joueur));
    assert(nouveauJoueur!=NULL);
    joueurInit(nouveauJoueur, j->nom, j->progression, j->score);
    return nouveauJoueur;

}

void joueurTestDeRegression()
{
    Joueur j;
    Vaisseau *v=NULL;
    char nom[]="Superman";
    printf("Test de regression de Joueur\n");

    printf("---------- Test de joueurInit ------------\n");
    joueurInit(&j, nom, 5, 9000);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------- Test de joueurGetNumArmeSelectionne ---------\n");
    assert(joueurGetNumArmeSelectionne(&j)==0);
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
    printf("\n");

    printf("------- Test de joueurSetScore --------- \n");
    joueurSetScore(&j, 5550);
    assert(joueurGetScore(&j)==5550);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("------- Test de joueurGetVaisseau --------\n");
    v=joueurGetVaisseau(&j);
    assert(v!=NULL);
    assert(vaisseauGetPointEcran(v)==5 && vaisseauGetPointStructure(v)==100);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("------ Test de joueurSetArmeSelectionne ---------\n");
    joueurSetArmeSelectionne(&j, 1);
    assert(joueurGetNumArmeSelectionne(&j)==1);
    printf("=========> Resultat : OK \n");
    printf("\n");

     /* Les tests de liberations sont à effecter avec valgrind de préferences */
    printf("------- Test de joueurLibere ------------\n");
    joueurLibere(&j);
    assert(j.vaisseau==NULL);
    printf("=========> Resultat : OK \n");
    printf("\n");

}

