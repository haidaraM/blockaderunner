/**
* @file Menu.h
* @brief Le module Menu gère l'introduction au jeu et le menu principal.
* @author Yann Cortial
*
*/
#ifndef _MENU_H
#define _MENU_H

#include "Outils.h"
#include "Ressource.h"



#define MENU_DUREE_INTRO					3.0f		/* 3 secondes */

/* Definitions des differents etats du menu */
enum { MENU_ETAT_INTRO,
        MENU_ETAT_CHOIX_JOUEUR,
        MENU_ETAT_ENTREE_JOUEUR,
        MENU_ETAT_PRINCIPAL,
        MENU_ETAT_CMD,
        MENU_ETAT_OPTION,
        MENU_ETAT_INFO,
        MENU_ETAT_CHOIX_NIVEAU,
        MENU_ETAT_SCORE,
        MENU_ETAT_CHARGEMENT,
        MENU_ETAT_QUITTER,
        MENU_ETAT_PAUSE,
        MENU_ETAT_REPRENDRE,
        MENU_ETAT_REJOUER,
        MENU_ETAT_PAUSE_SCORE,
        MENU_ETAT_PAUSE_CMD,
        MENU_ETAT_PAUSE_RETOUR_MENU_PRINCIPAL
        };

#define MENU_PADDING_HORZ					20
#define MENU_PADDING_VERT					20
#define MENU_ZONE_X							364
#define MENU_ZONE_Y							22
#define MENU_ZONE_LARGEUR					672
#define MENU_ZONE_HAUTEUR					678


#define MENU_NUM_BASIC_ELEMENTS				(13 + RESS_NUM_NIVEAUX)
#define MENU_NUM_ELEMENTS					(MENU_NUM_BASIC_ELEMENTS + RESS_SAU_MAX_JOUEURS)

#define MENU_RETOUR							0
#define MENU_JOUEURS						1
#define MENU_NOUVEAU_JOUEUR					2
#define MENU_ENTRER_NOM						3
#define MENU_INFO							4
#define MENU_CHANGER_JOUEUR					5
#define MENU_CMD							6
#define MENU_JOUER							7
#define MENU_SCORE							8
#define MENU_QUITTER						9
#define MENU_REPRENDRE                      10
#define MENU_REJOUER                        11
#define MENU_RETOUR_MENU_PRINCIPAL          12
#define MENU_NIVEAU							13


#define MENU_TXT_JOUEUR_VIDE 				"___"
#define MENU_TXT_JOUEURS					"Joueurs"
#define MENU_TXT_NOUVEAU_JOUEUR				"Nouveau Joueur"
#define MENU_TXT_ENTRER_NOM					"Entrez un nom : "
#define MENU_TXT_INFO						"Info"
#define MENU_TXT_CHANGER_JOUEUR				"Changer de Joueur"
#define MENU_TXT_CMD						"Commandes"
#define MENU_TXT_JOUER						"Jouer"
#define MENU_TXT_SCORE						"Meilleurs Scores"
#define MENU_TXT_RETOUR						"<<"
#define MENU_TXT_QUITTER					"Quitter"
#define MENU_TXT_NIVEAU						"Niveau "
#define MENU_TXT_REPRENDRE                  "Reprendre"
#define MENU_TXT_REJOUER                    "Rejouer"
#define MENU_TXT_RETOUR_MENU_PRINCIPAL      "Retour au menu principal"



/**
* @struct ElementMenu
* @brief Element du Menu : un texte avec états (actionable, visible, surlignable), position & dimension, et procédure associée.
*/
typedef struct
{
	/** texte affichable de l'element menu */
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
* @struct Menu
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
	/** Lors de la création d'un nouveau joueur, sert à stocker le nom. */
	char nomNouveauJoueur[JOUEUR_NOM_MAXCHAR+1];
	/** tableau des noms des meilleurs joueurs */
	char **nomsMeilleursJoueurs;
	/** tableau des meilleurs scores (sous forme de chaines de caracteres) */
	char **meilleursScores;
	/** Niveau sélectionné par le joueur. */
	int niveauChoisi;
	/** Réference au module Ressource. (Permet de sauver l'etat des joueurs, d'obtenir les meilleurs joueurs classés). */
	Ressource *ressource;

} Menu;



/**
* @fn void menuInit(Menu *menu, Ressource *res)
* @brief Initialise le module.
* @param menu[in, out] : doit être non NULL.
* @param res[in, out] : doit être non NULL et initialisé.
*/
void menuInit(Menu *menu, Ressource *res);

/**
* @fn void menuLibere(Menu *menu)
* @brief Libère les ressources du module.
* @param [in, out] menu : initialisé
*/
void menuLibere(Menu *menu);

/**
* @fn void menuIntro(Menu *menu, float tempsBoucleEcoule)
* @brief Affiche l'image d'intro (splashscreen).
* @param [in, out] menu
* @param [in] tempsBoucleEcoule
*/
void menuIntro(Menu *menu, float tempsBoucleEcoule);

