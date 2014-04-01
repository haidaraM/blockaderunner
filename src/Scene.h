/**
* @file Scene.h
* @brief Gère la scène : positions, statuts de toutes les instances, potentiellement 'affichables' (visuel et audio).
* @author Yann Cortial
*/
#ifndef _SCENE_H
#define _SCENE_H

#define SCENE_VITESSE_DEFILEMENT_FOND 		((4098.0f - 1366.0f)/(10.0f * 6.0f))




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
	/** index image fond (background du niveau). */
	int indexImageFond;
	/** position courante (et taille) du fond du niveau (background). */
	Rectangle rectangleImageFond;
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



void sceneChargeNiveau(Scene *scene, Niveau *niveau);


/**
* @brief Permet de refiler le temps écoulé à la scène : utile pour les animations (défilement du fond, ...). 
*/
void sceneAnime(Scene *scene, float tempsSecondes);

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

