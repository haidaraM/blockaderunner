/**
* @file GraphiqueSDL.c
* @brief Fichier d'implementation du module GraphiqueSDL : SDL_image, SDL_ttf, SDL_gfx
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "GraphiqueSDL.h"
#include "ElementScene.h"
#include "Scene.h"
#include "Outils.h"


/* -----------Fonctions internes ----------------- */

static SDL_Surface *chargeImage(char *nomFichier)
{
    SDL_Surface *image = NULL;
    char file[64], dir[64];

    if (nomFichier == NULL)
        return NULL;

    strcpy(file, nomFichier);
    strcpy(dir, RESS_DIR_IMAGES);

    image = IMG_Load(strcat(dir, file));
    if (image == NULL) {
        fprintf(stderr, "ERREUR : %s (%d) : impossible de charger l'image %s dans %s.\n   %s\n", __FILE__, __LINE__,
                nomFichier, RESS_DIR_IMAGES, IMG_GetError());
    }

    assert(image != NULL);
    return image;
}

static void chargePolices(GraphiqueSDL *graphique)
{
    char file[64], dir[64];
    char *nomFic;
    assert(graphique != NULL);

    strcpy(file, RESS_POL_FICHIER_MENU);
    strcpy(dir, RESS_DIR_POLICES);
    nomFic = strcat(dir, file);

    graphique->policeMenu = TTF_OpenFont(nomFic, RESS_POL_TAILLE_MENU);
    if (!graphique->policeMenu) {
        fprintf(stderr, "ERREUR: %s (%d) TTF_OpenFont: %s\n", __FILE__, __LINE__, TTF_GetError());
        exit(2);
    }

    graphique->policeListeJoueurs = TTF_OpenFont(nomFic, RESS_POL_TAILLE_LISTE_JOUEURS);
    if (!graphique->policeListeJoueurs) {
        fprintf(stderr, "ERREUR: %s (%d) TTF_OpenFont: %s\n", __FILE__, __LINE__, TTF_GetError());
        exit(2);
    }

}

/**
* @brief Affecte à un pixel de la Surface une couleur.
*/
static void setSDLPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* p est l'adresse du pixel ciblé: */
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *) p = pixel;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *) p = pixel;
            break;
    }
}

/**
* @brief calcule la position de la nouvelle surface après rotation
*/
static SDL_Rect positionPivot(int dimension_image, int angle, SDL_Rect position)
{
    double pi = M_PI; /* 3.1415926...*/

    angle %= 360; /* l'angle est ajusté entre 0 et 359° (360° correspondant à un tour complet)*/

    if (angle <= 90) {
        /* cos et sin prennent des valeurs en radian, d'où la conversion angle[rad] = angle[deg]/180.*pi*/
        position.x += dimension_image / 2 * (1 - sin(angle / 180. * pi) - cos(angle / 180. * pi));
        position.y += dimension_image / 2 * (1 - sin(angle / 180. * pi) - cos(angle / 180. * pi));
    }
    else if (angle <= 180) {
        position.x += dimension_image / 2 * (1 - sin(angle / 180. * pi) + cos(angle / 180. * pi));
        position.y += dimension_image / 2 * (1 - sin(angle / 180. * pi) + cos(angle / 180. * pi));
    }
    else if (angle <= 270) {
        position.x += dimension_image / 2 * (1 + sin(angle / 180. * pi) + cos(angle / 180. * pi));
        position.y += dimension_image / 2 * (1 + sin(angle / 180. * pi) + cos(angle / 180. * pi));
    }
    else if (angle <= 360) {
        position.x += dimension_image / 2 * (1 + sin(angle / 180. * pi) - cos(angle / 180. * pi));
        position.y += dimension_image / 2 * (1 + sin(angle / 180. * pi) - cos(angle / 180. * pi));
    }

    return position;
}

/**
* @fn void graphiqueInitAnimation(const GraphiqueSDL * graphique, Animation * monAnimation, int typeEx)
* @brief Initialise les animations : decoupe les images pour constituer les frames
* @param [in] graphique
* @param [in,out] monAnimation
* @param [in] typeEx
*/
static void graphiqueInitAnimation(const GraphiqueSDL *graphique, Animation *monAnimation, int typeEx)
{

    int i;
    SDL_Rect decoupage;

#ifdef JEU_VERBOSE
    printf("    Initialisation des explosions (Animation) : %d .\n", typeEx);
#endif

    decoupage.y = 0;
    switch (typeEx) {

        case ANIMATION_EXPLOSION_0:
            /* creation du tableau de frames */
            animationInitAnimation(monAnimation, ANIMATION_NB_FRAMES_EXPLOSION_0);
            /* parametres de decoupage */
            decoupage.h = RESS_IMG_HAUTEUR_EXPLOSION_0;
            decoupage.w = ANIMATION_HAUTEUR_FRAME_EXPLOSION_0;
            for (i = 0; i < ANIMATION_NB_FRAMES_EXPLOSION_0; i++) {
                animationSetFrame(monAnimation, i, graphique->images[RESS_IMG_EXPLOSION_0],
                                  ANIMATION_DELAI_FRAME_EXPLOSION_0);
                decoupage.x = ANIMATION_HAUTEUR_FRAME_EXPLOSION_0 * i;
                monAnimation->frames[i].decoupage = decoupage;
            }
            break;
        case ANIMATION_EXPLOSION_1:
            /* creation du tableau de frames */
            animationInitAnimation(monAnimation, ANIMATION_NB_FRAMES_EXPLOSION_1);
            /* parametres de decoupage suite */
            decoupage.h = RESS_IMG_HAUTEUR_EXPLOSION_1;
            decoupage.w = ANIMATION_HAUTEUR_FRAME_EXPLOSION_1;
            for (i = 0; i < ANIMATION_NB_FRAMES_EXPLOSION_1; i++) {
                animationSetFrame(monAnimation, i, graphique->images[RESS_IMG_EXPLOSION_1],
                                  ANIMATION_DELAI_FRAME_EXPLOSION_1);
                decoupage.x = ANIMATION_HAUTEUR_FRAME_EXPLOSION_1 * i;
                monAnimation->frames[i].decoupage = decoupage;
            }
            break;
        case ANIMATION_EXPLOSION_2:
            /* creation du tableau de frames */
            animationInitAnimation(monAnimation, ANIMATION_NB_FRAMES_EXPLOSION_2);
            /* parametres de decoupage suite */
            decoupage.h = RESS_IMG_HAUTEUR_EXPLOSION_2;
            decoupage.w = ANIMATION_HAUTEUR_FRAME_EXPLOSION_2;
            for (i = 0; i < ANIMATION_NB_FRAMES_EXPLOSION_2; i++) {
                animationSetFrame(monAnimation, i, graphique->images[RESS_IMG_EXPLOSION_2],
                                  ANIMATION_DELAI_FRAME_EXPLOSION_2);
                decoupage.x = ANIMATION_HAUTEUR_FRAME_EXPLOSION_2 * i;
                monAnimation->frames[i].decoupage = decoupage;
            }
            break;
        default:
            break;
    }

}

