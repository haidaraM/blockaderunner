/**
* @file Ressource.h
* @brief Module dictionnaire de ressources : images, sons, polices, joueurs.
* @author Yann Cortial
*
*/
#ifndef _RESSOURCE_H
#define _RESSOURCE_H



#include "Joueur.h"
#include "Niveau.h"



#define RESS_NUM_NIVEAUX										8
#define RESS_NUM_IMAGES											64
#define RESS_NUM_SONS_COURTS       								11
#define RESS_NUM_SONS_LONGS    	    							2
#define RESS_NUM_POLICES										1



/* REPERTOIRES */

#define RESS_DIR_IMAGES											"data/images/"
#define RESS_DIR_SONS											"data/sons/"
#define RESS_DIR_POLICES										"data/polices/"
#define RESS_DIR_SAUVEGARDES									"data/sauvegardes/"
#define RESS_DIR_NIVEAU                                         "data/niveau/"


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

#define RESS_IMG_DEBRIS_ASTEROIDE                               2
#define RESS_IMG_FICHIER_DEBRIS_ASTEROIDE                       "debris_asteroide.png"
#define RESS_IMG_LARGEUR_DEBRIS_ASTEROIDE                       24
#define RESS_IMG_HAUTEUR_DEBRIS_ASTEROIDE                       24

#define RESS_IMG_ASTEROIDE      		                        3
#define RESS_IMG_FICHIER_ASTEROIDE                              "asteroide_00.png"
#define RESS_IMG_LARGEUR_ASTEROIDE                              88
#define RESS_IMG_HAUTEUR_ASTEROIDE                              70

#define RESS_IMG_MISSILE_JOUEUR                                 7
#define RESS_IMG_FICHIER_MISSILE_JOUEUR                         "missile_tir_joueur.png"
#define RESS_IMG_LARGEUR_MISSILE_JOUEUR                         45
#define RESS_IMG_HAUTEUR_MISSILE_JOUEUR                         20

#define RESS_IMG_TIR_JOUEUR_LASER                               8
#define RESS_IMG_FICHIER_TIR_JOUEUR_LASER                      "laser_tir.png"
#define RESS_IMG_LARGEUR_TIR_JOUEUR_LASER                       32
#define RESS_IMG_HAUTEUR_TIR_JOUEUR_LASER                       4

#define RESS_IMG_TIR_ENNEMI_LASER                               9
#define RESS_IMG_FICHIER_TIR_ENNEMI_LASER                      "laser_tir_ennemi.png"
#define RESS_IMG_LARGEUR_TIR_ENNEMI_LASER                       32
#define RESS_IMG_HAUTEUR_TIR_ENNEMI_LASER                       4

#define RESS_IMG_TIR_ENNEMI_MISSILE                             10
#define RESS_IMG_FICHIER_TIR_ENNEMI_MISSILE                     "missile_tir_ennemi.png"
#define RESS_IMG_LARGEUR_TIR_ENNEMI_MISSILE                     32
#define RESS_IMG_HAUTEUR_TIR_ENNEMI_MISSILE                     4

#define RESS_IMG_BONUS_SCORE		                            14
#define RESS_IMG_FICHIER_BONUS_SCORE        	              	"bonus_score.png"
#define RESS_IMG_LARGEUR_BONUS_SCORE    	        	        40
#define RESS_IMG_HAUTEUR_BONUS_SCORE 	             	        40

#define RESS_IMG_BONUS_MISSILE		                            15
#define RESS_IMG_FICHIER_BONUS_MISSILE        	              	"bonus_missile.png"
#define RESS_IMG_LARGEUR_BONUS_MISSILE    		                40
#define RESS_IMG_HAUTEUR_BONUS_MISSILE	  		                40

#define RESS_IMG_VAISSEAU_ECLAIREUR			 					16
#define RESS_IMG_FICHIER_VAISSEAU_ECLAIREUR						"ennemi_eclaireur.png"
#define RESS_IMG_LARGEUR_VAISSEAU_ECLAIREUR						48
#define RESS_IMG_HAUTEUR_VAISSEAU_ECLAIREUR						46

#define RESS_IMG_VAISSEAU_CHASSEUR			 					17
#define RESS_IMG_FICHIER_VAISSEAU_CHASSEUR						"ennemi_chasseur.png"
#define RESS_IMG_LARGEUR_VAISSEAU_CHASSEUR						128
#define RESS_IMG_HAUTEUR_VAISSEAU_CHASSEUR						53

#define RESS_IMG_VAISSEAU_CROISEUR			 					18
#define RESS_IMG_FICHIER_VAISSEAU_CROISEUR						"ennemi_croiseur.png"
#define RESS_IMG_LARGEUR_VAISSEAU_CROISEUR						286
#define RESS_IMG_HAUTEUR_VAISSEAU_CROISEUR						91



#define RESS_IMG_SPLASH						 					32
#define RESS_IMG_FICHIER_SPLASH									"splash0.jpg"
#define RESS_IMG_LARGEUR_SPLASH									1366
#define RESS_IMG_HAUTEUR_SPLASH			 						720

#define RESS_IMG_FOND_MENU					 					33
#define RESS_IMG_FICHIER_FOND_MENU								"menu.jpg"
#define RESS_IMG_LARGEUR_FOND_MENU								1366
#define RESS_IMG_HAUTEUR_FOND_MENU		 						720

/* Images des niveaux */
#define RESS_IMG_FOND_NIVEAU_0				 					48
#define RESS_IMG_FICHIER_FOND_NIVEAU_0							"bg0.jpg"
#define RESS_IMG_LARGEUR_FOND_NIVEAU							4098
#define RESS_IMG_HAUTEUR_FOND_NIVEAU     						720

