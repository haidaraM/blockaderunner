/**
* @file Ressource.h
* @brief module permettant de gerer les resources : images, sons ...
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

#define RESS_VAISSEAU_JOUEUR 					0
#define RESS_FICHIER_VAISSEAU_JOUEUR			"playership.png"


/**
* @struct Ressource
* @brief
*/
typedef struct
{

	SDL_Surface **images;

} Ressource;

/**
* @fn void ressourceInit(Ressource *res)
* @brief
*/
void ressourceInit(Ressource *res);

/**
* @fn void ressourceLibere(Ressource *res)
* @brief
*/
void ressourceLibere(Ressource *res);

/**
* @fn SDL_Surface* ressourceGetImage(Ressource *res, int nomRessource)
* @brief
*/
SDL_Surface* ressourceGetImage(Ressource *res, int nomRessource);


#endif


