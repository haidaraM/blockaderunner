/**
* @file fichier d'implementation du module GraphiqueSDL
* @brief
*/
#include "GraphiqueSDL.h"
#include "ElementScene.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* --------------------------------------------------------------------------------------------------			Fonctions internes */ 

SDL_Surface* chargeImage(char* nomFichier)
{
	SDL_Surface *image = NULL;
	char file[64], dir[64];

	if (nomFichier == NULL)
		return NULL;

	strcpy(file, nomFichier);
	strcpy(dir, RESS_DIR_IMAGES);

	image 					= IMG_Load(strcat(dir, file));
	if (image == NULL)
	{
		printf("ERREUR : Ressources : impossible de charger l'image %s dans %s.\n   %s\n", nomFichier, RESS_DIR_IMAGES, IMG_GetError());
	}

	assert( image != NULL );
	return image;
}

void chargePolices(GraphiqueSDL *graphique)
{
	char file[64], dir[64];
	char *nomFic;
	assert( graphique != NULL);
	
	strcpy(file, RESS_POL_FICHIER_MENU);
	strcpy(dir, RESS_DIR_POLICES);
	nomFic = strcat(dir, file);
	
	graphique->policeMenu 	= TTF_OpenFont(nomFic, RESS_POL_TAILLE_MENU);
	if(!graphique->policeMenu) {
    	printf("TTF_OpenFont: %s\n", TTF_GetError());
	    exit(2);
	}

	graphique->policeListeJoueurs 	= TTF_OpenFont(nomFic, RESS_POL_TAILLE_LISTE_JOUEURS);
	if(!graphique->policeListeJoueurs) {
    	printf("TTF_OpenFont: %s\n", TTF_GetError());
	    exit(2);
	}
}













/* --------------------------------------------------------------------------------------------------			Interface du Module */ 

