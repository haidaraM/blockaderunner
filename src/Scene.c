/**
* @file Scene.c
* @brief Fichier d'implementation du module
* @author Yann CORTIAL - Mohamed El Mouctar HAIDARA
*/
#include "Scene.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>


/**
* @fn void sceneInitialiseFlags(Scene * scene)
* @brief Met les flags associés aux sons à zero
* @param [in, out] scene : non null
*/
void sceneInitialiseFlags(Scene * scene)
{
    /* Réinitialisation des evenements */
    scene->evenements.asteroide_explosion   = 0;
    scene->evenements.joueur_tir_laser 		= 0;
    scene->evenements.joueur_tir_missile	= 0;
    scene->evenements.joueur_tir_erreur     = 0;
    scene->evenements.joueur_degats_laser	= 0;
    scene->evenements.joueur_explosion		= 0;
    scene->evenements.joueur_degats_collision = 0;
    scene->evenements.joueur_bonus_missile	= 0;
    scene->evenements.joueur_degats_missile	= 0;
    scene->evenements.joueur_bonus_score	= 0;
    scene->evenements.ennemi_tir_laser		= 0;
    scene->evenements.ennemi_tir_missile	= 0;
    scene->evenements.ennemi_degats_laser	= 0;
    scene->evenements.ennemi_degats_missile	= 0;
    scene->evenements.ennemi_explosion		= 0;

}


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
    tabDynInit(&scene->positionsExplosions);

    assert( scene->acteurs.tab != NULL && scene->tirs.tab != NULL && scene->bonus.tab != NULL && scene->decors.tab != NULL && scene->positionsExplosions.tab != NULL);


    /* Initialisation des points de défilement */
    scene->pointsDefilement	= (Point*)malloc(SCENE_NUM_POINTS_DEFILEMENT*sizeof(Point));
    assert(scene->pointsDefilement != NULL);
    for (i=0; i< SCENE_NUM_POINTS_DEFILEMENT; i++)
    {
        scene->pointsDefilement[i].x = randomInt(0, scene->largeurAffichage);
        scene->pointsDefilement[i].y = randomInt(0, scene->hauteurAffichage);
    }

    /* initialisation vaisseau du Joueur */
    scene->elementVaisseauJoueur= sceneCreerElementScene(scene, ELEMENT_TYPE_VAISSEAU_JOUEUR);
    elementSetPosition(scene->elementVaisseauJoueur, 32, (hauteurGraphique - scene->elementVaisseauJoueur->hauteur)/2);
    scene->elementVaisseauJoueur->data = (void*)player->vaisseau;

    /* mise des flags des evenements son à 0 */
    sceneInitialiseFlags(scene);

}

void sceneLibere(Scene *scene)
{
    int i;
    ElementScene *e;
    PositionExplosion *pos;
    assert( scene != NULL);

    /* lbération des points de défilement. */
    free(scene->pointsDefilement);

    /* libération des acteurs restants. */
    for (i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->acteurs, i);
        if ( e!= NULL)
        {
            sceneDetruitElement(e);
        }
    }
    tabDynLibere(&scene->acteurs);

    /* libération des tirs restants. */
    for (i=0; i<sceneGetNbTirs(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->tirs, i);
        if ( e!= NULL)
        {
            sceneDetruitElement(e);
        }
    }
    tabDynLibere(&scene->tirs);

    /* libération des bonus restants. */
    for (i=0; i<sceneGetNbBonus(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->bonus, i);
        if ( e!= NULL)
        {
            sceneDetruitElement(e);
        }
    }
    tabDynLibere(&scene->bonus);

    /* libération des éléments de décor restants. */
    for (i=0; i<sceneGetNbDecors(scene); i++)
    {
        e=(ElementScene *)tabDynGetElement(&scene->decors, i);
        if ( e!= NULL)
        {
            sceneDetruitElement(e);
        }
    }
    tabDynLibere(&scene->decors);

    /* liberation des animations */
    for(i=0; i<sceneGetNbExplosions(scene); i++)
    {
        pos=(PositionExplosion *) tabDynGetElement(&scene->positionsExplosions, i);
        free(pos->ateur);
        free(pos);
    }
    tabDynLibere(&scene->positionsExplosions);

    /* Liberation du vaisseauJoueur */
    sceneDetruitElement(scene->elementVaisseauJoueur);
    /* Liberation du joueur qu'on a passé à la scene : correspond à la copie */
    joueurLibere(scene->joueur);

}



