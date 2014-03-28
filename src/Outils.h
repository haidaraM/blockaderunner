#ifndef _OUTILS_H
#define _OUTILS_H

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

#endif

