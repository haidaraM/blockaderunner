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
        armeInit(&vaisseauJ->armes[i], ARME_0);
    }
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
        armeInit(&vaisseau->armes[i], ARME_0);
    }
}

void vaisseauLibere(Vaisseau *vaisseau)
{
    assert(vaisseau!=NULL);
    free(vaisseau->armes);
    vaisseau->armes=NULL;
}

void armeInit(Arme * a, int type)
{
    switch(type)
    {
        case ARME_0:
            a->typeArme=ARME_0;
            a->munitions=ARME_0_MUNITIONS;
            a->degatEcran=ARME_0_DEGAT_E;
            a->degatStructure=ARME_0_DEGAT_S;
            break;
        default:
            break;
    }
}
