/**
* @file Scene.h
* @brief Gère la scène : positions des elements, collisions, statuts de toutes les instances, potentiellement 'affichables' (visuel et audio).
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/
#ifndef _SCENE_H
#define _SCENE_H

#include "ElementScene.h"
#include "Ressource.h"
#include "Joueur.h"
#include "Outils.h"




#define SCENE_VITESSE_DEFILEMENT_POINTS 	420.0f
#define SCENE_NUM_POINTS_DEFILEMENT 		64

#define SCENE_VITESSE_LASER					640.0f
#define SCENE_VITESSE_ASTEROIDE				128.0f	
#define SCENE_VITESSE_ECLAIREUR				180.0f
#define SCENE_VITESSE_CHASSEUR				128.0f
#define SCENE_VITESSE_CROISEUR				64.0f







typedef struct
{
	/** garde trace du temps écoulé (pour animations). */
	float horlogePrecedente;
	/** Portion visible de la scène. */
	int largeurAffichage, hauteurAffichage;
	/** Element constituant le vaisseau du joueur **/
	ElementScene *vaisseauJoueur;
	/** tableau dynamique qui regroupent tous les ennemis de la scène (vaisseaux et asteroides 'collisionables').*/
	TabDyn acteurs;
	/** tableau dynamique des tirs. */
	TabDyn tirs;
	/** tableau dynamique des bonus. */
	TabDyn bonus;
	/** tableau dynamique des éléments de décor. */
	TabDyn decors;
	/** index image fond (background du niveau). */
	int indexImageFond;
	/** position courante (et taille) du fond du niveau (background). */
	Rectangle rectangleImageFond;
	/** Tableau de points de defilement (FX).*/
	Point *pointsDefilement;
	/** pointeur vers l'instance en cours du module Niveau : décrit le niveau du jeu en cours.*/
	Niveau *niveau;
	/** pointeur vers  le joueur courant */
	Joueur *joueur;
	/** pointeur vers l'instance du module Ressource : utile pour créer des elements. */
	Ressource *ressource;
} Scene;


/**
* @brief Initialise la scène.
*
* Un lien vers le module Ressource est nécessaire pour instancier les divers elements (Ressource permet d'associer des ressources (images, sons)).
*
*/
void sceneInit(Scene *scene, Ressource *res, Joueur *player, int largeurGraphique, int hauteurGraphique);
/**
* @brief Libère les ressources du module.
*/
void sceneLibere(Scene *scene);


/**
* @brief Charge un Niveau du Jeu.
*/
void sceneChargeNiveau(Scene *scene, Niveau *niveau, Ressource *res);
/**
* @brief Initialise l'horloge de la scene.
*/
void sceneResetHorloge(Scene *scene, float horloge);
/**
* @brief fait defiler le fond d'ecran.
*/
void sceneDefileScene(Scene *scene);

/**
* @fn int sceneGetNbActeurs(const Scene * scene)
* @brief renvoie le nombre d'acteurs sur la scene
*/
int sceneGetNbActeurs(const Scene * scene);
/**
* @fn int sceneGetNbTirs(const Scene * scene)
* @brief renvoie le nombre de tirs actifs.
*/
int sceneGetNbTirs(const Scene * scene);
/**
* @fn int sceneGetNbBonus(const Scene * scene)
* @brief renvoie le nombre de bonus capturables.
*/
int sceneGetNbBonus(const Scene * scene);
/**
* @fn int sceneGetNbDecors(const Scene * scene)
* @brief renvoie le nombre d'éléments de décor.
*/
int sceneGetNbDecors(const Scene * scene);


/**
* @fn void sceneAnime(Scene *scene, float tempsSecondes)
* @brief Permet de passer le temps écoulé à la scène : fait évoluer les animations et les supprime s'il sortent de l'ecran.
* @param [in, out] scene
*/
void sceneAnime(Scene *scene, float tempsSecondes);

/**
* @brief (inutilisé)
*/
ElementScene* sceneCreerElementScene(Scene *scene, int type);

/**
* @fn void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
* @brief Deplace le vaisseau du joueur vers le haut.
* @param scene[in, out] : instance de la Scene.
* @param tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
* @brief Deplace le vaisseau du joueur vers le bas.
* @param scene[in, out] : instance de la Scene.
* @param tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes);
* @brief Deplace le vaisseau du joueur vers la gauche.
* @param scene[in, out] : instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes);
* @brief Deplace le vaisseau du joueur vers la droite.
* @param scene[in, out] : instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes);

/**
* @fn void sceneJoueurDeclencheTir(Scene * scene)
* @brief Cree un element qui correspond au tir du joueur
* @param [in, out] scene (doit etre initialisé )
*/
void sceneJoueurDeclencheTir(Scene * scene);

/**
* @fn void sceneEnnemiTirLaser(Scene * scene)
* @brief Cree un element qui correspond au tir laser d'un ennemi.
* @param [in, out] scene (doit etre initialisé )
* @param x position en x du point de départ du tir
* @param y position en y du point de départ du tir.
*/
void sceneEnnemiTirLaser(Scene * scene, int x, int y);

/**
* @fn void sceneTestDeCollision(Scene *scene)
* @brief test de collision
* @param [in, out] scene : initialisée
*/
void sceneTestDeCollision(Scene *scene);

/**
* @fn void sceneTestDeRegression()
* @brief Effectue les tests pour verifier l'integrité du module
*/
void sceneTestDeRegression();

#endif

