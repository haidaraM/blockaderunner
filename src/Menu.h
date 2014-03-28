/**
* @file Menu.h
* @brief Le module Menu gère l'introduction au jeu et le menu principal.
* @author Yann Cortial
*
*/
#ifndef _MENU_H
#define _MENU_H

#include "Outils.h"
#include "Joueur.h"
#include "Ressource.h"



#define MENU_DUREE_INTRO					8.0f		/* 8 secondes */


#define MENU_ETAT_INTRO						0
#define MENU_ETAT_CHOIX_JOUEUR				1
#define MENU_ETAT_ENTREE_JOUEUR				2
#define MENU_ETAT_PRINCIPAL					8
#define MENU_ETAT_CMD						9
#define MENU_ETAT_OPTION					10
#define MENU_ETAT_INFO						11
#define MENU_ETAT_CHOIX_NIVEAU				12	
#define MENU_ETAT_SCORE						13					
#define MENU_ETAT_CHARGEMENT				64
#define MENU_ETAT_QUITTER					128


#define MENU_PADDING_HORZ					20
#define MENU_PADDING_VERT					20
#define MENU_ZONE_X							364
#define MENU_ZONE_Y							22
#define MENU_ZONE_LARGEUR					672
#define MENU_ZONE_HAUTEUR					678


#define MENU_NUM_BASIC_ELEMENTS				10
#define MENU_NUM_ELEMENTS					(MENU_NUM_BASIC_ELEMENTS + RESS_SAU_MAX_JOUEURS) 

#define MENU_RETOUR						0
#define MENU_JOUEURS					1
#define MENU_NOUVEAU_JOUEUR				2
#define MENU_ENTRER_NOM					3
#define MENU_INFO						4
#define MENU_OPTION						5
#define MENU_CMD						6
#define MENU_JOUER						7
#define MENU_SCORE						8
#define MENU_QUITTER					9

#define MENU_TXT_JOUEUR_VIDE 				"*"
#define MENU_TXT_JOUEURS					"Joueurs"
#define MENU_TXT_NOUVEAU_JOUEUR				"Nouveau Joueur"
#define MENU_TXT_ENTRER_NOM					"Entrez un nom : "
#define MENU_TXT_INFO						"Info"
#define MENU_TXT_OPTION						"Options"
#define MENU_TXT_CMD						"Commandes"
#define MENU_TXT_JOUER						"Jouer"
#define MENU_TXT_SCORE						"Meilleurs Scores"
#define MENU_TXT_RETOUR						"<<<"
#define MENU_TXT_QUITTER					"Quitter"



/**
* @brief Element du Menu : un texte avec états (actionable, visible, surlignable) et position & dimension.
*/
typedef struct
{
	char *texte;
	/** booléen */
	int visible;
	/** booléen */
	int actionable;
	/** booléen */
	int surligne;
	/** position */
	Rectangle rect;
	/** procédure à exécuter si l'élément est actionable. */
	void (*action)(void*);

} ElementMenu;


/**
* @brief Structure principale du module Menu.
*/
typedef struct
{
	/** Etat courant du Menu : intro, choix du joueur, menu principal, chargement d'un niveau, etc.... */
	int etat;
	/** Temps écoulé depuis le lancement de l'application : sert à l'affichage temporaire de l'intro (splashscreen). */
	float tempsEcoule;
	/** Tableau de tous les éléments Menu affichables et statiques. */
	ElementMenu *elements;
	/** Joueur courant (index dans le tableau maintenu par le module Ressource) */
	int joueurCourant;
	/** Réference au module Ressource. (Permet de sauver l'etat des joueurs). */
	Ressource *ressource;

} Menu;



/**
* @brief Initialise le module.
* @param menu[in, out] : doit être non NULL.
* @param res[in, out] : doit être non NULL et initialisé.
*/
void menuInit(Menu *menu, Ressource *res);
/**
* @brief Libère les ressources du module.
*/
void menuLibere(Menu *menu);
/**
* @brief On affiche l'image d'intro (splashscreen).
*/
void menuIntro(Menu *menu, float tempsBoucleEcoule);
/**
* @brief Appelée lorque l'utilisateur souhaite remonter d'un cran dans les menus.
*/
void menuRetour(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite quitter l'application.
*/
void menuQuitter(void *m);
/**
* @brief Appelée lorque l'utilisateur doit choisir le Joueur.
*/
void menuChoixJoueur(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite créer un nouveau Joueur.
*/
void menuNouveauJoueur(void *m);
/**
* @brief Appelée lorque l'utilisateur doit entrer dans le Menu principal.
*/
void menuPrincipal(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite voir les commandes du jeu (clavier).
*/
void menuCommandes(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite modifier les options de jeu.
*/
void menuOptions(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite avoir des informations sur le jeu (auteurs, ...).
*/
void menuInfo(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite voir les meilleurs scores.
*/
void menuScores(void *m);
/**
* @brief Appelée lorque l'utilisateur souhaite lancer une partie.
*/
void menuJouer(void *m);
/**
* @brief Appelée lorque l'utilisateur a sélectionné un joueur.
*/
void menuSelectionJoueur(void *m);

#endif

