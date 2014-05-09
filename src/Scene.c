/**
* @file Scene.c
* @brief Fichier d'implementation du module
* @author Mohamed El Mouctar HAIDARA - YANN COrtial
*/
#include "Scene.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>



void sceneInit(Scene *scene, Ressource *res, int largeurGraphique, int hauteurGraphique)
{
    int i;

    assert( scene != NULL && res != NULL );

    scene->horlogePrecedente= 0.0f;
    scene->largeurAffichage = largeurGraphique;
    scene->hauteurAffichage = hauteurGraphique;
    scene->niveau 			= NULL;
    scene->ressource 		= res;

    tabDynInit(&scene->acteurs);
    tabDynInit(&scene->tirs);
    tabDynInit(&scene->bonus);
    tabDynInit(&scene->decors);

    assert( scene->acteurs.tab != NULL && scene->tirs.tab != NULL && scene->bonus.tab != NULL && scene->decors.tab != NULL );


    /* Initialisation des points de défilement */
    scene->pointsDefilement	= (Point*)malloc(SCENE_NUM_POINTS_DEFILEMENT*sizeof(Point));
    assert(scene->pointsDefilement != NULL);
    for (i=0; i< SCENE_NUM_POINTS_DEFILEMENT; i++)
    {
        scene->pointsDefilement[i].x = randomInt(0, scene->largeurAffichage);
        scene->pointsDefilement[i].y = randomInt(0, scene->hauteurAffichage);
    }

    /* initialisation vaisseau du Joueur */
    scene->vaisseauJoueur= (ElementScene*)malloc(sizeof(ElementScene));
    assert( scene->vaisseauJoueur != NULL);
    elementInit(scene->vaisseauJoueur, ELEMENT_TYPE_VAISSEAU_JOUEUR, RESS_IMG_VAISSEAU_JOUEUR,
                ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_JOUEUR), ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_JOUEUR), scene->largeurAffichage, scene->hauteurAffichage);
    elementSetPosition(scene->vaisseauJoueur, 32, (hauteurGraphique - scene->vaisseauJoueur->hauteur)/2);

}

void sceneLibere(Scene *scene)
{
    int i;
    ElementScene *e;
    assert( scene != NULL);

    /* lbération des points de défilement. */
    free(scene->pointsDefilement);

    /* libération des acteurs restants. */
    for (i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->acteurs, i);
        if ( e!= NULL)
        {
            elementLibere(e);
            free(e);
        }
    }
    tabDynLibere(&scene->acteurs);

    /* libération des tirs restants. */
    for (i=0; i<sceneGetNbTirs(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->tirs, i);
        if ( e!= NULL)
        {
            elementLibere(e);
            free(e);
        }
    }
    tabDynLibere(&scene->tirs);

    /* libération des bonus restants. */
    for (i=0; i<sceneGetNbBonus(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->bonus, i);
        if ( e!= NULL)
        {
            elementLibere(e);
            free(e);
        }
    }
    tabDynLibere(&scene->bonus);

    /* libération des éléments de décor restants. */
    for (i=0; i<sceneGetNbDecors(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->decors, i);
        if ( e!= NULL)
        {
            elementLibere(e);
            free(e);
        }
    }
    tabDynLibere(&scene->decors);

    /* Liberation du vaisseauJoueur */
	elementLibere(scene->vaisseauJoueur);
    free(scene->vaisseauJoueur);
}