/**
* @fn static void graphiqueAlloueAnimateur(GraphiqueSDL * graphique, const Scene * scene)
* @brief Se charge d'associer les images respectives des explosions
* @param [in,out] graphique
* @param [in] scene
*/
static void graphiqueAlloueAnimateur(GraphiqueSDL *graphique, const Scene *scene)
{
    int i;
    for (i = 0; i < sceneGetNbExplosions(scene); i++) {
        PositionExplosion *e = (PositionExplosion *) tabDynGetElement(&scene->positionsExplosions, i);
        /* s'il n'a pas eté encore cree on le cree */
        if (e->ateur == NULL) {
            e->ateur = (Animateur *) malloc(sizeof(Animateur));
            if (e->type == ELEMENT_TYPE_ECLAIREUR){
                animationInitAnimateur((Animateur *) e->ateur, graphique->lesExplosions[ANIMATION_EXPLOSION_0]);
            }
            else if (e->type == ELEMENT_TYPE_CROISEUR){
                animationInitAnimateur((Animateur *) e->ateur, graphique->lesExplosions[ANIMATION_EXPLOSION_2]);
            }
            else if (e->type == ELEMENT_TYPE_CHASSEUR){
                animationInitAnimateur((Animateur *) e->ateur, graphique->lesExplosions[ANIMATION_EXPLOSION_1]);
            }

            animationJoueAnimation(e->ateur);

        }


    }
}


/* ---------------Interface du Module----------------------- */

