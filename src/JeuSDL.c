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

    /* Initialisation du système audio */
    audioInit(&jeu->audio, &jeu->ressource);

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
    int sonTir=-1; /* Variable utilisée pour jouer un son lors d'un tir */
    Joueur * copieJoueur=NULL;

    GraphiqueSDL *graphique	 		= &jeu->graphique;
    EntreeSDL *entree				= &jeu->entree;
    Menu *menu						= &jeu->menu;

    float tempsDernierAffichage, tempsDernierDefilementScene, dureeBoucle, debutBoucle;
    /* Période de temps (secondes) entre deux raffraichissements écran */
    float periodeAffichage 			= 1.0f/60.0f;
    float periodeDefilementScene 	= 1.0f/24.0f;/*1.0f/12.0f;*/

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
        if (entreeFermetureJeu(entree)==1)
            continueJeu 		= 0;


        switch( jeu->etatCourantJeu )
        {

        case JEU_RETOUR_MENU:

            sceneLibere( &jeu->scene );
            free(copieJoueur);
            jeu->etatCourantJeu 	= JEU_ETAT_MENU;
            menuPrincipal((void*)menu);
            /* on arrete le son de la scene */
            audioStopSon(&jeu->audio, RESS_SON_AMBIENCE);
            break;

        case JEU_ETAT_JEU:		/*-------------   J E U   ---------------*/

            /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
            if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
            {
                /* On anime la scène à intervalles réguliers (correspondant au rafraichissement de l'ecran de sorte que les incréments soient suffisament significatifs en pixels). */
                sceneAnime(&jeu->scene, getTempsSecondes());

                graphiqueEfface( graphique );
                /*
                */
                graphiqueAfficheScene( graphique, &jeu->scene );
                /*
                */
                graphiqueRaffraichit( graphique );

                tempsDernierAffichage 	= getTempsSecondes();

                audioJoueScene(&jeu->audio, &jeu->scene);
            }

            /* L'utilisateur a appuyé sur ESC */
            if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==1)
                toucheDetectee = SDLK_ESCAPE;
            /* L'utilisateur vient de relâcher la touche ESC */
            if (entreeToucheEnfoncee(entree, SDLK_ESCAPE)==0 && toucheDetectee == SDLK_ESCAPE)
            {
                /*continueJeu	 		= 0;*/
                jeu->etatCourantJeu 	= JEU_RETOUR_MENU;
                audioJoueSon(&jeu->audio, RESS_SON_MENU_BACK);
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
                sonTir=sceneJoueurDeclencheTir(&jeu->scene);
                /* Je voulais faire pareil avec les tirs ennemis mais ça ne marche pas d'abord*/
                switch(sonTir)
                {
                case 0:
                    audioJoueSon(&jeu->audio, RESS_SON_TIR_LASER);
                    break;
                case 1:
                    audioJoueSon(&jeu->audio, RESS_SON_MISSILE);
                    break;
                default :
                    audioJoueSon(&jeu->audio, RESS_SON_ERREUR);
                    break;
                }

                toucheDetectee=-1;
            }

            /* Choix de l'arme */
            /* Laser */
            if (entreeToucheEnfoncee(entree, SDLK_F5)==1)
                toucheDetectee= SDLK_F5;
            if(entreeToucheEnfoncee(entree, SDLK_F5)==0 && toucheDetectee == SDLK_F5)
            {
                joueurSetArmeSelectionne(copieJoueur, ARME_LASER);
                audioJoueSon(&jeu->audio, RESS_SON_CHANGE_ARME);
                toucheDetectee=-1;
            }
            /* Missile */
            if (entreeToucheEnfoncee(entree, SDLK_F6)==1)
                toucheDetectee= SDLK_F6;
            if(entreeToucheEnfoncee(entree, SDLK_F6)==0 && toucheDetectee == SDLK_F6)
            {
                joueurSetArmeSelectionne(copieJoueur, ARME_MISSILE);
                audioJoueSon(&jeu->audio, RESS_SON_CHANGE_ARME);
                toucheDetectee=-1;
            }

			/* Si le joueur a gagné un bonus missile OU tiré un missile ==> mettre a jour l'affichage des munitions dans graphique */
			if (jeu->scene.evenements.joueur_bonus_missile == 1  ||  jeu->scene.evenements.joueur_tir_missile == 1)
				graphiqueSetMunitions(graphique, sceneGetMunitionMissileJoueur(&jeu->scene));

            /* Défilement de l'image de fond. */
            if ( (getTempsSecondes() - tempsDernierDefilementScene) >= periodeDefilementScene)
            {
                if(sceneDefileScene(&jeu->scene))
                {
                    /* si  on arrive à la fin du niveau, on retourne au menu */
                    jeu->etatCourantJeu = JEU_RETOUR_MENU;
                    /* Eventuellement (si le joueur joue son niveau max) : on met à jour la progression du  joueur & on sauve sur disque la progression du joueur */
                    if(jeu->niveauCourant==joueurGetProgression(jeu->joueur))
                    {
                        joueurSetProgression(jeu->joueur);
                        joueurSetScore(jeu->joueur, joueurGetScore(jeu->scene.joueur));/* ici on récupère le score réalisé par la copie du Joueur dans Scene pour le sauvegarder. */
                        ressourceSauveJoueurs(&jeu->ressource);
                    }
                    /* on affiche le texte de fin de niveau */
                    graphiqueAfficheFinNiveau(graphique);
                }
                tempsDernierDefilementScene = getTempsSecondes();
            }


            if(sceneTestVaisseauMort(&jeu->scene))
            {
                /* arret du son de la scene */
                audioStopSon(&jeu->audio, RESS_SON_AMBIENCE);
                audioJoueSon(&jeu->audio, RESS_SON_MORT);
                graphiqueAfficheMort(graphique);
                jeu->etatCourantJeu=JEU_RETOUR_MENU;
            }

            break;


        case JEU_ETAT_MENU:			/*-------------   M E N U   ---------------*/

            /* on joue le son du menu */
            audioJoueSon(&jeu->audio, RESS_SON_MENU);
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
                        }
                        else if (sourisBoutonGauche == 1)
                        {
                            choixMenu = i;
                        }
                        else if (choixMenu == i)
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

                            audioJoueSon(&jeu->audio, RESS_SON_MENU_VALIDATE);

                        }

                    }
                    else if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 1)
                    {
                        menu->elements[i].surligne = 1;
                        audioJoueSon(&jeu->audio, RESS_SON_MENU_SURVOL);
                    }
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
                audioJoueSon(&jeu->audio, RESS_SON_MENU_BACK);
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
                copieJoueur=joueurCopieJoueur(jeu->joueur);
                sceneInit(&jeu->scene, &jeu->ressource, copieJoueur, jeu->graphique.largeur, jeu->graphique.hauteur);
                sceneChargeNiveau(&jeu->scene, &niveau, &jeu->ressource);
				graphiqueSetMunitions(graphique, sceneGetMunitionMissileJoueur(&jeu->scene));

                jeu->etatCourantJeu 	= JEU_ETAT_JEU;
                sceneResetHorloge(&jeu->scene, getTempsSecondes());
                tempsDernierDefilementScene = getTempsSecondes();
            }
            /* (affichage vide). */
            if ( (getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage)
            {
                graphiqueEfface( graphique );

                graphiqueRaffraichit( graphique );

                tempsDernierAffichage 	= getTempsSecondes();
            }

            /* On arrete le son du menu et on joue le son de la scene */
            audioStopSon(&jeu->audio, RESS_SON_MENU);
            audioJoueSon(&jeu->audio, RESS_SON_AMBIENCE);

            break;

        default:
            break;
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
    audioLibere(&jeu->audio);
    SDL_Quit();
}

