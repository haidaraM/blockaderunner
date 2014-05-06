/**
* @file Niveau.c
* @brief Fichier d'implementation du module Niveau
*/
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
    assert(numero>=0 && numero <=6);
    strcpy(nomFichier, RESS_DIR_NIVEAU);

    switch(numero)
    {
    case 0:
        strcat(nomFichier, "niveau0");
        strcat(niveau->description, NIVEAU_0_DESCRIPTION);
        break;
    case 1:
        strcat(nomFichier, "niveau1");
        strcat(niveau->description, NIVEAU_1_DESCRIPTION);
        break;
    case 2:
        strcat(nomFichier, "niveau2");
        strcat(niveau->description, NIVEAU_2_DESCRIPTION);
        break;
    default:
        strcat(nomFichier, "niveau3");
        strcat(niveau->description, NIVEAU_3_DESCRIPTION);
        break;
    }

    fic=fopen(nomFichier, "r");
    if(fic == NULL)
    {
        printf("Erreur :(Niveau) Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }
    /* lecture du nombre d'ennemis */
    valRet=fscanf(fic, "#nbEnnemis : %d #nbBonus : %d", &niveau->nbEnnemis, &niveau->nbBonus);
    assert(valRet==2);

    fclose(fic);
}
