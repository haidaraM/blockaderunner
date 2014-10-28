/**
* @file Outils.h
* @brief Boîte à outils : tableau dynamique, timer, nombres aléatoires, etc ...
* @author Yann Cortial - Mohamed El Mouctar HAIDARA
*/
#ifndef _OUTILS_H
#define _OUTILS_H

/*-------------------------------------------  CHRONO --------------------------------------------------------*/
/**
* @fn float getTempsSecondes()
* @brief Renvoie un float marquant le temps en secondes.
*/
float getTempsSecondes();

/*------------------------------------------  NOMBRES ALEATOIRES ---------------------------------------------------*/

/**
* @fn int randomInt(int borneInf, int borneSup)
* @brief Renvoie un entier pseudo-aléatoire uniformément distribué entre borneInf et borneSup tel que :    borneInf <= (retour) < borneSup
* @param [in] borneInf
* @param [in] borneSup
*/
int randomInt(int borneInf, int borneSup);
/**
* @fn int randomFloat()
* @brief Renvoie un float entre 0.0 et 1.0
*/
float randomFloat();

/*-------------------------------------------------	GEOMETRIE -----------------------------------------------------------*/

/**
* @struct Point
* @brief un Point 2D.
*/
typedef struct
{
    int x;
    int y;
} Point;

/**
* @struct Rectangle
* @brief un Rectangle = une position (coin supérieur gauche) + une dimension (largeur, hauteur).
* Utile pour le menu pour voir si la souris est sur du texte ou pas et pour sauvegarder les dimensions des images.
*/
typedef struct
{
    int x;
    int y;
    int largeur;
    int hauteur;
} Rectangle;

/**
* @fn unsigned char rectangleContient(const Rectangle *rect, int x, int y)
* @brief Renvoie 1 si le rectangle contient le point (x, y), 0 sinon.
* @param [in] rect
* @param x
* @param y
*/
unsigned char rectangleContient(const Rectangle *rect, int x, int y);


/*-------------------------------------	TABLEAU DYNAMIQUE -------------------------------------------------------------*/

/**
* @struct TabDyn
* @brief Represente un tableau dynamique qui peut stocker n'importe quoi.
*/
typedef struct
{
    /** taille du tableau (note: le tableau est compact à gauche). */
    int tailleUtilisee;
    /** capacité du tableau. */
    int capacite;
    /** tableau de pointeurs génériques. */
    void **tab;
} TabDyn;

/**
* @fn void tabDynInit(TabDyn *t)
* @brief Initialise un tableau dynamique avec capacité 1 et tailleUtilisee 0
* @param [in, out] t doit être non NULL.
*/
void tabDynInit(TabDyn *t);

/**
* @fn void tabDynLibere(TabDyn *t)
* @brief Libère un tableau dynamique : les éléments du tableau doivent être impérativement libérés un à un, au préalable, par l'utilisateur.
* @param [in, out] t
*/
void tabDynLibere(TabDyn *t);

/**
* @fn void tabDynAjoute(TabDyn *t, void* element)
* @brief Ajoute un élément générique à un tableau dynamique.
* @param [in, out] t : initialisé
* @param [in] element
*/
void tabDynAjoute(TabDyn *t, void* element);

/**
* @fn void* tabDynGetElement(const TabDyn *t, int index)
* @brief Renvoie un des éléments du tableau dynamique.
* @param [in] t : initialisé
* @param [in] index
*/
void* tabDynGetElement(const TabDyn *t, int index);

/**
* @fn void tabDynSupprimeElement(TabDyn *t, int index)
* @brief supprime un element du tableau dynamique
* @param [in, out] t (doit etre initialise)
* @param [in] index (position de l'element dans le tableau )
*/
void tabDynSupprimeElement(TabDyn *t, int index);

/**
* @fn void tabDynTestDeRegression();
* @brief Effectue les tests pour verifier l'intégrité du tableau Dynamique
*/
void tabDynTestDeRegression();

#endif