void graphiqueInit(GraphiqueSDL *graphique, const Ressource *ressource, Menu *menu, int largeur, int hauteur,
                   char *titre, int mode)
{
    SDL_Rect **modes;
    char **fichiersImages;
    int i;
    int imgFlags, imgRes;
    SDL_Color couleurTexteMenu = {249, 255, 253};
    SDL_Color couleurTexteMenuSurvol = {249, 255, 53};
    SDL_Color couleurTexteScore = {249, 153, 86};
    SDL_Color couleurTexteMunitions = {0, 255, 253};
    SDL_Color couleurTexteMort = {255, 0, 0}; /* couleur rouge*/
    SDL_Color couleurTexteFinNiveau = {33, 238, 47}; /* couleur verte*/
    SDL_Color couleurTexteVictoire = {255, 238, 47}; /* couleur jaunatre*/
    Uint32 couleurNiveauStructure = 0x00B0FF; /* jaunatre */
    Uint32 couleurNiveauEcran = 0xFFB000; /* bleu */

    assert(graphique != NULL && ressource != NULL && menu != NULL && largeur > 0 && hauteur > 0);

#ifdef JEU_VERBOSE
    printf("GraphiqueSDL :\n    initialisation ...\n");
#endif

    graphique->surface = 0;
    graphique->largeur = 0;
    graphique->hauteur = 0;
    graphique->titre = GFX_FENETRE_TITRE_DEFAUT;
    graphique->mode = GFX_MODE_FENETRE;


#ifdef JEU_VERBOSE
    /*---------------------------------------------------------------------
    	 Evaluation des modes video disponibles */

    modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
    /* verifie s'il ya plusieurs modes disponibles */
    if(modes == (SDL_Rect **)0)
    {
        fprintf(stderr, "       %s %d No VIDEO modes available!\n", __FILE__, __LINE__);
        exit(-1);
    }

    /* Verifie si la resolution est limitee */
    if(modes == (SDL_Rect **)-1)
    {
        printf("    VIDEO : All resolutions available.\n");
    }
    else
    {
        /* Affiche les modes valides */
        printf("    Available Modes\n");
        for(i=0; modes[i]; ++i)
            printf("      %d x %d\n", modes[i]->w, modes[i]->h);
    }
#endif


    /*---------- Initialisation fenetre principale (SDL)---------------- */

    graphique->surface = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    assert(graphique->surface != NULL);

    /* Initialise la surface accessible (par blit..) à toute la surface graphique : toute opération en dehors de ces limites sera tronquée automatiquement. */
    SDL_SetClipRect(graphique->surface, NULL);

    graphique->couleurFond = SDL_MapRGB(graphique->surface->format, 0x00, 0x00, 0x00);
    graphiqueEfface(graphique);
    graphique->largeur = largeur;
    graphique->hauteur = hauteur;
    if (titre != NULL) {
        SDL_WM_SetCaption(titre, NULL);
        graphique->titre = titre;
    }
    else
        SDL_WM_SetCaption(graphique->titre, NULL);

    /* SDL interprète chaque pixel comme un entier 32 bits non signé :
    	on doit faire attention à l'architecture (BIG ENDIAN vs LITTLE ENDIAN) lors de la création de surfaces. */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    graphique->rmask = 0xff000000;
    graphique->gmask = 0x00ff0000;
    graphique->bmask = 0x0000ff00;
    graphique->amask = 0x000000ff;
#else
    graphique->rmask = 0x000000ff;
    graphique->gmask = 0x0000ff00;
    graphique->bmask = 0x00ff0000;
    graphique->amask = 0xff000000;
#endif

    /*------------------Initialisation de SDL_image ------------------- */

    imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    imgRes = IMG_Init(imgFlags);
    if ((imgRes & imgFlags) != imgFlags) {
        printf("IMG_Init: Impossible d'initialiser SDL_image avec support PNG et JPEG.\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }


    /*--------------Chargement de toutes les images du Jeu : ------------------- */

#ifdef JEU_VERBOSE
    printf("    chargement des images.\n");
#endif
    graphique->images = (SDL_Surface **) malloc(RESS_NUM_IMAGES * sizeof(SDL_Surface *));
    if (graphique->images == NULL) {
        fprintf(stderr, "ERREUR : Ressources (%s %d) : impossible d'allouer la memoire pour les images.\n", __FILE__,
                __LINE__);
        assert(graphique->images != NULL);
    }
    fichiersImages = ressource->images;
    for (i = 0; i < RESS_NUM_IMAGES; i++) {
        graphique->images[i] = 0;
        graphique->images[i] = chargeImage(fichiersImages[i]);
    }
#ifdef JEU_VERBOSE
    printf("    chargement des images OK.\n");
#endif

    /*--------------------- Initialisation de SDL_ttf : -------------------------*/

#ifdef JEU_VERBOSE
    printf("    initialisation SDL_ttf.\n");
#endif
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s(%d) %s\n", __FILE__, __LINE__, TTF_GetError());
        exit(2);
    }

#ifdef JEU_VERBOSE
    printf("    chargement des polices.\n");
#endif
    chargePolices(graphique);

    /* Creation des Elements Menu :
    	MENU_NUM_ELEMENTS paires de rendus de texte (normal & surligné)
    */
    graphique->textesMenu = (SDL_Surface **) malloc(2 * MENU_NUM_ELEMENTS * sizeof(SDL_Surface *));
    if (graphique->textesMenu == NULL) {
        fprintf(stderr, "ERREUR : %s (%d) : impossible d'allouer la memoire pour les rendus de texte (Menu).\n",
                __FILE__, __LINE__);
        assert(graphique->textesMenu != NULL);
    }
#ifdef JEU_VERBOSE
    printf("    rendu du texte (Menu).\n");
#endif
    for (i = 0; i < 2 * MENU_NUM_ELEMENTS; i++) {
        graphique->textesMenu[i] = NULL;
    }
    for (i = 0; i < MENU_NUM_BASIC_ELEMENTS; i++) {
        /* On rend une fois le texte normal */
        graphique->textesMenu[2 * i] = TTF_RenderText_Blended(graphique->policeMenu, menu->elements[i].texte,
                                                              couleurTexteMenu);
        assert(graphique->textesMenu[2 * i] != NULL);
        menu->elements[i].rect.largeur = graphique->textesMenu[2 * i]->w;
        menu->elements[i].rect.hauteur = graphique->textesMenu[2 * i]->h;
        /* On rend une seconde fois avec la couleur correspondant au texte surligné */
        graphique->textesMenu[2 * i + 1] = TTF_RenderText_Blended(graphique->policeMenu, menu->elements[i].texte,
                                                                  couleurTexteMenuSurvol);
        assert(graphique->textesMenu[2 * i + 1] != NULL);
    }
    /* cree le rendu de la liste des noms de joueurs */
    graphiquePrepareRenduListeJoueurs(graphique, menu);

#ifdef JEU_VERBOSE
    printf("    Elements du HUD.\n");
#endif

    /*------------------ Elements du HUD ---------------------------*/

    graphique->elementsHUD = (SDL_Surface **) malloc(GFX_NUM_ELEMENTS_HUD * sizeof(SDL_Surface *));
    assert(graphique->elementsHUD != NULL);
    graphique->elementsHUD[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, GFX_HUD_ELEMENT_LARGEUR, GFX_HUD_ELEMENT_HAUTEUR,
                                                     32,
                                                     graphique->rmask, graphique->gmask, graphique->bmask, 0);
    if (graphique->elementsHUD[0] == NULL) {
        fprintf(stderr, "ERREUR : %s (%d): impossible de créer élément du HUD.  %s\n", __FILE__, __LINE__,
                SDL_GetError());
        exit(1);
    }
    graphique->elementsHUD[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, GFX_HUD_ELEMENT_LARGEUR, GFX_HUD_ELEMENT_HAUTEUR,
                                                     32,
                                                     graphique->rmask, graphique->gmask, graphique->bmask, 0);
    if (graphique->elementsHUD[1] == NULL) {
        fprintf(stderr, "ERREUR : %s (%d): impossible de créer élément du HUD.  %s\n", __FILE__, __LINE__,
                SDL_GetError());
        exit(1);
    }
    /* Application des couleurs */
    SDL_FillRect(graphique->elementsHUD[0], NULL, couleurNiveauStructure);
    SDL_FillRect(graphique->elementsHUD[1], NULL, couleurNiveauEcran);

    /* score */
    graphique->elementsHUD[2] = TTF_RenderText_Blended(graphique->policeListeJoueurs, "Score : ", couleurTexteScore);
    assert(graphique->elementsHUD[2] != NULL);
    graphique->elementsHUD[3] = TTF_RenderText_Blended(graphique->policeListeJoueurs, "0000000", couleurTexteScore);
    assert(graphique->elementsHUD[3] != NULL);

    /* fin de niveau ou mort du joueur */
    graphique->elementsHUD[4] = TTF_RenderText_Blended(graphique->policeMenu, "Vous etes mort", couleurTexteMort);
    graphique->elementsHUD[5] = TTF_RenderText_Blended(graphique->policeMenu, "Fin du niveau", couleurTexteFinNiveau);
    graphique->elementsHUD[7] = TTF_RenderText_Blended(graphique->policeMenu,
                                                       "Mission accomplie! Vous avez brise le blocus de Shantori!",
                                                       couleurTexteVictoire);

    /* init nbre de missiles */
    graphique->elementsHUD[6] = TTF_RenderText_Blended(graphique->policeListeJoueurs, "4",
                                                       couleurTexteMunitions); /* constant 4 is hard-coded no good */

    /* Initialisation des animations */
    graphique->lesExplosions = (Animation **) malloc(NB_ANIMATION * sizeof(Animation *));
    if (graphique->lesExplosions == NULL) {
        fprintf(stderr, "ERREUR : %s (%d) : Impossible d'allouer de la mémoire pour les animations", __FILE__,
                __LINE__);
        exit(3);
    }
    for (i = 0; i < NB_ANIMATION; i++) {
        graphique->lesExplosions[i] = (Animation *) malloc(sizeof(Animation));
        graphiqueInitAnimation(graphique, graphique->lesExplosions[i], i);
    }
    /*------------------------------FIN------------------------------------ */

#ifdef JEU_VERBOSE
    printf("    initialisation OK.\n");
#endif

}

void graphiqueLibere(GraphiqueSDL *graphique)
{
    int i;

    /* Liberation des images */
    for (i = 0; i < RESS_NUM_IMAGES; i++)
        if (graphique->images[i] != NULL)
            SDL_FreeSurface(graphique->images[i]);
    free(graphique->images);

    for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
        if (graphique->textesMenu[2 * i] != NULL)
            SDL_FreeSurface(graphique->textesMenu[2 * i]);
        if (graphique->textesMenu[2 * i + 1] != NULL)
            SDL_FreeSurface(graphique->textesMenu[2 * i + 1]);
    }
    free(graphique->textesMenu);

    /* Liberation des polices */
    TTF_CloseFont(graphique->policeMenu);
    TTF_CloseFont(graphique->policeListeJoueurs);

    /* Liberation des HUD */
    for (i = 0; i < GFX_NUM_ELEMENTS_HUD; i++) {
        SDL_FreeSurface(graphique->elementsHUD[i]);
    }
    free(graphique->elementsHUD);

    /* SDL_ttf */
    TTF_Quit();

    /* SDL_image */
    IMG_Quit();

    /* Animations : explosions */
    for (i = 0; i < NB_ANIMATION; i++) {
        animationLibereAnimation(graphique->lesExplosions[i]);
        free(graphique->lesExplosions[i]);
    }
    free(graphique->lesExplosions);

}

