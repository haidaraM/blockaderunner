/**
* @file Niveau.h
* @brief Le module Niveau décrit le contenu d'un Niveau du jeu : nombre d'ennemis, image de fond etc.
* @author Yann Cortial - Mohamed El Mouctar
*/
#ifndef _NIVEAU_H
#define _NIVEAU_H

#include "Outils.h"



#define NIVEAU_0_DESCRIPTION									"Sortir du champ d'astéroïdes : attention aux éclaireurs!"
#define NIVEAU_1_DESCRIPTION                                    "Sortir du champ d'astéroïdes : attention aux éclaireurs!"
#define NIVEAU_2_DESCRIPTION                                    "Vagues de chasseurs ennemis détectées"
#define NIVEAU_3_DESCRIPTION                                    "Vagues de chasseurs ennemis détectées"
#define NIVEAU_4_DESCRIPTION                                    "Attention aux croiseurs ennemis!"
#define NIVEAU_5_DESCRIPTION                                    "Approche de Shantori"
#define NIVEAU_6_DESCRIPTION                                    "Orbite basse de Shantori"
#define NIVEAU_7_DESCRIPTION                                    "Entrée atmosphérique sur Shantori!"

#define NIVEAU_GROUPE_ASTEROIDES								0
#define NIVEAU_GROUPE_ECLAIREURS								1
#define NIVEAU_GROUPE_CHASSEURS									2
#define NIVEAU_GROUPE_CROISEURS									3


/**
* @struct GroupeNiveau
* @brief Structure utilisée pour la composition d'un niveau : décrit un groupe d'éléments de même type.
*/
typedef struct
{
	/** type d'element : champ d'asteroides, escadre de chasseurs, ... */
	int type;
	/** position min en x*/
	int xmin;
	/** position max en x*/
	int xmax;
	/** nombre d'éléments constituants (exemple : nombre de chasseurs dans l'escadre).*/
	int nombre;
} GroupeNiveau;

/**
* @struct Niveau
* @brief Cette structure contient les differentes informations qui caracterisent un niveau de jeu
*/
typedef struct
{
	/** entier : 0, 1, 2, 3... */
	char numero;
	/** chaîne de caractères : description courte du niveau. */
	char description[255];
	/** index dans Ressource de l'image de fond (background) du niveau. */
	int imageFond;
	/** Composition du niveau : asteroides, vaisseaux ennemi, etc. **/
	TabDyn composition;
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
* @param [in, out] niveau : initialisé
* @param [in] indexImage
*/
void niveauSetImageFond(Niveau *niveau, int indexImage);

/**
* @fn void niveauChargeFichier(Niveau * niveau, int numero)
* @brief Charge les caractéristiques du niveau a partir d'un fichier
* @param [in, out] niveau : initialisé
* @param [in] numero : correspond au numero du niveau
*/
void niveauChargeFichier(Niveau * niveau, int numero);

/**
* @fn int niveauGetNumGroupes(Niveau * niveau)
* @brief Renvoie le nombre de groupes qui composent le niveau (rappel : un groupe peut-etre un champ d'asteroides, une escadre de chasseurs ennemis, etc...)
* @param [in] niveau : initialisé
*/
int niveauGetNumGroupes(const Niveau * niveau);

/**
* @fn void niveauTestDeRegression()
* @brief Test de regression du module Niveau
*/
void niveauTestDeRegression();

#endif

