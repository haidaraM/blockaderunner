#include "Niveau.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "Ressource.h"



void niveauInit(Niveau *niveau, int numero)
{
    assert(niveau != NULL);

    niveau->numero = numero;
    niveau->description = NULL;
    niveau->imageFond = 0; /* vide */
    niveauChargeFichier(niveau, numero);
}

void niveauLibere(Niveau *niveau)
{
    assert(niveau != NULL);
}

void niveauSetImageFond(Niveau *niveau, int indexImage)
{
    assert(niveau != NULL);
    niveau->imageFond = indexImage;
}

void niveauChargeFichier (Niveau * niveau, int numero)
{
    FILE *fic;
    char nomFichier[128];
    int valRet=0;

    assert(niveau!=NULL);
    strcpy(nomFichier, RESS_DIR_NIVEAU);

    switch(numero)
    {
    case 0:
        strcat(nomFichier, "niveau0");
        break;
    default:
        strcat(nomFichier, "niveau1");
        break;
    }

    fic=fopen(nomFichier, "r");
    if(fic == NULL)
    {
        printf("Erreur :(Niveau) Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    /* lecture du nombre d'ennemis */
    valRet=fscanf(fic, "#nbEnnemis : %d", &niveau->nbEnnemis);
    assert(valRet>0);

    fclose(fic);
}