void graphiqueRaffraichit(GraphiqueSDL *graphique)
{
    assert(SDL_Flip(graphique->surface) != -1);
}

void graphiqueSetTitre(GraphiqueSDL *graphique, char *titre)
{
    if (titre != NULL) {
        SDL_WM_SetCaption(titre, NULL);
        graphique->titre = titre;
    }
}

void graphiqueEfface(GraphiqueSDL *graphique)
{
    SDL_FillRect(graphique->surface, &graphique->surface->clip_rect, graphique->couleurFond);
}

void graphiqueSetCouleurFond(GraphiqueSDL *graphique, unsigned char rouge, unsigned char vert, unsigned char bleu)
{
    graphique->couleurFond = SDL_MapRGB(graphique->surface->format, rouge, vert, bleu);
}

void graphiquePrepareRenduListeJoueurs(GraphiqueSDL *graphique, Menu *menu)
{
    int i;
    SDL_Color couleurTexteMenu = {249, 255, 253};
    SDL_Color couleurTexteMenuSurvol = {249, 255, 53};
    assert(graphique != NULL && menu != NULL);

    for (i = MENU_NUM_BASIC_ELEMENTS; i < MENU_NUM_ELEMENTS; i++) {
        if (graphique->textesMenu[2 * i] != NULL) {
            SDL_FreeSurface(graphique->textesMenu[2 * i]);
            graphique->textesMenu[2 * i] = NULL;
        }
        if (graphique->textesMenu[2 * i + 1] != NULL) {
            SDL_FreeSurface(graphique->textesMenu[2 * i + 1]);
            graphique->textesMenu[2 * i + 1] = NULL;
        }
    }

    for (i = MENU_NUM_BASIC_ELEMENTS; i < MENU_NUM_ELEMENTS; i++) {
        /* On rend une fois le texte normal */
        while (graphique->textesMenu[2 * i] == NULL)
            graphique->textesMenu[2 * i] = TTF_RenderText_Blended(graphique->policeListeJoueurs,
                                                                  menu->elements[i].texte, couleurTexteMenu);
        menu->elements[i].rect.largeur = graphique->textesMenu[2 * i]->w;
        menu->elements[i].rect.hauteur = graphique->textesMenu[2 * i]->h;
        /* On rend une seconde fois avec la couleur correspondant au texte surligné */
        while (graphique->textesMenu[2 * i + 1] == NULL)
            graphique->textesMenu[2 * i + 1] = TTF_RenderText_Blended(graphique->policeListeJoueurs,
                                                                      menu->elements[i].texte, couleurTexteMenuSurvol);
    }
}

