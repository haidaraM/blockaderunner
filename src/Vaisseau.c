#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Vaisseau.h"

void vaisseauJoueurInit(Vaisseau *vaisseauJ, int pointS, int pointE, int nbArmes)
{
    int i;
    assert(vaisseauJ!=NULL);
    assert(nbArmes!=0);

    /* Initialisation du type*/

    vaisseauJ->type=VAISSEAU_JOUEUR_TYPE;

    vaisseauJ->pointEcran=pointE;

    vaisseauJ->pointStructure=pointS;

    vaisseauJ->nbArmes=nbArmes;

    vaisseauJ->armes=(Arme *)malloc(sizeof(Arme)*nbArmes);
    for(i=0; i<nbArmes; i++)
    {
        armeInit(&vaisseauJ->armes[i], 1);
    }
}

void vaisseauEnnemiInit(Vaisseau *vaisseau, int pointS, int pointE, int nbArmes)
{
    assert(vaisseau!=NULL);

    /* Initialisation du type */
    vaisseau->type=VAISSEAU_ENNEMI_TYPE;

    vaisseau->pointEcran=pointE;

    vaisseau->pointStructure=pointS;

    vaisseau->nbArmes=nbArmes;
}

void vaisseauLibere(Vaisseau *vaisseau)
{
    int i;
    assert(vaisseau!=NULL);
    free(vaisseau->armes);
    vaisseau->armes=NULL;
}

void armeInit(Arme * a, int type)
{
    switch(type)
    {
        case ARME_1:
            a->typeArme=ARME_1;
            a->munitions=ARME_1_MUNITIONS;
            a->degatEcran=ARME_1_DEGAT_E;
            a->degatStructure=ARME_1_DEGAT_S;
            break;
        default:
            break;
    }
}
