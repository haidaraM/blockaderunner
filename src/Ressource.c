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

    /* Image joueur */
    res->images[RESS_IMG_VAISSEAU_JOUEUR] 							= RESS_IMG_FICHIER_VAISSEAU_JOUEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].largeur 			= RESS_IMG_LARGEUR_VAISSEAU_JOUEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_JOUEUR].hauteur 			= RESS_IMG_HAUTEUR_VAISSEAU_JOUEUR;

    /* Images ennemis */
    res->images[RESS_IMG_VAISSEAU_ECLAIREUR] 						= RESS_IMG_FICHIER_VAISSEAU_ECLAIREUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_ECLAIREUR].largeur 		= RESS_IMG_LARGEUR_VAISSEAU_ECLAIREUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_ECLAIREUR].hauteur 		= RESS_IMG_HAUTEUR_VAISSEAU_ECLAIREUR;

    res->images[RESS_IMG_VAISSEAU_CHASSEUR] 						= RESS_IMG_FICHIER_VAISSEAU_CHASSEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_CHASSEUR].largeur 		= RESS_IMG_LARGEUR_VAISSEAU_CHASSEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_CHASSEUR].hauteur 		= RESS_IMG_HAUTEUR_VAISSEAU_CHASSEUR;

    res->images[RESS_IMG_VAISSEAU_CROISEUR] 						= RESS_IMG_FICHIER_VAISSEAU_CROISEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_CROISEUR].largeur 		= RESS_IMG_LARGEUR_VAISSEAU_CROISEUR;
    res->dimensionImages[RESS_IMG_VAISSEAU_CROISEUR].hauteur 		= RESS_IMG_HAUTEUR_VAISSEAU_CROISEUR;

    /* Images des tirs */
    res->images[RESS_IMG_TIR_JOUEUR_LASER]                          = RESS_IMG_FICHIER_TIR_JOUEUR_LASER;
    res->dimensionImages[RESS_IMG_TIR_JOUEUR_LASER].largeur         = RESS_IMG_LARGEUR_TIR_JOUEUR_LASER;
    res->dimensionImages[RESS_IMG_TIR_JOUEUR_LASER].hauteur         = RESS_IMG_HAUTEUR_TIR_JOUEUR_LASER;

    res->images[RESS_IMG_TIR_ENNEMI_LASER]                          = RESS_IMG_FICHIER_TIR_ENNEMI_LASER;
    res->dimensionImages[RESS_IMG_TIR_ENNEMI_LASER].largeur         = RESS_IMG_LARGEUR_TIR_ENNEMI_LASER;
    res->dimensionImages[RESS_IMG_TIR_ENNEMI_LASER].hauteur         = RESS_IMG_HAUTEUR_TIR_ENNEMI_LASER;

    res->images[RESS_IMG_MISSILE_JOUEUR]                            = RESS_IMG_FICHIER_MISSILE_JOUEUR;
    res->dimensionImages[RESS_IMG_MISSILE_JOUEUR].largeur           = RESS_IMG_LARGEUR_MISSILE_JOUEUR;
    res->dimensionImages[RESS_IMG_MISSILE_JOUEUR].hauteur           = RESS_IMG_HAUTEUR_MISSILE_JOUEUR;

    res->images[RESS_IMG_TIR_ENNEMI_MISSILE]                        = RESS_IMG_FICHIER_TIR_ENNEMI_MISSILE;
    res->dimensionImages[RESS_IMG_TIR_ENNEMI_MISSILE].largeur       = RESS_IMG_LARGEUR_TIR_ENNEMI_MISSILE;
    res->dimensionImages[RESS_IMG_TIR_ENNEMI_MISSILE].hauteur       = RESS_IMG_HAUTEUR_TIR_ENNEMI_MISSILE;

    /* Images des bonus */
    res->images[RESS_IMG_BONUS_SCORE] 		                        = RESS_IMG_FICHIER_BONUS_SCORE;
    res->dimensionImages[RESS_IMG_BONUS_SCORE].largeur      	    = RESS_IMG_LARGEUR_BONUS_SCORE;
    res->dimensionImages[RESS_IMG_BONUS_SCORE].hauteur   	        = RESS_IMG_HAUTEUR_BONUS_SCORE;

    res->images[RESS_IMG_BONUS_MISSILE] 		                    = RESS_IMG_FICHIER_BONUS_MISSILE;
    res->dimensionImages[RESS_IMG_BONUS_MISSILE].largeur      	    = RESS_IMG_LARGEUR_BONUS_MISSILE;
    res->dimensionImages[RESS_IMG_BONUS_MISSILE].hauteur   	        = RESS_IMG_HAUTEUR_BONUS_MISSILE;

    /* Images du menu */
    res->images[RESS_IMG_SPLASH]		 							= RESS_IMG_FICHIER_SPLASH;
    res->dimensionImages[RESS_IMG_SPLASH].largeur 					= RESS_IMG_LARGEUR_SPLASH;
    res->dimensionImages[RESS_IMG_SPLASH].hauteur 					= RESS_IMG_HAUTEUR_SPLASH;

    res->images[RESS_IMG_FOND_MENU] 								= RESS_IMG_FICHIER_FOND_MENU;
    res->dimensionImages[RESS_IMG_FOND_MENU].largeur 				= RESS_IMG_LARGEUR_FOND_MENU;
    res->dimensionImages[RESS_IMG_FOND_MENU].hauteur 				= RESS_IMG_HAUTEUR_FOND_MENU;

    res->images[RESS_IMG_MENU_CMD]                          = RESS_IMG_FICHIER_MENU_CMD;
    res->dimensionImages[RESS_IMG_MENU_CMD].largeur         = RESS_IMG_LARGEUR_MENU_CMD;
    res->dimensionImages[RESS_IMG_MENU_CMD].hauteur         = RESS_IMG_HAUTEUR_MENU_CMD;

    /* Images des niveaux (backgrounds) */
    res->images[RESS_IMG_FOND_NIVEAU_0] 							= RESS_IMG_FICHIER_FOND_NIVEAU_0;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].largeur 			= RESS_IMG_LARGEUR_FOND_NIVEAU;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_0].hauteur 			= RESS_IMG_HAUTEUR_FOND_NIVEAU;

    res->images[RESS_IMG_FOND_NIVEAU_1]                             = RESS_IMG_FICHIER_FOND_NIVEAU_1;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_1].largeur 			= RESS_IMG_LARGEUR_FOND_NIVEAU;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_1].hauteur 			= RESS_IMG_HAUTEUR_FOND_NIVEAU;

    res->images[RESS_IMG_FOND_NIVEAU_2]                             = RESS_IMG_FICHIER_FOND_NIVEAU_2;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_2].largeur            = RESS_IMG_LARGEUR_FOND_NIVEAU;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_2].hauteur            = RESS_IMG_HAUTEUR_FOND_NIVEAU;

    res->images[RESS_IMG_FOND_NIVEAU_3]                             = RESS_IMG_FICHIER_FOND_NIVEAU_3;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_3].largeur            = RESS_IMG_LARGEUR_FOND_NIVEAU;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_3].hauteur            = RESS_IMG_HAUTEUR_FOND_NIVEAU;

    res->images[RESS_IMG_FOND_NIVEAU_4]                             = RESS_IMG_FICHIER_FOND_NIVEAU_4;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_4].largeur            = RESS_IMG_LARGEUR_FOND_NIVEAU;
    res->dimensionImages[RESS_IMG_FOND_NIVEAU_4].hauteur            = RESS_IMG_HAUTEUR_FOND_NIVEAU;

    /* Images asteroides */
    res->images[RESS_IMG_DEBRIS_ASTEROIDE]                          = RESS_IMG_FICHIER_DEBRIS_ASTEROIDE;
    res->dimensionImages[RESS_IMG_DEBRIS_ASTEROIDE].largeur         = RESS_IMG_LARGEUR_DEBRIS_ASTEROIDE;
    res->dimensionImages[RESS_IMG_DEBRIS_ASTEROIDE].hauteur         = RESS_IMG_HAUTEUR_DEBRIS_ASTEROIDE;

    res->images[RESS_IMG_ASTEROIDE]                                 = RESS_IMG_FICHIER_ASTEROIDE;
    res->dimensionImages[RESS_IMG_ASTEROIDE].largeur                = RESS_IMG_LARGEUR_ASTEROIDE;
    res->dimensionImages[RESS_IMG_ASTEROIDE].hauteur                = RESS_IMG_HAUTEUR_ASTEROIDE;
}

