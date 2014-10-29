#********************************************************************************#

		++++	+	+++++	+++++	+   +   +++++   +++     +++++   
		+   +	+	+   +	+	+  +	+   +   +  +    +       
		+++++	+	+   +	+	+++	+++++	+   +	++++	
		+   +	+	+   +	+	+  +	+   +	+  +	+		
		++++	+++++	+++++	+++++	+   +	+   +	+++	+++++		  
	
			++++	+   +	+   +	+   +	+++++	++++
			+   +	+   +	+   +	+   +	+	+   +
			++++	+   +	+ + +	+ + +	++++	++++
			+  +	+   +	+  ++ 	+  ++	+  	+  +
			+   +	+++++	+   +	+   +	+++++	+   +

#*******************************************************************************#
# BlockadeRunner #
  
Auteurs : 	Yann Cortial - Mohamed El Mouctar HAIDARA <elmhaidara@gmail.com>



Introduction

	Jeu de type shoot'em up à defilement horizontal réalisé en C avec 
	SDL et FMOD Ex dans le cadre de l'UE LIF7 de l'université Lyon 1 Claude Bernard.
	Resolution minimale : 1366 * 720
	---------------------------------------------------------------
	Le jeu n'est pas destiné à être commercialisé ni à être diffusé.
	Certaines ressources présentes dans le jeu notamment les images
	et les sons sont soumises à des droits.
	---------------------------------------------------------------



####################################################################################

					I N S T A L L A T I O N 

###################################################################################


(1) Dépendances :

	- FMOD Ex:

		Il faudra télécharger la librairie FMOD disponible sur : http://www.fmod.org/download/. 
		Plus précisement la version FMOD Ex Programmer's API ou éventuellement vous le trouverez dans une archive que
		je vous fournirai.
		 -	Dans l'archive téléchargé, copiez le dossier api (en le rennomant en "lib") dans le dossier du projet.
			Ce repertoire contient les fichiers nécessaires au bon fonctionnement de la librairie. 
	 	 -	Ensuite il faudra copier  le fichier ./lib/lib/libfmodex64-4.44.33.so (le numero peut varier selon 
	 	 	votre version) dans le repertoire /usr/lib/ en le rennomant en libfmodex64.so.
	 		Ce n'est pas la meilleure façon de faire mais ça marche quand même sur un pc 64bits. 
	 		Pour un systeme 32 bits, copier le fichier 	libfmodex-4.44.33.so  en le rennomant aussi en libfmodex64.so 
	 		Si ces manips ne fonctionnent pas : http://sindev.blogspot.fr/2009/02/how-to-installer-la-fmod-ex-sur-linux.html
	 
	 - SDL 1.2 : SDL_ttf, SDL_image, SDL_gfx
		
		Il suffit juste d'installer SDL 1.2 avec ses librairies associées (SDL_image, SDL_ttf et SDL_gfx), pas de manipulation particulière à effectuer.

		(linux) 		$ sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev
		(documentation : http://www.libsdl.org/release/SDL-1.2.15/docs/html/)

	 	En cas de problemes :  http://doc.ubuntu-fr.org/sdl
	 				     http://fr.openclassrooms.com/informatique/cours/apprenez-a-programmer-en-c/installation-de-la-sdl 
	 				     http://loka.developpez.com/tutoriel/sdl/installation/
	
	- Fichiers Data : En recuperant le projet sur le depot, il manquera les fichiers de données nécessaire pour faire marcher le jeu


(2) Télécharger l'archive compressée : blockade.tar.gz dans lequel vous trouverez les fichiers manquants

				(decompresser)	$ tar -xvzf blockade.tar.gz

(3) Compilation :

				Ouvrir le fichier Makefile avec un éditeur de texte,
				décommenter éventuellement les deux define selon les besoins : 

						MODE_JEU 	= MODE_NORMAL				#mode de jeu standard.
						#MODE_JEU	= MODE_INVULNERABLE			#permet de jouer sans encaisser de dégâts : utile pour tester le jeu de A à Z.

						VERBOSE 	= JEU_VERBOSE				#status d'initialisation affiché sur la sortie standard.
						#VERBOSE	= NO_VERBOSE				#aucun message sur la sortie standard hormis les messages d'erreurs éventuels.

						EXPLOSION		= NO_REPETE_EXPLOSION 	#Permet de ne pas repeter les animations sur la scene
						#EXPLOSION  	= REPETE_EXPLOSION 		#Perment de repeter les animations. Plus amusant

					
				Lancer la compilation avec :

								$ make


(4) Documentation interne :

				(doxygen)		$ doxygen doc/blockade.doxy

	
################################################################################################

					M A N U E L

################################################################################################


(1) Lancer le jeu 

		$ bin/blockade


(2) Commandes pour jouer à Blockade Runner :

		- Souris 							: pour naviguer dans le menu
		- Flèches directionnelles			: déplacer le vaisseau
		- Barre espace 						: tirer
		- F5								: choisir l'arme laser
		- F6								: choisir l'arme missiles


#############################################################################################

			D O C U M E N T A T I O N   A N N E X E

############################################################################################


(1) Fonctionnalités du programme :

	 	# Menu
		- Choisir un joueur existant
		- Créer un nouveau joueur
		- Navigation 
		- Voir les 5 meilleurs joueurs (classement sur le score)
		- Voir les commandes du jeu
		- Avoir des infos sur le programme
		- Choisir un niveau de jeu
		- Lancer le jeu

		# Jeu
		- Se déplacer
		- Tirer au laser
		- Tirer des missiles
		- Récolter des bonus (score et missile)
		- Eviter les astéroides : en les détruisant ou en se déplaçant
		- Eviter de percuter des vaisseaux ennemis.
		- Eviter les tirs ennemis (laser et missiles 'à tête chercheuse')
		- Détruire un maximum d'ennemis afin de maximiser son score
		- Compléter un niveau en survivant jusqu'au bout.
	
(2) Format des fichiers :

		### Fichiers NIVEAU : exemple de fichier	

Chasseurs
3000 3100 1
Chasseurs
3600 3700 2
Croiseurs
3000 3100 1
Eclaireurs
5700 12000 24
Chasseurs
14000 22000 32
Asteroides
15000 18000 40
Eclaireurs
15000 16000 1
Eclaireurs
18500 24000 13

Chaque paire de lignes définit un GroupeNiveau : 

		- le type de groupe ('Chasseurs', 'Croiseurs', 'Eclaireurs', 'Asteroides') : type des éléments qui seront générés pour le groupe.
		- trois entiers représentant dans l'ordre :
				* la valeur minimale en pixels (et en abscisse), de la zone où seront générés les éléments du groupe.
				* la valeur maximale en pixels (et en abscisse), de la zone où _____________________________________.
				* le nombre d'éléments à générer.

		### Fichier JOUEURS : exemple fichier

6
dev
0 100
Mohamed
3 75454
Cortial
7 91004
toto2000
0 0

Le premier chiffre représente le nombre de joueurs
Puis chaque paire de lignes définit un joueur :
		
		- nom du joueur
		- deux entiers représentant dans l'ordre :
			* la progression du joueur (quel niveau max il a atteint)
			* le score du joueur