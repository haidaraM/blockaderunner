#include <stdio.h>
#include "Jeu.h"

/** @file main.c
*
*
* 
* \mainpage
* 	Université Claude Bernard Lyon 1 - Licence Info - LIF7
*	Semestre printemps 2014
*
*
*	Blockade Runner :
*	Un shoot'em up à défilement horizontal, développé en C avec la librairie SDL (libsdl.org).
*
*	Auteurs :
*	Mohamed El Mouctar HAIDARA (p1212684)
*	Yann Cortial (x7005186)
*	
*/
int main ()
{
	Jeu jeu;

	jeuInit( &jeu );
	jeuBoucle( &jeu );
	jeuLibere( &jeu );

	#ifdef JEU_VERBOSE
	printf("Blockade - status de fin d'execution : OK.\n");
	#endif

	return 0;
}