void creeListeSons(Ressource *res)
{
    int i, nbSons;
    /* Initialisation des tableaux */
    nbSons=RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS;
    res->sons=(char **)malloc(nbSons * sizeof(char *));
    /* initialisation à NULL; */
    for(i=0; i<nbSons; i++)
    {
        res->sons[i]=NULL;
    }

    /*sons du menu */
    res->sons[RESS_SON_MENU]                                        =RESS_SON_FICHIER_MENU;
    res->sons[RESS_SON_MENU_SURVOL]                                 =RESS_SON_FICHIER_MENU_SURVOL;
    res->sons[RESS_SON_MENU_VALIDATE]                               =RESS_SON_FICHIER_MENU_VALIDATE;

    /*sons arme */
    res->sons[RESS_SON_TIR_LASER]                                   =RESS_SON_FICHIER_TIR_LASER;
    res->sons[RESS_SON_MISSILE]                                     =RESS_SON_FICHIER_MISSILE;
    res->sons[RESS_SON_TIR_LASER_ENNEMI]                            =RESS_SON_FICHIER_TIR_LASER_ENNEMI;
    res->sons[RESS_SON_CHANGE_ARME]                                 =RESS_SON_FICHIER_CHANGE_ARME;

    /* autres sons */
    res->sons[RESS_SON_ERREUR]                                      =RESS_SON_FICHIER_ERREUR;
    res->sons[RESS_SON_MORT]                                        =RESS_SON_FICHIER_MORT;
    res->sons[RESS_SON_AMBIENCE]                                    =RESS_SON_FICHIER_AMBIENCE;
    res->sons[RESS_SON_BONUS_SCORE]                                 =RESS_SON_FICHIER_BONUS_SCORE;

    /* explosions */
    res->sons[RESS_SON_EXPLOSION_ASTEROIDE]                         =RESS_SON_FICHIER_EXPLOSION_ASTEROIDE;
    res->sons[RESS_SON_EXPLOSION_ENNEMI]                            =RESS_SON_FICHIER_EXPLOSION_ENNEMI;
}

