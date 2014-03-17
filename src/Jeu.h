/**
* @file Jeu.h
* @brief fichier d'en-tête du module Jeu
* @author Cortial Yann
*
* Module principal du programme.
* Regroupe les sous-systèmes essentiels (video, audio), les modules de gestion de haut-niveau (entrées, ressources), et la vue/état global du jeu (Scene).
*/
#ifndef _JEU_H
#define _JEU_H

#include "Ecran.h"
#include "Entree.h"
#include "Ressource.h"
#include "Scene.h"



/**
* @struct Jeu
* @brief 
*/
typedef struct {

	/** Initialise et dispose la fenetre principale */
	Ecran ecran;
	/** Initialise et gère les évènements (clavier, souris ..) */
	Entree entree;
	/** Initialise et gère les ressources du jeu (images, sons, polices) */
	Ressource ressource;
	/** Initialise et gère la scène (ce qui est visible à l'écran et au-delà) */
	Scene scene;
	
} Jeu;

/**
* @fn void jeuInit(Jeu *)
* @brief Initialise les sous-systèmes (Video, Audio), et les modules de gestion (Entree, Ressource).
*/ 
void jeuInit(Jeu *);
/**
* @fn void jeuBoucle(Jeu *)
* @brief Boucle principale du programme.
*
* Gestion du temps écoulé, lecture des entrées, mise à jour de l'état du jeu et affichage final.
*/ 
void jeuBoucle(Jeu *);
/**
* @fn void jeuLibere(Jeu *)
* @brief Libère toutes les ressources mobilisées par le programme.
*/
void jeuLibere(Jeu *);

#endif