void graphiqueAfficheMenu(GraphiqueSDL *graphique, const Menu *menu)
{
    int i, count;
    SDL_Rect offset;
    SDL_Surface *nomNouveauJoueur;
    SDL_Color couleurTexteMenuSurvol = {249, 255, 53};
    SDL_Surface **nomsMeilleursJoueurs, **scoresMeilleursJoueurs;

    switch (menu->etat) {
        case MENU_ETAT_INTRO:

            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_SPLASH], NULL, graphique->surface, &offset);
            break;

        case MENU_ETAT_CHOIX_JOUEUR:

            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;

        case MENU_ETAT_ENTREE_JOUEUR:

            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            nomNouveauJoueur = TTF_RenderText_Blended(graphique->policeMenu, menu->nomNouveauJoueur,
                                                      couleurTexteMenuSurvol);
            offset.x = MENU_ZONE_X + MENU_PADDING_HORZ;
            offset.y = MENU_ZONE_Y + 5 * MENU_PADDING_VERT;
            SDL_BlitSurface(nomNouveauJoueur, NULL, graphique->surface, &offset);
            SDL_FreeSurface(nomNouveauJoueur);
            break;

        case MENU_ETAT_SCORE:

            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);

            count = 0;
            nomsMeilleursJoueurs = (SDL_Surface **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(SDL_Surface *));
            scoresMeilleursJoueurs = (SDL_Surface **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(SDL_Surface *));
            assert(nomsMeilleursJoueurs != NULL && scoresMeilleursJoueurs != NULL);

            for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++) {
                nomsMeilleursJoueurs[i] = NULL;
                scoresMeilleursJoueurs[i] = NULL;
                if (menu->nomsMeilleursJoueurs[i] != NULL) {
                    nomsMeilleursJoueurs[i] = TTF_RenderText_Blended(graphique->policeMenu,
                                                                     menu->nomsMeilleursJoueurs[i],
                                                                     couleurTexteMenuSurvol);
                    offset.x = MENU_ZONE_X + 5 * MENU_PADDING_HORZ;
                    offset.y = MENU_ZONE_Y + (5 + 2 * count) * MENU_PADDING_VERT;
                    SDL_BlitSurface(nomsMeilleursJoueurs[i], NULL, graphique->surface, &offset);

                    scoresMeilleursJoueurs[i] = TTF_RenderText_Blended(graphique->policeMenu, menu->meilleursScores[i],
                                                                       couleurTexteMenuSurvol);
                    offset.x = MENU_ZONE_X + 25 * MENU_PADDING_HORZ;
                    SDL_BlitSurface(scoresMeilleursJoueurs[i], NULL, graphique->surface, &offset);
                    count++;
                }
            }
            /* liberation des surfaces */
            for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++) {
                if (nomsMeilleursJoueurs[i] != NULL) {
                    SDL_FreeSurface(nomsMeilleursJoueurs[i]);
                    SDL_FreeSurface(scoresMeilleursJoueurs[i]);
                }
            }
            /* liberation des tableaux de surfaces */
            free(nomsMeilleursJoueurs);
            free(scoresMeilleursJoueurs);

            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;

        case MENU_ETAT_CMD:
            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
            offset.x = MENU_ZONE_X - 6;
            offset.y = MENU_ZONE_Y - 5;
            SDL_BlitSurface(graphique->images[RESS_IMG_MENU_CMD], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;

        case MENU_ETAT_INFO:
            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
            offset.x = MENU_ZONE_X - 7;
            offset.y = MENU_ZONE_Y - 7;
            SDL_BlitSurface(graphique->images[RESS_IMG_MENU_INFO], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;
        case MENU_ETAT_PAUSE:
            offset.x = MENU_ZONE_X;
            offset.y = MENU_ZONE_Y;
            SDL_BlitSurface(graphique->images[RESS_IMG_MENU_PAUSE], NULL, graphique->surface, &offset);

            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;
        case MENU_ETAT_PAUSE_CMD:
            offset.x = MENU_ZONE_X;
            offset.y = MENU_ZONE_Y + 2;
            SDL_BlitSurface(graphique->images[RESS_IMG_MENU_CMD], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;

        case MENU_ETAT_PAUSE_SCORE:
            offset.x = MENU_ZONE_X;
            offset.y = MENU_ZONE_Y;
            SDL_BlitSurface(graphique->images[RESS_IMG_MENU_PAUSE], NULL, graphique->surface, &offset);

            count = 0;
            nomsMeilleursJoueurs = (SDL_Surface **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(SDL_Surface *));
            scoresMeilleursJoueurs = (SDL_Surface **) malloc(RESS_NUM_MEILLEURS_JOUEURS * sizeof(SDL_Surface *));
            assert(nomsMeilleursJoueurs != NULL && scoresMeilleursJoueurs != NULL);

            for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++) {
                nomsMeilleursJoueurs[i] = NULL;
                scoresMeilleursJoueurs[i] = NULL;
                if (menu->nomsMeilleursJoueurs[i] != NULL) {
                    nomsMeilleursJoueurs[i] = TTF_RenderText_Blended(graphique->policeMenu,
                                                                     menu->nomsMeilleursJoueurs[i],
                                                                     couleurTexteMenuSurvol);
                    offset.x = MENU_ZONE_X + 5 * MENU_PADDING_HORZ;
                    offset.y = MENU_ZONE_Y + (5 + 2 * count) * MENU_PADDING_VERT;
                    SDL_BlitSurface(nomsMeilleursJoueurs[i], NULL, graphique->surface, &offset);

                    scoresMeilleursJoueurs[i] = TTF_RenderText_Blended(graphique->policeMenu, menu->meilleursScores[i],
                                                                       couleurTexteMenuSurvol);
                    offset.x = MENU_ZONE_X + 25 * MENU_PADDING_HORZ;
                    SDL_BlitSurface(scoresMeilleursJoueurs[i], NULL, graphique->surface, &offset);
                    count++;
                }
            }
            /* liberation des surfaces */
            for (i = 0; i < RESS_NUM_MEILLEURS_JOUEURS; i++) {
                if (nomsMeilleursJoueurs[i] != NULL) {
                    SDL_FreeSurface(nomsMeilleursJoueurs[i]);
                    SDL_FreeSurface(scoresMeilleursJoueurs[i]);
                }
            }
            /* liberation des tableaux de surfaces */
            free(nomsMeilleursJoueurs);
            free(scoresMeilleursJoueurs);

            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;

        default:

            offset.x = 0;
            offset.y = 0;
            SDL_BlitSurface(graphique->images[RESS_IMG_FOND_MENU], NULL, graphique->surface, &offset);
            for (i = 0; i < MENU_NUM_ELEMENTS; i++) {
                if (menu->elements[i].visible == 1) {
                    offset.x = menu->elements[i].rect.x;
                    offset.y = menu->elements[i].rect.y;
                    if (menu->elements[i].surligne == 0)
                        SDL_BlitSurface(graphique->textesMenu[2 * i], NULL, graphique->surface, &offset);
                    else
                        SDL_BlitSurface(graphique->textesMenu[2 * i + 1], NULL, graphique->surface, &offset);
                }
            }
            break;
    }
}