void creeListePolices(Ressource *res)
{}

void chargeJoueurs(Ressource *res)
{
    FILE *fic;

    int i;
    char nom[64];
    int numJoueurs=0, score=0, progression=0;
    int valret;
    char nomFic[128], file[64];

    strcpy(nomFic, RESS_DIR_SAUVEGARDES);
    strcpy(file, RESS_SAU_FICHIER_JOUEURS);
    strcat(nomFic, file);

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

void creeNiveaux(Ressource *res)
{
    int i;
    assert(res != NULL);

    res->niveaux = (Niveau*)malloc(RESS_NUM_NIVEAUX * sizeof(Niveau));
    assert( res->niveaux != NULL);

    for (i=0; i< RESS_NUM_NIVEAUX; i++)
    {
        printf("Creation niveau %d\n", i);
        niveauInit(&(res->niveaux[i]), i);
        niveauSetImageFond(&res->niveaux[i], RESS_IMG_FOND_NIVEAU_0 + i);
    }
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
	res->meilleursJoueurs = (Joueur**)malloc(RESS_NUM_MEILLEURS_JOUEURS*sizeof(Joueur*));
    assert( res->joueurs != NULL && res->meilleursJoueurs != NULL);

    for (i=0; i< RESS_SAU_MAX_JOUEURS; i++)
        res->joueurs[i] = NULL;/* initialisation à NULL */
    for (i=0; i< RESS_NUM_MEILLEURS_JOUEURS; i++)
        res->meilleursJoueurs[i] = NULL;/* initialisation à NULL */


#ifdef JEU_VERBOSE
    printf("	chargement des données joueurs.\n");
#endif

    chargeJoueurs(res);

    /* --- */
    creeListeImages(res);

    /* --- */
    creeListeSons(res);

    /* --- */
    creeListePolices(res);

#ifdef JEU_VERBOSE
    printf("	creation des niveaux du jeu.\n");
#endif
    /* --- */
    creeNiveaux(res);

#ifdef JEU_VERBOSE
    printf("	initialisation OK.\n");
#endif
}

void ressourceLibere(Ressource *res)
{
    int i;
    /* Liberation des joueurs */
    for (i=0; i< RESS_SAU_MAX_JOUEURS; i++)
        if (res->joueurs[i] != NULL)
        {
            joueurLibere(res->joueurs[i]);
            free(res->joueurs[i]);
        }
    free(res->joueurs);
    res->joueurs=NULL;
	free(res->meilleursJoueurs);
	res->meilleursJoueurs = NULL;

    /*Liberation des niveaux */
    for(i=0; i<RESS_NUM_NIVEAUX; i++)
    {
        niveauLibere(&res->niveaux[i]);
    }
    free(res->niveaux);
    res->niveaux=NULL;

    free(res->images);
    res->images=NULL;
    free(res->dimensionImages);
    res->dimensionImages=NULL;
    free(res->sons);
    res->sons=NULL;
}

int ressourceGetNumJoueurs(const Ressource *res)
{
    assert( res!=NULL);
    return res->numJoueurs;
}

Joueur** ressourceGetJoueurs(const Ressource *res)
{
    assert( res != NULL);
    return res->joueurs;
}

Joueur** ressourceGetMeilleursJoueurs(const Ressource *res)
{
    assert( res != NULL);
    return res->meilleursJoueurs;
}

void ressourceAjouteJoueur(Ressource *res, char nomJoueur[JOUEUR_NOM_MAXCHAR+1], int indexJoueur)
{
    assert( res != NULL && indexJoueur >= 0);

    if (indexJoueur >= res->numJoueurs)
    {
        indexJoueur = res->numJoueurs;
        res->joueurs[indexJoueur] = (Joueur*)malloc(sizeof(Joueur));
        assert(res->joueurs[indexJoueur] != NULL);
        joueurInit(res->joueurs[indexJoueur], nomJoueur, 0, 0);
        res->numJoueurs += 1;
    }
    else
    {
        joueurInit(res->joueurs[indexJoueur], nomJoueur, 0, 0);
    }
}

void ressourceSauveJoueurs(Ressource *res)
{
    FILE *fic;

    int i;
    int valret;
    char nomFic[128], file[64];

    assert( res!=NULL && res->joueurs!=NULL);

    strcpy(nomFic, RESS_DIR_SAUVEGARDES);
    strcpy(file, RESS_SAU_FICHIER_JOUEURS);
    strcat(nomFic, file);

    fic 		= fopen(nomFic, "w");
    if(fic == NULL)
    {
        printf("Erreur : (Ressource) : Impossible d'ouvrir le fichier %s.\n", nomFic);
        exit(EXIT_FAILURE);
    }

    valret = fprintf(fic, "%d\n", res->numJoueurs);
    assert(valret >= 1);

    for (i=0; i< res->numJoueurs; i++)
    {
        valret = fprintf(fic, "%s\n", res->joueurs[i]->nom);
        if (valret < 1)
        {
            printf("Erreur d'ecriture du fichier %s.\n", nomFic);
            exit(EXIT_FAILURE);
        }
        valret = fprintf(fic, "%d %d\n", (int)res->joueurs[i]->progression, res->joueurs[i]->score);
        if (valret <= 0)
        {
            printf("Erreur d'ecriture du fichier %s.\n", nomFic);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fic);
}

void ressourceTrieJoueurs(Ressource * res)
{
    int i, j, count, fini, indmax, nbJoueurs;
    Joueur ** joueurs = NULL, *joueurMax;
    assert( res!=NULL && res->joueurs!=NULL);

    nbJoueurs=ressourceGetNumJoueurs(res);
	joueurs = (Joueur**)malloc(nbJoueurs*sizeof(Joueur*));
	assert(joueurs != NULL);

	/* on re-copie pour ne pas modifier le tableau original dans Ressource (res) */
	for (i=0; i< nbJoueurs; i++)
		joueurs[i] = res->joueurs[i];

	/* on trie sur le score */
	for(i=0; i<nbJoueurs-1; i++)
    {
        indmax=i;
        for(j=i+1; j<nbJoueurs; j++)
        {
        	if(joueurGetScore(joueurs[j]) > joueurGetScore(joueurs[indmax]))
        	    indmax=j;
        }
        joueurMax=joueurs[indmax];
        joueurs[indmax]=joueurs[i];
        joueurs[i]=joueurMax;
    }

	/* re-init à zero */
	for (i=0; i< RESS_NUM_MEILLEURS_JOUEURS; i++)
		res->meilleursJoueurs[i] = NULL;

	/* on affecte les meilleurs joueurs */
	fini = 0;
	count = 0;
	while (fini == 0)
	{
		res->meilleursJoueurs[count] = joueurs[count];
		count++;
		if (count >= RESS_NUM_MEILLEURS_JOUEURS || count >= nbJoueurs)
			fini = 1;
	}

	free(joueurs);

    /* premier tri par niveau atteint */
    /*for(i=0; i<nbJoueurs-1; i++)
    {
        indmax=i;
        for(j=i+1; j<nbJoueurs; j++)
        {
            if(joueurGetProgression(joueurs[j]) > joueurGetProgression(joueurs[indmax]))
                indmax=j;
        }
        joueurMax=joueurs[indmax];
        joueurs[indmax]=joueurs[i];
        joueurs[i]=joueurMax;
    }*/

	/* par score */
    /*for(i=0; i<nbJoueurs-1; i++)
    {
        indmax=i;
        for(j=i+1; j<nbJoueurs; j++)
        {
            if(joueurGetProgression(joueurs[j]) == joueurGetProgression(joueurs[indmax]))
                if(joueurGetScore(joueurs[j]) > joueurGetScore(joueurs[indmax]))
                    indmax=j;
        }
        joueurMax=joueurs[indmax];
        joueurs[indmax]=joueurs[i];
        joueurs[i]=joueurMax;
    }*/

}

Niveau ressourceGetNiveau(const Ressource *res, int numeroNiveau)
{
    assert(res != NULL && numeroNiveau >=0 && numeroNiveau < RESS_NUM_NIVEAUX);

    return res->niveaux[numeroNiveau];
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

void ressourceTestDeRegression()
{
    Ressource res, tabRes[10];
    int i;
    Joueur ** joueurs=NULL;
    printf("Test de regression du module ressource \n");
    printf("-------------Test de ressourceInit avec un et plusieurs ressources------------------\n");
    ressourceInit(&res);
    assert(res.joueurs!=NULL);
    assert(res.images!=NULL);
    assert(res.sons!=NULL);
    assert(res.niveaux!=NULL);
    for(i=0; i<10; i++)
    {
        ressourceInit(&tabRes[i]);
        assert(tabRes[i].joueurs!=NULL);
        assert(tabRes[i].images!=NULL);
        assert(tabRes[i].sons!=NULL);
        assert(tabRes[i].niveaux!=NULL);

    }
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("-------------Test de ressourceGetLargeurImage avec vaisseauJoueur-----------\n");
    assert(ressourceGetLargeurImage(&res, RESS_IMG_VAISSEAU_JOUEUR)==128);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("-------------Test de ressourceGetHauteurImage avec vaisseauJoueur-----------\n");
    assert(ressourceGetHauteurImage(&res, RESS_IMG_VAISSEAU_JOUEUR)==45);
    printf("=========> Resultat : OK \n");
    printf("\n");


    printf("-------------Test de ressourceGetLargeurImage avec l'image d'intro-----------\n");
    assert(ressourceGetLargeurImage(&res, RESS_IMG_SPLASH)==1366);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("-------------Test de ressourceGetHauteurImage avec l'image d'intro-----------\n");
    assert(ressourceGetHauteurImage(&res, RESS_IMG_SPLASH)==720);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("---------- Test de ressourceGetJoueurs-------------------\n");
    joueurs=ressourceGetJoueurs(&res);
    assert(strcmp(joueurs[0]->nom, "dev")==0);
    printf("=========> Resultat : OK \n");
    printf("\n");


    printf("--------------Test de ressourceLibere-----------\n");
    ressourceLibere(&res);
    assert(res.joueurs==NULL);
    assert(res.images==NULL);
    assert(res.sons==NULL);
    assert(res.niveaux==NULL);
    for(i=0; i<10; i++)
    {
        ressourceLibere(&tabRes[i]);
        assert(tabRes[i].joueurs==NULL);
        assert(tabRes[i].images==NULL);
        assert(tabRes[i].sons==NULL);
        assert(tabRes[i].niveaux==NULL);
    }
    printf("=========> Resultat : OK \n");
    printf("\n");
}

