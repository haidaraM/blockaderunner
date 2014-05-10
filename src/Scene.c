/**
* @file Scene.c
* @brief Fichier d'implementation du module
* @author Mohamed El Mouctar HAIDARA - YANN COrtial
*/
#include "Scene.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>



void sceneInit(Scene *scene, Ressource *res, Joueur *player, int largeurGraphique, int hauteurGraphique)
{
    int i;

    assert( scene != NULL && res != NULL && player != NULL);

    scene->horlogePrecedente= 0.0f;
    scene->largeurAffichage = largeurGraphique;
    scene->hauteurAffichage = hauteurGraphique;
    scene->niveau 			= NULL;
	scene->joueur 			= player;
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
                ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_JOUEUR), ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_JOUEUR),
				scene->largeurAffichage, scene->hauteurAffichage);
    elementSetPosition(scene->vaisseauJoueur, 32, (hauteurGraphique - scene->vaisseauJoueur->hauteur)/2);
	scene->vaisseauJoueur->data = (void*)player->vaisseau;
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
    /*elementLibere(scene->vaisseauJoueur); */ /* Bug quand on quitte le niveau et on revient dans la partie */
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
		switch(groupe->type)
		{
		case NIVEAU_GROUPE_ASTEROIDES:

		    for(j=0; j<groupe->nombre; j++)
		    {
		        ElementScene * asteroide = (ElementScene *) malloc(sizeof(ElementScene));
		        elementInit(asteroide, ELEMENT_TYPE_ASTEROIDE, RESS_IMG_ASTEROIDE, ressourceGetLargeurImage(res, RESS_IMG_ASTEROIDE),
			                    ressourceGetHauteurImage(res, RESS_IMG_ASTEROIDE), scene->largeurAffichage, scene->hauteurAffichage );
		        /* Positionnement aleatoire sur la scene */
		        elementSetPosition(asteroide, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
		        tabDynAjoute(&scene->acteurs, (void *)asteroide );
		    }
			break;

		case NIVEAU_GROUPE_ECLAIREURS:

			for(j=0; j<groupe->nombre; j++)
		    {
		        ElementScene * eclaireur = (ElementScene *) malloc(sizeof(ElementScene));
		        elementInit(eclaireur, ELEMENT_TYPE_ECLAIREUR, RESS_IMG_VAISSEAU_ECLAIREUR, ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_ECLAIREUR),
			                    ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_ECLAIREUR), scene->largeurAffichage, scene->hauteurAffichage );
		        /* Positionnement aleatoire sur la scene */
		        elementSetPosition(eclaireur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
		        tabDynAjoute(&scene->acteurs, (void *)eclaireur );
		    }
			break;

		case NIVEAU_GROUPE_CHASSEURS:

			for(j=0; j<groupe->nombre; j++)
		    {
		        ElementScene * chasseur = (ElementScene *) malloc(sizeof(ElementScene));
		        elementInit(chasseur, ELEMENT_TYPE_CHASSEUR, RESS_IMG_VAISSEAU_CHASSEUR, ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_CHASSEUR),
			                    ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_CHASSEUR), scene->largeurAffichage, scene->hauteurAffichage );
		        /* Positionnement aleatoire sur la scene */
		        elementSetPosition(chasseur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
		        tabDynAjoute(&scene->acteurs, (void *)chasseur );
		    }
			break;

		case NIVEAU_GROUPE_CROISEURS:

			for(j=0; j<groupe->nombre; j++)
		    {
		        ElementScene * croiseur = (ElementScene *) malloc(sizeof(ElementScene));
		        elementInit(croiseur, ELEMENT_TYPE_CROISEUR, RESS_IMG_VAISSEAU_CROISEUR, ressourceGetLargeurImage(res, RESS_IMG_VAISSEAU_CROISEUR),
			                    ressourceGetHauteurImage(res, RESS_IMG_VAISSEAU_CROISEUR), scene->largeurAffichage, scene->hauteurAffichage );
		        /* Positionnement aleatoire sur la scene */
		        elementSetPosition(croiseur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
		        tabDynAjoute(&scene->acteurs, (void *)croiseur );
		    }
			break;
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
    int i, dx, x, y, dy, deltaJoueurEnnemi;
    float dt 	= tempsSecondes - scene->horlogePrecedente;
    ElementScene * e=NULL;
    float vitesseDeplacementLaser;

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
        if(elementGetType(e) == ELEMENT_TYPE_LASER_JOUEUR || elementGetType(e)==ELEMENT_TYPE_MISSILE_JOUEUR)
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
			elementSetPosition(e, x-dx*3/4, elementGetY(e));
			/* Suppression des tirs ennemis qui sortent de l'ecran (à gauche)*/
			if (x-dx*3/4 + e->largeur < 0)
			{
				tabDynSupprimeElement(&scene->tirs, i);
			}
		}
    }

    /* Deplacement des Acteurs (asteroides et vaisseaux) de la scene */
    for(i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e = (ElementScene *) tabDynGetElement(&scene->acteurs, i);
        x = elementGetX(e);
		y = elementGetY(e);

        switch(elementGetType(e))
		{
		case ELEMENT_TYPE_ASTEROIDE:
			dx = -(int)(dt * SCENE_VITESSE_ASTEROIDE);
            elementSetPosition(e, x+dx, y);
        	break;
		case ELEMENT_TYPE_DEBRIS_ASTEROIDE:
			dx = (int)(dt * e->vecX * SCENE_VITESSE_ASTEROIDE);
			dy = (int)(dt * e->vecY * SCENE_VITESSE_ASTEROIDE);
			elementSetPosition(e, x+dx, y+dy);
			/* on supprime le debris dès qu'il n'est plus visible */
			if (elementVisible(e) != 1)
				tabDynSupprimeElement(&scene->acteurs, i);
			break;
		case ELEMENT_TYPE_ECLAIREUR:
			dx = -(int)(dt * SCENE_VITESSE_ECLAIREUR);
			dy = 0;
			if (elementVisible(e) == 1)
			{
				deltaJoueurEnnemi = elementGetY(scene->vaisseauJoueur) - y;
				/* L'ennemi  tente de tirer */
				if (abs(deltaJoueurEnnemi) < 64)	
					sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
				dy =  (int)(dt * 0.4f * (float)deltaJoueurEnnemi);/* Les ennemis tentent de s'aligner avec le joueur */
			}
			elementSetPosition(e, x+dx, y+dy);
			break;
		case ELEMENT_TYPE_CHASSEUR:
			dx = -(int)(dt * SCENE_VITESSE_CHASSEUR);
			dy = 0;
			if (elementVisible(e) == 1)
			{
				deltaJoueurEnnemi = elementGetY(scene->vaisseauJoueur) - y;
				/* L'ennemi  tente de tirer */
				if (abs(deltaJoueurEnnemi) < 64)	
					sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
				dy =  (int)(dt * 0.6f * (float)deltaJoueurEnnemi);/* Les ennemis tentent de s'aligner avec le joueur */
			}
			elementSetPosition(e, x+dx, y+dy);
			break;
		case ELEMENT_TYPE_CROISEUR:
			dx = -(int)(dt * SCENE_VITESSE_CROISEUR);
			dy = 0;
			if (elementVisible(e) == 1)
			{
				deltaJoueurEnnemi = elementGetY(scene->vaisseauJoueur) - y;
				/* L'ennemi  tente de tirer */
				if (abs(deltaJoueurEnnemi) < 128)	
					sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
				dy =  (int)(dt * 0.1f * (float)deltaJoueurEnnemi);/* Les ennemis tentent de s'aligner avec le joueur */
			}
			elementSetPosition(e, x+dx, y+dy);
			break;
		default:
			dx = -(int)(dt * SCENE_VITESSE_ASTEROIDE);
            elementSetPosition(e, x+dx, y);
        	break;
        }

		if(x+dx < - (e->largeur))
        {/* Suppression des acteurs qui sortent completement de l'ecran à gauche.*/
         	tabDynSupprimeElement(&scene->acteurs, i);
        }
    }

	
	/* RESOLUTION DES COLLISIONS : */
	sceneTestDeCollision(scene);

    scene->horlogePrecedente = tempsSecondes;
}


