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
* @brief Represente les caractéristiques du joueur.
*/

typedef struct
{
        /** Chaine de caractères correspondant au nom du joueur */
       char nom[JOUEUR_NOM_MAXCHAR];
       /** Progression du joueur */
       unsigned int progression;
       /** Score */
       int score;
       /** Pointeur vers le vaisseau du joueur */
       Vaisseau *vaisseau;
} Joueur;

/**
* @fn void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score)
* @brief Initialise un joueur
* @param [in, out] joueur
* @param [in] nom
* @param [in] progression
* @param [in] score
*/
void joueurInit(Joueur *joueur, char *nom, unsigned int progression, int score);

/**
* @fn void joueurLibere(Joueur * joueur)
* @brief libere un joueur
* @param [in, out] joueur
*/
void joueurLibere(Joueur * joueur);

/**
* @fn void joueurSetScore(Joueur * joueur);
* @brief met à jour le score du joeur. !
* @param [in, out] joueur : non null et initialisé
* @param [in] score
*/
void joueurSetScore(Joueur * joueur, int score);

/**
* @fn Vaisseau * joueurGetVaisseau(const Joueur * joueur)
* @brief Renvoie le vaisseau du joueur
* @param [in] joueur : initialisé
*/
Vaisseau * joueurGetVaisseau(const Joueur * joueur);

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
* @brief met a jour la progression (niveau )du joueur dans le jeu.
* @param [in, out] joueur
*/
void joueurSetProgression(Joueur * joueur);

/**
* @fn void joueurSetArmeSelectionne(Joueur * joueur, int numArme)
* @brief Met à jour l'arme selectionné par le joueur
* @param [in, out] joueur : initialisé
* @param [in] numArme : 0 <= numArme <nbArme
*/
void joueurSetArmeSelectionne(Joueur * joueur, int numArme );

/**
* @fn int joueurGetNumArmeSelectionne(const Joueur * joueur)
* @brief Renvoie le numero de l'arme selectionné par le joueur
* @param [in] joueur : initialisé
*/
int joueurGetNumArmeSelectionne(const Joueur * joueur);

/**
* @fn Joueur * joueurCopieJoueur(Joueur * j)
* @brief fais une copie de joueur
* @param [in] j : initialisé
*/
Joueur * joueurCopieJoueur(Joueur * j);

/**
* @fn void joueurTestDeRegression()
* @brief effectue tout une batterie de tests pour le module Joueur en verifiant la coherence des differents elements
*/
void joueurTestDeRegression();

#endif

