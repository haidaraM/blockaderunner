/**
* @file Joueur.h
* @brief Fichier d'entete du module joueur
* Un joueur a un nom, a atteint un certain niveau et a un score
*/
#ifndef _JOUEUR_H
#define _JOUEUR_H

/**
* @struct Joueur
* @brief
*/

typedef struct
{
       char * nomJoueur;
       unsigned int progression;
       int score;
} Joueur;

/**
* @fn void joueurInit(Joueur *joueur, char *nom, unsigned int progression)
* @brief Initialise un joueur
* @param [in, out] joueur
* @param [in] nom
* @param [in] progression
*/
void joueurInit(Joueur *joueur, char *nom, unsigned int progression);

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
*/
void joueurSetScore(Joueur * joueur);

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
