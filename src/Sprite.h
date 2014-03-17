/**
* @file Sprite.h
* @brief
*/
#ifndef _SPRITE_H
#define _SPRITE_H




#define SPRITE_TYPE_NON_DEFINI					-1
#define SPRITE_TYPE_VAISSEAU_JOUEUR				0



typedef struct
{
	int visible;
	int type;
	int x, y, largeur, hauteur;
	int indexImage;
	int largeurEcran;
	int hauteurEcran;
} Sprite;



void spriteInit(Sprite *sprite, int type, int indexImage, int largeur, int hauteur, int largeurEcran, int hauteurEcran);
void spriteLibere(Sprite *sprite);

int spriteVisible(Sprite *sprite);
int spriteGetX(Sprite *sprite);
int spriteGetY(Sprite *sprite);
void spriteSetPosition(Sprite *sprite, int x, int y);

int spriteGetIndexImage(Sprite *sprite);


#endif

