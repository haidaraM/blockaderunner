/**
* @file Sprite.h
* @brief
*
*  Une instance d'un type donné (élément du Jeu) : vaisseau, asteroide, etc. Caractérisé par des liens sur des ressources prédéfinies (images, sons). 
*  Tous les Sprites sont gérés par la Scene, qui décident notamment lesquels sont visibles, créés, détruits.
*/
#ifndef _SPRITE_H
#define _SPRITE_H



#define SPRITE_TYPE_NON_DEFINI					-1
#define SPRITE_TYPE_VAISSEAU_JOUEUR				0



typedef struct
{
	/** booléen : le sprite est dans la portion visible de la scène (ecran) ou pas. */
	int visible;
	/** type d'entité. */
	int type;
	/** position en X sur la scène. */
	int x;
	/** position en Y sur la scène. */
	int y;
	/** largeur du sprite. */
	int largeur;
	/** hauteur du sprite. */
	int hauteur;
	/** handle référençable dans Ressource (associe une image). */
	int indexImage;
	/** Largeur portion visible de la scène (ecran). */
	int largeurEcran;
	/** Hauteur portion visible de la scène (ecran). */
	int hauteurEcran;
} Sprite;


/**
* @brief Initialise un sprite.
* @param sprite[in, out] : le sprite à initialiser, doit être non null.
* @param type : type d'entité 
* @param indexImage : image associée au sprite (fournie par Ressource).
* @param largeur : largeur du sprite.
* @param hauteur : hauteur du sprite.
* @param largeurEcran : largeur de l'ecran (portion visible de la scène).
* @param largeurEcran : hauteur de l'ecran (portion visible de la scène).
*/
void spriteInit(Sprite *sprite, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran);
/**
* @brief libère proprement un sprite.
*/
void spriteLibere(Sprite *sprite);
/**
* @brief renvoie 1 si le sprite est visible (ie. dans la portion visible de la Scene), 0 sinon.
*/
int spriteVisible(const Sprite *sprite);
/**
* @brief renvoie la position en X du sprite.
*/
int spriteGetX(const Sprite *sprite);
/**
* @brief renvoie la position en Y du sprite.
*/
int spriteGetY(const Sprite *sprite);
/**
* @brief Affecte une nouvelle position au sprite.
*/
void spriteSetPosition(Sprite *sprite, int x, int y);
/**
* @brief renvoie le handle de l'image associée au sprite (handle lisible par Ressource).
*/
int spriteGetIndexImage(const Sprite *sprite);


#endif

