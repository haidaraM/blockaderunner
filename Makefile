MODE_JEU		= MODE_NORMAL
#MODE_JEU 		= MODE_INVULNERABLE

VERBOSE 		= JEU_VERBOSE
#VERBOSE 		= NO_VERBOSE

EXPLOSION		= NO_REPETE_EXPLOSION
#EXPLOSION  	= REPETE_EXPLOSION

#OS				= WIN32
OS				= LINUX

#Definitions des macros pour le prépocesseur 
DEFINE 			= -D$(OS) -D$(VERBOSE) -D$(MODE_JEU) -D$(EXPLOSION)

#Repertoires des fichiers sources, obj et des executables
OBJ		 		= obj
SRC		 		= src
BIN		 		= bin

#Executable du jeu
EXEC 			= blockade

#Executable du Test de regression
MAIN_TEST		= testRegression

CC 				= gcc
LD 				= gcc

 
ifeq ($(OS),WIN32)
	LIBS 			= -L"C:\code\lib\SDL\lib" -lmingw32 -lSDLmain -lSDL.dll
	INCLUDE		 	= -I$(SRC) -I"C:\code\lib\SDL\include\SDL"
endif
ifeq ($(OS),LINUX)
	LIBS 			= -lSDL -lSDL_image -lSDL_ttf -lfmodex64 -lSDL_gfx -lm
	INCLUDE		 	= -I/usr/include -I/usr/include/SDL -I$(SRC)
endif


LDFLAGS  		= 
CFLAGS 			= $(DEFINE) -Wall -pedantic -ansi -ggdb #-O2   # pour optimiser


all: $(BIN)/$(EXEC) $(BIN)/$(MAIN_TEST)



$(BIN)/$(EXEC): $(OBJ)/main.o $(OBJ)/JeuSDL.o $(OBJ)/Outils.o $(OBJ)/Ressource.o $(OBJ)/Joueur.o $(OBJ)/Niveau.o $(OBJ)/GraphiqueSDL.o $(OBJ)/EntreeSDL.o $(OBJ)/Menu.o $(OBJ)/Scene.o $(OBJ)/ElementScene.o $(OBJ)/Vaisseau.o $(OBJ)/Audio.o $(OBJ)/Animation.o
	$(LD)  $^ $(LDFLAGS) $(LIBS) -o $@

$(BIN)/$(MAIN_TEST): $(OBJ)/MainTest.o $(OBJ)/Joueur.o $(OBJ)/Vaisseau.o $(OBJ)/ElementScene.o $(OBJ)/Outils.o $(OBJ)/Scene.o $(OBJ)/Ressource.o $(OBJ)/Niveau.o 
	$(LD) $(CFLAGS) $^ -o $@ 

$(OBJ)/%.o: $(SRC)/%.c 
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXEC) $(BIN)/$(MAIN_TEST)

