/**
* @file JeuSDL.c
* @brief Fichier d'implémentation du module JeuSDL
* @author
*/
#include "JeuSDL.h"
#include <SDL/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>



float getTempsSecondes()
{
	return (float)clock()/(float)CLOCKS_PER_SEC;
}



void jeuInit(JeuSDL *jeu)
{
	#ifdef JEU_VERBOSE
		printf("BLOCKADE > Initialisation des modules :\n\n");
	#endif

	assert( jeu != NULL );
	assert( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != -1 );

	/* Initialisation du dictionnaire des ressources du jeu */
	ressourceInit(&jeu->ressource);

	/* Initialisation du Menu */
	menuInit(&jeu->menu);

	/* Initialisation fenêtre principale */
	graphiqueInit(&jeu->graphique, &jeu->ressource, &jeu->menu, 1366, 720, "Blockade Runner", GFX_MODE_FENETRE);

	/* Initialisation des entrées souris + clavier */
	entreeInit(&jeu->entree);

	/* Initialisation de la scène */
	sceneInit(&jeu->scene, &jeu->ressource, jeu->graphique.largeur, jeu->graphique.hauteur);

	jeu->etatCourantJeu = JEU_ETAT_MENU;

	#ifdef JEU_VERBOSE
		printf("\nBLOCKADE > initialisation OK.\n\n");
	#endif
}



void jeuBoucle(JeuSDL *jeu)
{
	int continueJeu					= 1;
	GraphiqueSDL *graphique	 		= &jeu->graphique;
	EntreeSDL *entree				= &jeu->entree;
	Menu *menu						= &jeu->menu;

    float tempsDernierAffichage, dureeBoucle, debutBoucle;
    /* Période de temps (secondes) entre deux raffraichissements écran */
    float periodeAffichage = 1.0f/32.0f;

	graphiqueRaffraichit(graphique);

    tempsDernierAffichage	= getTempsSecondes();
	dureeBoucle	 			= 0.0f;

	/***************************************/
	/* Tant que ce n'est pas la fin du Jeu */
	/***************************************/
	while ( continueJeu == 1 )
	{
       	debutBoucle 		= getTempsSecondes();

		/* Sonde les entrées (souris + clavier) pour des évènements */
		entreeSonde( entree );

		/* Traitement des Evenements */
		if (entreeFermetureJeu(entree)==1)
			continueJeu 		= 0;

		
		if ( jeu->etatCourantJeu == JEU_ETAT_NIVEAU )
		{	/* Le jeu est enclenché (Niveau) ... */

			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
				continueJeu	 		= 0;

			if (entreeToucheEnfoncee(entree, SDLK_UP) == 1)
				sceneDeplaceVaisseauJoueurHaut( &jeu->scene, dureeBoucle );
			if (entreeToucheEnfoncee(entree, SDLK_DOWN) == 1)
				sceneDeplaceVaisseauJoueurBas( &jeu->scene, dureeBoucle );
        	if (entreeToucheEnfoncee(entree, SDLK_RIGHT)==1)
        	    sceneDeplaceVaisseauJoueurDroite(&jeu->scene, dureeBoucle);
            if (entreeToucheEnfoncee(entree, SDLK_LEFT)==1)
        	    sceneDeplaceVaisseauJoueurGauche(&jeu->scene, dureeBoucle);
	
        	/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
        	if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
        	{
        		graphiqueEfface( graphique );
				/*
				*/
				graphiqueAfficheScene( graphique, &jeu->scene );
				/*
				*/
            	graphiqueRaffraichit( graphique );

        		tempsDernierAffichage 	= getTempsSecondes();
        	}

		} else{
			/* Le Menu est affiché ... */

			/* on passe au menu les entrées et la durée de la boucle (en secondes) */		
			menuMiseAJour(menu, dureeBoucle);

			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
				continueJeu	 		= 0;

			/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
        	if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
        	{
        		graphiqueEfface( graphique );
				/*
				*/
				graphiqueAfficheMenu( graphique, &jeu->menu );
				/*
				*/
            	graphiqueRaffraichit( graphique );

        		tempsDernierAffichage 	= getTempsSecondes();
        	}
		}
		

		dureeBoucle 		= getTempsSecondes() - debutBoucle;
	}
}


void jeuLibere( JeuSDL *jeu )
{
	ressourceLibere( &jeu->ressource );
	menuLibere( &jeu->menu );
	sceneLibere( &jeu->scene );
	entreeLibere( &jeu->entree );
	graphiqueLibere( &jeu->graphique );

	SDL_Quit();
}

