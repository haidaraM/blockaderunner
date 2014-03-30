/**
* @file fichier d'implementation du module EntreeSDL
* @brief
*/
#include "EntreeSDL.h"
#include <assert.h>
#include <stdlib.h>



void entreeInit(EntreeSDL *entree)
{
	int i;
	assert( entree != NULL );

	#ifdef JEU_VERBOSE
		printf("Entrées (clavier, souris) :\n    initialisation ...\n");
	#endif

	entree->fermetureJeu 		= 0;
	entree->nombreTouches		= 0;
	entree->clavier				= 0;
	entree->toucheDetectee		= -1;
	entree->toucheRelachee 		= -1;
	entree->sourisX				= 0;
	entree->sourisY 			= 0;
	entree->boutonSourisGauche	= 0;
	entree->boutonSourisDroit	= 0;

	/* On recupère le nombre de touches du clavier géré par SDL */
	SDL_GetKeyState(&entree->nombreTouches);
	entree->clavier 			= (unsigned char*)malloc( entree->nombreTouches * sizeof(unsigned char) );
	assert( entree->clavier != NULL );

	/* On initialise toutes les touches du clavier à zero (non-enfoncée) */
	for (i=0; i< entree->nombreTouches; i++)
		entree->clavier[i]			= 0;

	/* On positionne la souris en haut à gauche de la fenêtre */
	SDL_WarpMouse(0, 0);

	#ifdef JEU_VERBOSE
		printf("    initialisation OK.\n");
	#endif
}

void entreeLibere(EntreeSDL *entree)
{
	free(entree->clavier);
}



void entreeSonde(EntreeSDL *entree)
{
	SDL_Event event;
	entree->toucheRelachee 									= -1;

	/* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
	while ( SDL_PollEvent( &event ) )
	{
		/* Si l'utilisateur a cliqué sur la croix de fermeture */
		if ( event.type == SDL_QUIT )
			entree->fermetureJeu 							= 1;

		/* Si l'utilisateur a appuyé sur une touche */
		if ( event.type == SDL_KEYDOWN )
		{
			entree->clavier[event.key.keysym.sym] 			= 1;
			if (entree->toucheDetectee == -1)
			{
				entree->toucheDetectee								= event.key.keysym.sym;
			}
		}
		/* Si l'utilisateur a relâché une touche */
		if ( event.type == SDL_KEYUP )
		{
			entree->clavier[event.key.keysym.sym] 			= 0;
			if (entree->toucheDetectee == event.key.keysym.sym)
			{
				entree->toucheRelachee								= entree->toucheDetectee;
			}
			entree->toucheDetectee									= -1;
		}

		/* Si l'utilisateur a clické sur un bouton de souris */
		if ( event.type == SDL_MOUSEBUTTONDOWN )
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				entree->boutonSourisGauche					= 1;
			if (event.button.button == SDL_BUTTON_RIGHT)
				entree->boutonSourisDroit 					= 1;
		}

		/* Si l'utilisateur a relâché un bouton de souris */
		if ( event.type == SDL_MOUSEBUTTONUP )
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				entree->boutonSourisGauche					= 0;
			if (event.button.button == SDL_BUTTON_RIGHT)
				entree->boutonSourisDroit 					= 0;
		}

		/* Si l'utilisateur a déplacé la souris */
		if ( event.type == 	SDL_MOUSEMOTION )
		{
			entree->sourisX 								= (int)event.motion.x;
			entree->sourisY 								= (int)event.motion.y;
		}
	}
}


unsigned char entreeFermetureJeu(const EntreeSDL *entree)
{
	return entree->fermetureJeu;
}
unsigned char entreeToucheEnfoncee(const EntreeSDL *entree, SDLKey touche)
{
	return entree->clavier[touche];
}
char entreeGetAlphaNum(const EntreeSDL *entree)
{
	if (entree->toucheRelachee >= SDLK_a && entree->toucheRelachee <= SDLK_z)
		return 'a' + (entree->toucheRelachee - SDLK_a);

	if (entree->toucheRelachee >= SDLK_KP0 && entree->toucheRelachee <= SDLK_KP9)
		return '0' + (entree->toucheRelachee - SDLK_KP0);

	return 0;
}
unsigned char entreeBoutonSourisGauche(const EntreeSDL *entree)
{
	return entree->boutonSourisGauche;
}
unsigned char entreeBoutonSourisDroit(const EntreeSDL *entree)
{
	return entree->boutonSourisDroit;
}
int entreeGetSourisX(const EntreeSDL *entree)
{
	return entree->sourisX;
}
int entreeGetSourisY(const EntreeSDL *entree)
{
	return entree->sourisY;
}