void sceneChargeNiveau(Scene *scene, Niveau *niveau )
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
                ElementScene * asteroide = sceneCreerElementScene(scene, ELEMENT_TYPE_ASTEROIDE);
                /* Positionnement aleatoire sur la scene */
                elementSetPosition(asteroide, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
                tabDynAjoute(&scene->acteurs, (void *)asteroide );
            }
            break;

        case NIVEAU_GROUPE_ECLAIREURS:

            for(j=0; j<groupe->nombre; j++)
            {
                ElementScene * eclaireur = sceneCreerElementScene(scene, ELEMENT_TYPE_ECLAIREUR);
                /* Positionnement aleatoire sur la scene */
                elementSetPosition(eclaireur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
                tabDynAjoute(&scene->acteurs, (void *)eclaireur );
            }
            break;

        case NIVEAU_GROUPE_CHASSEURS:

            for(j=0; j<groupe->nombre; j++)
            {
                ElementScene * chasseur = sceneCreerElementScene(scene, ELEMENT_TYPE_CHASSEUR);
                /* Positionnement aleatoire sur la scene */
                elementSetPosition(chasseur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
                tabDynAjoute(&scene->acteurs, (void *)chasseur );
            }
            break;

        case NIVEAU_GROUPE_CROISEURS:

            for(j=0; j<groupe->nombre; j++)
            {
                ElementScene * croiseur = sceneCreerElementScene(scene, ELEMENT_TYPE_CROISEUR);
                /* Positionnement aleatoire sur la scene */
                elementSetPosition(croiseur, randomInt(groupe->xmin, groupe->xmax), randomInt(0, 720));
                tabDynAjoute(&scene->acteurs, (void *)croiseur );
            }
            break;
        default :
            break;
        }
    }
}


void sceneResetHorloge(Scene *scene, float horloge)
{
    assert(scene != NULL);
    scene->horlogePrecedente = horloge;
}

int sceneDefileScene(Scene *scene)
{
    if ((scene->rectangleImageFond.x + 1) < (4098 - 1366))
    {
        scene->rectangleImageFond.x += 1;
        return 0;
    }
    else return 1;
}

