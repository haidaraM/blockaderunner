#ifndef _ENTREE_H
#define _ENTREE_H

#include "SDL/SDL.h"


/* Note :
	http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
	gives SDL keys 
*/


typedef struct
{
	unsigned char fermetureJeu;
	int nombreTouches;
	unsigned char *clavier;
	int sourisX, sourisY;
	unsigned char boutonSourisGauche;
	unsigned char boutonSourisDroit;
} Entree;



void entreeInit(Entree *entree);
void entreeLibere(Entree *entree);

void entreeSonde(Entree *entree);
unsigned char entreeFermetureJeu(Entree *entree);
unsigned char entreeToucheEnfoncee(Entree *entree, SDLKey touche);
unsigned char entreeBoutonSourisGauche(Entree *entree);
unsigned char entreeBoutonSourisDroit(Entree *entree);
int entreeGetSourisX(Entree *entree);
int entreeGetSourisY(Entree *entree);

#endif 

