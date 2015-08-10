/**
* @file Animation.h
* @brief Module utilisé pour réaliser des animations : explosions (pour le moment)
* @author Mohamed El Mouctar HAIDARA
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/

#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SDL/SDL.h>

#define NB_ANIMATION                                3
#define VITESSE_GLOBALE_EXPLOSIONS                 0.02

#define ANIMATION_EXPLOSION_0                       0
#define ANIMATION_DUREE_EXPLOSION_0                 1.02f
#define ANIMATION_NB_FRAMES_EXPLOSION_0             34
#define ANIMATION_DELAI_FRAME_EXPLOSION_0           (ANIMATION_DUREE_EXPLOSION_0 / ANIMATION_NB_FRAMES_EXPLOSION_0)
#define ANIMATION_HAUTEUR_FRAME_EXPLOSION_0         RESS_IMG_HAUTEUR_EXPLOSION_0

#define ANIMATION_EXPLOSION_1                       1
#define ANIMATION_DUREE_EXPLOSION_1                 1.0f
#define ANIMATION_NB_FRAMES_EXPLOSION_1             64
#define ANIMATION_DELAI_FRAME_EXPLOSION_1           (ANIMATION_DUREE_EXPLOSION_1 / ANIMATION_NB_FRAMES_EXPLOSION_1)
#define ANIMATION_HAUTEUR_FRAME_EXPLOSION_1         RESS_IMG_HAUTEUR_EXPLOSION_1


#define ANIMATION_EXPLOSION_2                       2
#define ANIMATION_DUREE_EXPLOSION_2                 1.0f
#define ANIMATION_NB_FRAMES_EXPLOSION_2             48
#define ANIMATION_DELAI_FRAME_EXPLOSION_2           (ANIMATION_DUREE_EXPLOSION_2 / ANIMATION_NB_FRAMES_EXPLOSION_2)
#define ANIMATION_HAUTEUR_FRAME_EXPLOSION_2         RESS_IMG_HAUTEUR_EXPLOSION_2

/* TODO : revoir la durée des explositions */

/**
* @struct Frame
* @brief Element de base d'une animation : "capture" de l'animation à un instant t
*/
typedef struct {
    /** Partie de l'image qui correspondra à une frame donnée */
    SDL_Rect decoupage;
    /** L'image à un instant t de l'animation */
    SDL_Surface *image;
    /** Temps durant lequel la frame sera affichée*/
    float delai;
} Frame;

/**
* @struct Animation
* @brief Regroupement de Frame pour former une animation
*/
typedef struct {
    /** Nombre de frames comportant l'animation */
    int nbFrames;
    /** Tableau de frames */
    Frame *frames;
} Animation;

/**
 * @enum EtatAnimation
 */
typedef enum {
    STOP, PLAY
} EtatAnimation;

/**
* @struct Animateur
* @brief Structure utilisée pour jouer une animation, sauvegarder l'etat de l'animation, la frame courante etc
*/
typedef struct {
    /** Reference vers l'animation qui sera jouée*/
    Animation *anim;
    /** Etat de l'animation */
    EtatAnimation statut;
    /** Indice de la frame courante de l'animation */
    int frameCourante;
    /** Temps ecoulé depuis l'apparition de la frame courante */
    float compteur;
} Animateur;


/**
* @fn void animationInitAnimation(Animation * anim, int nb);
* @brief initialise une animation
* @param [in,out] anim
* @param [in] nb : nombre de frames de l'animation
*/
void animationInitAnimation(Animation *anim, int nb);

/**
* @fn void animationLibereAnimation(Animation * anim);
* @brief Libere une animation
* @param  [in] anim : initialisé
*/
void animationLibereAnimation(Animation *anim);

/**
* @fn void animationSetFrame(Animation * anim, int pos, SDL_Surface *surface, float delai);
* @brief Affecte une surface et un délai à une frame donnée
* @param [in, out] anim
* @param [in] pos
* @param [in, out] surface
* @param [in] delai
*/
void animationSetFrame(Animation *anim, int pos, SDL_Surface *surface, float delai);

/* ********************************************************************************************************* */
/**
* @fn void animationInitAnimateur(Animateur * ateur, Animation *anim)
* @brief Initialise l'animateur
* @param [in,out] ateur
*/
void animationInitAnimateur(Animateur *ateur, Animation *anim);

/**
* @fn void animationJoueAnimation(Animateur * ateur)
* @brief Joue l'animation : met le statut de l'animateur a PLAY
* @param [in,out] ateur : initialisé
*/
void animationJoueAnimation(Animateur *ateur);

/**
* @fn void animationStopAnimation(Animateur * ateur)
* @brief Stop l'animation : met le statut de l'animateur à STOP
* @param [in,out] ateur
*/
void animationStopAnimation(Animateur *ateur);


/**
* @fn void animationMAJAnimateur(Animateur * ateur)
* @brief Met à jour le compteur interne de l'Animateur et met à jour la frame à afficher si nécessaire
* @param [in,out] ateur : initialisé
*/
void animationMAJAnimateur(Animateur *ateur);

/**
* @fn void animationBlitFrame (Animateur * ateur, SDL_Surface *dest, SDL_Rect *pos)
* @brief Dessine la frame courante
* @param [in,out] ateur;
* @param [in,out] dest : surface principale
* @param [in,out] position
*/
void animationBlitFrame(Animateur *ateur, SDL_Surface *dest, SDL_Rect *pos);

/**
 * @brief Test la fin d'une animation
 */
int animationCheckFin(const Animateur *animateur);

#endif