void sceneAnime(Scene *scene, float tempsSecondes)
{
    int i, dx, x, y, dy, deltaJoueurEnnemi, typeElement;
    float dt 	= tempsSecondes - scene->horlogePrecedente;
    ElementScene * e=NULL;

    /* mise des flags des evenements son à 0 */
    sceneInitialiseFlags(scene);

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

    /* Deplacement des Bonus */
    for (i=0; i< sceneGetNbBonus(scene); i++)
    {
        e = (ElementScene*)tabDynGetElement(&scene->bonus, i);
        x = elementGetX(e);
        y = elementGetY(e);
        dx = (int)(dt * e->vecX * SCENE_VITESSE_BONUS);
        dy = (int)(dt * e->vecY * SCENE_VITESSE_BONUS);
        elementSetPosition(e, x+dx, y+dy);
        /* on supprime le bonus dès qu'il n'est plus visible */
        if (elementVisible(e) != 1)
        {
            sceneDetruitElement(e);
            tabDynSupprimeElement(&scene->bonus, i);
        }
    }

    /* Deplacement des tirs de la scene (tirs joueur et ennemis) */
    for(i=0; i<sceneGetNbTirs(scene); i++)
    {
        e = (ElementScene *) tabDynGetElement(&scene->tirs, i);
        typeElement = elementGetType(e);
        x = elementGetX(e);
        y = elementGetY(e);
        dx = 0;
        dy = 0;
        switch(typeElement)
        {
        case ELEMENT_TYPE_LASER_JOUEUR:
            dx = (int)(dt * SCENE_VITESSE_TIR);
            break;
        case ELEMENT_TYPE_MISSILE_JOUEUR:
            dx = (int)(dt * SCENE_VITESSE_TIR);
            break;
        case ELEMENT_TYPE_LASER_ENNEMI:
            dx = -(int)(dt * SCENE_VITESSE_TIR * 3.0f/4.0f);/* (note:le facteur 3/4 simule la vitesse moindre des lasers ennemis par rapport au laser du joueur) */
            break;
        case ELEMENT_TYPE_MISSILE_ENNEMI:
            dx = -(int)(dt * SCENE_VITESSE_TIR * 3.0f/4.0f);
            deltaJoueurEnnemi = elementGetY(scene->elementVaisseauJoueur) - y;
            dy =  (int)(dt * (float)deltaJoueurEnnemi);/* Les missiles sont à tête chercheuse. */
            break;
        }
        elementSetPosition(e, x+dx, y+dy);
        /* Suppression des tirs qui sortent de l'ecran */
        if(elementVisible(e)!=1)
        {
            sceneDetruitElement(e);
            tabDynSupprimeElement(&scene->tirs, i);
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
            if(x+dx < - (e->largeur))
            {
                /* Suppression des acteurs qui sortent completement de l'ecran à gauche.*/
                sceneDetruitElement(e);
                tabDynSupprimeElement(&scene->acteurs, i);
            }
            break;
        case ELEMENT_TYPE_DEBRIS_ASTEROIDE:
            dx = 1+(int)(dt * e->vecX * 1.5f*SCENE_VITESSE_ASTEROIDE);
            dy = 1+(int)(dt * e->vecY * 1.5f*SCENE_VITESSE_ASTEROIDE);
            /* corrige le probleme des debris qui stagnent */
            if(dx == 0)
                dx+=2;
            elementSetPosition(e, x+dx, y+dy);
            /* on supprime le debris dès qu'il n'est plus visible */
            if (elementVisible(e) != 1)
            {
                sceneDetruitElement(e);
                tabDynSupprimeElement(&scene->acteurs, i);
            }
            break;
        case ELEMENT_TYPE_ECLAIREUR:
            dx = -(int)(dt * SCENE_VITESSE_ECLAIREUR);
            dy = 0;
            if (elementVisible(e) == 1)
            {
                deltaJoueurEnnemi = elementGetY(scene->elementVaisseauJoueur) - y;
                /* L'ennemi  tente de tirer. Il ne tire pas s'il se trouve derriere le vaisseau du joueur */
                if (abs(deltaJoueurEnnemi) < 64 && elementGetX(scene->elementVaisseauJoueur) <= elementGetX(e))
                    sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
                /* Les ennemis tentent de s'aligner sur le joueur */
                dy =  (int)(dt * 0.95f * (float)deltaJoueurEnnemi);
            }
            elementSetPosition(e, x+dx, y+dy);
            if(x+dx < - (e->largeur))
            {
                /* Suppression des acteurs qui sortent completement de l'ecran à gauche.*/
                sceneDetruitElement(e);
                tabDynSupprimeElement(&scene->acteurs, i);
            }
            break;
        case ELEMENT_TYPE_CHASSEUR:
            dx = -(int)(dt * SCENE_VITESSE_CHASSEUR);
            dy = 0;
            if (elementVisible(e) == 1)
            {
                deltaJoueurEnnemi = elementGetY(scene->elementVaisseauJoueur) - y;
                /* L'ennemi  tente de tirer.Il ne tire pas s'il se trouve derriere le vaisseau du joueur */
                if (abs(deltaJoueurEnnemi) < 64 && elementGetX(scene->elementVaisseauJoueur) <= elementGetX(e))
                    sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
                /* Les ennemis tentent de s'aligner sur le joueur */
                dy =  (int)(dt * 0.95f * (float)deltaJoueurEnnemi);
            }
            elementSetPosition(e, x+dx, y+dy);
            if(x+dx < - (e->largeur))
            {
                /* Suppression des acteurs qui sortent completement de l'ecran à gauche.*/
                sceneDetruitElement(e);
                tabDynSupprimeElement(&scene->acteurs, i);
            }
            break;
        case ELEMENT_TYPE_CROISEUR:
            dx = -(int)(dt * SCENE_VITESSE_CROISEUR);
            dy = 0;
            if (elementVisible(e) == 1)
            {
                deltaJoueurEnnemi = elementGetY(scene->elementVaisseauJoueur) - y;
                /* L'ennemi  tente de tirer.Il ne tire pas s'il se trouve derriere le vaisseau du joueur */
                if (abs(deltaJoueurEnnemi) < 128 && elementGetX(scene->elementVaisseauJoueur) <= elementGetX(e))
                    sceneEnnemiDeclencheTir(scene, e, tempsSecondes);
                /* Les ennemis tentent de s'aligner sur le joueur */
                dy =  (int)(dt * 0.6f * (float)deltaJoueurEnnemi);
            }
            elementSetPosition(e, x+dx, y+dy);
            if(x+dx < - (e->largeur))
            {
                /* Suppression des acteurs qui sortent completement de l'ecran à gauche.*/
                sceneDetruitElement(e);
                tabDynSupprimeElement(&scene->acteurs, i);
            }
            break;
        default:
            dx = -(int)(dt * SCENE_VITESSE_ASTEROIDE);
            elementSetPosition(e, x+dx, y);
            break;
        }

    }


    /* RESOLUTION DES COLLISIONS : */
    sceneTestDeCollision(scene);

    scene->horlogePrecedente = tempsSecondes;
}

