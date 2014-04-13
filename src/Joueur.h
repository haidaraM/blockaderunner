/**
* @file Joueur.h
* @brief Fichier d'entete du module joueur
* Un joueur a un nom, a atteint un certain niveau et a un score
*/
#include "Vaisseau.h"

#ifndef _JOUEUR_H
#define _JOUEUR_H

#define JOUEUR_NOM_MAXCHAR				47
#define JOUEUR_MAX_SCORE				10000000


/**
* @struct Joueur
* @brief
*/

typedef struct
{
       char nom[JOUEUR_NOM_MAXCHAR];
       unsigned int progression;
       int score;
       Vaisseau vaisseau;
} Joueur;

/**
* @fn void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score, int pointS, int pointE, int nbArmes)
* @brief Initialise un joueur
* @param [in, out] joueur
* @param [in] nom
* @param [in] progression
* @param [in] score
* @param [in] pointS
* @param [in] pointE
* @param [in] nbArmes
*/
void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score, int pointS, int pointE, int nbArmes);

/**
* @fn void joueurLibere(Joueur * joueur)
* @brief libere un joueur
* @param [in, out] joueur
*/
void joueurLibere(Joueur * joueur);

/**
* @fn void joueurSetScore(Joueur * joueur);
* @brief met à jour le score du joeur. A REVOIR!!!!!!
* @param [in, out] joueur
* @param [in] score
*/
void joueurSetScore(Joueur * joueur, int score);

/**
* @fn int joueurGetScore(const Joueur *joueur)
* @brief renvoie le score du joueur
* @param [in] joueur
* @return int
*/
int joueurGetScore(const Joueur *joueur);

/**
* @fn unsigned int joueurGetProgression(const Joueur *joueur)
* @brief renvoie la progression du joueur
* @param  [in] joueur
*/
unsigned int joueurGetProgression(const Joueur *joueur);

/**
* @fn void joueurSetProgression(Joueur * joueur)
* @brief met a jour la progression (niveau )du joueur dans le jeu. A REVOIR!!!!!!
* @param [in, out] joueur
*/
void joueurSetProgression(Joueur * joueur);

/**
* @fn void joueurTestDeRegression()
* @brief effectue tout une batterie de tests pour le module Joueur en verifiant la coherence des differents elements
*/
void joueurTestDeRegression();

#endif

