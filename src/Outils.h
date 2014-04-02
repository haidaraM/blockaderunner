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

