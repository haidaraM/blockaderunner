/**
* @file Animation.c
* @brief Fichier d'implémentation du module animation
* @author Mohamed El Mouctar HAIDARA
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#include <assert.h>
#include "Animation.h"

/**
* @fn static void animationInitFrame( Frame * frame, SDL_Surface * image, float delai)
* @brief Initialise une frame donnée
* @param [in,out] frame
* @param [in,out] image
* @param [in] delai
*/
static void animationInitFrame(Frame *frame, SDL_Surface *image, float delai)
{
    assert(frame != NULL);
    frame->image = image;
    frame->delai = delai;
}

static void animationAfficheFrame(Frame *frame, SDL_Surface *dest, SDL_Rect *pos)
{
    assert(frame != NULL);
    SDL_BlitSurface(frame->image, &frame->decoupage, dest, pos);
}

/**
* @fn static void animationNextFrame(Animateur * ateur)
* @brief Passe à la frame suivant
* @param [in,out] ateur : initialisé
*/
static void animationNextFrame(Animateur *ateur)
{
    ateur->frameCourante++;
    /* Retour à la frame 0 si nous sommes à la dernière */
    if (ateur->frameCourante == ateur->anim->nbFrames) {
        ateur->frameCourante = 0;
#ifdef NO_REPETE_EXPLOSION
        ateur->statut = STOP;
#endif /* REPETE_EXPLOSION */
    }
    ateur->compteur = 0;
}

/* *************************************************************************************** */

void animationInitAnimation(Animation *anim, int nb)
{
    assert(anim != NULL);
    anim->frames = (Frame *) malloc(sizeof(Frame) * nb);
    anim->nbFrames = nb;
}

void animationSetFrame(Animation *anim, int pos, SDL_Surface *surface, float delai)
{
    assert(anim != NULL);
    animationInitFrame(&anim->frames[pos], surface, delai);
}

void animationLibereAnimation(Animation *anim)
{
    assert(anim != NULL);
    free(anim->frames);
}

/* ********************************************************************************** */
void animationInitAnimateur(Animateur *ateur, Animation *anim)
{
    assert(ateur != NULL && anim != NULL);
    ateur->anim = anim;
    ateur->frameCourante = 0;
    ateur->compteur = 0;
    animationJoueAnimation(ateur);
}

void animationJoueAnimation(Animateur *ateur)
{
    assert(ateur != NULL);
    ateur->statut = PLAY;
}

void animationStopAnimation(Animateur *ateur)
{
    assert(ateur != NULL);
    ateur->statut = STOP;
}


void animationMAJAnimateur(Animateur *ateur)
{
    Frame *frame;
    /* ne mettre à jour l'animation que si elle est jouée */
    if (ateur->statut == STOP)
        return;

    frame = &ateur->anim->frames[ateur->frameCourante];
    /*  if(frame->delai == 0)
          return; */
    ateur->compteur += VITESSE_GLOBALE_EXPLOSIONS;
    /* passage à la frame suivante */
    if (ateur->compteur >= frame->delai)
        animationNextFrame(ateur);
}

void animationBlitFrame(Animateur *ateur, SDL_Surface *dest, SDL_Rect *pos)
{
    if (ateur->statut == PLAY)
        animationAfficheFrame(&ateur->anim->frames[ateur->frameCourante], dest, pos);
}

