/**
* @file Joueur.h
* @brief Fichier d'entete du module joueur
* Un joueur a un nom, a atteint un certain niveau et a un score
*/
#ifndef _JOUEUR_H
#define _JOUEUR_H

#define JOUEUR_NOM_MAXCHAR				47




/**
* @struct Joueur
* @brief
*/

typedef struct
{
       char *nom;
       unsigned int progression;
       int score;
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