void sceneTestDeCollision(Scene *scene)
{
    int i, j, d, numDebris, typeElement;
    ElementScene * t=NULL, *e=NULL;
    assert(scene!=NULL);

	/* On itère sur tous les TIRS du jeu */
    for(i=0; i<sceneGetNbTirs(scene); i++)
    {
        t = (ElementScene *) tabDynGetElement(&scene->tirs, i);
		switch(elementGetType(t))
		{
		case ELEMENT_TYPE_LASER_ENNEMI:

			if(elementTestDeCollision(scene->vaisseauJoueur, t))
        	{
            	tabDynSupprimeElement(&scene->tirs, i);
				/* Le vaisseau du joueur encaisse des dégats */
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, ARME_LASER);
			}
			break;

		case ELEMENT_TYPE_LASER_JOUEUR:

			for(j=0; j<sceneGetNbActeurs(scene); j++)
		    {
		    	e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
				typeElement = elementGetType(e);

				/* Laser contre asteroide : */
		    	if(typeElement == ELEMENT_TYPE_ASTEROIDE)
		        {
		        	/* Les asteroides disparaissent avec un seul tir */
		            if(elementTestDeCollision(t, e))
		            {
		        	    /* Suppression du tir */
		                tabDynSupprimeElement(&scene->tirs, i);
						/* Creation des débris d'asteroide ! */
						numDebris = randomInt(2, 10);
						for (d=0; d < numDebris; d++)
						{
							ElementScene * debris = (ElementScene *) malloc(sizeof(ElementScene));
		        			elementInit(debris, ELEMENT_TYPE_DEBRIS_ASTEROIDE, RESS_IMG_DEBRIS_ASTEROIDE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ),
			                    		ressourceGetHauteurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ), scene->largeurAffichage, scene->hauteurAffichage );
		        			elementSetPosition(debris, elementGetX(e), elementGetY(e));
							elementSetDirection(debris, -1.0f + 2.0f*randomFloat(), -1.0f + 2.0f*randomFloat());
		        			tabDynAjoute(&scene->acteurs, (void *)debris );
						}
		                /* Suppression de l'asteroide */
		                tabDynSupprimeElement(&scene->acteurs, j);
		                /* mise à jour du score */
		                joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+10);
		            }
		        }

				/* Laser contre vaisseau ennemi : */
				if (typeElement == ELEMENT_TYPE_ECLAIREUR || typeElement == ELEMENT_TYPE_CHASSEUR || typeElement == ELEMENT_TYPE_CROISEUR)
				{
					if (elementTestDeCollision(t, e))
					{
						/* Suppression du tir */
		                tabDynSupprimeElement(&scene->tirs, i);
						/* Le vaisseau ennemi encaisse des dégats */
						vaisseauSetDegats((Vaisseau*)e->data, ARME_LASER);
						/* Le vaisseau ennemi est détruit */
						if (vaisseauGetPointStructure((Vaisseau*)e->data) == 0)
						{
							tabDynSupprimeElement(&scene->acteurs, j);
							/* mise à jour du score */
		                	joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+100);
						}
					}
				}
		    }
			break;

        case ELEMENT_TYPE_MISSILE_JOUEUR:

			for(j=0; j<sceneGetNbActeurs(scene); j++)
		    {
		    	e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
				typeElement = elementGetType(e);

		    	if(typeElement == ELEMENT_TYPE_ASTEROIDE)
		        {
		        	/* Les asteroides disparaissent avec un seul tir */
		            if(elementTestDeCollision(t, e))
		            {
		        	    /* Suppression du tir */
		                tabDynSupprimeElement(&scene->tirs, i);
						/* Creation des débris d'asteroide ! */
						numDebris = randomInt(2, 10);
						for (d=0; d < numDebris; d++)
						{
							ElementScene * debris = (ElementScene *) malloc(sizeof(ElementScene));
		        			elementInit(debris, ELEMENT_TYPE_DEBRIS_ASTEROIDE, RESS_IMG_DEBRIS_ASTEROIDE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ),
			                    		ressourceGetHauteurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ), scene->largeurAffichage, scene->hauteurAffichage );
		        			elementSetPosition(debris, elementGetX(e), elementGetY(e));
							elementSetDirection(debris, -1.0f + 2.0f*randomFloat(), -1.0f + 2.0f*randomFloat());
		        			tabDynAjoute(&scene->acteurs, (void *)debris );
						}
		                /* Suppression de l'asteroide */
		                tabDynSupprimeElement(&scene->acteurs, j);
		                /* mise à jour du score */
		                joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+10);
		            }
		        }
			
				/* Missile contre vaisseau ennemi : */
				if (typeElement == ELEMENT_TYPE_ECLAIREUR || typeElement == ELEMENT_TYPE_CHASSEUR || typeElement == ELEMENT_TYPE_CROISEUR)
				{
					if (elementTestDeCollision(t, e))
					{
						/* Suppression du tir */
		                tabDynSupprimeElement(&scene->tirs, i);
						/* Le vaisseau ennemi encaisse des dégats */
						vaisseauSetDegats((Vaisseau*)e->data, ARME_MISSILE);
						/* Le vaisseau ennemi est détruit */
						if (vaisseauGetPointStructure((Vaisseau*)e->data) == 0)
						{
							tabDynSupprimeElement(&scene->acteurs, j);
							/* mise à jour du score */
		                	joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+250);
						}
					}
				}
		    }
			break;


		}
    }

    /* collision vaisseauJoueur - acteurs */
    for(i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e=(ElementScene *) tabDynGetElement(&scene->acteurs, i);
        if(elementTestDeCollision(scene->vaisseauJoueur, e))
        {            
			/* le vaisseau du joueur encaisse des dégats */
			switch(elementGetType(e))
			{
			case ELEMENT_TYPE_ASTEROIDE:
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				break;
			case ELEMENT_TYPE_ECLAIREUR:
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				break;
			case ELEMENT_TYPE_CHASSEUR:
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				break;
			case ELEMENT_TYPE_CROISEUR:
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				vaisseauSetDegats((Vaisseau*)scene->vaisseauJoueur->data, VAISSEAU_COLLISION);
				break;
			}
			/* Suppression de l'acteur */
            tabDynSupprimeElement(&scene->acteurs, i);
        }
    }

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

