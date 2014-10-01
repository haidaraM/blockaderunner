/**
* @file Animation.h
* @brief Module utilisé pour réaliser des animations : explosions etc...
* Il sera utilisé avec SDL et combiné à GraphiqueSDL.
* PRINCIPE : Des images seront affichées les unes après les autres, chaque image restant affiché durant un delai.
*
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


#endif
