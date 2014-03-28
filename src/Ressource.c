/**
* @file Ressource.c
* @brief
*/
#include "Ressource.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


/*------------------------------------------------------------------------------------------------------------------
	FONCTIONS INTERNES
*/


void creeListeImages(Ressource *res)
{
	int i;

	/* initialisation des tableaux */

	res->images 			= (char**)malloc(RESS_NUM_IMAGES * sizeof(char*));
	res->dimensionImages 	= (Rectangle*)malloc(RESS_NUM_IMAGES * sizeof(Rectangle));
	assert( res->images != NULL  &&  res->dimensionImages != NULL );

	for (i=0; i< RESS_NUM_IMAGES; i++)
	{
		res->images[i]		= NULL;
		res->dimensionImages[i].largeur = 0;
		res->dimensionImages[i].hauteur = 0;
	}

	/* données */

	res->images[RESS_IMG_VAISSEAU_JOUEUR] 							= RESS_IMG_FICHIER_VAISSEAU_JOUEUR;
	res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].largeur 			= RESS_IMG_LARGEUR_VAISSEAU_JOUEUR;
	res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].hauteur 			= RESS_IMG_HAUTEUR_VAISSEAU_JOUEUR;

	res->images[RESS_IMG_SPLASH]		 							= RESS_IMG_FICHIER_SPLASH;
	res->dimensionImages[RESS_IMG_SPLASH].largeur 					= RESS_IMG_LARGEUR_SPLASH;
	res->dimensionImages[RESS_IMG_SPLASH].hauteur 					= RESS_IMG_HAUTEUR_SPLASH;

	res->images[RESS_IMG_FOND_MENU] 								= RESS_IMG_FICHIER_FOND_MENU;
	res->dimensionImages[RESS_IMG_FOND_MENU].largeur 				= RESS_IMG_LARGEUR_FOND_MENU;
	res->dimensionImages[RESS_IMG_FOND_MENU].hauteur 				= RESS_IMG_HAUTEUR_FOND_MENU;

	res->images[RESS_IMG_FOND_NIVEAU_0] 							= RESS_IMG_FICHIER_FOND_NIVEAU_0;
	res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].largeur 			= RESS_IMG_LARGEUR_FOND_NIVEAU_0;
	res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].hauteur 			= RESS_IMG_HAUTEUR_FOND_NIVEAU_0;
}

void creeListeSons(Ressource *res)
{}

void creeListePolices(Ressource *res)
{}

void chargeJoueurs(Ressource *res)
{
	FILE *fic;
	
	int i;
	char nom[64];/* = NULL;*/
	int numJoueurs=0, score=0, progression=0;
	int valret;
	char dir[64], file[64];
	char *nomFic;
	strcpy(dir, RESS_DIR_SAUVEGARDES);
	strcpy(file, RESS_SAU_FICHIER_JOUEURS);
	nomFic = strcat(dir, file);

	assert( res!=NULL && res->joueurs!=NULL);

	fic 		= fopen(nomFic, "r");
	if(fic == NULL)
	{
		printf("Erreur : (Ressource) : Impossible d'ouvrir le fichier %s.\n", nomFic);
		exit(EXIT_FAILURE);	
	}
	
	fscanf(fic, "%d", &numJoueurs);
	if (numJoueurs > RESS_SAU_MAX_JOUEURS)
		numJoueurs = RESS_SAU_MAX_JOUEURS;

	res->numJoueurs = numJoueurs;
	
	for (i=0; i< numJoueurs; i++)
	{
		valret = fscanf(fic, "%s", nom);
		if (valret < 1)
		{	
			printf("Erreur de lecture du fichier %s : nom joueur illisible.\n", nomFic);
			exit(EXIT_FAILURE);
		}
		valret = fscanf(fic, "%d %d", &progression, &score);
		if (valret != 2)
		{	
			printf("Erreur de lecture du fichier %s : progression et score illisibles.\n", nomFic);
			exit(EXIT_FAILURE);
		}
		
		res->joueurs[i] = (Joueur*)malloc(sizeof(Joueur));
		assert( res->joueurs[i] != NULL);
		joueurInit(res->joueurs[i], nom, (unsigned int)progression, score);		
	}

	fclose(fic); 
}
















/*------------------------------------------------------------------------------------------------------------------
	INTERFACE DU MODULE
*/

void ressourceInit(Ressource *res)
{
	int i;
	assert( res != NULL);

	#ifdef JEU_VERBOSE
		printf("Ressource :\n    initialisation ...\n");
	#endif

	/* --- */
	res->joueurs = (Joueur**)malloc(RESS_SAU_MAX_JOUEURS*sizeof(Joueur*));
	assert( res->joueurs != NULL);

	for (i=0; i< RESS_SAU_MAX_JOUEURS; i++)
		res->joueurs[i] = NULL;/* initialisation à NULL */

	#ifdef JEU_VERBOSE
		printf("	chargement des données joueurs ...\n");
	#endif
	chargeJoueurs(res);

	/* --- */
	creeListeImages(res);

	/* --- */
	creeListeSons(res);

	/* --- */
	creeListePolices(res);

	#ifdef JEU_VERBOSE
		printf("	initialisation OK.\n");
	#endif
}

void ressourceLibere(Ressource *res)
{
	int i;
	for (i=0; i< RESS_SAU_MAX_JOUEURS; i++)
		if (res->joueurs[i] != NULL)
			free(res->joueurs[i]);
	free(res->joueurs);
	free(res->images);
	free(res->dimensionImages);
}

int ressourceGetNumJoueurs(Ressource *res)
{
	assert( res!=NULL);
	return res->numJoueurs;
}
Joueur** ressourceGetJoueurs(Ressource *res)
{
	assert( res != NULL);
	return res->joueurs;
}

int ressourceGetLargeurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->dimensionImages[nomRessource].largeur;
}

int ressourceGetHauteurImage(const Ressource *res, int nomRessource)
{
	assert( nomRessource < RESS_NUM_IMAGES );
	return res->dimensionImages[nomRessource].hauteur;
}



