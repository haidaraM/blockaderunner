#include "Outils.h"

unsigned char rectangleContient(Rectangle *rect, int x, int y)
{
	if ( x >= rect->x && y >= rect->y && x <= (rect->x + rect->largeur) && y <= (rect->y + rect->hauteur))
		return 1;
	return 0;
}

