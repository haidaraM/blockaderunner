/**
* @file Vaisseau.c
* @brief Fichier d'implementation du module Vaisseau
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Vaisseau.h"
#include "Outils.h"



void vaisseauInit(Vaisseau *vaisseau, int type)
{
    int i;
    assert(vaisseau!=NULL);
    switch(type)
    {
    case VAISSEAU_JOUEUR_TYPE:
        vaisseau->type=VAISSEAU_JOUEUR_TYPE;
        vaisseau->pointEcran=JOUEUR_POINTECRAN;
        vaisseau->pointStructure=JOUEUR_POINTSTRUCTURE;
        vaisseau->nbArmes=JOUEUR_NB_ARMES;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes=(Arme *)malloc(sizeof(Arme)*JOUEUR_NB_ARMES);
        for(i=0; i<JOUEUR_NB_ARMES; i++)
        {
            vaisseauArmeInit(&vaisseau->armes[i], i);
        }
        /* laser est selectionnée par défaut */
        vaisseau->numArmeSelectionne=ARME_LASER;
        break;
	case VAISSEAU_ECLAIREUR_TYPE:
        vaisseau->type = VAISSEAU_ECLAIREUR_TYPE;
        vaisseau->pointEcran = ECLAIREUR_POINTECRAN;
        vaisseau->pointStructure = ECLAIREUR_POINTSTRUCTURE;
        vaisseau->nbArmes = ECLAIREUR_ARMES;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes = (Arme *)malloc(sizeof(Arme)*ECLAIREUR_ARMES);
        for(i=0; i<ECLAIREUR_ARMES; i++)
        {
            vaisseauArmeInit(&vaisseau->armes[i], i);
        }
        vaisseau->numArmeSelectionne=ARME_LASER;
        break;
	case VAISSEAU_CHASSEUR_TYPE:
        vaisseau->type = VAISSEAU_CHASSEUR_TYPE;
        vaisseau->pointEcran = CHASSEUR_POINTECRAN;
        vaisseau->pointStructure = CHASSEUR_POINTSTRUCTURE;
        vaisseau->nbArmes = CHASSEUR_ARMES;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes = (Arme *)malloc(sizeof(Arme)*CHASSEUR_ARMES);
        for(i=0; i<CHASSEUR_ARMES; i++)
        {
            vaisseauArmeInit(&vaisseau->armes[i], i);
        }
        vaisseau->numArmeSelectionne=ARME_LASER;
        break;
	case VAISSEAU_CROISEUR_TYPE:
        vaisseau->type = VAISSEAU_CROISEUR_TYPE;
        vaisseau->pointEcran = CROISEUR_POINTECRAN;
        vaisseau->pointStructure = CROISEUR_POINTSTRUCTURE;
        vaisseau->nbArmes = CROISEUR_ARMES;
        /* Initialisation des armes du vaisseau */
        vaisseau->armes = (Arme *)malloc(sizeof(Arme)*CROISEUR_ARMES);
        for(i=0; i<CROISEUR_ARMES; i++)
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

void vaisseauSetPointVie(Vaisseau * vaisseau, int pEcran, int pStructure)
{
	assert(vaisseau != NULL);
	vaisseau->pointEcran = pEcran;
	vaisseau->pointStructure = pStructure;
}

void vaisseauSetDegats(Vaisseau * vaisseau, int typeDegats)
{
    assert(vaisseau!=NULL);

	switch(typeDegats)
	{
	case ARME_LASER:
		vaisseau->pointEcran -= ARME_LASER_DEGAT_E;
		if (vaisseau->pointEcran < 0)
		{
			vaisseau->pointStructure -= ARME_LASER_DEGAT_S;
			if (vaisseau->pointStructure < 0)
				vaisseau->pointStructure = 0;
			vaisseau->pointEcran = 0;
		}
		break;
	case ARME_MISSILE:
		vaisseau->pointStructure -= ARME_MISSILE_DEGAT_S;
		if (vaisseau->pointStructure < 0)
			vaisseau->pointStructure = 0;
		break;
	case VAISSEAU_COLLISION:
		vaisseau->pointStructure -= VAISSEAU_COLLISION_DEGAT_S;
		if (vaisseau->pointStructure < 0)
			vaisseau->pointStructure = 0;
		break;
	}

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
        a->cadence=0.5f;
		a->tempsDernierTir = getTempsSecondes();	/* note : défini dans Outils.h */
        break;
    case ARME_MISSILE:
        a->typeArme=ARME_MISSILE;
        a->munitions=ARME_MISSILE_MUNITIONS;
        a->degatEcran=ARME_MISSILE_DEGAT_E;
        a->degatStructure=ARME_MISSILE_DEGAT_S;
        a->cadence=1.0f;
		a->tempsDernierTir = getTempsSecondes();
    default:
        break;
    }
}

Arme* vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau)
{
    assert(vaisseau!=NULL);
    return &vaisseau->armes[vaisseau->numArmeSelectionne];
}

int vaisseauGetDegatEcranArme(const Vaisseau * vaisseau )
{

    return vaisseauGetArmeSelectionnee(vaisseau)->degatEcran;
}

int vaisseauGetDegatStructureArme(const Vaisseau * vaisseau )
{
    return vaisseauGetArmeSelectionnee(vaisseau)->degatStructure;
}

int vaisseauGetMunitionsArme(const Vaisseau * vaisseau)
{
    return vaisseauGetArmeSelectionnee(vaisseau)->munitions;
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

    printf("--------- Test de vaisseauJoueurInit ---------\n" );
    vaisseauInit(&v,VAISSEAU_JOUEUR_TYPE);
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


