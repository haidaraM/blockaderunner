#include "Outils.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>


float getTempsSecondes()
{
	return (float)clock()/(float)CLOCKS_PER_SEC;
}

int randomInt(int borneInf, int borneSup)
{
    return rand()%(borneSup-borneInf) +borneInf;
}

float randomFloat()
{
	return (rand()%1048576)/1048576.0f;
}

unsigned char rectangleContient(const Rectangle *rect, int x, int y)
{
    if ( x >= rect->x && y >= rect->y && x <= (rect->x + rect->largeur) && y <= (rect->y + rect->hauteur))
        return 1;
    return 0;
}

void tabDynInit(TabDyn *t)
{
    assert(t != NULL);

    t->tab = (void**)malloc(1*sizeof(void*));
    assert(t->tab != NULL);

    t->capacite = 1;
    t->tailleUtilisee   = 0;
}

void tabDynLibere(TabDyn *t)
{
    assert(t != NULL);
    free(t->tab);
    t->tab = NULL;
    t->capacite = -1;
    t->tailleUtilisee = 0;
}

void tabDynAjoute(TabDyn *t, void* element)
{
    int i;
    void **T;
    if (t->tailleUtilisee == t->capacite)
    {
        T = t->tab;
        t->tab=(void**)malloc(t->capacite * 2 * sizeof(void*));
        assert(t->tab != NULL);
        for (i=0; i< t->tailleUtilisee; i++)
            t->tab[i]=T[i];
        free(T);
        t->capacite *= 2;
    }

    t->tab[t->tailleUtilisee] = element;
    t->tailleUtilisee++;
}

void* tabDynGetElement(const TabDyn *t, int index)
{
    assert(t != NULL );
    assert(index < t->tailleUtilisee);
    return t->tab[index];
}

void tabDynSupprimeElement(TabDyn *t, int index)
{
    int i;
    void ** temp=NULL;
    assert(index>=0);

    if(t->tailleUtilisee < t->capacite/3)
    {
        temp=t->tab;
        t->capacite/=2;
        t->tab=(void **) malloc(t->capacite* sizeof(void *));
        for(i=0; i<t->tailleUtilisee; i++)
        {
            t->tab[i]=temp[i];
        }
        free(temp);
    }

    for(i=index; i<t->tailleUtilisee-1; i++)
    {
        t->tab[i]=t->tab[i+1];
    }
    t->tailleUtilisee--;
}
/* *************************************** Partie liste chainée *************************************** */
void listeInit(Liste *liste)
{
    assert(liste != NULL);
    liste->dernier = NULL;
    liste->premier=NULL;
}

CelluleListe* celluleListeCreer(void *donnee)
{
    CelluleListe *cell = (CelluleListe*)malloc(sizeof(CelluleListe));
    cell->suiv = NULL;
    cell->prec = NULL;
    cell->donnee = donnee;
    return cell;
}

Liste* listeCreer()
{
    Liste* liste;
    liste = (Liste*)malloc(sizeof(Liste));
    assert(liste != NULL);

    listeInit(liste);
    return liste;
}

void listeDetruire(Liste *liste)
{
    listeLibere(liste);
    free(liste);
    liste = NULL;
}

void listeLibere(Liste *liste)
{
    CelluleListe *cell, *suiv;

    assert(liste != NULL);
    cell = liste->premier;

    while (cell != NULL)
    {
        suiv = cell->suiv;
        free(cell);
        cell = suiv;
    }
    liste->dernier=NULL;
    liste->premier=NULL;
}

void listeAjouteTete(Liste *liste, void *donnee)
{
    CelluleListe *nouvelleCellule;
    assert(liste != NULL);
    nouvelleCellule=celluleListeCreer(donnee);

    if (liste->premier==NULL)
    {
        liste->dernier=nouvelleCellule;
    }
    else
    {
        liste->premier->prec=nouvelleCellule;
    }
    nouvelleCellule->suiv = liste->premier;
    liste->premier = nouvelleCellule;
}

void listeAjouteQueue(Liste *liste, void *donnee)
{
    CelluleListe *nouvelleCelule;
    assert(liste != NULL);
    nouvelleCelule=celluleListeCreer(donnee);

    if (liste->dernier==NULL)
    {
        liste->premier = nouvelleCelule;
    }
    else
    {
        liste->dernier->suiv=nouvelleCelule;
    }
    nouvelleCelule->prec=liste->dernier;
    liste->dernier=nouvelleCelule;
}

int listeGetIndex(Liste *liste, void *donnee)
{
    int index = 0;
    CelluleListe *cell;
    assert(liste != NULL);

    cell = liste->premier;
    while (cell != NULL)
    {
        if (donnee == cell->donnee)
            return index;
        index++;
    }

    return  -1;
}

void listeSupprime(Liste *liste, void *donnee)
{
    CelluleListe *cell, *prec;
    assert(liste !=NULL);

    cell = liste->premier;
    if (cell == NULL)
        return;

    if (donnee == cell->donnee)
    {
        liste->premier = cell->suiv;
        free(cell);
        return;
    }

    while (cell !=NULL)
    {
        prec = cell;
        cell = cell->suiv;
        if (donnee == cell->donnee)
        {
            prec->suiv = cell->suiv;
            free(cell);
        }
    }
}



