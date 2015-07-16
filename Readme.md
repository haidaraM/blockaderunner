BlockadeRunner
===================




Jeu de type **shoot'em up** à defilement horizontal réalisé en **C avec SDL et FMOD Ex** dans le cadre de l'UE LIF7 de [l'Université Lyon 1 Claude Bernard.](http://www.univ-lyon1.fr/) durant l'année 2013-2014. Projet que je continue toujours durant mon temps libre. Si vous souhaitez contribuer, je me ferai un plaisir de vous accueillir!.  

**Le jeu n'est pas destiné à être commercialisé. Certaines ressources présentes dans le jeu notamment les images	et les sons sont soumises à des droits et ne nous appartiennent pas.
Pour les bibliothèques, réferez vous à leur licences respectives. Vous pouvez faire tout ce que vous voulez avec le code.**  

**Copyright 2014, Yann Cortial, Mohamed Haidara.
Tous droits reservés**

Auteurs : 
- Yann Cortial
- Mohamed El Mouctar HAIDARA <elmhaidara@gmail.com>

[![Build Status](https://travis-ci.org/haidaraM/blockaderunner.svg?branch=master)](https://travis-ci.org/haidaraM/blockaderunner)

##I. Capture
![Démarrage](/capture/1.png)
![Accueil](/capture/2.png)
![Score](/capture/3.png)
![Niveaux](/capture/4.png)
![Jeu](/capture/5.png)
![Jeu](/capture/6.png)
![Jeu](/capture/7.png)



##II. Configuration requise
Le jeu a été testé essentiellement sur un système **Linux (Ubuntu) 64 bits.**  
Résolution minimale :  **1366*720**.  
Espace mémoire : **40 Mo** d'espace libre.  

##III. Installation
###Dépendances

* **SDL 1.2** : SDL_ttf,  SDL_image,  SDL_gfx  
Il suffit juste d'installer SDL 1.2 avec ses librairies associées (SDL_image, SDL_ttf et SDL_gfx), pas de manipulation particulière à effectuer.
`$ sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev. `
En cas de problèmes : 
	* [Doc ubuntu](http://doc.ubuntu-fr.org/sdl) 
	* [OpenClassroom](http://fr.openclassrooms.com/informatique/cours/apprenez-a-programmer-en-c/installation-de-la-sdl )
	* [Autres](http://loka.developpez.com/tutoriel/sdl/installation/)
* **FMOD EX** : Elle se trouve dans le repertoire du projet.   
En cas de problèmes : [Installation FMOD Ex](http://sindev.blogspot.fr/2009/02/how-to-installer-la-fmod-ex-sur-linux.html)
* **Libxml2** : `sudo apt-get install libxml2 libxml2-dev libxml2-doc libxml2-dbg`

###Compilation
Rajoutez deux dossiers vides dans le répertoire principale du projet: `$ mkdir bin` et `$ mkdir obj`.
Ouvrez le fichier Makefile_2 avec un éditeur de texte, dé-commenter éventuellement les macros selon les besoins : 

	MODE_JEU = MODE_NORMAL   #mode de jeu standard.
	#MODE_JEU = MODE_INVULNERABLE	 #permet de jouer sans encaisser de dégâts : utile pour tester le jeu de A à Z.
	
	VERBOSE = JEU_VERBOSE    #status d'initialisation affichés sur la sortie
	#VERBOSE = NO_VERBOSE    #aucun message sur la sortie standard hormis les messages d'erreurs éventuels. 
	
	EXPLOSION = NO_REPETE_EXPLOSION 	#Permet de ne pas répéter les animations sur la scène
	#EXPLOSION = REPETE_EXPLOSION 		#Permet de répéter les animations. Plus amusant.

Ensuite pour lancer la compilation, tapez, en étant dans le répertoire principale :   
`$ make install`
En cas d'erreurs avec les bibliothèques externes, reportez vous aux dépendances.

##IV. Lancement du jeu
En étant dans le répertoire principale, tapez la commande :  
`$ make run`

##V. Format de fichier
Chaque niveau est décrit par un fichier dans le repertoire data ainsi que les sauvegardes.
Les fichiers de description d'un niveau et le fichier de sauvegarde se présentent ainsi.
###Fichier niveau : Niveau.xml
Ce fichier xml contient la description de tous les niveaux du jeu.
Un niveau à une description, est composé de plusieurs vagues d'ennemis appélées groupeNiveau et a une image de fond.
Chaque groupeNiveau est constitué comme suit : 
- le type de groupe ('Chasseurs', 'Croiseurs', 'Eclaireurs', 'Asteroides') : type des éléments qui seront dans le groupe. 
- trois entiers représentant dans l'ordre : **le nombre d'éléments à générer.**, **la valeur minimale en pixels** (et en abscisse),  **la valeur maximale** en pixels (et en abscisse) 
de la zone où seront générés les éléments du groupe.

###Fichier joueur
Le premier chiffre représente le nombre de joueurs puis chaque paire de lignes définit un joueur :	
- **Nom du joueur**
- Deux entiers représentant dans l'ordre : **la progréssion du joueur et son score** 

##VI. Documentation
Pour générer la documentation, installez doxygen si ce n'est pas le cas et tapez la commande suivant en étant dans le repertoire principal :  
`$ doxygen doc/blockade.doxy`

##VII. TODO
* Migrer vers SDL2
* Afficher un message après le chargement du niveau
* Amélioration de la gestion de l'audio (ajout volume, options etc...)
* Ajouter un temps d'invulnérabilité 
* Ajouter une direction pour les missiles
* Amélioration des animations (rotation astéroïdes, explosions)
* Améliorer l'intelligence des ennemis
* Ajouter de nouveaux bonus
* Collision pixel perfect
