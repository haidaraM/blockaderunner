/**
* @file Jeu.h
* @brief fichier d'en-tête du module Jeu
* @author Cortial Yann
*
* Module principal du programme.
* Regroupe l'accès aux sous-systèmes essentiels (video, audio), les modules de gestion de haut-niveau (entrées, ressources), et la vue/état global du jeu (Scene).
*/
#ifndef _JEU_H
#define _JEU_H

#include "Ecran.h"
#include "Entree.h"
#include "Ressource.h"
#include "Menu.h"
/*#include "Niveau.h"*/
#include "Joueur.h"
#include "Scene.h"

#define JEU_ETAT_MENU 				0
#define JEU_ETAT_NIVEAU				1

/**
* @struct Jeu
* @brief 
*/
typedef struct {

	/** Initialise et dispose la fenetre principale. */
	Ecran ecran;
	/** Initialise et gère les évènements (clavier, souris ..). */
	Entree entree;
	/** Initialise et gère les ressources du jeu (images, sons, polices). */
	Ressource ressource;

	/** Menu principal */
	Menu menu;
	/** Scène (ce qui est visible à l'écran et au-delà : instancie le contenu du Niveau). */
	Scene scene;
	/** Joueur courant (sélectionné par le Menu). */
	Joueur joueur;

	/** Phase courante = JEU_ETAT_MENU ou JEU_ETAT_NIVEAU. */
	int etatCourantJeu;
	
} Jeu;

/**
* @fn void jeuInit(Jeu *)
* @brief Initialise notamment les sous-systèmes (Video, Audio), et les modules de gestion (Entree, Ressource).
* @param jeu[in, out] : doit être non NULL.
*/ 
void jeuInit(Jeu *jeu);
/**
* @fn void jeuBoucle(Jeu *)
* @brief Boucle principale du programme.
*
* Gestion du temps écoulé, lecture des entrées, mise à jour de l'état du jeu et affichage final.
*/ 
void jeuBoucle(Jeu *jeu);
/**
* @fn void jeuLibere(Jeu *)
* @brief Libère toutes les ressources mobilisées par le programme.
*/
void jeuLibere(Jeu *jeu);

#endif

