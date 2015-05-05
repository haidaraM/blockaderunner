/**
* @file Menu.c
* @brief fichier d'implementation du Menu
* @author Yann Cortial
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Menu.h"
#include "Joueur.h"

/* ------------	Fonctions Internes --------------------------------- */

static void creeListeJoueurs(Menu *menu)
{
    int i;
    int index, numJoueurs;
    Joueur **joueurs = NULL;
    assert(menu != NULL);

    numJoueurs = ressourceGetNumJoueurs(menu->ressource);
    joueurs = ressourceGetJoueurs(menu->ressource);
    assert(joueurs != NULL);

    for (i = 0; i < RESS_SAU_MAX_JOUEURS; i++) {
        index = i + MENU_NUM_BASIC_ELEMENTS;
        if (i < numJoueurs)
            menu->elements[index].texte = joueurs[i]->nom;
        else menu->elements[index].texte = MENU_TXT_JOUEUR_VIDE;
        assert(menu->elements[index].texte != NULL);
        menu->elements[index].visible = 1;
        if (i < numJoueurs)
            menu->elements[index].actionable = 1;
        else menu->elements[index].actionable = 0;
        menu->elements[index].surligne = 0;
        menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
        menu->elements[index].rect.y = MENU_ZONE_Y + (3 + i) * 24;
        if (i < numJoueurs)
            menu->elements[index].action = menuPrincipal;
    }
}


/* -----------------	Interface du Module -------------------------- */

