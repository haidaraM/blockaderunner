/**
* @file EntreeSDL.h
* @brief Module de gestion des entrées (couplé avec SDL) : clavier, souris et évènements divers.
* @author Yann Cortial
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#ifndef _ENTREE_SDL_H
#define _ENTREE_SDL_H

#include <SDL/SDL.h>

/**
* @struct EntreeSDL
* @brief Cette structure permet de gerer le clavier et la souris grâce à SDL
*/
typedef struct
{
    /** booléen renseignant si la fermeture du programme a été demandée.*/
    unsigned char fermetureJeu;
    /** nombre de touches du clavier. */
    int nombreTouches;
    /** tableau de booléen stockant l'état du clavier. */
    unsigned char *clavier;
    /** dernière touche détectée (sert en interne). */
    int toucheDetectee;
    /** dernière touche relâchée. */
    int toucheRelachee;
    /** Etat de la souris : position en x et y. */
    int sourisX, sourisY;
    /** booléen : vaut 1 si le bouton gauche de la souris est enfoncé, 0 sinon. */
    unsigned char boutonSourisGauche;
    /** booléen : vaut 1 si le bouton droit de la souris est enfoncé, 0 sinon. */
    unsigned char boutonSourisDroit;

} EntreeSDL;


/**
* @fn void entreeInit(EntreeSDL *entree)
* @brief Initialise le module.
* @param [in, out] entree : doit être non NULL.
* @return none
*/
void entreeInit(EntreeSDL *entree);

/**
* @fn void entreeLibere(EntreeSDL *entree)
* @brief Libère les ressources du module.
* @param [in, out] entree
*/
void entreeLibere(EntreeSDL *entree);

/**
* @fn void entreeSonde(EntreeSDL *entree)
* @brief Récupère tous les nouveaux évènements survenus depuis le dernier appel.
* Doit être appelée avant de tester l'état des touches et de la souris (typiquement régulièrement, dans la boucle principale du programme).
* @param [in, out] entree : initialisé
*/
void entreeSonde(EntreeSDL *entree);

/**
* @fn unsigned char entreeFermetureJeu(const EntreeSDL *entree)
* @brief Teste si la fermeture du programme a été demandée par l'utilisateur.
* La fermeture du programme est un évènement dispatché par l'OS, typiquement par exemple lorsque l'utilsateur a tenté de fermer en cliquant la fenêtre principale du programme.
* @param [in] entree
*/
unsigned char entreeFermetureJeu(const EntreeSDL *entree);

/**
* @fn unsigned char entreeToucheEnfoncee(const EntreeSDL *entree, SDLKey touche)
* @brief Detecte si une touche est enfoncée.
* @param [in] entree: instance d'EntreeSDL.
* @param [in] touche : un nom de touche SDL : voir cette page pour une liste complète des touches prises en charge http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
* @return 1 si la touche est enfoncée, 0 sinon.
*/
unsigned char entreeToucheEnfoncee(const EntreeSDL *entree, SDLKey touche);

/**
* @fn char entreeGetAlphaNum(const EntreeSDL *entree)
* @brief Renvoie le caractère alphanumérique pressé au clavier.
* @param [in] entree: instance d'EntreeSDL.
* @return renvoie 0 si aucun caractère alphanumérique n'est pressé.
*/
char entreeGetAlphaNum(const EntreeSDL *entree);

/**
* @fn unsigned char entreeBoutonSourisGauche(const EntreeSDL *entree)
* @brief Teste si le bouton souris gauche est enfoncé.
* @param [in] entree : instance d'EntreeSDL.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/
unsigned char entreeBoutonSourisGauche(const EntreeSDL *entree);

/**
* @fn unsigned char entreeBoutonSourisDroit(const EntreeSDL *entree)
* @brief Teste si le bouton souris droit est enfoncé.
* @param [in] entree: instance d'EntreeSDL.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/
unsigned char entreeBoutonSourisDroit(const EntreeSDL *entree);

/**
* @fn int entreeGetSourisX(const EntreeSDL *entree)
* @brief Renvoie la position courante en X de la souris.
* @param [in] entree : instance d'EntreeSDL.
* @return un entier décrivant la position en X de la souris.
*/
int entreeGetSourisX(const EntreeSDL *entree);

/**
* @fn int entreeGetSourisY(const EntreeSDL *entree)
* @brief Renvoie la position courante en Y de la souris.
* @param [in] entree : instance d'EntreeSDL.
* @return un entier décrivant la position en Y de la souris.
*/
int entreeGetSourisY(const EntreeSDL *entree);

#endif

