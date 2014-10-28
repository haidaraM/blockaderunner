#Makefile du projet BlockadeRunner
#Realise par Yoan Cortial et Mohamed El Mouctar HAIDARA. Lire le readme pour plus d'informations
#Partie windows non fonctionnel

MODE_JEU		= MODE_NORMAL
#MODE_JEU 		= MODE_INVULNERABLE

VERBOSE 		= JEU_VERBOSE
#VERBOSE 		= NO_VERBOSE

EXPLOSION		= NO_REPETE_EXPLOSION
#EXPLOSION  	= REPETE_EXPLOSION

#OS				= WIN32
OS				= LINUX

#Definitions des macros pour le préprocesseur 
DEFINE 			= -D$(OS) -D$(VERBOSE) -D$(MODE_JEU) -D$(EXPLOSION)

#Repertoires des fichiers sources, obj et des executables
OBJ		 		= obj
SRC		 		= src
BIN		 		= bin


#Executable du jeu
EXEC 			= blockade

#Executable du Test de regression
MAIN_TEST		= testRegression

#Compilateurs et editeurs de lien
CC 				= @gcc
LD 				= @gcc

 
ifeq ($(OS),WIN32)
	LIBS 			= -L"C:\code\lib\SDL\lib" -lmingw32 -lSDLmain -lSDL.dll
	INCLUDE		 	= -I$(SRC) -I"C:\code\lib\SDL\include\SDL"
endif
ifeq ($(OS),LINUX)
	LIBS 			= -lSDL -lSDL_image -lSDL_ttf -lfmodex64 -lSDL_gfx -lm
	INCLUDE		 	= -I/usr/include -I/usr/include/SDL -I$(SRC)
endif

#Options de compilation
LDFLAGS  		= 
CFLAGS 			= $(DEFINE) -Wall -pedantic -ansi -ggdb #-O2   # pour optimiser


all: $(BIN)/$(EXEC) $(BIN)/$(MAIN_TEST)


#Creation de l'executable principale
$(BIN)/$(EXEC): $(OBJ)/main.o $(OBJ)/JeuSDL.o $(OBJ)/Outils.o $(OBJ)/Ressource.o $(OBJ)/Joueur.o $(OBJ)/Niveau.o $(OBJ)/GraphiqueSDL.o $(OBJ)/EntreeSDL.o $(OBJ)/Menu.o $(OBJ)/Scene.o $(OBJ)/ElementScene.o $(OBJ)/Vaisseau.o $(OBJ)/Audio.o $(OBJ)/Animation.o
	$(LD)  $^ $(CFLAGS) $(LIBS) -o $@
	@echo "Je suis trop fort! Compilation réussi"

# Creation de l'executable pour les tests de regression
$(BIN)/$(MAIN_TEST): $(OBJ)/MainTest.o $(OBJ)/Joueur.o $(OBJ)/Vaisseau.o $(OBJ)/ElementScene.o $(OBJ)/Outils.o $(OBJ)/Scene.o $(OBJ)/Ressource.o $(OBJ)/Niveau.o 
	$(LD) $(CFLAGS) $^ -o $@ 

# Creation des dependances
$(OBJ)/%.o: $(SRC)/%.c 
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Suppression de tous les fichiers obj et executables pour forcer la recompilation complète
clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXEC) $(BIN)/$(MAIN_TEST)