void menuInit(Menu *menu, Ressource *res)
{
    int index, i;
    char niv[32], indexNiv[16];

    assert(menu != NULL);
    assert(res != NULL);

#ifdef JEU_VERBOSE
	printf("Menu :\n    initialisation ...\n");
	#endif


    menu->ressource = res;
    menu->etat = MENU_ETAT_INTRO;
    menu->tempsEcoule = 0.0f;
    menu->joueurCourant = -1;/* par défaut */
    menu->nomNouveauJoueur[0] = '\0';
    menu->nomsMeilleursJoueurs = (char **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(char *));
    menu->meilleursScores = (char **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(char *));
    assert(menu->nomsMeilleursJoueurs != NULL && menu->meilleursScores != NULL);
    for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++) {
        menu->meilleursScores[i] = (char *) malloc(16 * sizeof(char));
        assert(menu->meilleursScores[i] != NULL);
    }
    menu->niveauChoisi = -1;
    menu->elements = NULL;
    menu->elements = (ElementMenu *) malloc(MENU_NUM_ELEMENTS * sizeof(ElementMenu));
    assert(menu->elements != NULL);



    /* Definition des Elements du Menu */

    index = MENU_RETOUR;
    menu->elements[index].texte = MENU_TXT_RETOUR;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_PADDING_VERT;
    menu->elements[index].action = menuRetour;

    index = MENU_JOUEURS;
    menu->elements[index].texte = MENU_TXT_JOUEURS;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 0;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_PADDING_VERT;

    index = MENU_NOUVEAU_JOUEUR;
    menu->elements[index].texte = MENU_TXT_NOUVEAU_JOUEUR;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_ZONE_LARGEUR / 2;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 2 * MENU_PADDING_VERT;
    menu->elements[index].action = menuNouveauJoueur;

    index = MENU_ENTRER_NOM;
    menu->elements[index].texte = MENU_TXT_ENTRER_NOM;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 0;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_PADDING_VERT;

    index = MENU_JOUER;
    menu->elements[index].texte = MENU_TXT_JOUER;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_PADDING_VERT;
    menu->elements[index].action = menuJouer;

    index = MENU_SCORE;
    menu->elements[index].texte = MENU_TXT_SCORE;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + 5 * MENU_PADDING_VERT;
    menu->elements[index].action = menuScores;

    index = MENU_CMD;
    menu->elements[index].texte = MENU_TXT_CMD;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + 7 * MENU_PADDING_VERT;
    menu->elements[index].action = menuCommandes;

    index = MENU_CHANGER_JOUEUR;
    menu->elements[index].texte = MENU_TXT_CHANGER_JOUEUR;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + 9 * MENU_PADDING_VERT;
    menu->elements[index].action = menuChangerJoueur;

    index = MENU_INFO;
    menu->elements[index].texte = MENU_TXT_INFO;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + 11 * MENU_PADDING_VERT;
    menu->elements[index].action = menuInfo;

    index = MENU_QUITTER;
    menu->elements[index].texte = MENU_TXT_QUITTER;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 2 * MENU_PADDING_VERT;
    menu->elements[index].action = menuQuitter;

    index = MENU_REPRENDRE;
    menu->elements[index].texte = MENU_TXT_REPRENDRE;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_PADDING_VERT;
    menu->elements[index].action = menuReprendre;

    index = MENU_REJOUER;
    menu->elements[index].texte = MENU_TXT_REJOUER;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + 9 * MENU_PADDING_VERT;
    menu->elements[index].action = menuReJouer;

    index = MENU_RETOUR_MENU_PRINCIPAL;
    menu->elements[index].texte = MENU_TXT_RETOUR_MENU_PRINCIPAL;
    menu->elements[index].visible = 0;
    menu->elements[index].actionable = 1;
    menu->elements[index].surligne = 0;
    menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
    menu->elements[index].rect.y = MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 4 * MENU_PADDING_VERT;
    menu->elements[index].action = menuRetourPrincipal;



    /* les 8 niveaux */
    for (i = MENU_NIVEAU; i < MENU_NUM_BASIC_ELEMENTS; i++) {
        strcpy(niv, MENU_TXT_NIVEAU);
        /* conversion du numero du niveau en caractere */
        sprintf(indexNiv, "%d", i - MENU_NIVEAU);
        strcat(niv, indexNiv);
        index = i;
        menu->elements[index].texte = (char *) malloc(64 * sizeof(char));
        assert(menu->elements[index].texte != NULL);
        strcpy(menu->elements[index].texte, niv);
        menu->elements[index].visible = 0;
        menu->elements[index].actionable = 1;
        menu->elements[index].surligne = 0;
        menu->elements[index].rect.x = MENU_ZONE_X + MENU_PADDING_HORZ;
        menu->elements[index].rect.y = MENU_ZONE_Y + (3 + 2 * (i - MENU_NIVEAU)) * MENU_PADDING_VERT;
        menu->elements[index].action = menuCommencerNiveau;
    }


    /* Remplissage de la liste des noms de joueurs */
    creeListeJoueurs(menu);

#ifdef JEU_VERBOSE
	printf("	initialisation OK.\n");
	#endif
}

void menuLibere(Menu *menu)
{
    int i;

    for (i = MENU_NIVEAU; i < MENU_NUM_BASIC_ELEMENTS; i++)
        free(menu->elements[i].texte);

    for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++)
        free(menu->meilleursScores[i]);

    free(menu->nomsMeilleursJoueurs);
    free(menu->meilleursScores);
    free(menu->elements);
}

void menuCommencerNiveau(void *m) { }

void menuIntro(Menu *menu, float tempsBoucleEcoule)
{
    if (menu->etat != MENU_ETAT_INTRO)
        return;

    menu->tempsEcoule += tempsBoucleEcoule;
    if (menu->tempsEcoule > MENU_DUREE_INTRO) {
        menu->tempsEcoule = 0.0f;
        menuChoixJoueur((void *) menu);
    }
}

void menuRetour(void *m)
{
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    switch (menu->etat) {
        case MENU_ETAT_INTRO:
            menuQuitter((void *) menu);
            break;
        case MENU_ETAT_CHOIX_JOUEUR:
            menuQuitter((void *) menu);
            break;
        case MENU_ETAT_ENTREE_JOUEUR:
            menuChoixJoueur((void *) menu);
            break;
        case MENU_ETAT_QUITTER:
            break;
        case MENU_ETAT_PAUSE_CMD:
            menuPause(menu);
            break;
        case MENU_ETAT_PAUSE_SCORE:
            menuPause(menu);
            break;
        default:
            menuPrincipal((void *) menu);
            break;
    }
}

