/**
* @file Niveau.h
* @brief Le module Niveau décrit le contenu d'un Niveau du jeu : nombre d'ennemis, image de fond etc.
* @author Yann Cortial - Mohamed El Mouctar
*/
#ifndef _NIVEAU_H
#define _NIVEAU_H


#define NIVEAU_0_DESCRIPTION									"Sortir du champ d'astéroïdes !"
#define NIVEAU_1_DESCRIPTION                                    "Ennemis Eclaireurs!"
#define NIVEAU_2_DESCRIPTION                                    "Niveau 2"
#define NIVEAU_3_DESCRIPTION                                    "Niveau 3"

typedef struct
{
	/** entier : 1, 2, 3... */
	char numero;
	/** chaîne de caractères : description courte du niveau. */
	char description[100];
	/** index dans Ressource de l'image de fond (background) du niveau. */
	int imageFond;
	/** Nombre d'ennemis du niveau : asteroides et vaisseauEnnemis **/
	int nbEnnemis;
	/** Nombre de bonus du niveau */
	int nbBonus;
} Niveau;


/**
* @fn void niveauInit(Niveau *niveau, int numero)
* @brief Initialise le niveau.
* @param [in, out] niveau : doit être non NULL.
* @param [in] numero
*/
void niveauInit(Niveau *niveau, int numero);

/**
* @fn void niveauLibere(Niveau *niveau)
* @brief Libère le niveau.
* @param [in, out] niveau : doit etre non NULL
*/
void niveauLibere(Niveau *niveau);

/**
* @fn void niveauSetImageFond(Niveau *niveau, int indexImage)
* @brief Donne l'index de l'image de fond au niveau
* @param [in, out] niveau
* @param [in] indexImage
*/
void niveauSetImageFond(Niveau *niveau, int indexImage);

/**
* @fn void niveauChargeFichier (Niveau * niveau, int numero)
* @brief Charge les caractéristiques du niveau a partir d'un fichier (cf M Meyer ). FICHIER A COMPLETER!!!
* @param [in, out] niveau
* @param [in] numero : correspond au numero du niveau
*/
void niveauChargeFichier (Niveau * niveau, int numero);

#endif

