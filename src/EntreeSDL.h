/**
* @file EntreeSDL.h
* @brief Module de gestion des entrées (couplé avec SDL) : clavier, souris et évènements divers.
* @author Yann Cortial
*/
#ifndef _ENTREE_SDL_H
#define _ENTREE_SDL_H

#include "SDL/SDL.h"



typedef struct
{
	/** booléen renseignant si la fermeture du programme a été demandé (évènement).*/
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
* @brief Initialise le module.
* @param entree[in, out] : doit être non NULL.
*/
void entreeInit(EntreeSDL *entree);
/**
* @brief Libère les ressources du module.
*/
void entreeLibere(EntreeSDL *entree);
/**
* @brief Récupère tous les nouveaux évènements survenus depuis le dernier appel. 
*
* Doit être appelée avant de tester l'état des touches et de la souris (typiquement régulièrement, dans la boucle principale du programme).
*/
void entreeSonde(EntreeSDL *entree);
/**
* @brief Teste si la fermeture du programme a été demandée par l'utilisateur.
*
* La fermeture du programme est un évènement dispatché par l'OS, typiquement par exemple lorsque l'utilsateur a tenté de fermer en cliquant la fenêtre principale du programme.
*/
unsigned char entreeFermetureJeu(const EntreeSDL *entree);
/** 
* @brief Detecte si une touche est enfoncée. 
* @param entree[in, out] : instance d'EntreeSDL.
* @param touche : un nom de touche SDL : voir cette page pour une liste complète des touches prises en charge http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
* @return 1 si la touche est enfoncée, 0 sinon.
*/
unsigned char entreeToucheEnfoncee(const EntreeSDL *entree, SDLKey touche);
/** 
* @brief Renvoie le caractère alphanumérique pressé au clavier. 
* @param entree[in, out] : instance d'EntreeSDL.
* @return renvoie 0 si aucun caractère alphanumérique n'est pressé.
*/
char entreeGetAlphaNum(const EntreeSDL *entree);
/**
* @brief Teste si le bouton souris gauche est enfoncé.
*	
* @param entree[in, out] : instance d'EntreeSDL.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/
unsigned char entreeBoutonSourisGauche(const EntreeSDL *entree);
/**
* @brief Teste si le bouton souris droit est enfoncé.
*	
* @param entree[in, out] : instance d'EntreeSDL.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/

unsigned char entreeBoutonSourisDroit(const EntreeSDL *entree);
/**
* @brief Renvoie la position courante en X de la souris.
*	
* @param entree[in, out] : instance d'EntreeSDL.
* @return un entier décrivant la position en X de la souris.
*/
int entreeGetSourisX(const EntreeSDL *entree);
/**
* @brief Renvoie la position courante en Y de la souris.
*	
* @param entree[in, out] : instance d'EntreeSDL.
* @return un entier décrivant la position en Y de la souris.
*/
int entreeGetSourisY(const EntreeSDL *entree);

#endif