void sceneCreeBonusEventuel(Scene *scene, ElementScene *pere)
{
    int r;
    switch(elementGetType(pere))
    {
    case ELEMENT_TYPE_ECLAIREUR:
        /* bonus eventuel */
        if (randomInt(0, 101) <= SCENE_PROBA_BONUS_SCORE_ECLAIREUR)
        {
            ElementScene* bonus = sceneCreerElementScene(scene, ELEMENT_TYPE_BONUS_SCORE);
            elementSetPosition(bonus, elementGetX(pere), elementGetY(pere));
            elementSetDirection(bonus, -1.0f + 2.0f*randomFloat(), -1.0f +2.0f*randomFloat());
            tabDynAjoute(&scene->bonus, (void*)bonus);
        }
        break;
    case ELEMENT_TYPE_CHASSEUR:
        /* bonus eventuel */
        if (randomInt(0, 101) <= SCENE_PROBA_BONUS_SCORE_CHASSEUR)
        {
            ElementScene* bonus = sceneCreerElementScene(scene, ELEMENT_TYPE_BONUS_SCORE);
            elementSetPosition(bonus, elementGetX(pere), elementGetY(pere));
            elementSetDirection(bonus, -1.0f + 2.0f*randomFloat(), -1.0f +2.0f*randomFloat());
            tabDynAjoute(&scene->bonus, (void*)bonus);
        }
        break;
    case ELEMENT_TYPE_CROISEUR:
        /* bonus eventuel */
        r = randomInt(0, 101);
        if (r <= SCENE_PROBA_BONUS_MISSILE_CROISEUR)
        {
            ElementScene* bonus = sceneCreerElementScene(scene, ELEMENT_TYPE_BONUS_MISSILE);
            elementSetPosition(bonus, elementGetX(pere), elementGetY(pere));
            elementSetDirection(bonus, -1.0f + 2.0f*randomFloat(), -1.0f +2.0f*randomFloat());
            tabDynAjoute(&scene->bonus, (void*)bonus);
        }
        else if (r <= SCENE_PROBA_BONUS_SCORE_CROISEUR)
        {
            ElementScene* bonus = sceneCreerElementScene(scene, ELEMENT_TYPE_BONUS_SCORE);
            elementSetPosition(bonus, elementGetX(pere), elementGetY(pere));
            elementSetDirection(bonus, -1.0f + 2.0f*randomFloat(), -1.0f +2.0f*randomFloat());
            tabDynAjoute(&scene->bonus, (void*)bonus);
        }
        break;
    }
}

