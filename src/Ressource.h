/**
* @file Ressource.h
* @brief Module dictionnaire de ressources : images, sons, polices.
* @author Yann Cortial
*
*/
#ifndef _RESSOURCE_H
#define _RESSOURCE_H



#include "Outils.h"
#include "Joueur.h"
#include "Niveau.h"



#define RESS_NUM_NIVEAUX										7
#define RESS_NUM_IMAGES											32
#define RESS_NUM_SONS											0
#define RESS_NUM_POLICES										1


/* NIVEAUX */
#define RESS_NIV_0_DESCRIPTION									"Sortir du champ d'astéroïdes !"


/* REPERTOIRES */

#define RESS_DIR_IMAGES											"data/images/"
#define RESS_DIR_SONS											"data/sons/"
#define RESS_DIR_POLICES										"data/polices/"
#define RESS_DIR_SAUVEGARDES									"data/sauvegardes/"


/* SAUVEGARDES */

#define RESS_SAU_MAX_JOUEURS									20
#define RESS_SAU_FICHIER_JOUEURS								"joueurs"


/* TEXTES */

#define RESS_TXT_TITRE_JEU 	 									"Blockade Runner"


/* POLICES */

#define RESS_POL_FICHIER_MENU									"boombox2.ttf"
#define RESS_POL_TAILLE_MENU									18
#define RESS_POL_TAILLE_LISTE_JOUEURS							12


/* IMAGES */

#define RESS_IMG_NULL						 					0

#define RESS_IMG_VAISSEAU_JOUEUR			 					1
#define RESS_IMG_FICHIER_VAISSEAU_JOUEUR						"playership2.png"
#define RESS_IMG_LARGEUR_VAISSEAU_JOUEUR						128
#define RESS_IMG_HAUTEUR_VAISSEAU_JOUEUR 						45

#define RESS_IMG_TIR_JOUEUR_LASER                               2
#define RESS_IMG_FICHIER_TIR_JOUEUR_LASER                      "laser_tir.png"
#define RESS_IMG_LARGEUR_TIR_JOUEUR_LASER                       32
#define RESS_IMG_HAUTEUR_TIR_JOUEUR_LASER                       4

#define RESS_IMG_TIR_LASER_JOUEUR                               3
#define RESS_IMG_FICHIER_TIR_LASER_JOUEUR                       "laser_tir.png"
#define RESS_IMG_LARGEUR_TIR_LASER_JOUEUR                             32
#define RESS_IMG_HAUTEUR_TIR_LASER_JOUEUR                             4

#define RESS_IMG_SPLASH						 					10
#define RESS_IMG_FICHIER_SPLASH									"splash0.jpg"
#define RESS_IMG_LARGEUR_SPLASH									1366
#define RESS_IMG_HAUTEUR_SPLASH			 						720

#define RESS_IMG_FOND_MENU					 					11
#define RESS_IMG_FICHIER_FOND_MENU								"menu.jpg"
#define RESS_IMG_LARGEUR_FOND_MENU								1366
#define RESS_IMG_HAUTEUR_FOND_MENU		 						720

#define RESS_IMG_FOND_NIVEAU_0				 					20
#define RESS_IMG_FICHIER_FOND_NIVEAU_0							"bg1.jpg"
#define RESS_IMG_LARGEUR_FOND_NIVEAU_0							4098
#define RESS_IMG_HAUTEUR_FOND_NIVEAU_0	 						720


/**
* @struct Ressource
* @brief
*/
typedef struct
{
	int numJoueurs;
	/** Tableau de pointeurs sur Joueur : tous les joueurs sauvegardés. */
	Joueur **joueurs;
	/** Tableau de chaines de caractères (noms des fichiers images) */
	char **images;
	/** Tableau de Rectangles stockant les dimensions de chaque image */
	Rectangle *dimensionImages;
	/** Tableau de chaines de caractères (noms des fichiers sons) */
	char **sons;
	/** Tableau de chaines de caractères (noms des fichiers ttf) */
	char **polices;

	/** Tableau de tous les niveaux du jeu. */
	Niveau *niveaux;

} Ressource;

/**
* @fn void ressourceInit(Ressource *res)
* @brief Initialise le module.
* @param res[in, out] : doit être non NULL.
*/
void ressourceInit(Ressource *res);

/**
* @fn void ressourceLibere(Ressource *res)
* @brief Libère toutes les ressources gérées par le module (images, sons, polices).
*/
void ressourceLibere(Ressource *res);


/**
* @brief Renvoie le nombre de joueurs sauvegardés.
*/
int ressourceGetNumJoueurs(Ressource *res);
/**
* @brief Renvoie le tableau de pointeurs sur Joueur (ie tous les joueurs connus).
*/
Joueur** ressourceGetJoueurs(Ressource *res);
/**
* @brief Ajoute un joueur à la liste des joueurs sauvegardés.
*/
void ressourceAjouteJoueur(Ressource *res, char nomJoueur[JOUEUR_NOM_MAXCHAR+1], int indexJoueur);

Niveau ressourceGetNiveau(Ressource *res, int numeroNiveau);


/**
* @brief Renvoie la largeur d'une image cataloguée.
* @param res[in, out] : instance de Ressource.
* @param nomRessource : un entier définissant la ressource demandée. Par exemple RESS_VAISSEAU_JOUEUR.
* @return largeur de l'image.
*/
int ressourceGetLargeurImage(const Ressource *res, int nomRessource);
/**
* @brief Renvoie la hauteur d'une image cataloguée.
* @param res[in, out] : instance de Ressource.
* @param nomRessource : un entier définissant la ressource demandée. Par exemple RESS_VAISSEAU_JOUEUR.
* @return hauteur de l'image.
*/
int ressourceGetHauteurImage(const Ressource *res, int nomRessource);

#endif


