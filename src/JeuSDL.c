/**
* @file JeuSDL.c
* @brief Fichier d'implémentation du module JeuSDL.
* @author Yann Cortial - Mohamed El Mouctar HAIDARA.
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "JeuSDL.h"
#include "Scene.h"


/*------------- INTERFACE DU MODULE --------------------------- */

void jeuInit(JeuSDL *jeu)
{
    srand((unsigned int) time(NULL));

#ifdef JEU_VERBOSE
    printf("BLOCKADE > Initialisation des modules :\n\n");
#endif

    assert(jeu != NULL);
    assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != -1);

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


    jeu->etatCourantJeu = JEU_ETAT_MENU_PRINCIPAL;
    jeu->joueur = NULL;

#ifdef JEU_VERBOSE
    printf("\nBLOCKADE > initialisation OK.\n\n");
#endif
}


void jeuBoucle(JeuSDL *jeu)
{
    int i;
    int choixMenu = -1;
    int toucheDetectee = -1;
    int continueJeu = 1;
    int sourisX, sourisY;
    unsigned char sourisBoutonGauche;
    char alphaNum;
    Niveau niveau;
    Joueur *copieJoueur = NULL;

    GraphiqueSDL *graphique = &jeu->graphique;
    EntreeSDL *entree = &jeu->entree;
    Menu *menu = &jeu->menu;


    float tempsDernierAffichage, tempsDernierDefilementScene, dureeBoucle, debutBoucle;
    /* Période de temps en secondes entre deux raffraichissements écran : Framerate. */
    float periodeAffichage = 1.0f / 60.0f;
    float periodeDefilementScene = 1.0f / 24.0f;

    graphiqueRaffraichit(graphique);

    tempsDernierAffichage = getTempsSecondes();
    dureeBoucle = 0.0f;

    /***************************************/
    /* Tant que ce n'est pas la fin du Jeu */
    /***************************************/
    while (continueJeu == 1) {
        debutBoucle = getTempsSecondes();

        /* Sonde les entrées (souris + clavier) : détecte les évènements */
        entreeSonde(entree);
        if (entreeFermetureJeu(entree) == 1)
            continueJeu = 0;


        switch (jeu->etatCourantJeu) {

            /*-------------   M E N U   ---------------*/
            case JEU_ETAT_MENU_PRINCIPAL:

                /* on joue le son du menu */
                audioJoueSon(&jeu->audio, RESS_SON_MENU);
                /* on passe au menu les entrées souris et la durée de la boucle (en secondes) */
                sourisX = entreeGetSourisX(entree);
                sourisY = entreeGetSourisY(entree);
                sourisBoutonGauche = entreeBoutonSourisGauche(entree);
                /* Si on est dans l'intro, on incrémente le temps dans le module Menu. */
                if (menu->etat == MENU_ETAT_INTRO)
                    menuIntro(menu, dureeBoucle);

                /* Pour chaque élément visible du Menu : on évalue la position souris (surlignage) et le click (activation). */
                for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                    /* on ne s'interesse qu'aux éléments-menu actionables (cliquables) */
                    if (menu->elements[i].visible == 1 && menu->elements[i].actionable == 1) {
                        /* Si l'élément est déjà surligné */
                        if (menu->elements[i].surligne == 1) {
                            /* Si la souris n'est pas sur l'élément alors on ne le rend plus surligné */
                            if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 0) {
                                menu->elements[i].surligne = 0;
                                choixMenu = -1;
                            }/* Sinon : si le bouton souris est enfoncé alors on repère le choix (clic) du joueur par la variable choixMenu. */
                            else if (sourisBoutonGauche == 1) {
                                choixMenu = i;
                            }
                                /* Sinon (ie.le bouton souris n'est plus enfoncé)  ... */
                            else if (choixMenu ==
                                     i)                        /* ... ici le joueur vient de relacher le souris (donc a cliqué) sur l'élément */
                            {
                                if (menu->etat == MENU_ETAT_CHOIX_JOUEUR) {
                                    menuSelectionneJoueur(menu, i);
                                    jeu->joueur = menuGetJoueurChoisi(menu);
                                }
                                if (menu->etat == MENU_ETAT_CHOIX_NIVEAU) {
                                    menuSelectionneNiveau(menu, i);
                                    jeu->niveauCourant = menuGetNiveauChoisi(menu);
                                    if (jeu->niveauCourant != -1) {
                                        jeu->chargementOK = 0;
                                        jeu->etatCourantJeu = JEU_ETAT_CHARGEMENT_NIVEAU;
                                    }
                                }
                                /* On appelle la callback associé à l'élément menu. */
                                (menu->elements[i].action)((void *) menu);
                                choixMenu = -1;
                                audioJoueSon(&jeu->audio, RESS_SON_MENU_VALIDATE);
                            }
                        }/* sinon : l'élément n'est pas surligné mais la souris est dessus : on le surligne */
                        else if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 1) {
                            menu->elements[i].surligne = 1;
                            audioJoueSon(&jeu->audio, RESS_SON_MENU_SURVOL);
                        }
                    }
                }

                /* Cas où on doit lire le clavier pour entrer un nom de joueur */
                if (menu->etat == MENU_ETAT_ENTREE_JOUEUR) {
                    alphaNum = entreeGetAlphaNum(entree);
                    if (alphaNum != 0) {
                        menuSetCaractere(menu, alphaNum);
                    }
                    if (entreeToucheEnfoncee(entree, SDLK_BACKSPACE) == 1) {
                        toucheDetectee = SDLK_BACKSPACE;
                    }
                    if (entreeToucheEnfoncee(entree, SDLK_BACKSPACE) == 0 && toucheDetectee == SDLK_BACKSPACE) {
                        toucheDetectee = -1;
                        menuEffaceCaractere(menu);
                    }
                    if (entreeToucheEnfoncee(entree, SDLK_RETURN) == 1) {
                        toucheDetectee = SDLK_RETURN;
                    }
                    if (entreeToucheEnfoncee(entree, SDLK_RETURN) == 0 && toucheDetectee == SDLK_RETURN) {
                        toucheDetectee = -1;
                        menuSetFinLectureClavier(menu);
                        graphiquePrepareRenduListeJoueurs(graphique, menu);
                        jeu->joueur = menuGetJoueurChoisi(menu);
                    }
                }

                /* L'utilisateur a appuyé sur ESC */
                if (entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 1)
                    toucheDetectee = SDLK_ESCAPE;
                /* L'utilisateur vient de relâcher la touche ESC */
                if (entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 0 && toucheDetectee == SDLK_ESCAPE) {
                    toucheDetectee = -1;
                    audioJoueSon(&jeu->audio, RESS_SON_MENU_BACK);
                    menuRetour((void *) menu);
                }

                /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
                if ((getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage) {
                    graphiqueEfface(graphique);
                    /*
                    */
                    graphiqueAfficheMenu(graphique, menu);
                    /*
                    */
                    graphiqueRaffraichit(graphique);

                    tempsDernierAffichage = getTempsSecondes();
                }

                /* Si le Menu est en état 'Quitter' : on quitte le jeu. */
                if (menu->etat == MENU_ETAT_QUITTER)
                    continueJeu = 0;

                break; /* JEU_ETAT_MENU_PRINCIPAL */

                /* --------- RETOUR au MENU PRINCIPAL : quand le joueur selectionne cette option lors de la pause -------------- */
            case JEU_RETOUR_MENU_PRINCIPAL:
                /* liberation des differents elements initialisés */
                sceneLibere(&jeu->scene);
                free(copieJoueur);
                jeu->etatCourantJeu = JEU_ETAT_MENU_PRINCIPAL;
                menuPrincipal((void *) menu);
                /* on arrete le son de la scene */
                audioStopSon(&jeu->audio, RESS_SON_AMBIENCE);
                break; /* break JEU_RETOUR_MENU_PRINCIPAL */

                /*--------------	CHARGEMENT D'UN NIVEAU 	-------------------*/
            case JEU_ETAT_CHARGEMENT_NIVEAU :

                if (jeu->chargementOK == 0) {
                    niveau = ressourceGetNiveau(&jeu->ressource, jeu->niveauCourant);

                    /* Initialisation de la scène avec une copie du Joueur courant */
                    copieJoueur = joueurCopieJoueur(jeu->joueur);
                    sceneInit(&jeu->scene, &jeu->ressource, copieJoueur, jeu->graphique.largeur,
                              jeu->graphique.hauteur);

                    /* Chargement du niveau dans la scene */
                    sceneChargeNiveau(&jeu->scene, &niveau);

                    graphiqueSetMunitions(graphique, sceneGetMunitionMissileJoueur(&jeu->scene));

                    jeu->etatCourantJeu = JEU_ETAT_JEU;
                    sceneResetHorloge(&jeu->scene, getTempsSecondes());
                    tempsDernierDefilementScene = getTempsSecondes();
                }
                /* (affichage vide). */
                if ((getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage) {
                    graphiqueEfface(graphique);

                    graphiqueRaffraichit(graphique);

                    tempsDernierAffichage = getTempsSecondes();
                }

                /* On arrete le son du menu et on joue le son de la scene */
                audioStopSon(&jeu->audio, RESS_SON_MENU);
                audioJoueSon(&jeu->audio, RESS_SON_AMBIENCE);
                break; /* break JEU_ETAT_CHARGEMENT_NIVEAU */


            case JEU_ETAT_JEU:        /*-------------   J E U   ---------------*/

                /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche et anime. */
                if ((getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage) {
                    /* On anime la scène à intervalles réguliers (correspondant au rafraichissement de l'ecran de sorte
                    que les incréments soient suffisament significatifs en pixels). */
                    sceneAnime(&jeu->scene, getTempsSecondes());

                    sceneMAJAngleRotation(&jeu->scene);

                    graphiqueEfface(graphique);
                    /*
                    */
                    graphiqueAfficheScene(graphique, &jeu->scene);
                    /* */
                    graphiqueRaffraichit(graphique);

                    /* suppression des explosions terminées */
                    sceneSupprimeExplosion(&jeu->scene);

                    tempsDernierAffichage = getTempsSecondes();
                }

                /* Joue les sons dont le flag est à un */
                audioJoueScene(&jeu->audio, &jeu->scene);

                /* ----------- Partie pour le retour menu pause ------------------- */
                /* L'utilisateur a appuyé sur ESC */
                if (entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 1)
                    toucheDetectee = SDLK_ESCAPE;
                /* L'utilisateur vient de relâcher la touche ESC */
                if (entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 0 && toucheDetectee == SDLK_ESCAPE) {
                    jeu->etatCourantJeu = JEU_ETAT_PAUSE;
                    audioJoueSon(&jeu->audio, RESS_SON_MENU_BACK);
                    menuPause(menu);
                    toucheDetectee = -1;
                }

                /* Deplacemennt du joueur
                 Déplacement en diagonale possible */
                if (entreeToucheEnfoncee(entree, SDLK_UP) == 1)
                    sceneDeplaceVaisseauJoueurHaut(&jeu->scene, dureeBoucle);
                if (entreeToucheEnfoncee(entree, SDLK_DOWN) == 1)
                    sceneDeplaceVaisseauJoueurBas(&jeu->scene, dureeBoucle);
                if (entreeToucheEnfoncee(entree, SDLK_RIGHT) == 1)
                    sceneDeplaceVaisseauJoueurDroite(&jeu->scene, dureeBoucle);
                if (entreeToucheEnfoncee(entree, SDLK_LEFT) == 1)
                    sceneDeplaceVaisseauJoueurGauche(&jeu->scene, dureeBoucle);

                /* Declenchement des tirs */
                if (entreeToucheEnfoncee(entree, SDLK_SPACE) == 1)
                    toucheDetectee = SDLK_SPACE;
                if (entreeToucheEnfoncee(entree, SDLK_SPACE) == 0 && toucheDetectee == SDLK_SPACE) {
                    sceneJoueurDeclencheTir(&jeu->scene);
                    toucheDetectee = -1;
                }

                /* Choix de l'arme */
                /* Laser */
                if (entreeToucheEnfoncee(entree, SDLK_F5) == 1)
                    toucheDetectee = SDLK_F5;
                if (entreeToucheEnfoncee(entree, SDLK_F5) == 0 && toucheDetectee == SDLK_F5) {
                    joueurSetArmeSelectionne(copieJoueur, ARME_LASER);
                    audioJoueSon(&jeu->audio, RESS_SON_CHANGE_ARME);
                    toucheDetectee = -1;
                }
                /* Missile */
                if (entreeToucheEnfoncee(entree, SDLK_F6) == 1)
                    toucheDetectee = SDLK_F6;
                if (entreeToucheEnfoncee(entree, SDLK_F6) == 0 && toucheDetectee == SDLK_F6) {
                    joueurSetArmeSelectionne(copieJoueur, ARME_MISSILE);
                    audioJoueSon(&jeu->audio, RESS_SON_CHANGE_ARME);
                    toucheDetectee = -1;
                }

                /* Si le joueur a gagné un bonus missile OU tiré un missile ==> mettre a jour l'affichage des munitions dans graphique */
                if (jeu->scene.evenements.joueur_bonus_missile == 1 || jeu->scene.evenements.joueur_tir_missile == 1)
                    graphiqueSetMunitions(graphique, sceneGetMunitionMissileJoueur(&jeu->scene));

                /* Défilement de l'image de fond. */
                if ((getTempsSecondes() - tempsDernierDefilementScene) >= periodeDefilementScene) {
                    if (sceneDefileScene(&jeu->scene)) {
                        /* si  on arrive à la fin du niveau, on retourne au menu */
                        jeu->etatCourantJeu = JEU_RETOUR_MENU_PRINCIPAL;
                        /* Eventuellement (si le joueur joue son niveau max) : on met à jour la progression du  joueur
                        & on sauve sur disque la progression du joueur */
                        if (jeu->niveauCourant == joueurGetProgression(jeu->joueur)) {
                            /* ici on récupère le score réalisé par la copie du Joueur dans Scene pour le sauvegarder (plus un Bonus). */
                            joueurSetScore(jeu->joueur, joueurGetScore(jeu->scene.joueur));
                            joueurSetProgression(jeu->joueur);/* on avance la progression du joueur (acces au niveau suivant débloqué)*/
                            ressourceSauveJoueurs(&jeu->ressource);
                        }
                        /* on joue un son */
                        audioJoueSon(&jeu->audio, RESS_SON_FIN_NIVEAU);
                        /* on affiche le texte de fin de niveau */
                        if (jeu->niveauCourant < RESS_NUM_NIVEAUX - 1)
                            graphiqueAfficheFinNiveau(graphique);
                        else graphiqueAfficheVictoire(graphique);
                    }
                    tempsDernierDefilementScene = getTempsSecondes();
                }


                if (sceneTestVaisseauMort(&jeu->scene)) {
                    /* arret du son de la scene */
                    audioStopSon(&jeu->audio, RESS_SON_AMBIENCE);
                    audioJoueSon(&jeu->audio, RESS_SON_MORT);
                    /* affichage du msg */
                    graphiqueAfficheMort(graphique);
                    jeu->etatCourantJeu = JEU_RETOUR_MENU_PRINCIPAL;
                }
                break; /* break JEU_ETAT_JEU */

                /* -------------------- PAUSE --------------------- */
            case JEU_ETAT_PAUSE :
                audioPauseSon(&jeu->audio, RESS_SON_AMBIENCE);
                /* Arret des deplacements et des animations */
                scenePause(&jeu->scene);

                /* on passe au menu les entrées souris et la durée de la boucle (en secondes) */
                sourisX = entreeGetSourisX(entree);
                sourisY = entreeGetSourisY(entree);
                sourisBoutonGauche = entreeBoutonSourisGauche(entree);

                for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                    /* on ne s'interesse qu'aux éléments-menu actionables (cliquables) */
                    if (menu->elements[i].visible == 1 && menu->elements[i].actionable == 1) {
                        /* Si l'élément est déjà surligné */
                        if (menu->elements[i].surligne == 1) {
                            /* Si la souris n'est pas sur l'élément alors on ne le rend plus surligné */
                            if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 0) {
                                menu->elements[i].surligne = 0;
                                choixMenu = -1;
                            }
                                /* Sinon : si le bouton souris est enfoncé alors on repère le choix (clic) du joueur
                                  par la variable choixMenu. */
                            else if (sourisBoutonGauche == 1) {
                                choixMenu = i;
                            }
                                /* Sinon (ie.le bouton souris n'est plus enfoncé)  ... */
                            else if (choixMenu == i) {
                                /* ... ici le joueur vient de relacher le souris (donc a cliqué) sur l'élément */
                                /* On appelle la callback associé à l'élément menu. */
                                (menu->elements[i].action)((void *) menu);
                                choixMenu = -1;
                                audioJoueSon(&jeu->audio, RESS_SON_MENU_VALIDATE);
                            }
                        }
                            /* sinon : l'élément n'est pas surligné mais la souris est dessus : on le surligne */
                        else if (rectangleContient(&menu->elements[i].rect, sourisX, sourisY) == 1) {
                            menu->elements[i].surligne = 1;
                            audioJoueSon(&jeu->audio, RESS_SON_MENU_SURVOL);
                        }
                    }
                }


                if (menu->etat == MENU_ETAT_QUITTER)
                    continueJeu = 0;
                else if (menu->etat == MENU_ETAT_REJOUER) {
                    /* liberation de la scene : elle sera reinitialisée dans JEU_ETAT_CHARGEMENT_NIVEAU*/
                    sceneLibere(&jeu->scene);
                    free(copieJoueur);
                    /* changement de l'etat du jeu */
                    jeu->etatCourantJeu = JEU_ETAT_CHARGEMENT_NIVEAU;
                    /* On enleve le son dans l'etat pause */
                    audioReprendSon(&jeu->audio, RESS_SON_AMBIENCE);
                    /* On l'arrete. JEU_ETAT_CHARGEMENT_NIVEAU se chargera de le lancer */
                    audioStopSon(&jeu->audio, RESS_SON_AMBIENCE);
                }
                else if (menu->etat == MENU_ETAT_PAUSE_RETOUR_MENU_PRINCIPAL) {
                    jeu->etatCourantJeu = JEU_RETOUR_MENU_PRINCIPAL;
                }

                /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge : on affiche. */
                if ((getTempsSecondes() - tempsDernierAffichage) >= periodeAffichage) {
                    graphiqueAfficheMenu(graphique, menu);

                    graphiqueRaffraichit(graphique);

                    tempsDernierAffichage = getTempsSecondes();
                }
                /* ----------- retour au jeu ------------------- */
                /* L'utilisateur a appuyé sur echap */
                if (entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 1)
                    toucheDetectee = SDLK_ESCAPE;
                /* L'utilisateur vient de relâcher la touche echap ou a choisi l'option reprendre dans le menu*/
                if ((entreeToucheEnfoncee(entree, SDLK_ESCAPE) == 0 && toucheDetectee == SDLK_ESCAPE) ||
                    menu->etat == MENU_ETAT_REPRENDRE) {
                    jeu->etatCourantJeu = JEU_ETAT_JEU;
                    audioReprendSon(&jeu->audio, RESS_SON_AMBIENCE);
                    audioJoueSon(&jeu->audio, RESS_SON_MENU_BACK);
                    toucheDetectee = -1;
                }

                break; /* break JEU_ETAT_PAUSE */

            default:
                break;
        }

        dureeBoucle = getTempsSecondes() - debutBoucle;
    } /* FIn du while ( continueJeu == 1 ) */
}


void jeuLibere(JeuSDL *jeu)
{
    ressourceLibere(&jeu->ressource);
    menuLibere(&jeu->menu);
    entreeLibere(&jeu->entree);
    graphiqueLibere(&jeu->graphique);
    audioLibere(&jeu->audio);
    SDL_Quit();
}

