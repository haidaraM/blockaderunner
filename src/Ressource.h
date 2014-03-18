/**
* @file Ressource.h
* @brief Module de gestion des ressources : images, sons, polices.
* @author Yann Cortial
*
* Le module interface avec SDL.
*/
#ifndef _RESSOURCE_H
#define _RESSOURCE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



#define RESS_NUM_IMAGES							1
#define RESS_NUM_SONS							0
#define RESS_NUM_POLICES						0

#define RESS_DIR_IMAGES							"data/images/"
#define RESS_DIR_SONS							"data/sounds/"
#define RESS_DIR_POLICES						"data/fonts/"
#define RESS_DIR_SAVE							"data/save/"

#define RESS_TITRE_JEU 							"Blockade Runner"

#define RESS_VAISSEAU_JOUEUR 					0
#define RESS_FICHIER_VAISSEAU_JOUEUR			"playership.png"


/**
* @struct Ressource
* @brief
*/
typedef struct
{

	/** Tableau de pointeurs sur SDL_Surface (images chargées à l'aide de SDL_image).*/
	SDL_Surface **images;

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
* @fn SDL_Surface* ressourceGetImage(Ressource *res, int nomRessource)
* @brief Renvoie un pointeur sur une image cataloguée par le module.
* @param res[in, out] : instance de Ressource.
* @param nomRessource : un entier définissant la ressource demandée. Par exemple RESS_VAISSEAU_JOUEUR.
* @return un pointeur sur un objet de type SDL_Surface.
*/
SDL_Surface* ressourceGetImage(const Ressource *res, int nomRessource);
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


