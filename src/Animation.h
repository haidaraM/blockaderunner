/**
* @file Animation.h
* @brief Module utilisé pour réaliser des animations : explosions etc...
* Il sera utilisé avec SDL et combiné à GraphiqueSDL.
* @author Mohamed El Mouctar HAIDARA
*/

#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "GraphiqueSDL.h"

/**
* @struct AnimationFrame
* @brief Constitue l'element de base d'une animation
*/
typedef struct
{
    /** L'image à un instant t de l'animation */
    SDL_Surface * image;
    /** Temps durant lequel l'animation sera affichée*/
    Uint16 delai;
} AnimationFrame;

/**
* @struct Animation
* @brief Regroupement d'AnimationFrame pour former une animation
*/
typedef struct
{
    /** Nombre de frames comportant une animation */
    Uint16 nbFrames;
    /** Tableau de frames */
    AnimationFrame * frames;
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
* @fn void animationInitFrame( AnimationFrame * frame, SDL_Surface * image, Uint16 delai);
* @brief Initialise la frame
* @param [in, out] frame
* @param [in] image
*/
void animationInitFrame( AnimationFrame * frame, SDL_Surface * image, Uint16 delai);

/**
* @brief Libere la frame
*/
void animationLibereFrame(AnimationFrame * frame);

/**
* @brief Affiche la frame
*/
void animationAfficheFrame(AnimationFrame * frame, SDL_Surface * dest, SDL_Rect * pos);
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
void animationBlitFrame (Animateur * ateur, SDL_Surface *dest, SDL_Rect *pos);



#endif
