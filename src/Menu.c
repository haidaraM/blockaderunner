#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>





void menuInit(Menu *menu, Ressource *res)
{
	int i;
	int index;
	int numJoueurs;
	Joueur **joueurs;
	
	assert( menu != NULL );
	assert( res != NULL );

	#ifdef JEU_VERBOSE
		printf("Menu :\n    initialisation ...\n");
	#endif


	menu->ressource 	= res;
	menu->etat			= MENU_ETAT_INTRO;
	menu->tempsEcoule 	= 0.0f;
	menu->joueurCourant = 0;/* par défaut */
	menu->elements 		= NULL;
	menu->elements 		= (ElementMenu*)malloc(MENU_NUM_ELEMENTS * sizeof(ElementMenu));
	assert( menu->elements != NULL);

	/* Definition des Elements des Menus */
	
	index = MENU_RETOUR;
	menu->elements[index].texte 				= MENU_TXT_RETOUR;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;
	menu->elements[index].action				= menuRetour;

	index = MENU_JOUEURS;
	menu->elements[index].texte 				= MENU_TXT_JOUEURS;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 0;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_NOUVEAU_JOUEUR;
	menu->elements[index].texte 				= MENU_TXT_NOUVEAU_JOUEUR;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_ZONE_LARGEUR/2;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 2*MENU_PADDING_VERT;
	menu->elements[index].action				= menuNouveauJoueur;

	index = MENU_ENTRER_NOM;
	menu->elements[index].texte 				= MENU_TXT_ENTRER_NOM;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 0;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_JOUER;
	menu->elements[index].texte 				= MENU_TXT_JOUER;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;
	menu->elements[index].action				= menuJouer;

	index = MENU_SCORE;
	menu->elements[index].texte 				= MENU_TXT_SCORE;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 5*MENU_PADDING_VERT;
	menu->elements[index].action				= menuScores;

	index = MENU_CMD;
	menu->elements[index].texte 				= MENU_TXT_CMD;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 7*MENU_PADDING_VERT;
	menu->elements[index].action				= menuCommandes;

	index = MENU_OPTION;
	menu->elements[index].texte 				= MENU_TXT_OPTION;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 9*MENU_PADDING_VERT;
	menu->elements[index].action				= menuOptions;

	index = MENU_INFO;
	menu->elements[index].texte 				= MENU_TXT_INFO;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 11*MENU_PADDING_VERT;
	menu->elements[index].action				= menuInfo;

	index = MENU_QUITTER;
	menu->elements[index].texte 				= MENU_TXT_QUITTER;
	menu->elements[index].visible 				= 0;
	menu->elements[index].actionable 			= 1;
	menu->elements[index].surligne	 			= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 2*MENU_PADDING_VERT;
	menu->elements[index].action				= menuQuitter;

	/* Remplissage de la liste des noms de joueurs */
	numJoueurs 			= ressourceGetNumJoueurs(res);
	joueurs 			= ressourceGetJoueurs(menu->ressource);
	for (i=0; i< RESS_SAU_MAX_JOUEURS; i++)
	{
		index = i + MENU_NUM_BASIC_ELEMENTS;
		if (i < numJoueurs)
				menu->elements[index].texte			= joueurs[i]->nom;
		else 	menu->elements[index].texte			= MENU_TXT_JOUEUR_VIDE;
		menu->elements[index].visible 				= 1;
		menu->elements[index].actionable 			= 1;
		menu->elements[index].surligne	 			= 0;
		menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
		menu->elements[index].rect.y				= MENU_ZONE_Y + (3 + index - MENU_NUM_BASIC_ELEMENTS)*MENU_PADDING_VERT;
		menu->elements[index].action				= menuPrincipal;	
	}
		
	#ifdef JEU_VERBOSE
		printf("	initialisation OK.\n");
	#endif
}

void menuLibere(Menu *menu)
{
	free(menu->elements);
}

void menuIntro(Menu *menu, float tempsBoucleEcoule)
{
	if (menu->etat != MENU_ETAT_INTRO)
		return;

	menu->tempsEcoule 	+= tempsBoucleEcoule;
	if (menu->tempsEcoule > MENU_DUREE_INTRO)
	{
		menu->tempsEcoule 	= 0.0f;
		menuChoixJoueur((void*)menu);
	}
}

void menuRetour(void *m)
{
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	switch(menu->etat)
	{
		case MENU_ETAT_INTRO:
			menuQuitter((void*)menu);
			break;
		case MENU_ETAT_CHOIX_JOUEUR:
			menuQuitter((void*)menu);
			break;
		case MENU_ETAT_ENTREE_JOUEUR:
			menuChoixJoueur((void*)menu);
			break;
		case MENU_ETAT_PRINCIPAL:
			menuChoixJoueur((void*)menu);
			break;
		case MENU_ETAT_QUITTER:
			break;
		default:
			menuPrincipal((void*)menu);
			break;
	}
}

void menuQuitter(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_QUITTER;
}
void menuChoixJoueur(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_CHOIX_JOUEUR;
	menu->elements[MENU_JOUEURS].visible = 1;
	menu->elements[MENU_NOUVEAU_JOUEUR].visible = 1;
	for (i=MENU_NUM_BASIC_ELEMENTS; i <MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 1;
}
void menuNouveauJoueur(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_ENTREE_JOUEUR;
	menu->elements[MENU_ENTRER_NOM].visible = 1;
}
void menuPrincipal(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_PRINCIPAL;
	menu->elements[MENU_JOUER].visible = 1;
	menu->elements[MENU_CMD].visible = 1;
	menu->elements[MENU_OPTION].visible = 1;
	menu->elements[MENU_INFO].visible = 1;
	menu->elements[MENU_QUITTER].visible = 1;
}
void menuCommandes(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_CMD;
	menu->elements[MENU_RETOUR].visible = 1;
}
void menuOptions(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_OPTION;
	menu->elements[MENU_RETOUR].visible = 1;
}
void menuInfo(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_INFO;
	menu->elements[MENU_RETOUR].visible = 1;
}
void menuScores(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_SCORE;
	menu->elements[MENU_RETOUR].visible = 1;
}
void menuJouer(void *m)
{
	int i;
	Menu *menu = (Menu*)m;
	assert(menu != NULL);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
		menu->elements[i].visible = 0;

	menu->etat 	= MENU_ETAT_CHOIX_NIVEAU;
	menu->elements[MENU_RETOUR].visible = 1;
}

void menuSelectionJoueur(void *m)
{}