void graphiqueInit(GraphiqueSDL *graphique, Ressource *ressource, Menu *menu, int largeur, int hauteur, char *titre, int mode)
{
	SDL_Rect **modes;
	char **fichiersImages;
	int i;
	int imgFlags, imgRes;
	SDL_Color couleurTexteMenu 			= { 249, 255, 253 };
	SDL_Color couleurTexteMenuSurvol 	= { 249, 255, 53 };

	assert( graphique != NULL && ressource != NULL && menu != NULL && largeur > 0 && hauteur > 0 );

	#ifdef JEU_VERBOSE
		printf("GraphiqueSDL :\n    initialisation ...\n");
	#endif

	graphique->surface		= 0;
	graphique->largeur 		= 0;
	graphique->hauteur		= 0;
	graphique->titre		= GFX_FENETRE_TITRE_DEFAUT;
	graphique->mode 		= GFX_MODE_FENETRE;


	#ifdef JEU_VERBOSE
	/*---------------------------------------------------------------------
		 Evaluation des modes video disponibles */

	modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
	/* verifie s'il ya plusieurs modes disponibles */
	if(modes == (SDL_Rect **)0){
		printf("    No VIDEO modes available!\n");
  		exit(-1);
	}

	/* Verifie si la resolution est limitee */
	if(modes == (SDL_Rect **)-1){
		printf("    VIDEO : All resolutions available.\n");
	}
	else{
	  	/* Affiche les modes valides */
	  	printf("    Available Modes\n");
	  	for(i=0;modes[i];++i)
	    	printf("      %d x %d\n", modes[i]->w, modes[i]->h);
	}
	/*free(modes);*/
	#endif


	/*---------------------------------------------------------------------
		 Initialisation fenetre principale (SDL) */

	graphique->surface 		= SDL_SetVideoMode( largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
	assert( graphique->surface != NULL );

	/* Initialise la surface accessible (par blit..) à toute la surface graphique : toute opération en dehors de ces limites sera tronquée automatiquement. */
	SDL_SetClipRect(graphique->surface, NULL);

	graphique->couleurFond	= SDL_MapRGB( graphique->surface->format, 0x00, 0x00, 0x00 );
	graphiqueEfface(graphique);
	graphique->largeur		= largeur;
	graphique->hauteur 		= hauteur;
	if (titre != NULL)
	{
		SDL_WM_SetCaption( titre, NULL );
		graphique->titre 	= titre;
	} else
		SDL_WM_SetCaption( graphique->titre, NULL);


	/*---------------------------------------------------------------------
		 Initialisation de SDL_image */

	imgFlags			= IMG_INIT_JPG | IMG_INIT_PNG;
	imgRes				= IMG_Init(imgFlags);
	if((imgRes & imgFlags) != imgFlags)
	{
   	 	printf("IMG_Init: Impossible d'initialiser SDL_image avec support PNG et JPEG.\n");
   	 	printf("IMG_Init: %s\n", IMG_GetError());
	}


	/*---------------------------------------------------------------------
	 	Chargement de toutes les images du Jeu : */

	#ifdef JEU_VERBOSE
		printf("    chargement des images.\n");
	#endif
	graphique->images 		= (SDL_Surface**)malloc(RESS_NUM_IMAGES*sizeof(SDL_Surface*));
	if (graphique->images == NULL)
	{
		printf("ERREUR : Ressources (GraphiqueSDL) : impossible d'allouer la memoire pour les images.\n");
		assert( graphique->images != NULL);
	}
	fichiersImages = ressource->images;	
	for (i=0; i< RESS_NUM_IMAGES; i++)
	{
		graphique->images[i]	= 0;
		graphique->images[i] 	= chargeImage(fichiersImages[i]);
	}
	#ifdef JEU_VERBOSE
		printf("    chargement des images OK.\n");
	#endif
	
	/*---------------------------------------------------------------------
		 Initialisation de SDL_ttf : */

	#ifdef JEU_VERBOSE
		printf("    initialisation SDL_ttf.\n");
	#endif
	if ( TTF_Init() == -1 ) {
    	printf("TTF_Init: %s\n", TTF_GetError());
    	exit(2);
	}

	#ifdef JEU_VERBOSE
		printf("    chargement des polices.\n");
	#endif
	chargePolices(graphique);

	/* Creation des Elements Menu : MENU_NUM_ELEMENTS paires de rendus de texte (normal & surligné) */
	graphique->textesMenu 	= (SDL_Surface**)malloc(2*MENU_NUM_ELEMENTS*sizeof(SDL_Surface*));
	if (graphique->textesMenu == NULL)
	{
		printf("ERREUR : (GraphiqueSDL) : impossible d'allouer la memoire pour les rendus de texte (Menu).\n");
		assert( graphique->textesMenu != NULL);
	}	
	#ifdef JEU_VERBOSE
		printf("    rendu du texte (Menu).\n");
	#endif
	for (i=0; i< 2*MENU_NUM_ELEMENTS; i++)
	{	
		graphique->textesMenu[i] = NULL;
	}
	for (i=0; i< MENU_NUM_BASIC_ELEMENTS; i++)
	{
		/* On rend une fois le texte normal */
		graphique->textesMenu[2*i]		= TTF_RenderText_Blended(graphique->policeMenu, menu->elements[i].texte, couleurTexteMenu);
		assert( graphique->textesMenu[2*i] != NULL );
		menu->elements[i].rect.largeur 	= graphique->textesMenu[2*i]->w;
		menu->elements[i].rect.hauteur 	= graphique->textesMenu[2*i]->h;
		/* On rend une seconde fois avec la couleur correspondant au texte surligné */
		graphique->textesMenu[2*i+1]	= TTF_RenderText_Blended(graphique->policeMenu, menu->elements[i].texte, couleurTexteMenuSurvol);
		assert( graphique->textesMenu[2*i+1] != NULL );
	}
	/* cree le rendu de la liste des noms de joueurs */
	graphiquePrepareRenduListeJoueurs(graphique, menu);



	/*---------------------------------------------------------------------
		FIN */
	
	#ifdef JEU_VERBOSE
		printf("    initialisation OK.\n");
	#endif

}

void graphiqueLibere(GraphiqueSDL *graphique)
{
	int i;

	for (i=0; i< RESS_NUM_IMAGES; i++)
		if (graphique->images[i] != NULL)
			SDL_FreeSurface(graphique->images[i]);
	free(graphique->images);

	for (i=0; i< MENU_NUM_ELEMENTS; i++)
	{
		if (graphique->textesMenu[2*i] != NULL)
			SDL_FreeSurface(graphique->textesMenu[2*i]);
		if (graphique->textesMenu[2*i+1] != NULL)
			SDL_FreeSurface(graphique->textesMenu[2*i+1]);
	}
	free(graphique->textesMenu);

	TTF_CloseFont(graphique->policeMenu);	

	/* SDL_ttf */
	TTF_Quit();

	/* SDL_image */
	IMG_Quit();
}

void graphiqueRaffraichit(GraphiqueSDL *graphique)
{
	assert( SDL_Flip( graphique->surface ) !=-1 );
}

void graphiqueSetTitre(GraphiqueSDL *graphique, char *titre)
{
	if (titre != NULL)
	{
		SDL_WM_SetCaption( titre, NULL);
		graphique->titre 	= titre;
	}
}

void graphiqueEfface(GraphiqueSDL *graphique)
{
	SDL_FillRect( graphique->surface, &graphique->surface->clip_rect, graphique->couleurFond );
}

void graphiqueSetCouleurFond(GraphiqueSDL *graphique, unsigned char rouge, unsigned char vert, unsigned char bleu)
{
	graphique->couleurFond	= SDL_MapRGB( graphique->surface->format, rouge, vert, bleu );
}

void graphiquePrepareRenduListeJoueurs(GraphiqueSDL *graphique, Menu *menu)
{
	int i;
	SDL_Color couleurTexteMenu 			= { 249, 255, 253 };
	SDL_Color couleurTexteMenuSurvol 	= { 249, 255, 53 };
	assert( graphique != NULL && menu != NULL);

	for (i=MENU_NUM_BASIC_ELEMENTS; i< MENU_NUM_ELEMENTS; i++)
	{
		if (graphique->textesMenu[2*i] != NULL)
		{
			SDL_FreeSurface(graphique->textesMenu[2*i]);
			graphique->textesMenu[2*i] = NULL;
		}
		if (graphique->textesMenu[2*i+1] != NULL)
		{
			SDL_FreeSurface(graphique->textesMenu[2*i+1]);
			graphique->textesMenu[2*i+1] = NULL;
		}
	}

	for (i=MENU_NUM_BASIC_ELEMENTS; i< MENU_NUM_ELEMENTS; i++)
	{
		/* On rend une fois le texte normal */
		while( graphique->textesMenu[2*i] == NULL )
			graphique->textesMenu[2*i]		= TTF_RenderText_Blended(graphique->policeListeJoueurs, menu->elements[i].texte, couleurTexteMenu);
		menu->elements[i].rect.largeur 	= graphique->textesMenu[2*i]->w;
		menu->elements[i].rect.hauteur 	= graphique->textesMenu[2*i]->h;
		/* On rend une seconde fois avec la couleur correspondant au texte surligné */
		while( graphique->textesMenu[2*i+1] == NULL )
			graphique->textesMenu[2*i+1]	= TTF_RenderText_Blended(graphique->policeListeJoueurs, menu->elements[i].texte, couleurTexteMenuSurvol);
	}
}

void graphiqueAfficheMenu(GraphiqueSDL *graphique, Menu *menu)
{
	int i;
	SDL_Rect offset;
	SDL_Surface *nomNouveauJoueur;
	SDL_Color couleurTexteMenuSurvol 	= { 249, 255, 53 };

	switch(menu->etat)
	{
	case MENU_ETAT_INTRO:
		offset.x = 0;
		offset.y = 0;
		SDL_BlitSurface( graphique->images[RESS_IMG_SPLASH], NULL, graphique->surface, &offset);
		break;
	case MENU_ETAT_CHOIX_JOUEUR:
		offset.x = 0;
		offset.y = 0;
		SDL_BlitSurface( graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
		for (i=0; i< MENU_NUM_ELEMENTS; i++)
		{
			if (menu->elements[i].visible == 1)
			{
				offset.x = menu->elements[i].rect.x;
				offset.y = menu->elements[i].rect.y;	
				if (menu->elements[i].surligne == 0)		
						SDL_BlitSurface( graphique->textesMenu[2*i], NULL, graphique->surface, &offset);
				else 	SDL_BlitSurface( graphique->textesMenu[2*i+1], NULL, graphique->surface, &offset);
			}	
		}
		break; 
	case MENU_ETAT_ENTREE_JOUEUR:
		offset.x = 0;
		offset.y = 0;
		SDL_BlitSurface( graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
		for (i=0; i< MENU_NUM_ELEMENTS; i++)
		{
			if (menu->elements[i].visible == 1)
			{
				offset.x = menu->elements[i].rect.x;
				offset.y = menu->elements[i].rect.y;	
				if (menu->elements[i].surligne == 0)		
						SDL_BlitSurface( graphique->textesMenu[2*i], NULL, graphique->surface, &offset);
				else 	SDL_BlitSurface( graphique->textesMenu[2*i+1], NULL, graphique->surface, &offset);
			}	
		}
		nomNouveauJoueur = TTF_RenderText_Blended(graphique->policeMenu, menu->nomNouveauJoueur, couleurTexteMenuSurvol);
		offset.x  = MENU_ZONE_X + MENU_PADDING_HORZ;
		offset.y  = MENU_ZONE_Y + 5*MENU_PADDING_VERT;
		SDL_BlitSurface( nomNouveauJoueur, NULL, graphique->surface, &offset);
		SDL_FreeSurface(nomNouveauJoueur);
		break; 
	default:
		offset.x = 0;
		offset.y = 0;
		SDL_BlitSurface( graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
		for (i=0; i< MENU_NUM_ELEMENTS; i++)
		{
			if (menu->elements[i].visible == 1)
			{
				offset.x = menu->elements[i].rect.x;
				offset.y = menu->elements[i].rect.y;	
				if (menu->elements[i].surligne == 0)		
						SDL_BlitSurface( graphique->textesMenu[2*i], NULL, graphique->surface, &offset);
				else 	SDL_BlitSurface( graphique->textesMenu[2*i+1], NULL, graphique->surface, &offset);
			}	
		}
		break; 
	}
}


void graphiqueAfficheScene(GraphiqueSDL *graphique, Scene *scene )
{
	int i;
	SDL_Rect srcBox, dstBox;
	ElementScene **elements = scene->elements;

	/* affichage du fond */
	srcBox.x 		= scene->rectangleImageFond.x;
	srcBox.y 		= scene->rectangleImageFond.y;
	srcBox.w		= scene->rectangleImageFond.largeur;
	srcBox.h		= scene->rectangleImageFond.hauteur;
	SDL_BlitSurface( graphique->images[scene->indexImageFond], &srcBox, graphique->surface, NULL);
	
	/* affichage des sprites */	
	for (i=0; i< scene->numElements; i++)
	{
		if (elements[i] != NULL && elementVisible(elements[i]) == 1)
		{
			dstBox.x = elementGetX(elements[i]);
			dstBox.y = elementGetY(elements[i]);
			SDL_BlitSurface( graphique->images[elementGetImageIndex(elements[i])], NULL, graphique->surface, &dstBox);
		}
	}
}