void menuQuitter(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->etat = MENU_ETAT_QUITTER;
}

void menuChoixJoueur(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->joueurCourant = -1;

    menu->etat = MENU_ETAT_CHOIX_JOUEUR;
    menu->elements[MENU_JOUEURS].visible = 1;
    menu->elements[MENU_NOUVEAU_JOUEUR].visible = 1;
    for (i = MENU_NUM_BASIC_ELEMENTS; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 1;
}

void menuNouveauJoueur(void *m)
{
    int i, numJoueurs;
    Menu *menu = (Menu *) m;

    assert(menu != NULL);

    numJoueurs = ressourceGetNumJoueurs(menu->ressource);
    /* le joueur courant est le prochain joueur vide dans la liste (ou le premier de la liste si elle est pleine, auquel cas l'ancien premier joueur sera écrasé).*/
    menu->joueurCourant = numJoueurs;
    if (menu->joueurCourant >= RESS_SAU_MAX_JOUEURS)
        menu->joueurCourant = 0;

    menu->nomNouveauJoueur[0] = '\0';

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->etat = MENU_ETAT_ENTREE_JOUEUR;
    menu->elements[MENU_ENTRER_NOM].visible = 1;
}

void menuPrincipal(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->etat = MENU_ETAT_PRINCIPAL;
    menu->elements[MENU_JOUER].visible = 1;
    menu->elements[MENU_SCORE].visible = 1;
    menu->elements[MENU_CMD].visible = 1;
    menu->elements[MENU_CHANGER_JOUEUR].visible = 1;
    menu->elements[MENU_INFO].visible = 1;
    menu->elements[MENU_QUITTER].visible = 1;
}

void menuCommandes(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    if (menu->etat == MENU_ETAT_PAUSE)
        menu->etat = MENU_ETAT_PAUSE_CMD;
    else menu->etat = MENU_ETAT_CMD;

    menu->elements[MENU_RETOUR].visible = 1;
}

void menuChangerJoueur(void *m)
{
    menuChoixJoueur(m);
}

void menuInfo(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->etat = MENU_ETAT_INFO;
    menu->elements[MENU_RETOUR].visible = 1;
}

void menuScores(void *m)
{
    int i;
    Menu *menu = (Menu *) m;
    Joueur **joueursClasses = NULL;
    assert(menu != NULL);
    /* remise à zero */
    for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++)
        menu->nomsMeilleursJoueurs[i] = NULL;

    /* On demande à ressource (qui maintient la liste des joueurs) de classer les meilleurs joueurs. */
    ressourceTrieJoueurs(menu->ressource);
    joueursClasses = ressourceGetMeilleursJoueurs(menu->ressource);
    for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++)
        if (joueursClasses[i] != NULL) {
            menu->nomsMeilleursJoueurs[i] = joueursClasses[i]->nom;
            sprintf(menu->meilleursScores[i], "%d", joueurGetScore(joueursClasses[i]));
        }


    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;
    if (menu->etat == MENU_ETAT_PAUSE)
        menu->etat = MENU_ETAT_PAUSE_SCORE;
    else menu->etat = MENU_ETAT_SCORE;
    menu->elements[MENU_RETOUR].visible = 1;
}

void menuJouer(void *m)
{
    int i;
    int progression;
    Menu *menu = (Menu *) m;
    assert(menu != NULL);

    /* Reinitialisation des elements visibles a 0 */
    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    menu->etat = MENU_ETAT_CHOIX_NIVEAU;
    menu->elements[MENU_RETOUR].visible = 1;

    assert(menu->joueurCourant > -1);
    progression = (int) joueurGetProgression(menu->ressource->joueurs[menu->joueurCourant]);
    for (i = MENU_NIVEAU; i < (MENU_NIVEAU + progression + 1); i++)
        menu->elements[i].visible = 1;
}