#define RESS_IMG_FOND_NIVEAU_1				 					49
#define RESS_IMG_FICHIER_FOND_NIVEAU_1							"bg1.jpg"

#define RESS_IMG_FOND_NIVEAU_2				 					50
#define RESS_IMG_FICHIER_FOND_NIVEAU_2							"bg2.jpg"

#define RESS_IMG_FOND_NIVEAU_3				 					51
#define RESS_IMG_FICHIER_FOND_NIVEAU_3							"bg3.jpg"

#define RESS_IMG_FOND_NIVEAU_4				 					52
#define RESS_IMG_FICHIER_FOND_NIVEAU_4							"bg4.jpg"

/* Sons longs */
#define RESS_SON_MENU                                           0
#define RESS_SON_FICHIER_MENU                                   "menu_fond.mp3"

#define RESS_SON_AMBIENCE                                       1
#define RESS_SON_FICHIER_AMBIENCE                               "ambience1.mp3"

/* sons courts */
#define RESS_SON_TIR_LASER                                      2
#define RESS_SON_FICHIER_TIR_LASER                              "tir_laser.wav"

#define RESS_SON_MISSILE                                        3
#define RESS_SON_FICHIER_MISSILE                                "missile.mp3"

#define RESS_SON_ERREUR                                         4
#define RESS_SON_FICHIER_ERREUR                                 "erreur.wav"

#define RESS_SON_MORT                                           5
#define RESS_SON_FICHIER_MORT                                   "mort.wav"

#define RESS_SON_EXPLOSION_ASTEROIDE                            6
#define RESS_SON_FICHIER_EXPLOSION_ASTEROIDE                    "explosion_asteroide.mp3"

#define RESS_SON_MENU_SURVOL                                    7
#define RESS_SON_FICHIER_MENU_SURVOL                            "menu_survol.wav"

#define RESS_SON_MENU_VALIDATE                                  8
#define RESS_SON_FICHIER_MENU_VALIDATE                          "menu_validate.wav"

#define RESS_SON_TIR_LASER_ENNEMI                               9
#define RESS_SON_FICHIER_TIR_LASER_ENNEMI                       "tir_laser2.wav"

#define RESS_SON_BONUS_SCORE                                    10
#define RESS_SON_FICHIER_BONUS_SCORE                            "bonus_score.wav"

#define RESS_SON_EXPLOSION_ENNEMI                               11
#define RESS_SON_FICHIER_EXPLOSION_ENNEMI                       "explosion_ennemi.wav"

#define RESS_SON_CHANGE_ARME                                    12
#define RESS_SON_FICHIER_CHANGE_ARME                            "change_arme.wav"




/**
* @struct Ressource
* @brief Cette structure contient tous les elements dont le jeu aura besoin : les joueurs sauvegardés, la liste des fichiers sons et images, les niveaux etc...
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
* @param [in, out] res : initialisé
*/
void ressourceLibere(Ressource *res);


/**
* @fn int ressourceGetNumJoueurs(const Ressource *res)
* @brief Renvoie le nombre de joueurs sauvegardés.
* @param [in] res : initialisé
*/
int ressourceGetNumJoueurs(const Ressource *res);

/**
* @fn Joueur** ressourceGetJoueurs(const Ressource *res)
* @brief Renvoie le tableau de pointeurs sur Joueur (ie tous les joueurs connus).
* @param [in] res : initialisé
*/
Joueur** ressourceGetJoueurs(const Ressource *res);

/**
* @fn void ressourceAjouteJoueur(Ressource *res, char nomJoueur[JOUEUR_NOM_MAXCHAR+1], int indexJoueur)
* @brief Ajoute un joueur à la liste des joueurs sauvegardés.
* @param [in, out] res : initialisé
* @param [in] nomJoueur
* @param [in] indexJoueur
*/
void ressourceAjouteJoueur(Ressource *res, char nomJoueur[JOUEUR_NOM_MAXCHAR+1], int indexJoueur);

/**
* @fn void ressourceSauveJoueurs(Ressource *res)
* @brief Sauve sur disque les données des joueurs.
* @param [in] res
*/
void ressourceSauveJoueurs(Ressource *res);

/**
* @fn Niveau ressourceGetNiveau(const Ressource *res, int numeroNiveau)
* @brief Renvoie le niveau dont le numero est passé en paramètre
* @param [in] res
* @param [in] numeroNiveau
*/
Niveau ressourceGetNiveau(const Ressource *res, int numeroNiveau);


/**
* @fn int ressourceGetLargeurImage(const Ressource *res, int nomRessource)
* @brief Renvoie la largeur d'une image cataloguée.
* @param [in] res : initialisé.
* @param [in] nomRessource : un entier définissant la ressource demandée. Par exemple RESS_VAISSEAU_JOUEUR.
* @return largeur de l'image.
*/
int ressourceGetLargeurImage(const Ressource *res, int nomRessource);

/**
* @fn int ressourceGetHauteurImage(const Ressource *res, int nomRessource)
* @brief Renvoie la hauteur d'une image cataloguée.
* @param [in] res : instance de Ressource.
* @param [in] nomRessource : un entier définissant la ressource demandée. Par exemple RESS_VAISSEAU_JOUEUR.
* @return hauteur de l'image.
*/
int ressourceGetHauteurImage(const Ressource *res, int nomRessource);

/**
* @brief Test de regression du module Ressource
*/
void ressourceTestDeRegression();

#endif


