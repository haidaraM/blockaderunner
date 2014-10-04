/**
* @file Animation.h
* @brief Module utilisé pour réaliser des animations : explosions etc...
* Il sera utilisé avec SDL et combiné à GraphiqueSDL.
* @author Mohamed El Mouctar HAIDARA
*/

#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SDL.h>

#define DUREE_EXPLOSION                 1.0
#define NB_FRAMES_EXPLOSION             42
#define DELAI_FRAME_EXPLOSION           (DUREE_EXPLOSION / NB_FRAMES_EXPLOSION)
#define LARGEUR_FRAME_EXPLOSION         122


/**
* @struct Frame
* @brief Constitue l'element de base d'une animation
*/
typedef struct
{
    /** Partie de l'image qui sera affiché */
    SDL_Rect decoupage;
    /** L'image à un instant t de l'animation */
    SDL_Surface * image;
    /** Temps durant lequel la frame sera affichée*/
    float delai;
} Frame;

/**
* @struct Animation
* @brief Regroupement d'AnimationFrame pour former une animation
*/
typedef struct
{
    /** Nombre de frames comportant une animation */
    Uint16 nbFrames;
    /** Tableau de frames */
    Frame * frames;
} Animation;

/**
* @struct Animateur
* @brief Structure utilisée pour jouer une animation, sauvegarder l'etat de l'animation, la frame courante etc
*/
typedef struct
{
    /** Reference vers l'animation qui sera jouée*/
    const Animation * anim;
    /** Etat de l'animation */
    enum {STOP, PLAY} statut;
    /** Indice de la frame courante de l'animation */
    Uint16 frameCourante;
    /** Temps ecoulé depuis l'apparition de la frame courante */
    Uint16 compteur;
} Animateur;

/**
* @fn void animationInitFrame( AnimationFrame * frame, SDL_Surface * image, float delai);
* @brief Initialise la frame
* @param [in, out] frame
* @param [in] image
*/
void animationInitFrame( Frame * frame, SDL_Surface * image, float delai);

/**
* @brief Affiche la frame
*/
void animationAfficheFrame(Frame * frame, SDL_Surface * dest, SDL_Rect * pos, SDL_Rect * decoupage);
/* ************************************************************************************************************ */

/**
* @brief initialise une animation
*/
void animationInitAnimation(Animation * anim, Uint16 nb);

/**
* @brief Libere une animation
*/
void animationLibereAnimation(Animation * anim);

/**
* @brief Affecte une surface et un délai à une frame donnée
*/
void animationSetFrame(Animation * anim, Uint16 pos, SDL_Surface *surface, Uint16 delai);
/* ********************************************************************************************************* */
/**
* @brief Initialise l'animateur
*/
void animationInitAnimateur(Animateur * ateur, Animation *anim);

/**
* @brief Joue l'animation
*/
void animationJoueAnimation(Animateur * ateur);

/**
* @brief Stop l'animation
*/
void animationStopAnimation(Animateur * ateur);

/**
* @brief Remet à zero l'animation
*/
void animationRewindAnimation(Animateur * ateur);

/**
* @brief Passe à la frame suivant
*/
void animationNextFrame(Animateur * ateur);

/**
* @brief Met à jour le compteur interne de l'Animateur et met à jour la frame à afficher si nécessaire
*/
void animationMAJAnimateur(Animateur * ateur);

/**
* @brief Dessine la frame courante
*/
void animationBlitFrame (Animateur * ateur, SDL_Surface *dest, SDL_Rect *pos, SDL_Rect * decoupage);



#endif
