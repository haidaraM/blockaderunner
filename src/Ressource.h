/**
* @file Ressource.h
* @brief Module dictionnaire de ressources : images, sons, polices.
* @author Yann Cortial
*
*/
#ifndef _RESSOURCE_H
#define _RESSOURCE_H



#include "Rectangle.h"



#define RESS_NUM_IMAGES											32
#define RESS_NUM_SONS											0
#define RESS_NUM_POLICES										1


/* REPERTOIRES */

#define RESS_DIR_IMAGES											"data/images/"
#define RESS_DIR_SONS											"data/sons/"
#define RESS_DIR_POLICES										"data/polices/"
#define RESS_DIR_SAUVEGARDES									"data/sauvegardes/"


/* TEXTES */

#define RESS_TXT_TITRE_JEU 	 									"Blockade Runner"


/* POLICES */

#define RESS_POL_FICHIER_MENU									"ethnocen.ttf"
#define RESS_POL_TAILLE_MENU									18


/* IMAGES */
 
#define RESS_IMG_VAISSEAU_JOUEUR			 					0
#define RESS_IMG_FICHIER_VAISSEAU_JOUEUR						"playership.png"
#define RESS_IMG_LARGEUR_VAISSEAU_JOUEUR						128
#define RESS_IMG_HAUTEUR_VAISSEAU_JOUEUR 						52

#define RESS_IMG_SPLASH						 					10
#define RESS_IMG_FICHIER_SPLASH									"splash0.jpg"
#define RESS_IMG_LARGEUR_SPLASH									1366
#define RESS_IMG_HAUTEUR_SPLASH			 						720

#define RESS_IMG_FOND_MENU					 					11
#define RESS_IMG_FICHIER_FOND_MENU								"menu.jpg"
#define RESS_IMG_LARGEUR_FOND_MENU								1366
#define RESS_IMG_HAUTEUR_FOND_MENU		 						720

#define RESS_IMG_FOND_NIVEAU_0				 					20
#define RESS_IMG_FICHIER_FOND_NIVEAU_0							"bg0.jpg"
#define RESS_IMG_LARGEUR_FOND_NIVEAU_0							4096
#define RESS_IMG_HAUTEUR_FOND_NIVEAU_0	 						720


/**
* @struct Ressource
* @brief
*/
typedef struct
{
	/** Tableau de chaines de caractères (noms des fichiers images) */	
	char **images;
	/** Tableau de Rectangles stockant les dimensions de chaque image */
	Rectangle *dimensionImages;
	
	char **sons;
	char **polices;

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