/**
* @fn void menuRetour(void *m)
* @brief Appelée lorque l'utilisateur souhaite remonter d'un cran dans les menus.
* @param [in] m
*/
void menuRetour(void *m);

/**
* @fn void menuQuitter(void *m)
* @brief Callback appelée lorque l'utilisateur souhaite quitter l'application.
* @param [in] m
*/
void menuQuitter(void *m);

/**
* @fn void menuChoixJoueur(void *m)
* @brief Callback appelée lorque l'utilisateur doit choisir le Joueur.
* @param [in] m
*/
void menuChoixJoueur(void *m);

/**
* @fn void menuNouveauJoueur(void *m)
* @brief Callback appelée lorque l'utilisateur souhaite créer un nouveau Joueur.
* @param [in] m
*/
void menuNouveauJoueur(void *m);

/**
* @fn void menuPrincipal(void *m)
* @brief Callback appelée lorque l'utilisateur doit entrer dans le Menu principal.
* @param [in] m
*/
void menuPrincipal(void *m);

/**
* @fn void menuCommandes(void *m);
* @brief Callback appelée lorque l'utilisateur souhaite voir les commandes du jeu (clavier).
* @param [in] m
*/
void menuCommandes(void *m);

/**
* @fn void menuChangerJoueur(void *m)
* @brief Callback appelée depuis le menu principal, lorque l'utilisateur souhaite changer de joueur.
* @param [in] m
*/
void menuChangerJoueur(void *m);

/**
* @fn void menuInfo(void *m
* @brief Callback appelée lorque l'utilisateur souhaite avoir des informations sur le jeu (auteurs, ...).
* @param [in]
*/
void menuInfo(void *m);

/**
* @fn void menuScores(void *m)
* @brief Callback appelée lorque l'utilisateur souhaite voir les meilleurs scores.
* @param [in] m
*/
void menuScores(void *m);

/**
* @fn void menuJouer(void *m)
* @brief Callback appelée lorque l'utilisateur souhaite lancer une partie.
* @param [in] m
*/
void menuJouer(void *m);

/**
* @fn void menuSelectionneJoueur(Menu *menu, int indexElement)
* @brief Appelée lorque l'utilisateur a sélectionné un joueur.
* @param [in, out] menu
* @param [in] indexElement
*/
void menuSelectionneJoueur(Menu *menu, int indexElement);

/**
* @fn void menuSetCaractere(Menu *menu, char alphaNum);
* @brief Appelée lorque l'utilisateur tape au clavier : un caractère alphanumérique a été saisi.
* @param [in,out] menu
* @param [in] alphaNum
*/
void menuSetCaractere(Menu *menu, char alphaNum);

/**
* @fn void menuCommencerNiveau(void* m)
* @brief Callback (vide - inutilisée, JeuSDL appelle directement le chargement d'un niveau).
* @param [in] m
*/
void menuCommencerNiveau(void* m);


/**
* @fn void menuEffaceCaractere(Menu *menu)
* @brief Appelée lorque l'utilisateur tape au clavier : la touche Backspace a été pressée.
* @param [in, out] menu
*/
void menuEffaceCaractere(Menu *menu);

/**
* @fn void menuSetFinLectureClavier(Menu *menu)
* @brief Appelée lorque l'utilisateur tape au clavier : la touche ENTER a été pressée, signifiant la fin de la saisie.
* @param [in, out] menu
*/
void menuSetFinLectureClavier(Menu *menu);

/**
* @fn Joueur* menuGetJoueurChoisi(const Menu *menu)
* @brief Renvoie le pointeur sur le joueur actif (ou NULL si aucun joueur n'a été selectionné dans le menu).
* @param [in] menu
*/
Joueur* menuGetJoueurChoisi(const Menu *menu);

/**
* @fn void menuSelectionneNiveau(Menu *menu, int indexElement)
* @brief Appelée lorsque l'utilisateur a choisi un niveau de jeu.
* @param [in, out] menu
* @param [in] indexElement
*/
void menuSelectionneNiveau(Menu *menu, int indexElement);

/**
* @fn int menuGetNiveauChoisi(const Menu *menu)
* @brief Renvoie le niveau selectionné ou -1 si aucun niveau n'a été selectionné.
* @param [in] menu
*/
int menuGetNiveauChoisi(const Menu *menu);

/**
* @fn void menuPause(void * m)
* @brief Appelée lorsque le joueur appuie sur P.
* Met a jour l'etat du menu et les elements visibles
* @param [in] m
*/
void menuPause(Menu *m);

/**
* @fn void menuReprendre(void *m)
* @brief Callback appelé lorsque le joueur souhaite reprendre la partie après la pause
* @param [in] m
*/
void menuReprendre(void *m);


/**
* @fn void menuReJouer(void *m)
* @brief Callback appelé lorsque le joueur souhaite rejouer la partie après la pause
* @param [in] m
*/
void menuReJouer(void *m);

/**
* @fn void menuRetourPrincipal(void *m)
* @brief Call back appelé lorsque le joueur souhaite retourner au menu principal dans le menu pause
* @param [in]
*/
void menuRetourPrincipal(void *m);

#endif

