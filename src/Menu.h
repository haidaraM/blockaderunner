/**
* @file Menu.h
* @brief Le module Menu gère le menu principal du jeu.
* @author Yann Cortial
*
*/
#ifndef _MENU_H
#define _MENU_H

#include "Rectangle.h"



#define MENU_DUREE_INTRO					8.0f		/* 8 secondes */

/*#define MENU_ETAT_INIT						-1*/
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


#define MENU_PADDING_HORZ					18
#define MENU_PADDING_VERT					18
#define MENU_ZONE_X							364
#define MENU_ZONE_Y							22
#define MENU_ZONE_LARGEUR					672
#define MENU_ZONE_HAUTEUR					678


#define MENU_NUM_ELEMENTS					10

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



typedef struct
{
	char *texte;
	/** booléen */
	int visible;
	/** booléen */
	int selectionable;
	/** booléen */
	int selectione;
	/** position */
	Rectangle rect;
} ElementMenu;

typedef struct
{
	/* Etat courant : intro, choix du joueur, menu principal, chargement, etc. */
	int etat;
	float tempsEcoule;
	/* tableau */
	ElementMenu *elements;
} Menu;



/**
* @brief Initialise le module.
* @param menu[in, out] : doit être non NULL.
*/
void menuInit(Menu *menu);
/**
* @brief Libère les ressources du module.
*/
void menuLibere(Menu *menu);
/**
* @brief Raffraichissement (surtout utile pour l'etat 'Intro' (splashscreen)).
*/
void menuMiseAJour(Menu *menu, float tempsBoucleEcoule);

#endif

