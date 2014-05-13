#******************************************************************#
	++++	+		+++++	+++++	+  	 +	+++++	++++	+++++
	+	+	+		+	+	+		+   +	+	+	+   +	+	
	+++++	+		+	+	+		++++	+++++	+	 +	++++
	+	+	+		+	+	+		+	+	+	+	+   +	+	
	++++	+++++	+++++	+++++	+	 +	+	+	++++	+++++	

			++++	+	+	+	+	+	+	+++++	++++
			+	+	+	+	++	+	++	+	+		+	+
			++++	+	+	+ +	+	+ + +	++++	++++
			+	+	+	+	+  ++	+  ++	+		+	+
			+ 	+	+++++	+	+	+	+	+++++	+	+
#*****************************************************************#

Auteurs : Yann Cortial - Mohamed El Mouctar HAIDARA

Introduction
	Jeu de type shoot'em up à defilement horizontal réalisé en C avec 
	SDL et FMOD dans le cadre de l'UE LIF7 de l'université Lyon 1 Claude Bernard.

Utilisation:
	- FMOD : Il faudra télécharger la librairie FMOD disponible sur : http://www.fmod.org/download/. 
			 Plus précisement la version FMOD Ex Programmer's API. 
			 -	Dans l'archive téléchargé, copiez le dossier api (en le rennomant en "lib") dans le dossier du projet.
			 	Ce repertoire contient les fichiers nécessaires au bon fonctionnement de la librairie. 
	 		 -	Ensuite il faudra copier  le fichier ./lib/lib/libfmodex64-4.44.33.so (le numero peut varier selon 
	 		 	votre version) dans le repertoire /usr/lib/ en le rennomant en libfmodex64.so.
	 		 Ce n'est pas la meilleure façon de faire mais ça marche quand même sur un pc 64bits. 
	 		 Si c'est manips ne fonctionnent pas : http://sindev.blogspot.fr/2009/02/how-to-installer-la-fmod-ex-sur-linux.html
	 
	 - SDL : Il suffit juste d'installer sdl, pas de manipulation particulière à effectuer.
	 		 Reportez vous à ces pages : http://doc.ubuntu-fr.org/sdl
	 		 							 http://fr.openclassrooms.com/informatique/cours/apprenez-a-programmer-en-c/installation-de-la-sdl 
	 		 							 http://loka.developpez.com/tutoriel/sdl/installation/



Attention : Le jeu n'est pas destiné à être commercialisé ni à être diffusé.
			Certaines ressources présentes dans le jeu notamment les images
			et les sons sont soumises à des droits.