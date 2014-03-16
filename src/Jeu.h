/**
* @file Jeu.h
* @brief fichier d'en-tête
* @author Cortial Yann
*/
#ifndef _JEU_H
#define _JEU_H

#include "Ecran.h"
#include "Entree.h"
#include "Ressource.h"
#include "Scene.h"



/**
* @struct Jeu
* @brief Structure utilisée pour la gestion d'une partie
*/
typedef struct {

	/** Initialise et dispose la fenetre principale */
	Ecran ecran;
	/** Initialise et gère les évènements (clavier, souris ..) */
	Entree entree;
	/** Initialise et gère les ressources du jeu (images, sons, polices) */
	Ressource ressource;
	/** Initialise et gère la scène (ce qui est visible à l'écran) */
	Scene scene;
	
} Jeu;

/**
* @fn void jeuInit(Jeu *)
* @brief
*/ 
void jeuInit(Jeu *);
/**
* @fn void jeuBoucle(Jeu *)
* @brief
*/ 
void jeuBoucle(Jeu *);
/**
* @fn void jeuLibere(Jeu *)
* @brief
*/
void jeuLibere(Jeu *);

#endif

