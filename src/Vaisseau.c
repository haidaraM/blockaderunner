#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Vaisseau.h"

void vaisseauJoueurInit(Vaisseau *vaisseauJ, int pointS, int pointE, int nbArmes)
{
    int i;
    assert(vaisseauJ!=NULL);
    assert(nbArmes!=0);

    vaisseauJ->type=VAISSEAU_JOUEUR_TYPE;

    vaisseauJ->pointEcran=pointE;

    vaisseauJ->pointStructure=pointS;

    vaisseauJ->nbArmes=nbArmes;

    /* Initialisation des armes du vaisseau */
    vaisseauJ->armes=(Arme *)malloc(sizeof(Arme)*nbArmes);
    for(i=0; i<nbArmes; i++)
    {
        armeInit(&vaisseauJ->armes[i], ARME_LAZER);
    }
    /* Arme 0 est selectionnée par défaut */
    vaisseauJ->armeSelectionne=0;
}

void vaisseauEnnemiInit(Vaisseau *vaisseau, int pointS, int pointE, int nbArmes)
{
    int i;
    assert(vaisseau!=NULL);

    /* Initialisation du type */
    vaisseau->type=VAISSEAU_ENNEMI_TYPE;

    vaisseau->pointEcran=pointE;

    vaisseau->pointStructure=pointS;

    vaisseau->nbArmes=nbArmes;

    /* Initialisation des armes du vaisseau */
    vaisseau->armes=(Arme *)malloc(sizeof(Arme)*nbArmes);
    for(i=0; i<nbArmes; i++)
    {
        armeInit(&vaisseau->armes[i], ARME_LAZER);
    }
}

void vaisseauLibere(Vaisseau *vaisseau)
{
    assert(vaisseau!=NULL);
    free(vaisseau->armes);
    vaisseau->armes=NULL;
    free(vaisseau);
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

void armeInit(Arme * a, int type)
{
    switch(type)
    {
        case ARME_LAZER:
            a->typeArme=ARME_LAZER;
            a->munitions=ARME_LAZER_MUNITIONS;
            a->degatEcran=ARME_LAZER_DEGAT_E;
            a->degatStructure=ARME_LAZER_DEGAT_S;
            a->cadence=10.5;
            break;
        case ARME_MISSILE:
            a->typeArme=ARME_MISSILE;
            a->munitions=ARME_MISSILE_MUNITIONS;
            a->degatEcran=ARME_MISSILE_DEGAT_E;
            a->degatStructure=ARME_MISSILE_DEGAT_S;
            a->cadence=5.5;
        default:
            break;
    }
}

void vaisseauTestDeregression()
{
    Vaisseau v;
    printf("Test de regression du vaisseau \n");

    printf("--------- Test de vaisseauJoueurInit avec 50 pE, 50 pS, 1 arme ---------\n" );
    vaisseauJoueurInit(&v, 50, 50, 1 );
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
