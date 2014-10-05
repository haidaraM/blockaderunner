/**
* @file Animation.h
* @brief Module utilisé pour réaliser des animations : explosions etc...
* Il sera utilisé avec SDL et combiné à GraphiqueSDL.
* @author Mohamed El Mouctar HAIDARA
*/

#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SDL.h>

#define NB_ANIMATION                                3
#define VITESSE_AFFICHAGE_EXPLOSION                 0.02

#define ANIMATION_EXPLOSION_1                       0
#define ANIMATION_DUREE_EXPLOSION_1                 1.02f
#define ANIMATION_NB_FRAMES_EXPLOSION_1             34
#define ANIMATION_DELAI_FRAME_EXPLOSION_1             (ANIMATION_DUREE_EXPLOSION_1 / ANIMATION_NB_FRAMES_EXPLOSION_1)
#define ANIMATION_HAUTEUR_FRAME_EXPLOSION_1         RESS_IMG_HAUTEUR_EXPLOSION_1

#define ANIMATION_EXPLOSION_2                       1
#define ANIMATION_DUREE_EXPLOSION_2                 1.02f
#define ANIMATION_NB_FRAMES_EXPLOSION_2             64
#define ANIMATION_DELAI_FRAME_EXPLOSION_2           (ANIMATION_DUREE_EXPLOSION_2 / ANIMATION_NB_FRAMES_EXPLOSION_2)


#define ANIMATION_EXPLOSION_3                       2
#define ANIMATION_DUREE_EXPLOSION_3                 1.02f
#define ANIMATION_NB_FRAMES_EXPLOSION_3             48
#define ANIMATION_DELAI_FRAME_EXPLOSION_3           (ANIMATION_DUREE_EXPLOSION_3 / ANIMATION_NB_FRAMES_EXPLOSION_3
#define ANIMATION_HAUTEUR_FRAME_EXPLOSION_3         RESS_IMG_HAUTEUR_EXPLOSION_3




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
* @brief Regroupement de Frame pour former une animation
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
    Animation * anim;
    /** Etat de l'animation */
    enum {STOP, PLAY} statut;
    /** Indice de la frame courante de l'animation */
    Uint16 frameCourante;
    /** Temps ecoulé depuis l'apparition de la frame courante */
    float compteur;
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
void animationAfficheFrame(Frame * frame, SDL_Surface * dest, SDL_Rect * pos);
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
void animationSetFrame(Animation * anim, Uint16 pos, SDL_Surface *surface, float delai);
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
