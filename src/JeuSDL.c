/**
* @file JeuSDL.c
* @brief Fichier d'implémentation du module JeuSDL
* @author Yann Cortial - Mohamed El Mouctar HAIDARA.
*/
#include "JeuSDL.h"
#include <SDL/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



/*-------------------------------------------------------------------------------------------
 FONCTIONS INTERNES */

float getTempsSecondes()
{
	return (float)clock()/(float)CLOCKS_PER_SEC;
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


	jeu->etatCourantJeu 	= JEU_ETAT_MENU;
	jeu->joueur 			= NULL;

	srand(time(NULL));
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
	char alphaNum;
	Niveau niveau;

	GraphiqueSDL *graphique	 		= &jeu->graphique;
	EntreeSDL *entree				= &jeu->entree;
	Menu *menu						= &jeu->menu;
	int score                       =0;

    float tempsDernierAffichage, tempsDernierDefilementScene, dureeBoucle, debutBoucle;
    /* Période de temps (secondes) entre deux raffraichissements écran */
    float periodeAffichage 			= 1.0f/32.0f;
	float periodeDefilementScene 	= 1.0f/8.0f;

	graphiqueRaffraichit(graphique);

    tempsDernierAffichage			= getTempsSecondes();
	dureeBoucle	 					= 0.0f;

	/***************************************/
	/* Tant que ce n'est pas la fin du Jeu */
	/***************************************/
	while ( continueJeu == 1 )
	{
       	debutBoucle 		= getTempsSecondes();

		/* Sonde les entrées (souris + clavier) : détecte les évènements */
		entreeSonde( entree );

		/* Traitement des Evenements */
		if (entreeFermetureJeu(entree)==1)
			continueJeu 		= 0;


		switch( jeu->etatCourantJeu )
		{

		case JEU_RETOUR_MENU:

				sceneLibere( &jeu->scene );
				jeu->etatCourantJeu 	= JEU_ETAT_MENU;
				menuPrincipal((void*)menu);
				break;

		case JEU_ETAT_JEU:		/*-------------   J E U   ---------------*/

			/* L'utilisateur a appuyé sur ESC */
			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
				toucheDetectee = SDLK_ESCAPE;
			/* L'utilisateur vient de relâcher la touche ESC */
			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==0 && toucheDetectee == SDLK_ESCAPE)
			{
				/*continueJeu	 		= 0;*/
				jeu->etatCourantJeu 	= JEU_RETOUR_MENU;
				toucheDetectee=-1;
			}

            /* Deplacemennt du joueur */
			if (entreeToucheEnfoncee(entree, SDLK_UP) == 1)
				sceneDeplaceVaisseauJoueurHaut( &jeu->scene, dureeBoucle );
			if (entreeToucheEnfoncee(entree, SDLK_DOWN) == 1)
				sceneDeplaceVaisseauJoueurBas( &jeu->scene, dureeBoucle );
        	if (entreeToucheEnfoncee(entree, SDLK_RIGHT)==1)
        	    sceneDeplaceVaisseauJoueurDroite(&jeu->scene, dureeBoucle);
            if (entreeToucheEnfoncee(entree, SDLK_LEFT)==1)
        	    sceneDeplaceVaisseauJoueurGauche(&jeu->scene, dureeBoucle);

            /* Declenchement des tirs */
            if (entreeToucheEnfoncee(entree, SDLK_SPACE)==1)
                toucheDetectee= SDLK_SPACE;
            if (entreeToucheEnfoncee(entree, SDLK_SPACE)==0 && toucheDetectee == SDLK_SPACE)
			{
				sceneJoueurDeclencheTir(&jeu->scene, jeu->joueur, &jeu->ressource);
				toucheDetectee=-1;
			}

			/* Défilement de l'image de fond. */
			if ( (getTempsSecondes() - tempsDernierDefilementScene) >= periodeDefilementScene)
			{
				sceneDefileScene(&jeu->scene);
				tempsDernierDefilementScene = getTempsSecondes();
			}

        	/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
        	if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
        	{
				/* On anime la scène à intervalles réguliers (correspondant au rafraichissement de l'ecran). */
				sceneAnime(&jeu->scene, getTempsSecondes());

        		graphiqueEfface( graphique );
				/*
				*/
				graphiqueAfficheScene( graphique, &jeu->scene );
				/*
				*/
            	graphiqueRaffraichit( graphique );

        		tempsDernierAffichage 	= getTempsSecondes();
        	}

        	/* test de collision */
        	sceneTestDeCollision(&jeu->scene, &score);
        	/* mise à jour du score au cours du jeu */
        	graphiqueSetScore(graphique, score);

        	joueurSetScore(jeu->joueur, score);

			break;

		case JEU_ETAT_MENU:			/*-------------   M E N U   ---------------*/

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
									if (menu->etat == MENU_ETAT_CHOIX_JOUEUR)
									{
										menuSelectionneJoueur(menu, i);
										jeu->joueur = menuGetJoueurChoisi(menu);

									}

									if (menu->etat == MENU_ETAT_CHOIX_NIVEAU)
									{
										menuSelectionneNiveau(menu, i);
										jeu->niveauCourant = menuGetNiveauChoisi(menu);
										if (jeu->niveauCourant != -1)
										{
											jeu->chargementOK = 0;
											jeu->etatCourantJeu = JEU_ETAT_CHARGEMENT_NIVEAU;
										}
									}
									/* On appelle la callback associé à l'élément menu. */
									(menu->elements[i].action)((void*)menu);
									choixMenu = -1;
								}

					} else if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 1)
							menu->elements[i].surligne = 1;
				}

			/* Cas où on doit lire le clavier pour entrer un nom de joueur */
			if (menu->etat == MENU_ETAT_ENTREE_JOUEUR)
			{
				alphaNum = entreeGetAlphaNum(entree);
				if (alphaNum != 0)
				{
					menuSetCaractere(menu, alphaNum);
				}
				if (entreeToucheEnfoncee(entree, SDLK_BACKSPACE) == 1)
					toucheDetectee = SDLK_BACKSPACE;
				if (entreeToucheEnfoncee(entree, SDLK_BACKSPACE) == 0 && toucheDetectee == SDLK_BACKSPACE)
				{
					toucheDetectee = -1;
					menuEffaceCaractere(menu);
				}
				if (entreeToucheEnfoncee(entree, SDLK_RETURN) == 1)
					toucheDetectee = SDLK_RETURN;
				if (entreeToucheEnfoncee(entree, SDLK_RETURN) == 0 && toucheDetectee == SDLK_RETURN)
				{
					toucheDetectee = -1;
					menuSetFinLectureClavier(menu);
					/*graphiquePrepareRenduListeJoueurs(graphique, menu);*/
					jeu->joueur = menuGetJoueurChoisi(menu);
				}
			}

			/* L'utilisateur a appuyé sur ESC */
			if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
				toucheDetectee = SDLK_ESCAPE;
			/* L'utilisateur vient de relâcher la touche ESC */
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
				graphiqueAfficheMenu( graphique, menu );
				/*
				*/
            	graphiqueRaffraichit( graphique );

        		tempsDernierAffichage 	= getTempsSecondes();
        	}

			/* Si le Menu est en état 'Quitter' : on quitte le jeu. */
			if (menu->etat == MENU_ETAT_QUITTER)
				continueJeu = 0;

			break;

		case JEU_ETAT_CHARGEMENT_NIVEAU :	/*--------------	CHARGEMENT D'UN NIVEAU 	-------------------*/

			if (jeu->chargementOK == 0)
			{
				niveau 					= ressourceGetNiveau(&jeu->ressource, jeu->niveauCourant);
				/* Initialisation de la scène */
				sceneInit(&jeu->scene, &jeu->ressource, jeu->graphique.largeur, jeu->graphique.hauteur);
				sceneChargeNiveau(&jeu->scene, &niveau, &jeu->ressource);
				jeu->etatCourantJeu 	= JEU_ETAT_JEU;

                score=joueurGetScore(jeu->joueur);
				graphiqueSetScore(&jeu->graphique, score);

                /* On recupère les caractèristique du vaisseau du joueur pour les donnner à la scene */
                sceneSetVaisseauJoueur(&jeu->scene, jeu->joueur->vaisseau);

				sceneResetHorloge(&jeu->scene, getTempsSecondes());
				tempsDernierDefilementScene = getTempsSecondes();
			}
			/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
        	if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
        	{
        		graphiqueEfface( graphique );

	           	graphiqueRaffraichit( graphique );

        		tempsDernierAffichage 	= getTempsSecondes();
        	}

			break;

		default:break;
		}

		dureeBoucle 		= getTempsSecondes() - debutBoucle;
	}
}


void jeuLibere( JeuSDL *jeu )
{
	ressourceLibere( &jeu->ressource );
	menuLibere( &jeu->menu );
	entreeLibere( &jeu->entree );
	graphiqueLibere( &jeu->graphique );

	SDL_Quit();
}

