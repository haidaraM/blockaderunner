/**
* @file Vaisseau.h
* @brief fichier d'entete du module vaisseau
*/

#ifndef _VAISSEAU_H
#define _VAISSEAU_H

#define VAISSEAU_NB_TYPES                               2

/* Caracteristiques du vaisseau du joueur */
#define VAISSEAU_JOUEUR_TYPE                            1
#define JOUEUR_NB_ARMES                                 1
#define JOUEUR_POINTECRAN                               100
#define JOUEUR_POINTSTRUCTURE                           100

/* Caracteristiques du vaisseau ennemi */
#define VAISSEAU_ENNEMI_TYPE                            2
#define ENNEMI_ARMES                                    1
#define ENNEMI_POINTECRAN                               50
#define ENNEMI_POINTSTRUCTURE                           50

/* Armes */
#define ARME_1                                          1
#define ARME_1_MUNITIONS                                1000
#define ARME_1_DEGAT_E                                  50
#define ARME_1_DEGAT_S                                  50

/**
* @struct Arme
* @brief Represente l'arme d'un vaisseau
*/
typedef struct
{
    int typeArme; /* 1, 2 ... */

    int degatEcran;

    int degatStructure;

    int munitions;

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
} Vaisseau;

/**
* @fn
* @brief
*/
void vaisseauJoueurInit(Vaisseau *vaisseauJ, int pointS, int pointE, int nbArmes);

/**
* @fn
* @brief
*/
void vaisseauEnnemiInit(Vaisseau *vaisseau, int pointS, int pointE, int nbArmes);

/**
* @fn
* @brief
*/
void vaisseauLibere(Vaisseau * vaisseau);

/**
* @fn void armeInit(Arme * a);
*/
void armeInit(Arme *a, int type);


/**
* @fn void vaisseauTestDeregression()
* @brief
*/
void vaisseauTestDeregression();

#endif