int sceneJoueurDeclencheTir(Scene * scene)
{
    int valret=-1;
    ElementScene * tir=NULL;
    if(vaisseauGetMunitionsArme(scene->joueur->vaisseau) > 0)
    {
        /* mise à jours des munitions */
        vaisseauMajMunitions(scene->joueur->vaisseau);
        tir=(ElementScene *) malloc(sizeof(ElementScene));
        assert(tir!=NULL);
        switch(joueurGetNumArmeSelectionne(scene->joueur))
        {
        case ARME_LASER:
            elementInit(tir, ELEMENT_TYPE_LASER_JOUEUR, RESS_IMG_TIR_JOUEUR_LASER, ressourceGetLargeurImage(scene->ressource,RESS_IMG_TIR_JOUEUR_LASER),
                        ressourceGetHauteurImage(scene->ressource, RESS_IMG_TIR_JOUEUR_LASER), scene->largeurAffichage, scene->hauteurAffichage );
            valret=0;
            break;
        case ARME_MISSILE:
            elementInit(tir, ELEMENT_TYPE_MISSILE_JOUEUR, RESS_IMG_MISSILE_JOUEUR, ressourceGetLargeurImage(scene->ressource    , RESS_IMG_MISSILE_JOUEUR),
                        ressourceGetHauteurImage(scene->ressource, RESS_IMG_MISSILE_JOUEUR), scene->largeurAffichage, scene->hauteurAffichage);
            valret=1;
            break;
        default :
            break;
        }
        /* positionne le tir en fonction de la position du vaisseau */
        elementSetPosition(tir, elementGetX(scene->vaisseauJoueur), elementGetY(scene->vaisseauJoueur));

        tabDynAjoute(&scene->tirs, (void *) tir);
    }
    return valret;
}

void sceneEnnemiDeclencheTir(Scene * scene, ElementScene *e, float tempsCourant)
{
    ElementScene * tir=NULL;
	Arme *arme = vaisseauGetArmeSelectionnee((Vaisseau*)e->data);

	/* L'ennemi n'a pas eu le temps de recharger son arme : il ne tire pas. */
	if (tempsCourant - arme->tempsDernierTir < arme->cadence)
		return;

	/* Sinon, il tire : */
	arme->tempsDernierTir = tempsCourant; 
    tir=(ElementScene *) malloc(sizeof(ElementScene));
    assert(tir!=NULL);
    elementInit(tir, ELEMENT_TYPE_LASER_ENNEMI, RESS_IMG_TIR_ENNEMI_LASER, ressourceGetLargeurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_LASER),
                        ressourceGetHauteurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_LASER), scene->largeurAffichage, scene->hauteurAffichage );
    /* positionne le tir en fonction de la position du vaisseau */
    elementSetPosition(tir, elementGetX(e), elementGetY(e));
    tabDynAjoute(&scene->tirs, (void *) tir);
}

void sceneTestDeRegression()
{
    printf("Test de regression du module scene \n ");
}






