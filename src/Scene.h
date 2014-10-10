/**
* @file Scene.h
* @brief Gère la scène : positions des elements, collisions, statuts de toutes les instances, potentiellement 'affichables' (visuel et audio).
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/
#ifndef _SCENE_H
#define _SCENE_H

#include "ElementScene.h"
#include "Ressource.h"
#include "Outils.h"





#define SCENE_BONUS_SCORE					3200		/* nombre de points de score ajoutés si le joueur acquiere un Bonus de score */
#define SCENE_BONUS_MISSILE					4			/* nombre de missiles que le joueur acquière lorsqu'il touche un Bonus missile */
#define SCENE_PROBA_BONUS_SCORE_ECLAIREUR 	10			/* note: pourcentages */
#define SCENE_PROBA_BONUS_SCORE_CHASSEUR	25
#define SCENE_PROBA_BONUS_SCORE_CROISEUR	70
#define SCENE_PROBA_BONUS_MISSILE_CROISEUR  40

#define SCENE_VITESSE_DEFILEMENT_POINTS 	420.0f
#define SCENE_NUM_POINTS_DEFILEMENT 		64

#define SCENE_VITESSE_BONUS					96.0f
#define SCENE_VITESSE_TIR					640.0f
#define SCENE_VITESSE_ASTEROIDE				128.0f
#define SCENE_VITESSE_ECLAIREUR				180.0f
#define SCENE_VITESSE_CHASSEUR				224.0f
#define SCENE_VITESSE_CROISEUR				64.0f
#define SCENE_VITESSE_ROTATION              18.0f




/**
* @struct EvenementScene
* @brief Structure utilisée en interne qui représente les évènements survenants sur la scène.
* Utile pour jouer les sons
*/
typedef struct
{
    char joueur_tir_laser;
    char joueur_tir_missile;
    char joueur_tir_erreur;
    char ennemi_tir_laser;
    char ennemi_tir_missile;

    char joueur_degats_collision;	/* un asteroide ou vaisseau collisionne avec le joueur */
    char joueur_degats_laser; 		/* un laser touche le joueur */
    char ennemi_degats_laser; 		/* un laser touche un ennemi */
    char joueur_degats_missile;		/* un missile touche le joueur */
    char ennemi_degats_missile;		/* un missile touche un ennemi */

    char joueur_explosion;			/* le joueur explose */
    char ennemi_explosion;			/* un ennemi explose */
    char asteroide_explosion;		/* un asteroide explose */

    char joueur_bonus_score;		/* le joueur vient d'acquerir un bonus de score */
    char joueur_bonus_missile;		/* le joueur vient d'acquerir un bonus missile */

} EvenementScene;

/**
* @struct PositionExplosion
* @brief Structure utilisée pour sauvegarder les positions des ennemis detruits.
* Utile pour afficher les explosions après la destruction des ennemis
*/
typedef struct
{
    /** type de l'element detruit **/
    int type;
    /** position x de l'element detruit */
    int x;
    /** position y de l'element detruit */
    int y;
    /** Lien vers l'animateur associé à l'explosion */
    void *ateur;

} PositionExplosion;

