/**
* @file ElementScene.h
* @brief Une instance d'un type donné (élément du Jeu) : vaisseau, asteroide, etc. Caractérisé par des liens sur des ressources prédéfinies (images, sons).
*  Tous les ElementScenes sont gérés par la Scene, qui décident notamment lesquels sont visibles, créés, détruits.
* @author Yann Cortial
*
*/
#ifndef _ELEMENT_SCENE_H
#define _ELEMENT_SCENE_H



#define ELEMENT_TYPE_NON_DEFINI					-1
#define ELEMENT_TYPE_VAISSEAU_JOUEUR			 0
#define ELEMENT_TYPE_ASTEROIDE      			 1
#define ELEMENT_TYPE_LASER                       2
#define ELEMENT_TYPE_MISSILE                     3


/**
* @struct ElementScene
* @brief Element de la Scene : element affichable et jouable (audio).
*/
typedef struct
{
	/** type d'entité. */
	int type;
	/** destructible par un tir */
	int destructible;
	/** booléen : le element est dans la portion visible de la scène (ecran) ou pas. */
	int visible;
	/** position en X sur la scène. */
	int x;
	/** position en Y sur la scène. */
	int y;
	/** largeur du element. */
	int largeur;
	/** hauteur du element. */
	int hauteur;
	/** handle référençable dans Ressource (associe une image). */
	int indexImage;
	/** Largeur portion visible de la scène (ecran) (sert en interne pour le calcul de visibilité). */
	int largeurSceneVisible;
	/** Hauteur portion visible de la scène (ecran) (sert en interne pour le calcul de visibilité). */
	int hauteurSceneVisible;
} ElementScene;


/**
* @brief Initialise un element.
* @param element[in, out] : le element à initialiser, doit être non null.
* @param type : type d'entité
* @param indexImage : image associée au element (fournie par Ressource).
* @param largeur : largeur du element.
* @param hauteur : hauteur du element.
* @param largeurEcran : largeur de l'ecran (portion visible de la scène).
* @param largeurEcran : hauteur de l'ecran (portion visible de la scène).
*/
void elementInit(ElementScene *element, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran);
/**
* @brief libère proprement un element.
*/
void elementLibere(ElementScene *element);
/**
* @brief Affecte le type d'element.
*/
void elementSetType(ElementScene *element, int type);

/**
* @fn elementGetType(ElementScene * scene)
* @brief Renvoie le type d'element
*/
int elementGetType(const ElementScene * element);

/**
* @brief renvoie 1 si l'element est destructible, 0 sinon.
*/
int elementDestructible(const ElementScene *element);
/**
* @brief renvoie 1 si l'element est visible (ie. dans la portion visible de la Scene), 0 sinon.
*/
int elementVisible(const ElementScene *element);
/**
* @brief renvoie la position en X du element.
*/
int elementGetX(const ElementScene *element);
/**
* @brief renvoie la position en Y du element.
*/
int elementGetY(const ElementScene *element);
/**
* @brief Affecte une nouvelle position au element.
*/
void elementSetPosition(ElementScene *element, int x, int y);
/**
* @brief renvoie le handle de l'image associée au element (handle lisible par Ressource).
*/
int elementGetImageIndex(const ElementScene *element);
/**
* @fn void elementSceneTestDeRegression()
* @brief Effectue tout une serie de test pour vérifier l'intégrité du module
*/
void elementSceneTestDeRegression();


#endif

