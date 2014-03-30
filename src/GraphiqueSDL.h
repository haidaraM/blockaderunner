/**
* @file GraphiqueSDL.h
* @brief Le module GraphiqueSDL gère l'affichage avec l'aide de SDL : fenêtre principale, double-buffering, bliting d'images.
* @author Yann Cortial
*
* Le module GraphiqueSDL interface avec SDL et SDL_image.
* Résolution de la fenêtre principale : 1366 x 720 px.
*/
#ifndef _GRAPHIQUE_SDL_H
#define _GRAPHIQUE_SDL_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "Ressource.h"
#include "Menu.h"
#include "Scene.h"

#define GFX_MODE_FULLSCREEN 				0
#define GFX_MODE_FENETRE	 				1
#define GFX_FENETRE_TITRE_DEFAUT			"Blockade Runner"


/**
* @struct GraphiqueSDL
* @brief Structure de gestion de l'affichage video.
*
* 
*/
typedef struct
{
	/** Dimension (largeur) de l'affichage en pixels. */
	int largeur;
	/** Dimension (hauteur) de l'affichage en pixels. */
	int hauteur;
	/** Mode d'affichage : fullscreen ou fenêtré (par défaut).*/
	int mode;
	/** Couleur de fond utilisée lors de l'effacement complet de l'affichage. */
	Uint32 couleurFond;
	/** Titre de la fenêtre */
	char *titre;
	/** Pointeur sur SDL_Surface (représente la surface d'affichage principale). */
	SDL_Surface *surface;
	/** Tableau de pointeurs sur SDL_Surface (toutes les images chargées du jeu). */
	SDL_Surface **images;
	/** Tableau de pointeurs sur SDL_Surface (tous les rendus (par paires) de texte du Menu (couleur normale et surligné)). */
	SDL_Surface **textesMenu;
	/** Tableau de pointeurs sur SDL_Surface (tous les rendus de texte des noms des joueurs). */
	SDL_Surface **textesNomsJoueurs;

	TTF_Font *policeMenu;
	TTF_Font *policeListeJoueurs;

} GraphiqueSDL;


/**
* @fn void graphiqueInit(GraphiqueSDL *graphique, Ressource *ressource, int largeur, int hauteur, char *titre, int mode)
* @brief Initialise le sous-système video.
* @param graphique[in, out] : doit être non NULL.
*/
void graphiqueInit(GraphiqueSDL *graphique, Ressource *ressource, Menu *menu, int largeur, int hauteur, char *titre, int mode);
/**
* @brief Libère les ressources.
*/
void graphiqueLibere(GraphiqueSDL *graphique);
/**
* @brief Permute les deux buffer-écran (double-buffering), raffraîchissant ainsi l'affichage.
*/
void graphiqueRaffraichit(GraphiqueSDL *graphique);
/**
* @brief Affiche un titre dans la fenêtre principale (caption).
*/
void graphiqueSetTitre(GraphiqueSDL *graphique, char *titre);
/**
* @brief Définit la couleur de fond.
*/
void graphiqueSetCouleurFond(GraphiqueSDL *graphique, unsigned char rouge, unsigned char vert, unsigned char bleu);

/**
* @brief Remplit la surface d'affichage d'une couleur unie, laquelle est définie par appel à graphiqueSetCouleurFond().
*/
void graphiqueEfface(GraphiqueSDL *graphique);
/**
* @brief Recalcule le rendu de la liste des noms de joueurs. (pour usage dans Menu).
*/
void graphiquePrepareRenduListeJoueurs(GraphiqueSDL *graphique, Menu *menu);
/**
* @brief Affiche le Menu.
*/
void graphiqueAfficheMenu(GraphiqueSDL *graphique, Menu *menu );
/**
* @brief Affiche la portion visible de la scène sur la surface d'affichage principale (fenêtre).
*/
void graphiqueAfficheScene(GraphiqueSDL *graphique, Scene *scene );

#endif