void sceneChargeNiveau(Scene *scene, Niveau *niveau, Ressource *res )
{
    int i, j, numGroupes;
	GroupeNiveau *groupe;
    assert(scene != NULL && niveau != NULL);

    scene->niveau = niveau;
    scene->indexImageFond = niveau->imageFond;
    scene->rectangleImageFond.x = 0;
    scene->rectangleImageFond.y = 0;
    scene->rectangleImageFond.largeur = scene->largeurAffichage;
    scene->rectangleImageFond.hauteur = scene->hauteurAffichage;

    /* chargement de la composition du niveau */
	numGroupes = niveauGetNumGroupes(niveau);
	for (i=0; i< numGroupes; i++)
	{
		groupe = (GroupeNiveau*)tabDynGetElement(&niveau->composition, i);
		
		/* asteroides ... */
		if (groupe->type == NIVEAU_GROUPE_ASTEROIDES)
		{
		    for(j=0; j<groupe->nombre; j++)
		    {
		        ElementScene * asteroide = (ElementScene *) malloc(sizeof(ElementScene));
		        elementInit(asteroide, ELEMENT_TYPE_ASTEROIDE, RESS_IMG_ASTEROIDE, ressourceGetLargeurImage(res, RESS_IMG_ASTEROIDE),
			                    ressourceGetHauteurImage(res, RESS_IMG_ASTEROIDE), scene->largeurAffichage, scene->hauteurAffichage );
		        /* Positionnement aleatoire sur la scene */
		        elementSetPosition(asteroide, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
		        tabDynAjoute(&scene->acteurs, (void *)asteroide );
		    }
		}
	}		
}

void sceneResetHorloge(Scene *scene, float horloge)
{
    assert(scene != NULL);
    scene->horlogePrecedente = horloge;
}

void sceneDefileScene(Scene *scene)
{
    if ((scene->rectangleImageFond.x + 1) < (4098 - 1366))
        scene->rectangleImageFond.x += 1;
}

void sceneAnime(Scene *scene, float tempsSecondes)
{
    int i, dx, x;
    float dt 	= tempsSecondes - scene->horlogePrecedente;
    ElementScene * e=NULL;
    float vitesseDeplacementLaser, vitesseDeplacementAsteroide;

    /* Points de défilement */
    dx     = -(int)(dt * SCENE_VITESSE_DEFILEMENT_POINTS);
    for (i=0; i< SCENE_NUM_POINTS_DEFILEMENT; i++)
    {
        scene->pointsDefilement[i].x += dx;
        if (scene->pointsDefilement[i].x < 0)
        {
            scene->pointsDefilement[i].x = scene->largeurAffichage -1;
            scene->pointsDefilement[i].y = randomInt(0, scene->hauteurAffichage);
        }
    }

    /* Deplacement des tirs de la scene (tirs joueur et ennemis) */
    vitesseDeplacementLaser 	= SCENE_VITESSE_LASER;
    dx							= (int)(dt * vitesseDeplacementLaser);

    for(i=0; i<sceneGetNbTirs(scene); i++)
    {
        e=(ElementScene *) tabDynGetElement(&scene->tirs, i);
        if(elementGetType(e) == ELEMENT_TYPE_LASER_JOUEUR)
        {
            x = elementGetX(e);
            elementSetPosition(e, x+dx, elementGetY(e));
            /* Suppression des tirs qui sortent de l'ecran */
            if(x+dx > scene->largeurAffichage)
            {
                tabDynSupprimeElement(&scene->tirs, i);
            }
        }
		if (elementGetType(e) == ELEMENT_TYPE_LASER_ENNEMI)
		{
			x = elementGetX(e);
			elementSetPosition(e, x-dx, elementGetY(e));
			/* Suppression des tirs ennemis qui sortent de l'ecran (à gauche)*/
			if (x-dx + e->largeur < 0)
			{
				tabDynSupprimeElement(&scene->tirs, i);
			}
		}
    }

    /* Deplacement des asteroides de la scene */
    vitesseDeplacementAsteroide     = SCENE_VITESSE_ASTEROIDE;
    dx                  = -(int) (dt * vitesseDeplacementAsteroide);
    for(i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e=(ElementScene *) tabDynGetElement(&scene->acteurs, i);
        if(elementGetType(e)==ELEMENT_TYPE_ASTEROIDE)
        {
            x=elementGetX(e);
            elementSetPosition(e, x+dx, elementGetY(e));
            /* Suppression des ennemis qui sortent completement de l'ecran */
            if(x+dx < - e->largeur)
            {
                tabDynSupprimeElement(&scene->acteurs, i);
            }
        }
    }
    scene->horlogePrecedente = tempsSecondes;
}

int sceneGetNbActeurs(const Scene * scene)
{
    assert(scene!=NULL);
    return scene->acteurs.tailleUtilisee;
}
int sceneGetNbTirs(const Scene * scene)
{
    assert(scene!=NULL);
    return scene->tirs.tailleUtilisee;
}
int sceneGetNbBonus(const Scene * scene)
{
    assert(scene!=NULL);
    return scene->bonus.tailleUtilisee;
}
int sceneGetNbDecors(const Scene * scene)
{
    assert(scene!=NULL);
    return scene->decors.tailleUtilisee;
}


ElementScene* sceneCreerElementScene(Scene *scene, int type)
{
    /* To Do */
    return NULL;
}

void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			=scene->vaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/0.88f;
    int dy						= -(int)(tempsSecondes * vitesseDeplacement);
    int y 						= elementGetY( vaiss );

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (y + dy) < 0)
        dy 						= -y;

    elementSetPosition( vaiss, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->vaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/0.88f;
    int dy						= (int)(tempsSecondes * vitesseDeplacement);
    int y 						= elementGetY( vaiss );

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (y + dy) > (vaiss->hauteurSceneVisible - vaiss->hauteur))
        dy 						= (vaiss->hauteurSceneVisible - vaiss->hauteur) - y;

    elementSetPosition( scene->vaisseauJoueur, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->vaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/3.0f;
    int dx						= (int)(tempsSecondes * vitesseDeplacement);
    int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ((x+dx) >(vaiss->largeurSceneVisible - vaiss ->largeur))
        dx                      =(vaiss->largeurSceneVisible - vaiss ->largeur) -x;
    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}

