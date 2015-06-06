/**
  *@file Outils.c
  *@brief Fichier d'implémantation du module outils
  * @author Yann Cortial
  */

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "Outils.h"

float getTempsSecondes()
{
    return (float) clock() / (float) CLOCKS_PER_SEC;
}

int randomInt(int borneInf, int borneSup)
{
    return rand() % (borneSup - borneInf) + borneInf;
}

float randomFloat()
{
    return (rand() % 1048576) / 1048576.0f;
}

unsigned char rectangleContient(const Rectangle *rect, int x, int y)
{
    if (x >= rect->x && y >= rect->y && x <= (rect->x + rect->largeur) && y <= (rect->y + rect->hauteur))
        return 1;
    return 0;
}

void tabDynInit(TabDyn *t)
{
    assert(t != NULL);

    t->tab = (void **) malloc(1 * sizeof(void *));
    assert(t->tab != NULL);

    t->capacite = 1;
    t->tailleUtilisee = 0;
}

void tabDynLibere(TabDyn *t)
{
    assert(t != NULL);
    free(t->tab);
    t->tab = NULL;
    t->capacite = -1;
    t->tailleUtilisee = 0;
}

void tabDynAjoute(TabDyn *t, void *element)
{
    int i;
    void **T;
    if (t->tailleUtilisee == t->capacite) {
        T = t->tab;
        t->tab = (void **) malloc(t->capacite * 2 * sizeof(void *));
        assert(t->tab != NULL);
        for (i = 0; i < t->tailleUtilisee; i++)
            t->tab[i] = T[i];
        free(T);
        t->capacite *= 2;
    }

    t->tab[t->tailleUtilisee] = element;
    t->tailleUtilisee++;
}

void *tabDynGetElement(const TabDyn *t, int index)
{
    assert(t != NULL);
    assert(index < t->tailleUtilisee);
    return t->tab[index];
}

void tabDynSupprimeElement(TabDyn *t, int index)
{
    int i;
    void **temp = NULL;
    assert(index >= 0);

    /* Diminution de la taille allouée si nécessaire */
    if (t->tailleUtilisee < t->capacite / 3) {
        temp = t->tab;
        t->capacite /= 2;
        t->tab = (void **) malloc(t->capacite * sizeof(void *));
        for (i = 0; i < t->tailleUtilisee; i++) {
            t->tab[i] = temp[i];
        }
        free(temp);
    }
    /* Decalage des elements du tableau */
    for (i = index; i < t->tailleUtilisee - 1; i++) {
        t->tab[i] = t->tab[i + 1];
    }


    /* ecrasement de l'element */
    /*t->tab[index]=t->tab[t->tailleUtilisee-1];*/

    t->tailleUtilisee--;
}

void tabDynTestDeRegression()
{

}




