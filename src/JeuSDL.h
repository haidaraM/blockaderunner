/**
* @file JeuSDL.h
* @brief fichier d'en-tête du module JeuSDL
* @author Cortial Yann
*
* Module principal du programme.
* Regroupe l'accès aux sous-systèmes essentiels (video, audio), les modules de gestion de haut-niveau (entrées, ressources), et la vue/état global du jeu (Scene).
*
* @bug Le rendu de texte dynamique a pas l'air très stable :
* 		Program received signal SIGSEGV, Segmentation fault.
* 		__strcpy_sse2_unaligned () at ../sysdeps/x86_64/multiarch/strcpy-sse2-unaligned.S:590
* 		590	../sysdeps/x86_64/multiarch/strcpy-sse2-unaligned.S: Aucun fichier ou dossier de ce type.
* 		(gdb) 
*/
#ifndef _JEU_SDL_H
#define _JEU_SDL_H

#include "GraphiqueSDL.h"
/*#include "AudioSDL.h"*/
#include "EntreeSDL.h"
#include "Ressource.h"
#include "Menu.h"
/*#include "Niveau.h"*/
#include "Joueur.h"
#include "Scene.h"
#include "Outils.h"

#define JEU_ETAT_MENU 				0
#define JEU_ETAT_CHARGEMENT_NIVEAU	1
#define JEU_ETAT_JEU				2

/**
* @struct JeuSDL
* @brief 
*/
typedef struct {

	/** Initialise et dispose la fenetre principale. */
	GraphiqueSDL graphique;
	/* AudioSDL audio; */
	/** Initialise et gère les évènements (clavier, souris ..). */
	EntreeSDL entree;

	/** Menu principal */
	Menu menu;
	/** Scène (ce qui est visible à l'écran et au-delà : instancie le contenu du Niveau). */
	Scene scene;
	/** Joueur courant (sélectionné par le Menu). */
	Joueur *joueur;
	/** Répertorie les ressources du jeu (images, sons, polices). */
	Ressource ressource;

	/** Phase courante = JEU_ETAT_MENU ou JEU_ETAT_NIVEAU. */
	int etatCourantJeu;
	/** Niveau en cours ou à charger */
	int niveauCourant;
	
} JeuSDL;

/**
* @fn void jeuInit(JeuSDL *)
* @brief Initialise notamment les sous-systèmes (Video, Audio), et les modules de gestion (Entree, Ressource).
* @param jeu[in, out] : doit être non NULL.
*/ 
void jeuInit(JeuSDL *jeu);
/**
* @fn void jeuBoucle(JeuSDL *)
* @brief Boucle principale du programme.
*
* Gestion du temps écoulé, lecture des entrées, mise à jour de l'état du jeu et affichage final.
*/ 
void jeuBoucle(JeuSDL *jeu);
/**
* @fn void jeuLibere(JeuSDL *)
* @brief Libère toutes les ressources mobilisées par le programme.
*/
void jeuLibere(JeuSDL *jeu);

#endif

