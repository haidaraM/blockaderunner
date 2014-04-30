/**
* @file Outils.h
* @brief Boîte à outils : listeChainee, tableaudynamique etc ...
* @author Yann Cortial
*/
#ifndef _OUTILS_H
#define _OUTILS_H

/*----------------------------------------------------------------------------  NOMBRES ALEATOIRES ------------------------------------------------------------------------*/

/**
* @fn int randomInt(int borneInf, int borneSup)
* @brief Renvoie un entier pseudo-aléatoire uniformément distribué entre borneInf et borneSup tel que :    borneInf <= (retour) < borneSup
*/
int randomInt(int borneInf, int borneSup);

/*----------------------------------------------------------------------------	GEOMETRIE ---------------------------------------------------------------------------------*/

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
	/** taille du tableau (note: le tableau est compact à gauche). */
	int tailleUtilisee;
	/** capacité du tableau. */
	int capacite;
	/** tableau de pointeurs génériques. */
	void **tab;
} TabDyn;

/**
* @brief Initialise un tableau dynamique : t doit être non NULL.
*/
void tabDynInit(TabDyn *t);
/**
* @brief Libère un tableau dynamique : les éléments du tableau doivent être impérativement libérés un à un, au préalable, par l'utilisateur.
*/
void tabDynLibere(TabDyn *t);
/**
* @brief Ajoute un élément générique à un tableau dynamique.
*/
void tabDynAjoute(TabDyn *t, void* element);
/**
* @brief Renvoie un des éléments du tableau dynamique.
*/
void* tabDynGetElement(const TabDyn *t, int index);
/**
* @brief supprime un element du tableau dynamique
* @param [in, out] t (doit etre initialise)
* @param [in] position (correspond à la position de l'element dans le tableau )
*/
void tabDynSupprimeElement(TabDyn *t, int position);

/*----------------------------------------------------------------------------	LISTE CHAINEE ---------------------------------------------------------------------------------*/

/**
* @struct CelluleListe
* @brief Cellule de liste doublement chaînée.
*/
struct s_CelluleListe
{
    /** Pointeur vers la cellule suivante de la cellule**/
	struct s_CelluleListe *suiv;
	/** Pointeur vers la cellule precedente de la cellule**/
	struct s_CelluleListe *prec;
	/** Pointeur generique constituant la donnee qui sera sauvegardee dans la cellule */
	void *donnee;
};
typedef struct s_CelluleListe CelluleListe;

/**
* @struct Liste
* @brief Constitut la liste en elle meme
*/
typedef struct
{
    /** Pointeur vers le premier element de la liste **/
	CelluleListe *premier;
	/** Pointeur vers le dernier element de la liste **/
	CelluleListe *dernier;
} Liste;

void listeInit(Liste *liste);

void listeLibere(Liste *liste);

Liste* listeCreer();

void listeDetruire(Liste *liste);

CelluleListe* celluleListeCreer(void *data);

void listeAjouteTete(Liste *liste, void *data);

void listeAjouteQueue(Liste *liste, void *data);

void listeSupprime(Liste *liste, void *data);



#endif