void sceneTestDeCollision(Scene *scene)
{
    int i, j, d, numDebris, typeElement, collision;
    ElementScene * t=NULL, *e=NULL, *b=NULL;
    PositionExplosion *posEx;
    assert(scene!=NULL);

    /* On itère sur tous les BONUS du jeu */
    for(i=0; i<sceneGetNbBonus(scene); i++)
    {
        b = (ElementScene *) tabDynGetElement(&scene->bonus, i);
        switch(elementGetType(b))
        {
        case ELEMENT_TYPE_BONUS_SCORE:

            if (elementTestDeCollision(scene->elementVaisseauJoueur, b))
            {
                sceneDetruitElement(b);
                tabDynSupprimeElement(&scene->bonus, i);
                /* on augmente le score du joueur */
                joueurSetScore(scene->joueur, joueurGetScore(scene->joueur) + SCENE_BONUS_SCORE);
                /* on met le flag associé dans les évènements à 1 */
                scene->evenements.joueur_bonus_score = 1;
            }
            break;

        case ELEMENT_TYPE_BONUS_MISSILE:

            if (elementTestDeCollision(scene->elementVaisseauJoueur, b))
            {
                sceneDetruitElement(b);
                tabDynSupprimeElement(&scene->bonus, i);
                /* on augmente le nombre de missiles restants du joueur */
                joueurAjouteMissiles(scene->joueur, SCENE_BONUS_MISSILE);
                /* on met le flag associé dans les évèenements à 1 */
                scene->evenements.joueur_bonus_missile = 1;
            }
            break;
        }
    }

    /* On itère sur tous les TIRS du jeu */
    for(i=0; i<sceneGetNbTirs(scene); i++)
    {

        t = (ElementScene *) tabDynGetElement(&scene->tirs, i);

        switch(elementGetType(t))
        {
        case ELEMENT_TYPE_LASER_ENNEMI:

            if(elementTestDeCollision(scene->elementVaisseauJoueur, t))
            {
                sceneDetruitElement(t);
                tabDynSupprimeElement(&scene->tirs, i);
#ifdef MODE_NORMAL
                /* Le vaisseau du joueur encaisse des dégats */
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, ARME_LASER);
#endif
                /* on met le flag associé dans les évènements à 1 */
                scene->evenements.joueur_degats_laser = 1;
            }
            break;

        case ELEMENT_TYPE_MISSILE_ENNEMI:

            if(elementTestDeCollision(scene->elementVaisseauJoueur, t))
            {
                sceneDetruitElement(t);
                tabDynSupprimeElement(&scene->tirs, i);
#ifdef MODE_NORMAL
                /* Le vaisseau du joueur encaisse des dégats */
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, ARME_MISSILE);
#endif
                /* on met le flag associé dans les évènements à 1 */
                scene->evenements.joueur_degats_missile = 1;
            }
            break;

        case ELEMENT_TYPE_LASER_JOUEUR:

            j = 0;
            collision = 0;
            while( j < sceneGetNbActeurs(scene)  &&  collision == 0 )
            {
                e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
                typeElement = elementGetType(e);

                /* Laser contre asteroide : */
                if(typeElement == ELEMENT_TYPE_ASTEROIDE)
                {
                    /* Les asteroides disparaissent avec un seul tir */
                    if(elementTestDeCollision(t, e))
                    {
                        collision = 1;
                        /* Suppression du tir du joueur */
                        sceneDetruitElement(t);
                        tabDynSupprimeElement(&scene->tirs, i);
                        /* Creation des débris d'asteroide ! */
                        numDebris = randomInt(2, 10);
                        for (d=0; d < numDebris; d++)
                        {
                            ElementScene * debris = sceneCreerElementScene(scene, ELEMENT_TYPE_DEBRIS_ASTEROIDE);
                            elementSetPosition(debris, elementGetX(e), elementGetY(e));
                            elementSetDirection(debris, -1.0f + 2.0f*randomFloat(), -1.0f + 2.0f*randomFloat());
                            tabDynAjoute(&scene->acteurs, (void *)debris );
                        }
                        /* Suppression de l'asteroide */
                        sceneDetruitElement(e);
                        tabDynSupprimeElement(&scene->acteurs, j);
                        /* mise à jour du score */
                        joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+10);
                        /* on met le flag associé dans les évènements à 1 */
                        scene->evenements.asteroide_explosion = 1;
                    }
                }
                /* Laser contre vaisseau ennemi : */
                else if (typeElement == ELEMENT_TYPE_ECLAIREUR || typeElement == ELEMENT_TYPE_CHASSEUR || typeElement == ELEMENT_TYPE_CROISEUR)
                {
                    if (elementTestDeCollision(t, e))
                    {
                        collision = 1;
                        sceneDetruitElement(t);
                        tabDynSupprimeElement(&scene->tirs, i);
                        /* Le vaisseau ennemi encaisse des dégats */
                        vaisseauSetDegats((Vaisseau*)e->data, ARME_LASER);
                        /* on met le flag associé dans les évènements à 1 */
                        scene->evenements.ennemi_degats_laser = 1;

                        /* Cas où le vaisseau ennemi est détruit */
                        if (vaisseauGetPointStructure((Vaisseau*)e->data) == 0)
                        {
                            /* sauvegarde de la position de la destruction et creation explosion*/
                            posEx=(PositionExplosion *)malloc(sizeof(PositionExplosion));
                            sceneGetDataElement(posEx, e);
                            tabDynAjoute(&scene->positionsExplosions, (void *) posEx);

                            sceneCreeBonusEventuel(scene, e);

                            /* liberation du vaisseau detruit */
                            sceneDetruitElement(e);
                            tabDynSupprimeElement(&scene->acteurs, j);
                            /* mise à jour du score */
                            joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+100);
                            /* on met le flag associé dans les évènements à 1 */
                            scene->evenements.ennemi_explosion = 1;
                        }
                    }
                }

                j++;
            }
            break;

        case ELEMENT_TYPE_MISSILE_JOUEUR:

            j = 0;
            collision = 0;
            while(j<sceneGetNbActeurs(scene)  &&  collision == 0)
            {
                e=(ElementScene *) tabDynGetElement(&scene->acteurs, j);
                typeElement = elementGetType(e);

                if(typeElement == ELEMENT_TYPE_ASTEROIDE)
                {
                    /* Les asteroides disparaissent avec un seul tir */
                    if(elementTestDeCollision(t, e))
                    {
                        collision = 1;
                        /* Suppression du tir */
                        sceneDetruitElement(t);
                        tabDynSupprimeElement(&scene->tirs, i);
                        /* Creation des débris d'asteroide ! */
                        numDebris = randomInt(2, 10);
                        for (d=0; d < numDebris; d++)
                        {
                            ElementScene * debris = sceneCreerElementScene(scene, ELEMENT_TYPE_DEBRIS_ASTEROIDE);
                            elementSetPosition(debris, elementGetX(e), elementGetY(e));
                            elementSetDirection(debris, -1.0f + 2.0f*randomFloat(), -1.0f + 2.0f*randomFloat());
                            tabDynAjoute(&scene->acteurs, (void *)debris );
                        }
                        /* Suppression de l'asteroide */
                        sceneDetruitElement(e);
                        tabDynSupprimeElement(&scene->acteurs, j);
                        /* mise à jour du score */
                        joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+10);
                        /* on met le flag associé dans les évènements à 1 */
                        scene->evenements.asteroide_explosion = 1;
                    }
                }
                else
                    /* Missile contre vaisseau ennemi : */
                    if (typeElement == ELEMENT_TYPE_ECLAIREUR || typeElement == ELEMENT_TYPE_CHASSEUR || typeElement == ELEMENT_TYPE_CROISEUR)
                    {
                        if (elementTestDeCollision(t, e))
                        {
                            collision = 1;
                            /* Suppression du tir */
                            sceneDetruitElement(t);
                            tabDynSupprimeElement(&scene->tirs, i);
                            /* Le vaisseau ennemi encaisse des dégats */
                            vaisseauSetDegats((Vaisseau*)e->data, ARME_MISSILE);
                            /* on met le flag associé dans les évènements à 1 */
                            scene->evenements.ennemi_degats_missile = 1;

                            /* Cas où le vaisseau ennemi est détruit */
                            if (vaisseauGetPointStructure((Vaisseau*)e->data) == 0)
                            {
                                /* sauvegarde de la position de la destruction et creation explosion*/
                                posEx=(PositionExplosion *)malloc(sizeof(PositionExplosion));
                                sceneGetDataElement(posEx, e);
                                tabDynAjoute(&scene->positionsExplosions, (void *) posEx);

                                sceneCreeBonusEventuel(scene, e);

                                sceneDetruitElement(e);
                                tabDynSupprimeElement(&scene->acteurs, j);
                                /* mise à jour du score */
                                joueurSetScore(scene->joueur, joueurGetScore(scene->joueur)+250);
                                /* on met le flag associé dans les évènements à 1 */
                                scene->evenements.ennemi_explosion = 1;
                            }
                        }
                    }

                j++;
            }
            break;
        default :
            break;


        }
    }

    /* collision vaisseauJoueur - acteurs */
    for(i=0; i<sceneGetNbActeurs(scene); i++)
    {
        e=(ElementScene *) tabDynGetElement(&scene->acteurs, i);
        if(elementTestDeCollision(scene->elementVaisseauJoueur, e))
        {
            /* le vaisseau du joueur encaisse des dégats */
            /* on met le flag associé dans les évènements à 1 */
            scene->evenements.joueur_degats_collision = 1;
            switch(elementGetType(e))
            {
#ifdef MODE_NORMAL
            case ELEMENT_TYPE_ASTEROIDE:
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                break;
            case ELEMENT_TYPE_ECLAIREUR:
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                break;
            case ELEMENT_TYPE_CHASSEUR:
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                break;
            case ELEMENT_TYPE_CROISEUR:
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                vaisseauSetDegats((Vaisseau*)scene->elementVaisseauJoueur->data, VAISSEAU_COLLISION);
                break;
#endif
            default :
                break;
            }
            if(elementGetType(e) != ELEMENT_TYPE_ASTEROIDE && elementGetType(e) != ELEMENT_TYPE_DEBRIS_ASTEROIDE)
            {
                /* creation explosion */
                posEx=(PositionExplosion *)malloc(sizeof(PositionExplosion));
                sceneGetDataElement(posEx, e);
                tabDynAjoute(&scene->positionsExplosions, (void *) posEx);
            }
            /* Suppression de l'acteur */
            sceneDetruitElement(e);
            tabDynSupprimeElement(&scene->acteurs, i);
        }
    }

}

