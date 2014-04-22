/**
* @file Vaisseau.h
* @brief fichier d'entete du module vaisseau
*/

#ifndef _VAISSEAU_H
#define _VAISSEAU_H

/* Caracteristiques du vaisseau joueur*/
#define VAISSEAU_JOUEUR_TYPE                            1
#define JOUEUR_NB_ARMES                                 1
#define JOUEUR_POINTECRAN                               100
#define JOUEUR_POINTSTRUCTURE                           100

/* Caracteristiques du vaisseau ennemi*/
#define VAISSEAU_ENNEMI_TYPE                            2
#define ENNEMI_ARMES                                    1
#define ENNEMI_POINTECRAN                               50
#define ENNEMI_POINTSTRUCTURE                           50

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
    int typeArme; /* Lazer, missile*/

    int degatEcran;

    int degatStructure;

    int munitions;

    float cadence;

} Arme;

/**
* @struct Vaisseau
* @brief Represente un vaisseau soit du joueur soit de l'ennemis
*/
typedef struct
{
    /* Type du vaisseau : 1 pour le joueur, 2 pour l'ennemi*/
    int type;
    /* */
    int pointEcran;
    /* */
    int pointStructure;
    /* */
    int nbArmes;
    /* les armes du vaisseau*/
    Arme *armes;
    /* */
    int armeSelectionne;
} Vaisseau;

/**
* @fn void vaisseauJoueurInit(Vaisseau *vaisseauJ, int pointS, int pointE, int nbArmes)
* @brief Initialise le vaisseau du joueur
*/
void vaisseauInit(Vaisseau *vaisseauJ, int type, int pointS, int pointE, int nbArmes);

/**
* @fn void vaisseauLibere(Vaisseau * vaisseau)
* @brief Libere la memoire alloue pour le vaisseau
* @param [in, out] vaisseau
*/
void vaisseauLibere(Vaisseau * vaisseau);

/**
* @fn void armeInit(Arme * a);
* @brief Initialise l'arme correspondant à type
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

