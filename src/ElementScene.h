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
#define ELEMENT_TYPE_DEBRIS_ASTEROIDE			 -2

#define ELEMENT_TYPE_LASER_JOUEUR                2
#define ELEMENT_TYPE_LASER_ENNEMI                3
#define ELEMENT_TYPE_MISSILE_JOUEUR              4
#define ELEMENT_TYPE_MISSILE_ENNEMI              5
#define ELEMENT_TYPE_BONUS_SCORE	             6
#define ELEMENT_TYPE_BONUS_MISSILE	             7

#define ELEMENT_TYPE_ECLAIREUR					 16
#define ELEMENT_TYPE_CHASSEUR					 17
#define ELEMENT_TYPE_CROISEUR					 18
#define ELEMENT_TYPE_VAISSEAU_ENNEMI             20




/**
* @struct ElementScene
* @brief Element de la Scene : element affichable et jouable (audio).
*/
typedef struct
{
	/** type d'entité. */
	int type;
	/** booléen : l'élement est dans la portion visible de la scène (ecran) ou pas. */
	int visible;
	/** position en X sur la scène. */
	int x;
	/** position en Y sur la scène. */
	int y;
	/** direction en X (nombre normalisé) */
	float vecX;
	/** direction en Y (nombre normalisé) */
	float vecY;
	/** largeur de l'élement. */
	int largeur;
	/** hauteur de l'élement. */
	int hauteur;
	/** handle référençable dans Ressource (associe une image). */
	int indexImage;
	/** Largeur portion visible de la scène (ecran) (sert en interne pour le calcul de visibilité). */
	int largeurSceneVisible;
	/** Hauteur portion visible de la scène (ecran) (sert en interne pour le calcul de visibilité). */
	int hauteurSceneVisible;
	/** pointeur generique */
	void * data;

} ElementScene;


/**
* @fn void elementInit(ElementScene *element, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran);
* @brief Initialise un element.
* @param [in, out] element : l'element à initialiser, doit être non null.
* @param type : type d'entité
* @param indexImage : image associée au element (fournie par Ressource).
* @param largeur : largeur du element.
* @param hauteur : hauteur du element.
* @param largeurEcran : largeur de l'ecran (portion visible de la scène).
* @param hauteurEcran : hauteur de l'ecran (portion visible de la scène).
*/
void elementInit(ElementScene *element, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran);

/**
* @fn void elementLibere(ElementScene *element)
* @brief libère proprement un element.
* @param [in, out] element : initialisé
*/
void elementLibere(ElementScene *element);

/**
* @fn void elementSetType(ElementScene *element, int type)
* @brief Affecte le type d'element.
* @param [in, out] element : initialisé
* @param [in] type
*/
void elementSetType(ElementScene *element, int type);

/**
* @fn elementGetType(const ElementScene * element)
* @brief Renvoie le type d'element
* @param [in] element : initialisé
*/
int elementGetType(const ElementScene * element);

/**
* @fn int elementVisible(const ElementScene *element)
* @brief renvoie 1 si l'element est visible (ie. dans la portion visible de la Scene), 0 sinon.
* @param [in] element
*/
int elementVisible(const ElementScene *element);

/**
* @fn int elementGetX(const ElementScene *element)
* @brief renvoie la position en X du element.
* @param [in] element : initialisé
*/
int elementGetX(const ElementScene *element);

/**
* @fn int elementGetY(const ElementScene *element)
* @brief renvoie la position en Y du element.
* @param [in] element : initialisé
*/
int elementGetY(const ElementScene *element);

/**
* @fn void elementSetPosition(ElementScene *element, int x, int y)
* @brief Affecte une nouvelle position au element.
* @param [in, out] element : initialisé
* @param [in] x
* @param [in] y
*/
void elementSetPosition(ElementScene *element, int x, int y);

/**
* @fn void elementSetDirection(ElementScene *element, int vx, int vy)
* @brief Affecte une nouvelle diection à l'élément.
* @param [in, out] element : initialisé
* @param [in] vx
* @param [in] vy
*/
void elementSetDirection(ElementScene *element, float vx, float vy);

/**
* @fn int elementGetImageIndex(const ElementScene *element)
* @brief renvoie le handle de l'image associée au element (handle lisible par Ressource).
* @param [in] element : initialisé
*/
int elementGetImageIndex(const ElementScene *element);

/**
* @fn int elementTestDeCollision(ElementScene * e1, ElementScene *e2);
* @brief Test de la collision entre deux elementsScene
* @param [in] e1 : initialisé
* @param [in] e2 : initialisé
* @return renvoi 1 en cas de collision. 0 sinon
*/
int elementTestDeCollision(const ElementScene * e1,const ElementScene *e2);


/**
* @fn void elementSceneTestDeRegression()
* @brief Effectue tout une serie de test pour vérifier l'intégrité du module
*/
void elementSceneTestDeRegression();


#endif