void graphiqueAfficheScene(GraphiqueSDL *graphique, const Scene *scene)
{
    int i, typeElement, pointS, pointE,amplitudeTremblement=0;
    SDL_Rect srcBox, dstBox, vBox;
    ElementScene **acteurs = (ElementScene **) scene->acteurs.tab;
    ElementScene **tirs = (ElementScene **) scene->tirs.tab;
    ElementScene **bonus = (ElementScene **) scene->bonus.tab;
    ElementScene **decors = (ElementScene **) scene->decors.tab;
    PositionExplosion **explosions = (PositionExplosion **) scene->positionsExplosions.tab;
    SDL_Surface *surfacePointS = NULL, *surfaceRotation;
    Uint32 couleurPointsDefilement = SDL_MapRGB(graphique->surface->format, 0xd0, 0xff, 0xff);


    Uint32 couleurNiveauStructure = 0x00B0FF; /* jaunatre */

    /* affichage du fond */
    srcBox.x = scene->rectangleImageFond.x;
    srcBox.y = scene->rectangleImageFond.y;
    srcBox.w = scene->rectangleImageFond.largeur;
    srcBox.h = scene->rectangleImageFond.hauteur;
    SDL_BlitSurface(graphique->images[scene->indexImageFond], &srcBox, graphique->surface, NULL);

    /* Allocation des animateurs aux explosions si nécessaire */
    graphiqueAlloueAnimateur(graphique, scene);

    /* tremblement de l'écran */
    if(sceneGetNbExplosions(scene)!=0){
        amplitudeTremblement = sceneGetNbExplosions(scene);
        graphiqueVibreEcran(graphique,scene->rectangleImageFond,scene->indexImageFond,amplitudeTremblement);
    }
    /* affichage des explosions */
    for (i = 0; i < sceneGetNbExplosions(scene); i++) {

        dstBox.x = explosions[i]->x - 40;
        dstBox.y = explosions[i]->y - 40;
        /* Affichage de la frame courante */
        animationBlitFrame(explosions[i]->ateur, graphique->surface, &dstBox);
        /* Passage à la frame suivante */
        animationMAJAnimateur(explosions[i]->ateur);
        /* explosion terminée */
        if(animationCheckFin(explosions[i]->ateur)){
            explosions[i]->ateur = NULL;
        }
    }



    /* affichage des decors */
    for (i = 0; i < sceneGetNbDecors(scene); i++) {
        if (decors[i] != NULL && elementVisible(decors[i]) == 1) {
            dstBox.x = elementGetX(decors[i]);
            dstBox.y = elementGetY(decors[i]);
            SDL_BlitSurface(graphique->images[elementGetImageIndex(decors[i])], NULL, graphique->surface, &dstBox);
        }
    }

    /* affichage des points de defilement */
    if (SDL_MUSTLOCK(graphique->surface)) {
        if (SDL_LockSurface(graphique->surface) < 0) {
            printf("Erreur : impossible de verrouiller l'ecran. %s\n", SDL_GetError());
            return;
        }
    }
    for (i = 0; i < SCENE_NUM_POINTS_DEFILEMENT; i++) {
        setSDLPixel(graphique->surface, scene->pointsDefilement[i].x, scene->pointsDefilement[i].y,
                    couleurPointsDefilement);
    }
    if (SDL_MUSTLOCK(graphique->surface)) {
        SDL_UnlockSurface(graphique->surface);
    }

    /* affichage des bonus */
    for (i = 0; i < sceneGetNbBonus(scene); i++) {
        if (bonus[i] != NULL && elementVisible(bonus[i]) == 1) {
            dstBox.x = elementGetX(bonus[i]);
            dstBox.y = elementGetY(bonus[i]);
            SDL_BlitSurface(graphique->images[elementGetImageIndex(bonus[i])], NULL, graphique->surface, &dstBox);
        }
    }

    /* affichage des acteurs : asteroides, ennemis */
    for (i = 0; i < sceneGetNbActeurs(scene); i++) {
        if (acteurs[i] != NULL && elementVisible(acteurs[i]) == 1) {
            typeElement = elementGetType(acteurs[i]);
            dstBox.x = elementGetX(acteurs[i]);
            dstBox.y = elementGetY(acteurs[i]);
            /* Affichage vaisseau ennemmis + barre de vie */
            if (typeElement == ELEMENT_TYPE_ECLAIREUR || typeElement == ELEMENT_TYPE_CHASSEUR ||
                typeElement == ELEMENT_TYPE_CROISEUR) {
                /* affichage vaisseau */
                SDL_BlitSurface(graphique->images[elementGetImageIndex(acteurs[i])], NULL, graphique->surface, &dstBox);
                /* barre de vie */
                surfacePointS = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                                     vaisseauGetPointStructure((Vaisseau *) acteurs[i]->data),
                                                     GFX_EPAISSEUR_BARRE_VIE, 32, graphique->rmask, graphique->gmask,
                                                     graphique->bmask, 0);
                /* coloration */
                SDL_FillRect(surfacePointS, NULL, couleurNiveauStructure);
                dstBox.y -= 4; /* decalage de la barre de vie */
                SDL_BlitSurface(surfacePointS, NULL, graphique->surface, &dstBox);
                SDL_FreeSurface(surfacePointS);
            }
                /* Mise en place de la rotation pour les debris asteroides */
            else if (typeElement == ELEMENT_TYPE_DEBRIS_ASTEROIDE) {
                /* rotation avec un petit dezoomage : 0.9 */
                surfaceRotation = rotozoomSurface(graphique->images[elementGetImageIndex(acteurs[i])],
                                                  sceneGetAngleRotation(scene), 0.9, 1);
                /* calcul approximatif de la position après rotation */
                dstBox = positionPivot(RESS_IMG_LARGEUR_DEBRIS_ASTEROIDE, sceneGetAngleRotation(scene), dstBox);
                SDL_BlitSurface(surfaceRotation, NULL, graphique->surface, &dstBox);
                SDL_FreeSurface(surfaceRotation);
            }
            else /* affichage normale */
                SDL_BlitSurface(graphique->images[elementGetImageIndex(acteurs[i])], NULL, graphique->surface, &dstBox);
        }
    }



    /* affiche du vaisseau joueur */
    vBox.x = elementGetX(scene->elementVaisseauJoueur);
    vBox.y = elementGetY(scene->elementVaisseauJoueur);
    SDL_BlitSurface(graphique->images[elementGetImageIndex(scene->elementVaisseauJoueur)], NULL, graphique->surface,
                    &vBox);

    /* affichage des tirs */
    for (i = 0; i < sceneGetNbTirs(scene); i++) {
        if (tirs[i] != NULL && elementVisible(tirs[i]) == 1) {
            dstBox.x = elementGetX(tirs[i]);
            dstBox.y = elementGetY(tirs[i]);
            SDL_BlitSurface(graphique->images[elementGetImageIndex(tirs[i])], NULL, graphique->surface, &dstBox);
        }
    }

    /* Affichage de l'interface */

    /* Affichage des points structures */
    pointS = vaisseauGetPointStructure(scene->elementVaisseauJoueur->data);
    for (i = 0; i < pointS / 50; i++) {
        dstBox.x = GFX_HUD_ELEMENT_LARGEUR;
        dstBox.y = graphique->hauteur - GFX_HUD_ELEMENT_HAUTEUR -
                   (i + 1) * (GFX_HUD_ELEMENT_HAUTEUR + GFX_HUD_ELEMENT_OFFSET);
        SDL_BlitSurface(graphique->elementsHUD[0], NULL, graphique->surface, &dstBox);
    }
    /* Affichage des points ecran */
    pointE = vaisseauGetPointEcran(scene->elementVaisseauJoueur->data);
    for (i = 0; i < pointE / 50; i++) {
        dstBox.x = 2 * GFX_HUD_ELEMENT_LARGEUR + GFX_HUD_ELEMENT_OFFSET;
        dstBox.y = graphique->hauteur - GFX_HUD_ELEMENT_HAUTEUR -
                   (i + 1) * (GFX_HUD_ELEMENT_HAUTEUR + GFX_HUD_ELEMENT_OFFSET);
        SDL_BlitSurface(graphique->elementsHUD[1], NULL, graphique->surface, &dstBox);
    }
    /* Affichage du nombre de missiles restant */
    dstBox.x = 5 * GFX_HUD_ELEMENT_LARGEUR;
    dstBox.y = graphique->hauteur - 4 * GFX_HUD_ELEMENT_HAUTEUR;
    SDL_BlitSurface(graphique->elementsHUD[6], NULL, graphique->surface, &dstBox);
    dstBox.x = 7 * GFX_HUD_ELEMENT_LARGEUR + GFX_HUD_ELEMENT_OFFSET;
    SDL_BlitSurface(graphique->images[RESS_IMG_MISSILE_JOUEUR], NULL, graphique->surface, &dstBox);

    /* Affichage du score*/
    dstBox.x = graphique->largeur / 2 - graphique->elementsHUD[2]->w;
    dstBox.y = GFX_HUD_ELEMENT_OFFSET;
    SDL_BlitSurface(graphique->elementsHUD[2], NULL, graphique->surface, &dstBox);
    graphiqueSetScore(graphique, joueurGetScore(scene->joueur));
    dstBox.x = GFX_HUD_ELEMENT_LARGEUR + graphique->largeur / 2;
    SDL_BlitSurface(graphique->elementsHUD[3], NULL, graphique->surface, &dstBox);
}

