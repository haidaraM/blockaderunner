/**
* @file GraphiqueSDL.h
* @brief Le module GraphiqueSDL gère l'affichage avec l'aide de SDL : fenêtre principale, double-buffering, bliting d'images.
* Le module GraphiqueSDL interface avec SDL et SDL_image.
* Résolution de la fenêtre principale : 1366 x 720 px.
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/
#ifndef _GRAPHIQUE_SDL_H
#define _GRAPHIQUE_SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Menu.h"
#include "Scene.h"
#include "Ressource.h"

#define GFX_MODE_FULLSCREEN 				0
#define GFX_MODE_FENETRE	 				1
#define GFX_FENETRE_TITRE_DEFAUT			"Blockade Runner"

#define GFX_NUM_ELEMENTS_HUD				9
#define GFX_HUD_ELEMENT_LARGEUR				8
#define GFX_HUD_ELEMENT_HAUTEUR				6
#define GFX_HUD_ELEMENT_OFFSET				2



/**
* @struct GraphiqueSDL
* @brief Structure de gestion de l'affichage video. Interface avec SDL, SDL_image et SDL_ttf.
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
    /** Un tableau des petites surfaces pour l'affichage des niveaux d'Ecran, Coque du vaisseau du joueur, texte quand le joueur meurt, etc. */
    SDL_Surface **elementsHUD;
    /** police du Menu */
    TTF_Font *policeMenu;
    /** police pour la liste des joueurs */
    TTF_Font *policeListeJoueurs;

    /* Utilisé en interne par SDL lors de la création de Surfaces. */
    Uint32 rmask, gmask, bmask, amask;

} GraphiqueSDL;


/**
* @fn void graphiqueInit(GraphiqueSDL *graphique, const Ressource *ressource,Menu *menu int largeur, int hauteur, char *titre, int mode)
* @brief Initialise le sous-système video.
* @param [in, out] graphique : doit être non NULL.
* @param [in] ressource : doit être non NULL.
* @param [in, out] menu
* @param [in] largeur
* @param [in] hauteur
* @param [in] titre
* @param [in] mode
*/
void graphiqueInit(GraphiqueSDL *graphique, const Ressource *ressource, Menu *menu, int largeur, int hauteur, char *titre, int mode);

/**
* @fn void graphiqueLibere(GraphiqueSDL *graphique)
* @brief Libère les ressources.
* @param [in, out] graphique : doit etre initialisé
*/
void graphiqueLibere(GraphiqueSDL *graphique);

/**
* @fn void graphiqueRaffraichit(GraphiqueSDL *graphique)
* @brief Permute les deux buffer-écran (double-buffering), raffraîchissant ainsi l'affichage.
* @param [in, out] graphique
*/
void graphiqueRaffraichit(GraphiqueSDL *graphique);

/**
* @fn void graphiqueSetTitre(GraphiqueSDL *graphique, const char *titre)
* @brief Affiche un titre dans la fenêtre principale (caption).
* @param [in, out] graphique
* @param [in] titre
*/
void graphiqueSetTitre(GraphiqueSDL *graphique, char *titre);

/**
* @fn void graphiqueSetCouleurFond(GraphiqueSDL *graphique, unsigned char rouge, unsigned char vert, unsigned char bleu)
* @brief Définit la couleur de fond.
* @param [in, out] graphique :initialisé
* @param [in] rouge
* @param [in] vert
* @param [in] bleu
*/
void graphiqueSetCouleurFond(GraphiqueSDL *graphique, unsigned char rouge, unsigned char vert, unsigned char bleu);

/**
* @fn void graphiqueEfface(GraphiqueSDL *graphique)
* @brief Remplit la surface d'affichage d'une couleur unie, laquelle est définie par appel à graphiqueSetCouleurFond().
* @param [in, out] graphique
*/
void graphiqueEfface(GraphiqueSDL *graphique);

/**
* @fn void graphiquePrepareRenduListeJoueurs(GraphiqueSDL *graphique, Menu *menu)
* @brief Recalcule le rendu de la liste des noms de joueurs. (pour usage dans Menu).
* @param [in, out] graphique : initialisé
* @param [in, out] menu : initialisé
*/
void graphiquePrepareRenduListeJoueurs(GraphiqueSDL *graphique, Menu *menu);

/**
* @fn void graphiqueSetScore(GraphiqueSDL *graphique, int score)
* @brief Met à jour l'affichage du score
* @param [in, out] graphique
* @param [in] score
*/
void graphiqueSetScore(GraphiqueSDL *graphique, int score);

/**
* @fn void graphiqueSetMunitions(GraphiqueSDL *graphique, int numMissiles)
* @brief Met à jour l'affichage du nombre de missiles restant.
* @param [in, out] graphique
* @param [in] numMissiles le nombre de missiles restant
*/
void graphiqueSetMunitions(GraphiqueSDL *graphique, int numMissiles);

/**
* @fn void graphiqueAfficheMenu(GraphiqueSDL *graphique, Menu *menu )
* @brief Affiche le Menu.
* @param [in,out] graphique
* @param [in] menu
*/
void graphiqueAfficheMenu(GraphiqueSDL *graphique,const Menu *menu );

/**
* @fn void graphiqueAfficheScene(GraphiqueSDL *graphique, Scene *scene )
* @brief Rend la portion visible de la scène et ses éléments (vaisseaux, asteroides, tirs, bonus,etc.) sur la surface d'affichage principale (fenêtre).
* @param [in,out] graphique : initialisé
* @param [in] scene: initialisé
*/
void graphiqueAfficheScene(GraphiqueSDL *graphique,const Scene *scene );

/**
* @fn void graphiqueAfficheMort(GraphiqueSDL * graphique)
* @brief affiche un texte quand le joueur meurt
* @param [in,out] graphiqe : initialisé
*/
void graphiqueAfficheMort(GraphiqueSDL * graphique);

/**
* @fn void graphiqueAfficheFinNiveau(const GraphiqueSDL * graphique)
* @brief affiche un texte quand le joueur a complété un niveau
* @param [in,out] graphique : initialisé
*/
void graphiqueAfficheFinNiveau(GraphiqueSDL * graphique);

/**
* @fn void graphiqueAfficheVictoire(const GraphiqueSDL * graphique)
* @brief Affichage de fin de jeu : victoire du joueur!
* @param [in,out] graphique : initialisé
*/
void graphiqueAfficheVictoire(GraphiqueSDL * graphique);

#endif

