#include "JeuSDL.h"

/** @file main.c
* @brief Fichier main principal. C'est ici que s'effectue le lancement du jeu
*
*
* \mainpage
* 	Université Claude Bernard Lyon 1 - Licence Info - LIF7
*	Semestre printemps 2014
*
*
*	Blockade Runner :
*	Un shoot'em up à défilement horizontal, développé en C avec les librairie SDL (libsdl.org), SDL_image, SDL_ttf, et FMOD Ex.
*
*	Auteurs :
*	Yann Cortial (x7005186)
*	Mohamed El Mouctar HAIDARA (p1212684)
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*
*/
int main() {
    JeuSDL jeu;

    jeuInit(&jeu);
    jeuBoucle(&jeu);
    jeuLibere(&jeu);

#ifdef JEU_VERBOSE
	printf("Blockade - status de fin d'execution : OK.\n");
#endif

    return 0;
}