void graphiqueSetScore(GraphiqueSDL *graphique, int score)
{
    static SDL_Color couleurTexteScore = {249, 153, 86};

    /* conversion : entier -> chaîne de caractères */
    char scoreChaine[16];
    int div = JOUEUR_MAX_SCORE / 10;
    int digit;
    int i = 0;
    int s = score;
    if (s >= JOUEUR_MAX_SCORE)
        s = JOUEUR_MAX_SCORE - 1;

    while (div >= 1) {
        digit = s / div;
        scoreChaine[i] = '0' + digit;
        i++;
        s = s - digit * div;
        div /= 10;
    }
    scoreChaine[i] = '\0';

    /* mise à jour du texte */
    SDL_FreeSurface(graphique->elementsHUD[3]);
    graphique->elementsHUD[3] = TTF_RenderText_Blended(graphique->policeListeJoueurs, scoreChaine, couleurTexteScore);
    assert(graphique->elementsHUD[3] != NULL);
}

void graphiqueSetMunitions(GraphiqueSDL *graphique, int numMissiles)
{
    static SDL_Color couleurTexteMunitions = {0, 255, 253};

    char chaineMun[2];
    if (numMissiles > 9)
        numMissiles = 9;/* pour etre sur de rester à un digit */
    chaineMun[0] = '0' + numMissiles;
    chaineMun[1] = '\0';

    SDL_FreeSurface(graphique->elementsHUD[6]);
    graphique->elementsHUD[6] = TTF_RenderText_Blended(graphique->policeListeJoueurs, chaineMun, couleurTexteMunitions);
    assert(graphique->elementsHUD[6] != NULL);
}

