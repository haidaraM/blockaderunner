/**
* @file Vaisseau.h
* @brief fichier d'entete du module vaisseau
*/

#ifndef _VAISSEAU_H
#define _VAISSEAU_H

/* Caracteristiques du vaisseau joueur*/
#define VAISSEAU_JOUEUR_TYPE                            1
#define JOUEUR_NB_ARMES                                 1
#define JOUEUR_POINTECRAN                               10
#define JOUEUR_POINTSTRUCTURE                           10

/* Caracteristiques du vaisseau ennemi*/
#define VAISSEAU_ENNEMI_TYPE                            2
#define ENNEMI_ARMES                                    1
#define ENNEMI_POINTECRAN                               5
#define ENNEMI_POINTSTRUCTURE                           5

/* Armes */
#define ARME_LAZER                                      0
#define ARME_LAZER_MUNITIONS                            1000
#define ARME_LAZER_DEGAT_E                              25
#define ARME_LAZER_DEGAT_S                              25

#define ARME_MISSILE                                    1
#define ARME_MISSILE_MUNITIONS                          100
#define ARME_MISSILE_DEGAT_E                            50
#define ARME_MISSILE_DEGAT_S                            50


/**
* @struct Arme
* @brief Represente l'arme du vaisseau
*/
typedef struct
{
    /** type de l'arme : laser, missile */
    int typeArme;

    int degatEcran;

    int degatStructure;
    /** Munitions (infinies pour le laze ) */
    int munitions;
    /** cadence de tir : utile pour le missile */
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
    /** Point ecran du vaisseau**/
    int pointEcran;
    /** Point structure du vaisseau */
    int pointStructure;
    /** Nombre d'arme du vaisseau. Une arme pour un debut **/
    int nbArmes;
    /** Tableau d'armes du vaisseau*/
    Arme *armes;
    /** Entier qui represente l'arme selectionnée. Arme 0 selectionnée par defaut **/
    int armeSelectionne;
} Vaisseau;

/**
* @fn void vaisseauJoueurInit(Vaisseau *vaisseauJ, int pointS, int pointE, int nbArmes)
* @brief Initialise le vaisseau du joueur
* @param [in, out] vaisseauJ
* @param [in] type
* @param [in] points
* @param [in] pointE
* @param [in] nbArmes
*/
void vaisseauInit(Vaisseau *vaisseauJ, int type, int pointS, int pointE, int nbArmes);

/**
* @fn void vaisseauLibere(Vaisseau * vaisseau)
* @brief Libere la memoire alloue pour le vaisseau. Vaisseau doit etre non null
* @param [in, out] vaisseau
*/
void vaisseauLibere(Vaisseau * vaisseau);

/**
* @fn void armeInit(Arme * a);
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
* @brief Renvoie les points ecran du vaisseau du joueur
* @param [in] vaisseau
*/
int vaisseauGetPointEcran(const Vaisseau * vaisseau);

/**
* @fn int vaisseauGetPointStructure(const Vaisseau * vaisseau);
* @brief Renvoie les points structure du vaisseau du joueur
* @param [in] vaisseau
*/
int vaisseauGetPointStructure(const Vaisseau * vaisseau);

/**
* @fn Arme vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau);
* @brief renvoie l'arme selectionnee
*/
Arme vaisseauGetArmeSelectionnee(const Vaisseau * vaisseau);

/**
* @fn void vaisseauTestDeregression()
* @brief Effectue les tests pour verifier l'integrité du module
*/
void vaisseauTestDeregression();


#endif

