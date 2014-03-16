
#ifndef _JEU_H
#define _JEU_H

#include "Ecran.h"
#include "Entree.h"
#include "Ressource.h"
#include "Scene.h"




typedef struct {

	/** Initialise et dispose la fenetre principale */
	Ecran ecran;
	/** Initialise et gère les évènements (clavier, souris ..) */
	Entree entree;
	/** Initialise et gère les ressources du jeu (images, sons, polices) */
	Ressource ressource;
	/** Initialise et gère la scène (ce qui est visible à l'écran) */
	Scene scene;
	
} Jeu;

void jeuInit(Jeu *);
void jeuBoucle(Jeu *);
void jeuLibere(Jeu *);

#endif