/**
* @struct Scene
* @brief Structure principale qui représente tous les éléments de la scène : asteroides, debris, bonus, vaisseaux, tirs, decors,etc.
*/
typedef struct
{
    /** Garde une trace du temps écoulé (pour animations). */
    float horlogePrecedente;
    /** Portion visible de la scène. */
    int largeurAffichage, hauteurAffichage;
    /** Element constituant le vaisseau du joueur **/
    ElementScene *elementVaisseauJoueur;
    /** tableau dynamique qui regroupent tous les ennemis de la scène (vaisseaux et asteroides 'collisionables').*/
    TabDyn acteurs;
    /** tableau dynamique des tirs. */
    TabDyn tirs;
    /** tableau dynamique des bonus. */
    TabDyn bonus;
    /** tableau dynamique des éléments de décor : INUTILISEE POUR LE MOMENT. */
    TabDyn decors;
    /** index image fond (background du niveau). */
    int indexImageFond;
    /** position courante (et taille) du fond du niveau (background). */
    Rectangle rectangleImageFond;
    /** Tableau de points de defilement (FX).*/
    Point *pointsDefilement;
    /** structure encapsulant les évènements courant (rédéfinis à chaque frame) */
    EvenementScene evenements;
    /** pointeur vers l'instance en cours du module Niveau : décrit le niveau du jeu en cours.*/
    Niveau *niveau;
    /** pointeur vers  le joueur courant */
    Joueur *joueur;
    /** pointeur vers l'instance du module Ressource : utile pour créer des elements. */
    Ressource *ressource;
    /** Tableau des positions des elements detruits notamment les vaisseaux ennemis **/
    TabDyn positionsExplosions;
    /* Utilisé en interne pour la rotation des asteroides */
    double angleRotation;

} Scene;


/**
* @fn void sceneInit(Scene *scene, Ressource *res, Joueur *player, int largeurGraphique, int hauteurGraphique)
* @brief Initialise la scène.
* Un lien vers le module Ressource est nécessaire pour instancier les divers elements (Ressource permet d'associer des ressources (images, sons)).
* @param [in, out] scene
* @param [in] res : initialisé
* @param [in,out] player : initialisé
* @param [in] largeurGraphique
* @param [in] hauteurGraphique
*/
void sceneInit(Scene *scene, Ressource *res, Joueur *player, int largeurGraphique, int hauteurGraphique);

/**
* @fn void sceneLibere(Scene *scene)
* @brief Libère les ressources du module.
* @param [in, out] scene
*/
void sceneLibere(Scene *scene);

/**
* @fn void sceneChargeNiveau(Scene *scene, Niveau *niveau)
* @brief Charge un Niveau du Jeu.
* @param [in, out] scene : initialisé
* @param [in] niveau : initialisé
*/
void sceneChargeNiveau(Scene *scene, Niveau *niveau);

/**
* @fn void sceneResetHorloge(Scene *scene, float horloge)
* @brief Initialise l'horloge de la scene.
* @param [in, out] scene : initialisé
* @param [in] horloge
*/
void sceneResetHorloge(Scene *scene, float horloge);

/**
* @fn void sceneDefileScene(Scene *scene)
* @brief Fait defiler le fond d'ecran.
* @param [in, out] scene : initialisé
* @return Renvoie 1 si on arrive à la fin de la scene, 0 sinon
*/
int sceneDefileScene(Scene *scene);

/**
* @fn int sceneGetNbActeurs(const Scene * scene)
* @brief renvoie le nombre d'acteurs sur la scene
* @param [in] scene : initialisé
*/
int sceneGetNbActeurs(const Scene * scene);

/**
* @fn int sceneGetNbTirs(const Scene * scene)
* @brief renvoie le nombre de tirs actifs.
* @param [in] scene : initialisé
*/
int sceneGetNbTirs(const Scene * scene);

/**
* @fn int sceneGetNbBonus(const Scene * scene)
* @brief renvoie le nombre de bonus capturables.
* @param [in] scene : initialisé
*/
int sceneGetNbBonus(const Scene * scene);

/**
* @fn int sceneGetNbDecors(const Scene * scene)
* @brief renvoie le nombre d'éléments de décor.
* @param [in] scene : initialisé
*/
int sceneGetNbDecors(const Scene * scene);

/**
* @fn void sceneGetDataElement(PositionExplosion * pos, const ElementScene * element)
* @brief recupere les elements de l'elementScene pour PositionExplosion
* @param [in,out] pos
* @param [in] element : initialisé
*/
void sceneGetDataElement(PositionExplosion * pos, const ElementScene * element);

/**
* @fn int sceneGetNbExplosions(const Scene * scene)
* @brief renvoie le nombre d'explosions à effectuer c'est à dire le nombre de vaisseaux detruits.
* @param [in] scene : initialisé
*/
int sceneGetNbExplosions(const Scene * scene);


