/**
* @file Vaisseau.h
* @brief fichier d'entete du module Vaisseau qui regroupe les fonctions qui vont gerer les caractèristiques des vaisseaux
*/

#ifndef _VAISSEAU_H
#define _VAISSEAU_H







/* Caracteristiques du vaisseau joueur*/
#define VAISSEAU_JOUEUR_TYPE                            1
#define JOUEUR_NB_ARMES                                 2
#define JOUEUR_POINTECRAN                               300
#define JOUEUR_POINTSTRUCTURE                           300

/* Caracteristiques éclaireurs ennemi*/
#define VAISSEAU_ECLAIREUR_TYPE                         3
#define ECLAIREUR_ARMES  								1
#define ECLAIREUR_POINTECRAN                            0
#define ECLAIREUR_POINTSTRUCTURE                        25

/* Caracteristiques chasseurs ennemi*/
#define VAISSEAU_CHASSEUR_TYPE   	                    4
#define CHASSEUR_ARMES  								1
#define CHASSEUR_POINTECRAN                            25
#define CHASSEUR_POINTSTRUCTURE                        50

/* Caracteristiques croiseurs ennemi*/
#define VAISSEAU_CROISEUR_TYPE                         	5
#define CROISEUR_ARMES  								2
#define CROISEUR_POINTECRAN                            	100
#define CROISEUR_POINTSTRUCTURE                         300

/* Armes */
#define ARME_LASER                                      0
#define ARME_LASER_MUNITIONS                            1000
#define ARME_LASER_DEGAT_E                              30
#define ARME_LASER_DEGAT_S                              20

#define ARME_MISSILE                                    1
#define ARME_MISSILE_MUNITIONS                          3
#define ARME_MISSILE_DEGAT_E                            0
#define ARME_MISSILE_DEGAT_S                            200

#define VAISSEAU_COLLISION								2
#define VAISSEAU_COLLISION_DEGAT_E						0
#define VAISSEAU_COLLISION_DEGAT_S						50



/**
* @struct Arme
* @brief Represente l'arme du vaisseau
*/
typedef struct
{
    /** type de l'arme : laser, missile */
    int typeArme;

    int degatEcran;
    /** Degat infligé à la coque du vaisseau */
    int degatStructure;
    /** Munitions (infinies pour le laser ) */
    int munitions;
    /** stocke le temps du dernier tir : pour ne pas tirer trop de fois par seconde. */
    float tempsDernierTir;
	/** cadence de tir max */
	float cadence;

} Arme;

/**
* @struct Vaisseau
* @brief Represente le vaisseau du joueur soit de l'ennemi
*/
typedef struct
{
    /** Type du vaisseau : 1 pour le joueur, 2 pour l'ennemi **/
    int type;
    /** Point ecran du vaisseau : quantité d'ecran anti laser, baisse avec les tirs laser. A 0, les pointStructures diminuent**/
    int pointEcran;
    /** Point structure du vaisseau : etat de la coque du vaisseau. A 0, le vaisseau est detruit*/
    int pointStructure;
    /** Nombre d'arme du vaisseau. Une arme pour un debut **/
    int nbArmes;
    /** Tableau d'armes du vaisseau*/
    Arme *armes;
    /** Entier qui represente l'arme selectionnée. Arme 0 selectionnée par defaut **/
    int numArmeSelectionne;
} Vaisseau;

/**
* @fn void vaisseauJoueurInit(Vaisseau *vaisseauJ, int type)
* @brief Initialise le vaisseau du joueur
* @param [in, out] vaisseauJ
* @param [in] type
*
* NOTE : TODO : enlever pointS, pointE et nbArmes qui ne servent à rien pour le moment.
*/
void vaisseauInit(Vaisseau *vaisseauJ, int type);

/**
* @fn void vaisseauLibere(Vaisseau * vaisseau)
* @brief Libere la memoire alloue pour le vaisseau.
* @param [in, out] vaisseau :  doit etre non null
*/
void vaisseauLibere(Vaisseau * vaisseau);

/**
* @fn void armeInit(Arme * a, int type);
* @brief Initialise l'arme correspondant à 'type' passé en parametre
* @param [in, out] arme
* @param [in] type
*/
void vaisseauArmeInit(Arme *a, int type);

/**
* @fn int vaisseauGetNbArmes(const Vaisseau * vaisseau)
* @brief Renvoie le nombre d'armes du vaisseau
* @param  [in] vaisseau
*/
int vaisseauGetNbArmes(const Vaisseau * vaisseau);

/**
* @fn int vaisseauGetPointEcran(const Vaisseau * vaisseau);
* @brief Renvoie les points ecran du vaisseau
* @param [in] vaisseau
*/
int vaisseauGetPointEcran(const Vaisseau * vaisseau);

/**
* @fn int vaisseauGetPointStructure(const Vaisseau * vaisseau);
* @brief Renvoie les points structure du vaisseau
* @param [in] vaisseau
*/
int vaisseauGetPointStructure(const Vaisseau * vaisseau);

/**
* @fn void vaisseauSetPointVie(Vaisseau * vaisseau, int pEcran, int pStructure);
* @brief Affecte les points ecran &  les points structure du vaisseau
* @param [in] vaisseau
* @param [in] pEcran
* @param [in] pStructure
*/
void vaisseauSetPointVie(Vaisseau * vaisseau, int pEcran, int pStructure);

/**
* @fn void vaisseauSetDegats(const Vaisseau * vaisseau, int arme);
* @brief Inflige des dégats au vaisseau (affecte les points ecran et structure).
* @param [in] vaisseau
* @param [in] typeDegats type de dommages : arme utilisée (laser ou missile), ou collision.
*/
void vaisseauSetDegats(Vaisseau * vaisseau, int typeDegats);

/**
* @fn int vaisseauGetMunitionsArme(Const Vaisseau * vaisseau)
* @brief renvoie les munitions de l'arme selectionnéé
* @param [in] vaisseau
*/
int vaisseauGetMunitionsArme(const Vaisseau * vaisseau);

/**
* @fn Arme* vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau);
* @brief renvoie un pointeur sur l'arme selectionnee
* @param [in] vaisseau : initialisé
*/
Arme* vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau);

/**
* @fn void vaisseauMajMunitions(Vaisseau * joueur)
* @brief Met à jour les munitions de l'arme selectionnée quand un tir un declenché
* @param [in, out] vaisseau : initialisé
*/
void vaisseauMajMunitions(Vaisseau * vaisseau);



/**
* @fn int vaisseauGetDegatEcranArme(const Vaisseau * vaisseau )
* @brief Renvoie le degat ecran de l'arme selectionné
* @param [in] vaisseau
*/
int vaisseauGetDegatEcranArme(const Vaisseau * vaisseau );

/**
* @fn int vaisseauGetDegatStructureArme(const Vaisseau * vaisseau )
* @brief Renvoie le degat structure de l'arme selectionné
* @param [in] vaisseau
*/
int vaisseauGetDegatStructureArme(const Vaisseau * vaisseau );

/**
* @fn void vaisseauTestDeregression()
* @brief Effectue les tests pour verifier l'integrité du module
*/
void vaisseauTestDeregression();


#endif

