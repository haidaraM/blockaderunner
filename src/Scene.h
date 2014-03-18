/**
* @file Scene.h
* @brief Gère la scène : positions, statuts de toutes les instances, potentiellement 'affichables' (visuel et audio).
* @author Yann Cortial
*/
#ifndef _SCENE_H
#define _SCENE_H

#include "Sprite.h"
#include "Ecran.h"
#include "Ressource.h"
#include "Niveau.h"



typedef struct
{
	/** nombre de sprites. */
	int numSprites;
	/** tableau de pointeur sur Sprite.*/
	Sprite **sprites;
	/** pointeur vers l'instance du module Ecran : utile pour l'affichage de la scène. */
	Ecran *ecran;
	/** pointeur vers l'instance en cours du module Niveau : décrit le niveau du jeu en cours.*/
	Niveau *niveau;
	/** pointeur vers l'instance du module Ressource : utile pour créer des sprites. */
	Ressource *ressource;
} Scene;


/**
* @brief Initialise la scène.
*
* Un lien vers le niveau en cours est nécessaire, la scène se construira d'après le contenu du niveau. 
* Un lien vers le module Ecran est nécessaire pour l'affichage de la scène (collection de sprites).
* Un lien vers le module Ressource est nécessaire pour instancier les divers sprites (Ressource permet d'associer des ressources (images, sons)).
*
*/
void sceneInit(Scene *scene, Niveau *niv, Ecran *ecran, Ressource *res);
/**
* @brief Libère les ressources du module.
*/
void sceneLibere(Scene *scene);
/**
* @brief Affiche la portion visible de la scène.
*/
void sceneAffiche(const Scene *scene);
/**
* @brief TODO : à implementer.
*/
Sprite* sceneCreerSprite(Scene *scene, int type);
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