void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			=scene->vaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/3.0f;
    int dx						= -(int)(tempsSecondes * vitesseDeplacement);
    int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (x + dx) < 0)
        dx						= -x;

    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}

void sceneJoueurDeclencheTir(Scene * scene, const Joueur * j,const Ressource *res)
{
    if(vaisseauGetArmeSelectionnee(j->vaisseau).munitions > 0)
    {
        ElementScene * tir=NULL;
        tir=(ElementScene *) malloc(sizeof(ElementScene));
        assert(tir!=NULL);

        switch(vaisseauGetArmeSelectionnee(j->vaisseau).typeArme)
        {
        case ARME_LAZER:
            elementInit(tir, ELEMENT_TYPE_LASER_JOUEUR, RESS_IMG_TIR_JOUEUR_LASER, ressourceGetLargeurImage(res,RESS_IMG_TIR_JOUEUR_LASER),
                        ressourceGetHauteurImage(res, RESS_IMG_TIR_JOUEUR_LASER), scene->largeurAffichage, scene->hauteurAffichage );
            break;
        default :
            break;
        }
        /* positionne le tir en fonction de la position du vaisseau */
        elementSetPosition(tir, elementGetX(scene->vaisseauJoueur), elementGetY(scene->vaisseauJoueur));

        tabDynAjoute(&scene->tirs, (void *) tir);
    }
}

void sceneTestDeCollision(Scene *scene, int *score)
{
    int i, j;
    ElementScene * t=NULL, *e=NULL;
    assert(scene!=NULL);
    /* collision tir - acteurs */
    for(i=0; i<sceneGetNbTirs(scene); i++)
    {
        t=(ElementScene *) tabDynGetElement(&scene->tirs, i);
        for(j=0; j<sceneGetNbActeurs(scene); j++)
        {
            e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
            if(elementGetType(e)==ELEMENT_TYPE_ASTEROIDE)
            {
                /* Les asteroides disparaissent avec un seul tir */
                if(elementTestDeCollision(t, e))
                {
                    /* Suppression du tir */
                    tabDynSupprimeElement(&scene->tirs, i);
                    /* Suppression du l'ennemis : ennemis ou asteroide */
                    tabDynSupprimeElement(&scene->acteurs, j);
                    /* mise à jour du score */
                    *score=*score+10;
                }
            }
        }
    }

    /* collision vaisseauJoueur - acteurs */
    for(j=0; j<sceneGetNbActeurs(scene); j++)
    {
        e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
        if(elementTestDeCollision(scene->vaisseauJoueur, e))
        {
            /* Suppression de l'acteur */
            tabDynSupprimeElement(&scene->acteurs, j);
        }
    }

}

void sceneSetVaisseauJoueur(Scene * scene, Vaisseau * vaisseau)
{
    assert(scene!=NULL);
    assert(vaisseau!=NULL);
    scene->vaisseauJoueur->data=vaisseau;
}

void sceneTestDeRegression()
{
    printf("Test de regression du module scene \n ");
}