void scenePause(Scene * scene)
{
    /* Le temps precedent de la scene recupere le temps qui s'est écoulé depuis le lancement du programme.
    Ainsi on decale l'intervalle de temps sans faire d'animations */
    sceneResetHorloge(scene, getTempsSecondes());
}

int sceneGetNbActeurs(const Scene * scene)
{
    return scene->acteurs.tailleUtilisee;
}
int sceneGetNbTirs(const Scene * scene)
{
    return scene->tirs.tailleUtilisee;
}
int sceneGetNbBonus(const Scene * scene)
{
    return scene->bonus.tailleUtilisee;
}
int sceneGetNbDecors(const Scene * scene)
{
    return scene->decors.tailleUtilisee;
}
int sceneGetNbExplosions(const Scene * scene)
{
    return scene->positionsExplosions.tailleUtilisee;
}


ElementScene* sceneCreerElementScene(const Scene *scene, int type)
{
    ElementScene *e=NULL;
    e=(ElementScene*)malloc(sizeof(ElementScene));
    assert(scene!=NULL);
    assert(e!=NULL);
    switch(type)
    {
    case ELEMENT_TYPE_DEBRIS_ASTEROIDE:
        elementInit(e, ELEMENT_TYPE_DEBRIS_ASTEROIDE, RESS_IMG_DEBRIS_ASTEROIDE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_DEBRIS_ASTEROIDE ), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_BONUS_SCORE:
        elementInit(e, ELEMENT_TYPE_BONUS_SCORE, RESS_IMG_BONUS_SCORE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_BONUS_SCORE),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_BONUS_SCORE), scene->largeurAffichage, scene->hauteurAffichage);
        break;
    case ELEMENT_TYPE_BONUS_MISSILE:
        elementInit(e, ELEMENT_TYPE_BONUS_MISSILE, RESS_IMG_BONUS_MISSILE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_BONUS_MISSILE),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_BONUS_MISSILE), scene->largeurAffichage, scene->hauteurAffichage);
        break;
    case ELEMENT_TYPE_CROISEUR:
        elementInit(e, ELEMENT_TYPE_CROISEUR, RESS_IMG_VAISSEAU_CROISEUR, ressourceGetLargeurImage(scene->ressource, RESS_IMG_VAISSEAU_CROISEUR),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_VAISSEAU_CROISEUR), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_VAISSEAU_JOUEUR:
        elementInit(e, ELEMENT_TYPE_VAISSEAU_JOUEUR, RESS_IMG_VAISSEAU_JOUEUR,ressourceGetLargeurImage(scene->ressource, RESS_IMG_VAISSEAU_JOUEUR), ressourceGetHauteurImage(scene->ressource, RESS_IMG_VAISSEAU_JOUEUR),
                    scene->largeurAffichage, scene->hauteurAffichage);
        break;
    case ELEMENT_TYPE_ECLAIREUR:
        elementInit(e, ELEMENT_TYPE_ECLAIREUR, RESS_IMG_VAISSEAU_ECLAIREUR, ressourceGetLargeurImage(scene->ressource, RESS_IMG_VAISSEAU_ECLAIREUR),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_VAISSEAU_ECLAIREUR), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_ASTEROIDE:
        elementInit(e, ELEMENT_TYPE_ASTEROIDE, RESS_IMG_ASTEROIDE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_ASTEROIDE),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_ASTEROIDE), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_CHASSEUR:
        elementInit(e, ELEMENT_TYPE_CHASSEUR, RESS_IMG_VAISSEAU_CHASSEUR, ressourceGetLargeurImage(scene->ressource, RESS_IMG_VAISSEAU_CHASSEUR),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_VAISSEAU_CHASSEUR), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_LASER_ENNEMI:
        elementInit(e, ELEMENT_TYPE_LASER_ENNEMI, RESS_IMG_TIR_ENNEMI_LASER, ressourceGetLargeurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_LASER),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_LASER), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_MISSILE_ENNEMI:
        elementInit(e, ELEMENT_TYPE_MISSILE_ENNEMI, RESS_IMG_TIR_ENNEMI_MISSILE, ressourceGetLargeurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_MISSILE),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_TIR_ENNEMI_MISSILE), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_LASER_JOUEUR :
        elementInit(e, ELEMENT_TYPE_LASER_JOUEUR, RESS_IMG_TIR_JOUEUR_LASER, ressourceGetLargeurImage(scene->ressource,RESS_IMG_TIR_JOUEUR_LASER),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_TIR_JOUEUR_LASER), scene->largeurAffichage, scene->hauteurAffichage );
        break;
    case ELEMENT_TYPE_MISSILE_JOUEUR:
        elementInit(e, ELEMENT_TYPE_MISSILE_JOUEUR, RESS_IMG_MISSILE_JOUEUR, ressourceGetLargeurImage(scene->ressource    , RESS_IMG_MISSILE_JOUEUR),
                    ressourceGetHauteurImage(scene->ressource, RESS_IMG_MISSILE_JOUEUR), scene->largeurAffichage, scene->hauteurAffichage);
        break;
    default :
        break;
    }
    return e;
}

