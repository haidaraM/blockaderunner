/**
* @file Niveau.c
* @brief Fichier d'implementation du module Niveau
*/
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "Ressource.h"
#include "Niveau.h"

/**
* @fn static void niveauChargeFichier(Niveau * niveau, int numero)
* @brief Charge les caractéristiques du niveau a partir d'un fichier
* @param [in, out] niveau : initialisé
* @param [in] numero : correspond au numero du niveau
*/

static void niveauChargeFichier(Niveau * niveau, int numero)
{
    FILE *fic;
    char nomFichier[128], typeGroupe[32];
    int valRet=0;
    GroupeNiveau *groupe;

    assert(niveau!=NULL);
    assert(numero>=0 && numero < RESS_NUM_NIVEAUX);

    strcpy(nomFichier, RESS_DIR_NIVEAU);

    switch(numero)
    {
    case 0:
        strcat(nomFichier, "niveau0");
        strcpy(niveau->description, NIVEAU_0_DESCRIPTION);
        break;
    case 1:
        strcat(nomFichier, "niveau1");
        strcpy(niveau->description, NIVEAU_1_DESCRIPTION);
        break;
    case 2:
        strcat(nomFichier, "niveau2");
        strcpy(niveau->description, NIVEAU_2_DESCRIPTION);
        break;
    case 3:
        strcat(nomFichier, "niveau3");
        strcpy(niveau->description, NIVEAU_3_DESCRIPTION);
        break;
    case 4:
        strcat(nomFichier, "niveau4");
        strcpy(niveau->description, NIVEAU_4_DESCRIPTION);
        break;
    case 5:
        strcat(nomFichier, "niveau5");
        strcpy(niveau->description, NIVEAU_5_DESCRIPTION);
        break;
    case 6:
        strcat(nomFichier, "niveau6");
        strcpy(niveau->description, NIVEAU_6_DESCRIPTION);
        break;
    case 7:
        strcat(nomFichier, "niveau7");
        strcpy(niveau->description, NIVEAU_7_DESCRIPTION);
        break;
    default:
        break;
    }

    fic=fopen(nomFichier, "r");
    if(fic == NULL)
    {
        printf("Erreur :(Niveau) Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }


    /* Lecture de la composition du niveau : */
    while (fscanf(fic, "%s", typeGroupe) > 0)
    {
        groupe = (GroupeNiveau*)malloc(sizeof(GroupeNiveau));
        assert(groupe != NULL);

        if (strcmp(typeGroupe, "Asteroides") == 0)
        {
            groupe->type = NIVEAU_GROUPE_ASTEROIDES;
            valRet = fscanf(fic, "%d %d %d", &groupe->xmin, &groupe->xmax, &groupe->nombre);
            assert(valRet == 3);
            tabDynAjoute(&niveau->composition, (void*) groupe);
        }
        if (strcmp(typeGroupe, "Eclaireurs") == 0)
        {
            groupe->type = NIVEAU_GROUPE_ECLAIREURS;
            valRet = fscanf(fic, "%d %d %d", &groupe->xmin, &groupe->xmax, &groupe->nombre);
            assert(valRet == 3);
            tabDynAjoute(&niveau->composition, (void*) groupe);
        }
        if (strcmp(typeGroupe, "Chasseurs") == 0)
        {
            groupe->type = NIVEAU_GROUPE_CHASSEURS;
            valRet = fscanf(fic, "%d %d %d", &groupe->xmin, &groupe->xmax, &groupe->nombre);
            assert(valRet == 3);
            tabDynAjoute(&niveau->composition, (void*) groupe);
        }
        if (strcmp(typeGroupe, "Croiseurs") == 0)
        {
            groupe->type = NIVEAU_GROUPE_CROISEURS;
            valRet = fscanf(fic, "%d %d %d", &groupe->xmin, &groupe->xmax, &groupe->nombre);
            assert(valRet == 3);
            tabDynAjoute(&niveau->composition, (void*) groupe);
        }
    }

    fclose(fic);
}

/* -------------------------- Interface du module ------------------------------ */

void niveauInit(Niveau *niveau, int numero)
{
    assert(niveau != NULL);

    niveau->numero = numero;
    niveau->imageFond = 0; /* vide */
    tabDynInit(&niveau->composition);

    niveauChargeFichier(niveau, numero);
}

void niveauLibere(Niveau *niveau)
{
    int i;
    GroupeNiveau *g;
    assert(niveau != NULL);

    for (i=0; i< niveau->composition.tailleUtilisee; i++)
    {
        g=(GroupeNiveau *)tabDynGetElement(&niveau->composition, i);
        if ( g!= NULL)
            free(g);
    }
    tabDynLibere(&niveau->composition);
}

void niveauSetImageFond(Niveau *niveau, int indexImage)
{
    assert(niveau != NULL);
    niveau->imageFond = indexImage;
}

int niveauGetNumGroupes(const Niveau *niveau)
{
    assert(niveau != NULL);
    return niveau->composition.tailleUtilisee;
}


void niveauTestDeRegression()
{
    Niveau  niveau;
    printf("-----------------Test de niveauInit----------------\n");
    niveauInit(&niveau, 7);
    assert(niveau.numero==7);
    assert(strcmp(niveau.description, NIVEAU_7_DESCRIPTION)==0);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("-------------- Test de niveauSetImageFond -------------\n");
    niveauSetImageFond(&niveau, RESS_IMG_FOND_NIVEAU_7);
    assert(niveau.imageFond==RESS_IMG_FOND_NIVEAU_7);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------------- Test de niveauGetNumGroupes---------------\n");
    assert(niveauGetNumGroupes(&niveau)==4);
    printf("=========> Resultat : OK \n");
    printf("\n");


       /* Les test de liberations sont à effecter avec valgrind de préferences */
    printf("-----------------Test de niveauLibere----------------\n");
    niveauLibere(&niveau);
     printf("=========> Resultat : OK \n");
    printf("\n");
}

