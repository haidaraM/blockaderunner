#include <stdio.h>
#include "Jeu.h"



int main ()
{
	Jeu jeu;

	jeuInit( &jeu );
	jeuBoucle( &jeu );
	jeuLibere( &jeu );

	printf("Blockade - status de fin d'execution : OK.\n");
	return 0;
}
