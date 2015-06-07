#Makefile du projet BlockadeRunner
#Realise par Yoan Cortial et Mohamed El Mouctar HAIDARA. Lire le readme pour plus d'informations

########## Executable du jeu ##########
EXEC 			= blockade

########## Executable du Test de regression ##########
MAIN_TEST		= testRegression

########## Options du jeu ##########
#MODE_JEU		= MODE_NORMAL
MODE_JEU 		= MODE_INVULNERABLE

VERBOSE 		= JEU_VERBOSE
#VERBOSE 		= NO_VERBOSE

EXPLOSION		= NO_REPETE_EXPLOSION
#EXPLOSION  	= REPETE_EXPLOSION
	
########## Definitions des macros pour le préprocesseur ##########
DEFINE 			= -D$(VERBOSE) -D$(MODE_JEU) -D$(EXPLOSION)

########## Repertoires des fichiers sources, obj et des executables ##########
OBJ_DIR		 		= obj
SRC_DIR		 		= src
BIN_DIR		 		= bin

# Fichiers 
INTERFACES_FILES		= Animation.h Audio.h ElementScene.h EntreeSDL.h GraphiqueSDL.h JeuSDL.h Joueur.h Menu.h Niveau.h Outils.h Ressource.h Scene.h Vaisseau.h
INT 		            = $(addprefix $(SRC_DIR)/, $(INTERFACES_FILES))					# construit le chemin des sources
OBJ			            = $(addprefix $(OBJ_DIR)/, $(INTERFACES_FILES:.h=.o))			# Génération du nom des fichiers obj


########## Compilateurs et editeurs de lien ##########
CC 				= @gcc
LD 				= @gcc
LIBS 			= -lSDL -lSDL_image -lSDL_ttf -lfmodex64 -lSDL_gfx -lm `xml2-config --libs`
INCLUDE		 	= -I./libs/fmod/inc `xml2-config --cflags`


########## Options de compilation ##########
LDFLAGS  		= -L./libs/fmod/lib $(LIBS)
CFLAGS 			= $(DEFINE) -Wall -pedantic -ansi -ggdb #-O2 # pour optimiser

#Autres commandes et message
ECHO			= @echo
RM				= @rm

install: $(BIN_DIR)/$(EXEC)

run: install
	@LD_LIBRARY_PATH=./libs/fmod/lib && export LD_LIBRARY_PATH && $(BIN_DIR)/$(EXEC)

test: $(BIN_DIR)/$(MAIN_TEST)
	@LD_LIBRARY_PATH=./libs/fmod/lib && export LD_LIBRARY_PATH && \
	valgrind --error-exitcode=1 --leak-check=full --suppressions=./valgrind.supp $(BIN_DIR)/$(MAIN_TEST)

#Creation de l'executable principale
$(BIN_DIR)/$(EXEC): $(OBJ_DIR)/main.o $(OBJ)
	$(LD)  $^ $(LDFLAGS) -o $@
	$(ECHO) "Je suis trop fort! Compilation réussie"

# Creation de l'executable pour les tests de regression
$(BIN_DIR)/$(MAIN_TEST): $(OBJ_DIR)/MainTest.o $(OBJ)
	$(LD)  $^ $(LDFLAGS) -o $@

# Creation des dependances
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(ECHO) "Compilation de $< (generation de $@)"
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Suppression de tous les fichiers obj et executables pour forcer la recompilation complète
clean:
	$(ECHO) "Nettoyage..."
	$(RM) -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(MAIN_TEST) $(BIN_DIR)/blockaderunner

