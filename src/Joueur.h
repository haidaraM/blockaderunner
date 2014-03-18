/**
* @file Joueur.h
* @brief Fichier d'entete du module joueur
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

void joueurInit(Joueur *joueur, char *nom, unsigned int progression);
void joueurLibere(Joueur * joueur);

void joueurSetScore(Joueur * joueur);
void joueurSetBonus(Joueur *joueur, int typeBonus);
int joueurGetScore(const Joueur *joueur);

unsigned int joueurGetProgression(const Joueur *joueur);
void joueurSetProgression(Joueur * joueur);

#endif