void sceneDeplaceVaisseauJoueurHaut(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			=scene->elementVaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/0.5f;
    int dy						= -(int)(tempsSecondes * vitesseDeplacement);
    int y 						= elementGetY( vaiss );

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (y + dy) < 0)
        dy 						= -y;

    elementSetPosition( vaiss, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurBas(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->elementVaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/0.5f;
    int dy						= (int)(tempsSecondes * vitesseDeplacement);
    int y 						= elementGetY( vaiss );

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (y + dy) > (vaiss->hauteurSceneVisible - vaiss->hauteur))
        dy 						= (vaiss->hauteurSceneVisible - vaiss->hauteur) - y;

    elementSetPosition( scene->elementVaisseauJoueur, elementGetX( vaiss ), y + dy );
}

void sceneDeplaceVaisseauJoueurDroite(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			= scene->elementVaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/1.5f;
    int dx						= (int)(tempsSecondes * vitesseDeplacement);
    int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ((x+dx) >(vaiss->largeurSceneVisible - vaiss ->largeur))
        dx                      =(vaiss->largeurSceneVisible - vaiss ->largeur) -x;
    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}

void sceneDeplaceVaisseauJoueurGauche(Scene *scene, float tempsSecondes)
{
    ElementScene *vaiss			=scene->elementVaisseauJoueur;
    float vitesseDeplacement 	= 768.0f/1.5f;
    int dx						= -(int)(tempsSecondes * vitesseDeplacement);
    int x                       = elementGetX(vaiss);

    /* Attention à ne pas sortir le vaisseau joueur de l'ecran : */
    if ( (x + dx) < 0)
        dx						= -x;

    elementSetPosition(vaiss, x+dx, elementGetY(vaiss));
}

void sceneJoueurDeclencheTir(Scene * scene)
{
    ElementScene * tir=NULL;
    /* On regarde s'il lui reste des munitions */
    if(vaisseauGetMunitionsArme(scene->joueur->vaisseau) > 0)
    {
        /* mise à jours des munitions */
        vaisseauMajMunitions(scene->joueur->vaisseau);
        switch(joueurGetNumArmeSelectionne(scene->joueur))
        {
        case ARME_LASER:
            tir=sceneCreerElementScene(scene, ELEMENT_TYPE_LASER_JOUEUR);
            /* on met le flag associé dans les évènements à 1 */
            scene->evenements.joueur_tir_laser = 1;
            break;
        case ARME_MISSILE:
            tir=sceneCreerElementScene(scene, ELEMENT_TYPE_MISSILE_JOUEUR);
            /* on met le flag associé dans les évènements à 1 */
            scene->evenements.joueur_tir_missile = 1;
            break;
        default :
            break;
        }
        /* positionne le tir en fonction de la position du vaisseau */
        elementSetPosition(tir, elementGetX(scene->elementVaisseauJoueur), elementGetY(scene->elementVaisseauJoueur));

        tabDynAjoute(&scene->tirs, (void *) tir);
    }
}

