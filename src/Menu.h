/**
* @file Menu.h
* @brief Le module Menu gère le menu principal du jeu.
* @author Yann Cortial
*
*/
#ifndef _MENU_H
#define _MENU_H






typedef struct
{
	int tmp;
} Menu;



/**
* @brief Initialise le module.
* @param menu[in, out] : doit être non NULL.
*/
void menuInit(Menu *menu);
/**
* @brief Libère les ressources du module.
*/
void menuLibere(Menu *menu);

#endif

