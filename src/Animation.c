/**
* @file Animation.c
* @brief Fichier d'implémentation du module animation
* @author Mohamed El Mouctar HAIDARA
*/
#include <assert.h>

#include "Animation.h"


void animationInitFrame( AnimationFrame * frame, SDL_Surface * image, Uint16 delai)
{
    assert(frame!=NULL);
    frame->image=image;
    frame->delai=delai;
}

void animationLibereFrame(AnimationFrame * frame)
{
    assert(frame!=NULL);
    SDL_FreeSurface(frame->image);
}

void animationAfficheFrame(AnimationFrame * frame, SDL_Surface * dest, SDL_Rect * pos)
{
    assert(frame!=NULL);
    SDL_BlitSurface(frame->image, NULL, dest, pos);
}
/* *************************************************************************************** */

void animationInitAnimation(Animation * anim, Uint16 nb)
{
    assert(anim!=NULL);
    anim->frames=(AnimationFrame *) malloc(sizeof(AnimationFrame)*nb);
    anim->nbFrames=nb;
}

void animationSetFrame(Animation * anim, Uint16 pos, SDL_Surface *surface, Uint16 delai)
{
    assert(anim!=NULL);
    animationLibereFrame(&anim->frames[pos]);
    animationInitFrame(&anim->frames[pos], surface, delai);
}

void animationLibereAnimation(Animation * anim)
{
    int i;
    assert(anim!=NULL);
    for(i=0; i<anim->nbFrames; i++)
        animationLibereFrame(&anim->frames[i]);

    free(anim->frames);
}

void animationInitAnimateur(Animateur * ateur, Animation *anim)
{
    assert(ateur!=NULL && anim!=NULL);
    ateur->anim=anim;
    animationRewindAnimation(ateur);
}

void animationJoueAnimation(Animateur * ateur)
{
    assert(ateur!=NULL);
    ateur->statut=PLAY;
}

void animationStopAnimation(Animateur * ateur)
{
    assert(ateur!=NULL);
    ateur->statut=STOP;
}

void animationRewindAnimation(Animateur * ateur)
{
    ateur->frameCourante = 0;
    ateur->compteur = 0;
    animationStopAnimation(ateur);
}

void animationNextFrame(Animateur * ateur)
{
    /* Retour à la frame 0 si nous sommes à la dernière */
   if (++ateur->frameCourante == ateur->anim->nbFrames)
        ateur->frameCourante = 0;
   ateur->compteur = 0;
}

void animationMAJAnimateur(Animateur * ateur)
{
    const AnimationFrame * frame;
    /* ne mettre à jour l'animation que si elle est jouée */
    if(ateur->statut == STOP)
        return ;

    frame = &ateur->anim->frames[ateur->frameCourante];
    if(frame->delai == 0)
        return;

    /* passage à la frame suivante */
    if (++ateur->compteur == frame->delai)
        animationNextFrame(ateur);
}

void animationBlitFrame (Animateur * ateur, SDL_Surface *dest, SDL_Rect *pos)
{
    animationAfficheFrame(&ateur->anim->frames[ateur->frameCourante], dest, pos);
}

