/**
* @file Niveau.h
* @brief Le module Niveau décrit le contenu d'un Niveau du jeu.
* @author Yann Cortial
*
*/
#ifndef _NIVEAU_H
#define _NIVEAU_H

typedef struct
{
	/** entier : 1, 2, 3... */
	char numero;
	/** chaîne de caractères : titre du niveau. */
	char *titre;
	/** chaîne de caractères : description courte du niveau. */
	char *description;
} Niveau;



/**
* @brief Initialise.
* @param niveau[in, out] : doit être non NULL.
*/
void niveauInit(Niveau *niveau);
/**
* @brief Libère.
*/
void niveauLibere(Niveau *niveau);


#endif