int sceneGetMunitionMissileJoueur(const Scene *scene)
{
    int mun = scene->joueur->vaisseau->armes[ARME_MISSILE].munitions;
    if (mun < 0)
        mun = 0;
    return mun;
}

void sceneEnnemiDeclencheTir(Scene * scene, ElementScene *e, float tempsCourant)
{
    ElementScene *tir=NULL;
    Vaisseau *vaisseau = (Vaisseau*)e->data;
    Arme *arme;
    int probaMissile;
    float modCadence = 1.0f;
    int ennemi = elementGetType(e);

    /* Le croiseur dispose de missiles .. */
    if (ennemi == ELEMENT_TYPE_CROISEUR)
    {
        modCadence = 0.33f;
        probaMissile = randomInt(0, 101);
        if (probaMissile < 14)
            vaisseau->numArmeSelectionne = ARME_MISSILE;
        else vaisseau->numArmeSelectionne = ARME_LASER;
    }
    if (ennemi == ELEMENT_TYPE_CHASSEUR)
        modCadence = 0.66f;

    arme = vaisseauGetArmeSelectionnee(vaisseau);

    /* L'ennemi n'a pas eu le temps de recharger son arme OU il n'a plus de munitions : il ne tire pas. */
    /* (note: on ajoute un peu d'aléatoire pour ne pas avoir des tirs métronomiques!)*/
    if (tempsCourant - arme->tempsDernierTir - 0.25f*randomFloat() < modCadence * arme->cadence  ||  vaisseauGetMunitionsArme(vaisseau) <= 0)
        return;

    /* Sinon, il tire : */
    arme->tempsDernierTir = tempsCourant;

    if (arme->typeArme == ARME_LASER)
    {
        tir=sceneCreerElementScene(scene, ELEMENT_TYPE_LASER_ENNEMI);
        /* on met le flag associé dans les évènements à 1 */
        scene->evenements.ennemi_tir_laser = 1;
    }
    else
    {
        /* missile */
        tir=sceneCreerElementScene(scene, ELEMENT_TYPE_MISSILE_ENNEMI);
        vaisseauMajMunitions(vaisseau);
        /* on met le flag associé dans les évènements à 1 */
        scene->evenements.ennemi_tir_missile = 1;
    }

    /* positionne le tir en fonction de la position du vaisseau */
    elementSetPosition(tir, elementGetX(e), elementGetY(e));
    if (ennemi == ELEMENT_TYPE_CROISEUR  &&  randomInt(0, 101) < 50)
        elementSetPosition(tir, elementGetX(e) + 32, elementGetY(e) + 64);/* simple probabilité que le tir vienne d'une tourelle du bas (dans le cas d'un croiseur). */

    tabDynAjoute(&scene->tirs, (void *) tir);
}

int sceneTestVaisseauMort(Scene * scene)
{
    Vaisseau * v=NULL;
    assert(scene!=NULL);
    v=(Vaisseau *)scene->elementVaisseauJoueur->data;
    if(vaisseauGetPointStructure(v)<=0)
    {
        /* on met le flag associé dans les évènements à 1 */
        scene->evenements.joueur_explosion = 1;
        return 1;

    }
    else
        return 0;
}


void sceneDetruitElement(ElementScene *element)
{
    assert(element!=NULL);
    elementLibere(element);
    free(element);
    element=NULL;
}


void sceneGetDataElement(PositionExplosion * pos, const ElementScene * element)
{
    assert(element != NULL);
    pos->x = elementGetX(element);
    pos->y = elementGetY(element);
    pos->type = elementGetType(element);
    pos->ateur=NULL;
}

void sceneTestDeRegression()
{
    Scene sc;
    Ressource res;
    Joueur j;
    printf("Test de regression du module scene \n");

    printf("--------Test de sceneInit --------- \n");
    /* on initialise les ressources et le joueur */
    ressourceInit(&res);
    joueurInit(&j, "dev", 1, 7050);
    sceneInit(&sc, &res, &j, 1366, 720);
    assert(sc.pointsDefilement!=NULL);
    assert(sc.acteurs.tailleUtilisee==0 && sc.acteurs.capacite==1);
    assert(sc.bonus.tailleUtilisee==0 && sc.bonus.capacite==1);

    printf("=========> Resultat : OK \n");
    printf("\n");

    /* Les tests de liberations sont à effecter avec valgrind de préferences */
    printf("--------Test de sceneLibere --------- \n");
    sceneLibere(&sc);
    printf("=========> Resultat : OK \n");
    printf("\n");

    /* on libere les ressources mobilisées */
    ressourceLibere(&res);
}






