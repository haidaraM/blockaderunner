/**
* @file Outils.h
* @brief Boîte à outils : math, geométrie, ...
* @author Yann Cortial
*/
#ifndef _OUTILS_H
#define _OUTILS_H

/*----------------------------------------------------------------------------  NOMBRES ALEATOIRES ------------------------------------------------------------------------*/

/**
* @brief Renvoie un entier pseudo-aléatoire uniformément distribué entre borneInf et borneSup tel que :    borneInf <= (retour) < borneSup
*/
int randomInt(int borneInf, int borneSup);

/*----------------------------------------------------------------------------	GEOMETRIE ---------------------------------------------------------------------------------*/

/**
* @brief un Point 2D.
*/
typedef struct
{
	int x;
	int y;
} Point;

/**
* @brief un Rectangle = une position (coin supérieur gauche) + une dimension (largeur, hauteur).
*/
typedef struct
{
	int x;
	int y;
	int largeur;
	int hauteur;
} Rectangle;

/**
* @brief Renvoie 1 si le rectangle contient le point (x, y), 0 sinon.
*/
unsigned char rectangleContient(Rectangle *rect, int x, int y);


/*----------------------------------------------------------------------------	TABLEAU DYNAMIQUE ---------------------------------------------------------------------------------*/

/**
* @brief Tableau dynamique
*/
typedef struct
{
	int tailleUtilisee;
	int capacite;
	void **tab;
} TabDyn;

/**
* @brief Initialise un tableau dynamique : t doit être non NULL.
*/
void tabDynInit(TabDyn *t);
/**
* @brief Libère un tableau dynamique : les éléments du tableau doivent être éventuellement préalablement libérés par l'utilisateur.
*/
void tabDynLibere(TabDyn *t);
/**
* @brief Ajoute un élément générique à un tableau dynamique.
*/
void tabDynAjoute(TabDyn *t, void* element);
/**
* @brief Renvoie un des éléments du tableau dynamique.
*/
void* tabDynGetElement(TabDyn *t, int index);

/**
* @brief supprime un element du tableau dynamique
* @param [in, out] t (doit etre initialise)
* @param [in] position (correspond à la position de l'element dans le tableau )
*/
void tabDynSupprimeElement(TabDyn *t, int position);

/*----------------------------------------------------------------------------	LISTE CHAINEE ---------------------------------------------------------------------------------*/

/**
* @brief Cellule de liste chaînée.
*/
/*struct s_CelluleListe
{
	s_CelluleListe *suiv;
	void *data;
};
typedef struct s_CelluleListe CelluleListe;

typedef struct
{
	CelluleListe *prem;
} Liste;

CelluleListe* celluleListeCreer(void *data);
Liste* listeCreer();
void listeDetruire(Liste *liste);
void listeInit(Liste *liste);
void listeLibere(Liste *liste);
void listeAjouteTete(Liste *liste, void *data);
void listeAjouteQueue(Liste *liste, void *data);
void listeSupprime(Liste *liste, void *data);
*/


#endif

