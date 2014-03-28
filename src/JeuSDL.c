/**
* @file JeuSDL.c
* @brief Fichier d'implémentation du module JeuSDL
* @author Yann Cortial.
*/
#include "JeuSDL.h"
#include <SDL/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>



/*-------------------------------------------------------------------------------------------
 FONCTIONS INTERNES */

float getTempsSecondes()
{
	return (float)clock()/(float)CLOCKS_PER_SEC;
}

void actionneMenu(Menu *menu, int sourisX, int sourisY, unsigned char sourisBoutonGauche)
{
	
}





/*---------------------------------------------------------------------------------------------
 INTERFACE DU MODULE */

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
	menuInit(&jeu->menu, &jeu->ressource);

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
	int i;
	int choixMenu					= -1;
	int toucheDetectee				= -1;
	int continueJeu					= 1;
	int sourisX, sourisY;
	unsigned char sourisBoutonGauche;

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
	
        	/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
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

			/* on passe au menu les entrées souris et la durée de la boucle (en secondes) */		
			sourisX 	= entreeGetSourisX(entree);
			sourisY		= entreeGetSourisY(entree);
			sourisBoutonGauche = entreeBoutonSourisGauche(entree);

			/* Si on est dans l'intro, on incrémente le temps dans le module Menu. */
			if (menu->etat == MENU_ETAT_INTRO)
				menuIntro(menu, dureeBoucle);

			/* Pour chaque élément visible du Menu : on évalue la position souris (surlignage) et le click (activation). */
			for (i=0; i< MENU_NUM_ELEMENTS; i++)
				if (menu->elements[i].visible == 1 && menu->elements[i].actionable == 1)
				{
					if (menu->elements[i].surligne == 1)
					{
						if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 0)
						{
							menu->elements[i].surligne = 0;
							choixMenu = -1;
						} else if (sourisBoutonGauche == 1)
							{
								choixMenu = i;
							} else if (choixMenu == i)
								{
									(menu->elements[i].action)((void*)menu);
									choixMenu = -1;
								}

					} else if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 1)
							menu->elements[i].surligne = 1;
				}	

			/* L'utilisateur a appuyé sur ESC */
			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
				toucheDetectee = SDLK_ESCAPE;
			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==0 && toucheDetectee == SDLK_ESCAPE)
			{
				toucheDetectee = -1;
				menuRetour((void*)menu);
			}

			/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
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

			/* Si le Menu est en état 'Quitter' : on quitte le jeu. */
			if (menu->etat == MENU_ETAT_QUITTER)
				continueJeu = 0;
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