/**
* @fn void sceneAnime(Scene *scene, float tempsSecondes)
* @brief Permet de passer le temps écoulé à la scène : fait évoluer les animations et les supprime si elles sortent de l'ecran.
* @param [in, out] scene : initialisé
* @param [in] tempsSecondes
*/
void sceneAnime(Scene *scene, float tempsSecondes);

/**
* @fn void scenePause (Scene * scene)
* @brief Permet de mettre le jeu en pause c'est à dire pas d'animations sur la scene.
* @param [in, out] scene
*/
void scenePause(Scene * scene);

/**
* @fn ElementScene* sceneCreerElementScene(const Scene *scene, int type)
* @brief Cree un element et l'initialise
* @param [in] scene
* @return Renvoie un pointeur vers l'element initialisé
*/
ElementScene* sceneCreerElementScene(const Scene *scene, int type);


/**
* @fn void sceneDetruitElement(ElementScene *element)
* @brief Detruit complement un element : le libere et le met à null. Doit etre appelé sur un element crée par la scene
* @param [in, out] element : initialisé
*/
void sceneDetruitElement(ElementScene *element);


/**
* @fn void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
* @brief Deplace le vaisseau du joueur vers le haut.
* @param [in, out]scene : instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
* @brief Deplace le vaisseau du joueur vers le bas.
* @param [in, out] scene : instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes);
* @brief Deplace le vaisseau du joueur vers la gauche.
* @param [in, out] scene: instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes);

/**
* @fn void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes);
* @brief Deplace le vaisseau du joueur vers la droite.
* @param [in, out] scene : instance de la Scene.
* @param [in] tempsSecondes : temps écoulé depuis le dernier appel. Utilisé pour calculer le déplacement à vitesse constante.
*/
void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes);

/**
* @fn int sceneJoueurDeclencheTir(Scene * scene)
* @brief Cree le tir du joueur et l'ajoute au tableaux des tirs
* @param [in, out] scene
*/
void sceneJoueurDeclencheTir(Scene * scene);

/**
* @fn int sceneGetMunitionMissileJoueur(const Scene *scene)
* @brief Renvoie le nombre de missiles restant au joueur.
* @param [in] scene : initialisé
*/
int sceneGetMunitionMissileJoueur(const Scene *scene);

/**
* @fn void sceneEnnemiDeclencheTir(Scene * scene, ElementScene *e, float tempsCourant)
* @brief Un ennemi tente de tirer
* @param [in, out] scene (doit etre initialisé )
* @param [in, out] e element-scene (ennemi)
* @param [in] tempsCourant temps associé à la frame courante (en secondes).
*/
void sceneEnnemiDeclencheTir(Scene * scene, ElementScene *e, float tempsCourant);

/**
* @fn void sceneTestDeCollision(Scene *scene)
* @brief test de collision des tous les elements de la scene
* @param [in, out] scene : initialisée
*/
void sceneTestDeCollision(Scene *scene);

/**
* @fn int sceneTestVaisseauMort( Scene * scene)
* @brief Test si le joueur est mort ou pas
* @param [in,out] initialisé
* @return Renvoie 1 si le joueur est mort, 0 sinon
*/
int sceneTestVaisseauMort(Scene * scene);

/**
* @fn double sceneGetAngleRotation(const Scene * scene )
* @brief Recupère l'angle de rotation des debris d'asteroides
* @param [in] scene : initialisé
*/
double sceneGetAngleRotation(const Scene * scene );

/**
* @fn void sceneMAJAngleRotation (Scene * scene)
* @brief Met à jour l'angle de rotation
*/
void sceneMAJAngleRotation (Scene * scene);

/**
* @fn void sceneTestDeRegression()
* @brief Effectue les tests pour verifier l'integrité du module
*/
void sceneTestDeRegression();

#endif