void graphiqueAfficheMort(GraphiqueSDL *graphique)
{
    SDL_Rect positionText;
    positionText.x = graphique->largeur / 2 - graphique->elementsHUD[4]->w / 2;
    positionText.y = graphique->hauteur / 2 - graphique->elementsHUD[4]->h / 2;
    assert(graphique != NULL);

    /* On blit le texte au centre de l'ecran */
    SDL_BlitSurface(graphique->elementsHUD[4], NULL, graphique->surface, &positionText);
    /* On met à jour l'ecran */
    graphiqueRaffraichit(graphique);
    /* On met le jeu en pause pendant 3s */
    SDL_Delay(3000);

}

void graphiqueAfficheFinNiveau(GraphiqueSDL *graphique)
{
    SDL_Rect positionText;
    positionText.x = graphique->largeur / 2 - graphique->elementsHUD[5]->w / 2;
    positionText.y = graphique->hauteur / 2 - graphique->elementsHUD[5]->h / 2;
    assert(graphique != NULL);

    /* On blit le texte au centre de l'ecran */
    SDL_BlitSurface(graphique->elementsHUD[5], NULL, graphique->surface, &positionText);
    /* On met à jour l'ecran */
    graphiqueRaffraichit(graphique);
    /* On met le jeu en pause pendant 3s */
    SDL_Delay(3000);
}

void graphiqueAfficheVictoire(GraphiqueSDL *graphique)
{
    SDL_Rect positionText;
    positionText.x = graphique->largeur / 2 - graphique->elementsHUD[7]->w / 2;
    positionText.y = graphique->hauteur / 2 - graphique->elementsHUD[7]->h / 2;
    assert(graphique != NULL);

    /* On blit le texte au centre de l'ecran */
    SDL_BlitSurface(graphique->elementsHUD[7], NULL, graphique->surface, &positionText);
    /* On met à jour l'ecran */
    graphiqueRaffraichit(graphique);
    /* On met le jeu en pause pendant 10s */
    SDL_Delay(10000);
}


void graphiqueVibreEcran(GraphiqueSDL *graphique, Rectangle rectangle, int indexImage, int amplitude){
    SDL_Rect srcBox;
    Rectangle oldRectangle = rectangle;
    srcBox.x =  rectangle.x +randomInt(-amplitude,amplitude);
    srcBox.y =  rectangle.y +randomInt(-amplitude,amplitude);
    srcBox.h = rectangle.hauteur;
    srcBox.w = rectangle.largeur;
    SDL_BlitSurface(graphique->images[indexImage], &srcBox, graphique->surface, NULL);

}


