/**
* @file Entree.h
* @brief Module de gestion des entrées : clavier, souris et évènements divers.
* @author Yann Cortial
*/
#ifndef _ENTREE_H
#define _ENTREE_H

#include "SDL/SDL.h"



typedef struct
{
	/** booléen renseignant si la fermeture du programme a été demandé (évènement).*/
	unsigned char fermetureJeu;
	/** nombre de touches du clavier. */
	int nombreTouches;
	/** tableau de booléen stockant l'état du clavier. */
	unsigned char *clavier;
	/** Etat de la souris : position en x et y. */
	int sourisX, sourisY;
	/** booléen : vaut 1 si le bouton gauche de la souris est enfoncé, 0 sinon. */
	unsigned char boutonSourisGauche;
	/** booléen : vaut 1 si le bouton droit de la souris est enfoncé, 0 sinon. */
	unsigned char boutonSourisDroit;
} Entree;


/**
* @brief Initialise le module.
* @param entree[in, out] : doit être non NULL.
*/
void entreeInit(Entree *entree);
/**
* @brief Libère les ressources du module.
*/
void entreeLibere(Entree *entree);
/**
* @brief Récupère tous les nouveaux évènements survenus depuis le dernier appel. 
*
* Doit être appelée avant de tester l'état des touches et de la souris (typiquement régulièrement, dans la boucle principale du programme).
*/
void entreeSonde(Entree *entree);
/**
* @brief Teste si la fermeture du programme a été demandée par l'utilisateur.
*
* La fermeture du programme est un évènement dispatché par l'OS, typiquement par exemple lorsque l'utilsateur a tenté de fermer en cliquant la fenêtre principale du programme.
*/
unsigned char entreeFermetureJeu(const Entree *entree);
/** 
* @brief Detecte si une touche est enfoncée. 
* @param entree[in, out] : instance d'Entree.
* @param touche : un nom de touche SDL : voir cette page pour une liste complète des touches prises en charge http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
* @return 1 si la touche est enfoncée, 0 sinon.
*/
unsigned char entreeToucheEnfoncee(const Entree *entree, SDLKey touche);
/**
* @brief Teste si le bouton souris gauche est enfoncé.
*	
* @param entree[in, out] : instance d'Entree.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/
unsigned char entreeBoutonSourisGauche(const Entree *entree);
/**
* @brief Teste si le bouton souris droit est enfoncé.
*	
* @param entree[in, out] : instance d'Entree.
* @return 1 si le bouton est enfoncé, 0 sinon.
*/

unsigned char entreeBoutonSourisDroit(const Entree *entree);
/**
* @brief Renvoie la position courante en X de la souris.
*	
* @param entree[in, out] : instance d'Entree.
* @return un entier décrivant la position en X de la souris.
*/
int entreeGetSourisX(const Entree *entree);
/**
* @brief Renvoie la position courante en Y de la souris.
*	
* @param entree[in, out] : instance d'Entree.
* @return un entier décrivant la position en Y de la souris.
*/
int entreeGetSourisY(const Entree *entree);

#endif

