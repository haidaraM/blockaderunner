#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



void menuInit(Menu *menu)
{
	int index;
	
	assert( menu != NULL );

	menu->etat			= MENU_ETAT_INTRO;
	menu->tempsEcoule 	= 0.0f;

	menu->elements 		= NULL;
	menu->elements 		= (ElementMenu*)malloc(MENU_NUM_ELEMENTS * sizeof(ElementMenu));
	assert( menu->elements != NULL);

	/* Definition des Elements des Menus */

	index = MENU_RETOUR;
	menu->elements[index].texte 				= MENU_TXT_RETOUR;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_JOUEURS;
	menu->elements[index].texte 				= MENU_TXT_JOUEURS;
	menu->elements[index].visible 				= 1;
	menu->elements[index].selectionable 		= 0;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_NOUVEAU_JOUEUR;
	menu->elements[index].texte 				= MENU_TXT_NOUVEAU_JOUEUR;
	menu->elements[index].visible 				= 1;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_ZONE_HAUTEUR - 2*MENU_PADDING_VERT;

	index = MENU_ENTRER_NOM;
	menu->elements[index].texte 				= MENU_TXT_ENTRER_NOM;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 0;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_JOUER;
	menu->elements[index].texte 				= MENU_TXT_JOUER;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + MENU_PADDING_VERT;

	index = MENU_SCORE;
	menu->elements[index].texte 				= MENU_TXT_SCORE;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 5*MENU_PADDING_VERT;

	index = MENU_CMD;
	menu->elements[index].texte 				= MENU_TXT_CMD;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 7*MENU_PADDING_VERT;

	index = MENU_OPTION;
	menu->elements[index].texte 				= MENU_TXT_OPTION;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 9*MENU_PADDING_VERT;

	index = MENU_INFO;
	menu->elements[index].texte 				= MENU_TXT_INFO;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 11*MENU_PADDING_VERT;

	index = MENU_QUITTER;
	menu->elements[index].texte 				= MENU_TXT_QUITTER;
	menu->elements[index].visible 				= 0;
	menu->elements[index].selectionable 		= 1;
	menu->elements[index].selectione	 		= 0;
	menu->elements[index].rect.x				= MENU_ZONE_X + MENU_PADDING_HORZ;
	menu->elements[index].rect.y				= MENU_ZONE_Y + 13*MENU_PADDING_VERT;
}

void menuLibere(Menu *menu)
{
	free(menu->elements);
}

void menuMiseAJour(Menu *menu, float tempsBoucleEcoule)
{
	if (menu->etat == MENU_ETAT_INTRO)
	{
		/*printf(" . ");*/
		menu->tempsEcoule 	+= tempsBoucleEcoule;
		if (menu->tempsEcoule > MENU_DUREE_INTRO)
		{
			menu->etat			= MENU_ETAT_CHOIX_JOUEUR;
			menu->tempsEcoule 	= 0.0f;
		}

		return;
	}
}


