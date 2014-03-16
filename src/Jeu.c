/**
* @file Jeu.c
* @brief Fichier d'implémentation du module Jeu
* @author
*/
#include "Jeu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>



float getTempsSecondes()
{
	return (float)clock()/(float)CLOCKS_PER_SEC;
}



void jeuInit(Jeu *jeu)
{
	#ifdef JEU_VERBOSE
		printf("BLOCKADE > Initialisation des modules :\n\n");
	#endif
 
	assert( jeu != NULL );
	assert( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != -1 );

	/* Initialisation fenêtre principale */
	ecranInit(&jeu->ecran, 1366, 768, "Jeu : tool test : SDL 1.2 : test 00", ECRAN_MODE_FENETRE);

	/* Initialisation des entrées souris + clavier */
	entreeInit(&jeu->entree);

	/* Initialisation des ressources du jeu */
	ressourceInit(&jeu->ressource);

	/* Initialisation de la scène */
	sceneInit(&jeu->scene, &jeu->ecran, &jeu->ressource);

	#ifdef JEU_VERBOSE
		printf("\nBLOCKADE > initialisation OK.\n\n");
	#endif
}



void jeuBoucle(Jeu *jeu)
{
	int continueJeu			= 1;
	Ecran *ecran	 		= &jeu->ecran;
	Entree *entree			= &jeu->entree;

    float tempsDernierAffichage, dureeBoucle, debutBoucle;
    /* Période de temps (secondes) entre deux raffraichissements écran */
    float periodeAffichage = 1.0f/60.0f;

	ecranRaffraichit(ecran);

    tempsDernierAffichage	= getTempsSecondes();
	dureeBoucle	 			= 0.0f;

	/************************************/
	/* Tant que ce n'est pas la fin ... */
	/************************************/
	while ( continueJeu == 1 )
	{
       	debutBoucle 		= getTempsSecondes();

		/* Sonde les entrées (souris + clavier) pour des évènements */
		entreeSonde( entree );
		if (entreeFermetureJeu(entree)==1 || entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
			continueJeu	 		= 0;
		
		if (entreeToucheEnfoncee(entree, SDLK_UP) == 1)
			sceneDeplaceVaisseauJoueurHaut( &jeu->scene, dureeBoucle );
		if (entreeToucheEnfoncee(entree, SDLK_DOWN) == 1)
			sceneDeplaceVaisseauJoueurBas( &jeu->scene, dureeBoucle );
			
        /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
        if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
        {
        	ecranEfface( ecran );
        
			sceneAffiche( &jeu->scene );    

            /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans a boucle) */
            ecranRaffraichit( ecran );

        	tempsDernierAffichage 	= getTempsSecondes();
        }

		dureeBoucle 		= getTempsSecondes() - debutBoucle;
	}
}


void jeuLibere( Jeu *jeu )
{
	sceneLibere( &jeu->scene);
	ressourceLibere( &jeu->ressource);
	entreeLibere( &jeu->entree );
	ecranLibere( &jeu->ecran );

	SDL_Quit();
}