void menuPause(Menu *m)
{
    int i;
    Menu *menu = (Menu *) m;

    assert(menu != NULL);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++)
        menu->elements[i].visible = 0;

    /* Defintions des éléments visibles */
    menu->elements[MENU_REPRENDRE].visible = 1;
    menu->elements[MENU_REJOUER].visible = 1;
    menu->elements[MENU_QUITTER].visible = 1;
    menu->elements[MENU_SCORE].visible = 1;
    menu->elements[MENU_CMD].visible = 1;
    menu->elements[MENU_RETOUR_MENU_PRINCIPAL].visible = 1;

    menu->etat = MENU_ETAT_PAUSE;

}

void menuSelectionneJoueur(Menu *menu, int indexElement)
{
    int index;
    int numJoueurs;
    assert(menu != NULL);

    numJoueurs = ressourceGetNumJoueurs(menu->ressource);
    index = indexElement - MENU_NUM_BASIC_ELEMENTS;
    if (index >= 0 && index < numJoueurs) {
        menu->joueurCourant = index;
        menuPrincipal(menu);
        return;

    } else {
        menuNouveauJoueur(menu);
    }
}

void menuSetCaractere(Menu *menu, char alphaNum)
{
    char s[2];
    assert(menu != NULL);

    if (strlen(menu->nomNouveauJoueur) >= (JOUEUR_NOM_MAXCHAR))
        return;

    s[0] = alphaNum;
    s[1] = '\0';

    strcat(menu->nomNouveauJoueur, s);
}

void menuEffaceCaractere(Menu *menu)
{
    assert(menu != NULL);

    if (strlen(menu->nomNouveauJoueur) == 0)
        return;

    menu->nomNouveauJoueur[strlen(menu->nomNouveauJoueur) - 1] = '\0';
}

void menuSetFinLectureClavier(Menu *menu)
{
    assert(menu != NULL);

    if (strlen(menu->nomNouveauJoueur) != 0) {
        /* on ajoute le nouveau joueur à Ressource */
        ressourceAjouteJoueur(menu->ressource, menu->nomNouveauJoueur, menu->joueurCourant);
        /* on demande à Ressource de sauver sur disque l'etat des joueurs (dont le nouveau) */
        ressourceSauveJoueurs(menu->ressource);

        printf("%s --> joueur ajouté. \n", menu->nomNouveauJoueur);
        creeListeJoueurs(menu);
    }

    menuPrincipal(menu);
}

Joueur *menuGetJoueurChoisi(const Menu *menu)
{
    assert(menu != NULL);
    if (menu->joueurCourant == -1)
        return NULL;

    return menu->ressource->joueurs[menu->joueurCourant];
}

void menuSelectionneNiveau(Menu *menu, int indexElement)
{
    assert(menu != NULL);
    if (indexElement == MENU_RETOUR) {
        menu->niveauChoisi = -1;
        return;
    }

    menu->niveauChoisi = indexElement - MENU_NIVEAU;
}

int menuGetNiveauChoisi(const Menu *menu)
{
    assert(menu != NULL);
    return menu->niveauChoisi;
}

void menuReprendre(void *m)
{
    Menu *menu = (Menu *) m;
    assert(menu != NULL);
    menu->etat = MENU_ETAT_REPRENDRE;
}

void menuReJouer(void *m)
{
    Menu *menu = (Menu *) m;
    assert(menu != NULL);
    menu->etat = MENU_ETAT_REJOUER;
}

void menuRetourPrincipal(void *m)
{
    Menu *menu = (Menu *) m;
    assert(menu != NULL);
    menu->etat = MENU_ETAT_PAUSE_RETOUR_MENU_PRINCIPAL;
}
