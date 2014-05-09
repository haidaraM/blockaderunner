/**
* @file Vaisseau.c
* @brief Fichier d'implementation du module Vaisseau
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Vaisseau.h"

void vaisseauInit(Vaisseau *vaisseau, int type, int pointS, int pointE, int nbArmes)
{
    int i;
    assert(vaisseau!=NULL);
    switch(type)
    {
    case VAISSEAU_JOUEUR_TYPE:
        vaisseau->type=VAISSEAU_JOUEUR_TYPE;
        vaisseau->pointEcran=pointE;
        vaisseau->pointStructure=pointS;
        vaisseau->nbArmes=nbArmes;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes=(Arme *)malloc(sizeof(Arme)*nbArmes);
        for(i=0; i<nbArmes; i++)
        {
            vaisseauArmeInit(&vaisseau->armes[i], i);
        }
        /* laser est selectionnée par défaut */
        vaisseau->numArmeSelectionne=ARME_LASER;
        break;
    case VAISSEAU_ENNEMI_TYPE:
        vaisseau->type=VAISSEAU_ENNEMI_TYPE;
        vaisseau->pointEcran=ENNEMI_POINTECRAN;
        vaisseau->pointStructure=ENNEMI_POINTSTRUCTURE;
        vaisseau->nbArmes=1;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes=(Arme *)malloc(sizeof(Arme)*nbArmes);
        for(i=0; i<nbArmes; i++)
        {
            vaisseauArmeInit(&vaisseau->armes[i], i);
        }
        vaisseau->numArmeSelectionne=ARME_LASER;
        break;
    default:
        break;
    }
}

void vaisseauLibere(Vaisseau *vaisseau)
{
    assert(vaisseau!=NULL);
    free(vaisseau->armes);
    vaisseau->armes=NULL;
}


int vaisseauGetNbArmes(const Vaisseau * vaisseau)
{
    assert(vaisseau!=NULL);
    return vaisseau->nbArmes;
}

int vaisseauGetPointEcran(const Vaisseau * vaisseau)
{
    assert(vaisseau!=NULL);
    return vaisseau->pointEcran;
}

int vaisseauGetPointStructure(const Vaisseau * vaisseau)
{
    assert(vaisseau!=NULL);
    return vaisseau->pointStructure;
}

void vaisseauArmeInit(Arme * a, int type)
{
    assert(a!=NULL);
    switch(type)
    {
    case ARME_LASER:
        a->typeArme=ARME_LASER;
        a->munitions=ARME_LASER_MUNITIONS;
        a->degatEcran=ARME_LASER_DEGAT_E;
        a->degatStructure=ARME_LASER_DEGAT_S;
        a->cadence=0.0;
        break;
    case ARME_MISSILE:
        a->typeArme=ARME_MISSILE;
        a->munitions=ARME_MISSILE_MUNITIONS;
        a->degatEcran=ARME_MISSILE_DEGAT_E;
        a->degatStructure=ARME_MISSILE_DEGAT_S;
        a->cadence=1.0;
    default:
        break;
    }
}

Arme vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau)
{
    assert(vaisseau!=NULL);
    return vaisseau->armes[vaisseau->numArmeSelectionne];
}

int vaisseauGetDegatEcranArme(const Vaisseau * vaisseau )
{

    return vaisseauGetArmeSelectionnee(vaisseau).degatEcran;
}

int vaisseauGetDegatStructureArme(const Vaisseau * vaisseau )
{
    return vaisseauGetArmeSelectionnee(vaisseau).degatStructure;
}

int vaisseauGetMunitionsArme(const Vaisseau * vaisseau)
{
    return vaisseauGetArmeSelectionnee(vaisseau).munitions;
}

void vaisseauMajMunitions(Vaisseau * vaisseau)
{
    int nouveau;
    assert(vaisseau!=NULL);
    nouveau=vaisseauGetMunitionsArme(vaisseau);
    nouveau--;
    vaisseau->armes[vaisseau->numArmeSelectionne].munitions=nouveau;
}

void vaisseauTestDeregression()
{
    Vaisseau v;
    printf("Test de regression du vaisseau \n");

    printf("--------- Test de vaisseauJoueurInit avec 50 pE, 50 pS, 1 arme ---------\n" );
    vaisseauInit(&v,VAISSEAU_JOUEUR_TYPE, 50, 50, 1 );
    assert(v.pointStructure==50 && v.pointEcran==50 && v.nbArmes==1);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------- Test de vaisseauGetPointStructure ---------\n");
    assert(vaisseauGetPointStructure(&v)== 50);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------- Test de vaisseauGetPointEcran ---------\n");
    assert(vaisseauGetPointEcran(&v)== 50);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------- Test de vaisseauGetNbArmes ------------ \n");
    assert(vaisseauGetNbArmes(&v)==1);
    printf("=========> Resultat : OK \n");
}


