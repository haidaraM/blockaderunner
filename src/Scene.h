/**
* @file Scene.h
* @brief Gère la scène : positions, statuts de toutes les instances, potentiellement 'affichables' (visuel et audio).
* @author Yann Cortial
*/
#ifndef _SCENE_H
#define _SCENE_H

#include "ElementScene.h"
#include "Ressource.h"
#include "Niveau.h"



typedef struct
{
	/** Portion visible de la scène. */
	int largeurAffichage, hauteurAffichage;
	/** nombre de elements. */
	int numElements;
	/** tableau de pointeur sur ElementScene.*/
	ElementScene **elements;
	/** pointeur vers l'instance en cours du module Niveau : décrit le niveau du jeu en cours.*/
	Niveau *niveau;
	/** pointeur vers l'instance du module Ressource : utile pour créer des elements. */
	Ressource *ressource;
} Scene;


/**
* @brief Initialise la scène.
*
* Un lien vers le module Ressource est nécessaire pour instancier les divers elements (Ressource permet d'associer des ressources (images, sons)).
*
*/
void sceneInit(Scene *scene, Ressource *res, int largeurGraphique, int hauteurGraphique);
/**
* @brief Libère les ressources du module.
*/
void sceneLibere(Scene *scene);

ElementScene* sceneCreerElementScene(Scene *scene, int type);
/**
* @brief Deplace le vaisseau du joueur vers le haut.
* @param scene[in, out] : instance de la Scene.
* @param tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes);
/**
* @brief Deplace le vaisseau du joueur vers le bas.
* @param scene[in, out] : instance de la Scene.
* @param tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes);
void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes);
void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes);

#endif

