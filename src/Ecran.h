/**
* @file Ecran.h
* @brief Le module Ecran gère l'affichage : fenêtre principale, double-buffering, bliting d'images.
* @author Yann Cortial
*
* Le module Ecran interface avec SDL et SDL_image.
*/
#ifndef _ECRAN_H
#define _ECRAN_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define ECRAN_MODE_FULLSCREEN 		0
#define ECRAN_MODE_FENETRE	 		1
#define ECRAN_TITRE_DEFAUT			"Blockade"


/**
* @struct Ecran
* @brief Structure de gestion de l'affichage.
*
* 
*/
typedef struct
{
	/** Dimension (largeur) de l'écran en pixels. */
	int largeur;
	/** Dimension (hauteur) de l'écran en pixels. */
	int hauteur;
	/** Mode d'affichage : fullscreen ou fenêtré (par défaut).*/
	int mode;
	/** Couleur de fond utilisée lors de l'effacement complet de l'affichage. */
	Uint32 couleurFond;
	/** Titre de la fenêtre */
	char *titre;
	/** Pointeur sur SDL_Surface (représente la surface d'affichage principale). */
	SDL_Surface *surface;
} Ecran;


/**
* @fn void ecranInit(Ecran *ecran, int largeur, int hauteur, char *titre, int mode)
* @brief Initialise le sous-système video.
* @param ecran[in, out] : doit être non NULL.
*/
void ecranInit(Ecran *ecran, int largeur, int hauteur, char *titre, int mode);
/**
* @brief Libère les ressources.
*/
void ecranLibere(Ecran *ecran);
/**
* @brief Permute les deux buffer-écran (double-buffering), raffraîchissant ainsi l'affichage.
*/
void ecranRaffraichit(Ecran *ecran);
/**
* @brief Affiche un titre dans la fenêtre principale (caption).
*/
void ecranSetTitre(Ecran *ecran, char *titre);
/**
* @brief Définit la couleur de fond.
*/
void ecranSetCouleurFond(Ecran *ecran, unsigned char rouge, unsigned char vert, unsigned char bleu);

/**
* @brief Remplit l'ecran d'une couleur unie, définie par appel à ecranSetCouleurFond().
*/
void ecranEfface(Ecran *ecran);
/**
* @brief Effectue un 'blit' d'une image sur la surface d'affichage principal (fenêtre).
*/
void ecranAfficheImage(Ecran *ecran, SDL_Surface* image, int x, int y );

#endif

