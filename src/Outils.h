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
* @param [in] borneInf
* @param [in] borneSup
*/
int randomInt(int borneInf, int borneSup);
/**
* @fn int randomFloat()
* @brief Renvoie un float entre 0.0 et 1.0
*/
float randomFloat();

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
* @struct Rectangle
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
* @fn unsigned char rectangleContient(const Rectangle *rect, int x, int y)
* @brief Renvoie 1 si le rectangle contient le point (x, y), 0 sinon.
* @param [in] rect
* @param x
* @param y
*/
unsigned char rectangleContient(const Rectangle *rect, int x, int y);


/*----------------------------------------------------------------------------	TABLEAU DYNAMIQUE ---------------------------------------------------------------------------------*/

/**
* @struct TadDyn
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
* @fn void tabDynInit(TabDyn *t)
* @brief Initialise un tableau dynamique
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
* @param [in, out]
* @param [in] element
*/
void tabDynAjoute(TabDyn *t, void* element);

/**
* @fn void* tabDynGetElement(const TabDyn *t, int index)
* @brief Renvoie un des éléments du tableau dynamique.
* @param [in] t
* @param [in] index
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

