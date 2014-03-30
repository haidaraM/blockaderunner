#OS				= WIN32
OS				= LINUX
VERBOSE 		= JEU_VERBOSE

DEFINE 			= -D$(OS) -D$(VERBOSE)

OBJ		 		= obj
SRC		 		= src
BIN		 		= bin
EXEC 			= blockade

#Executables des Tests de regression
JOUEUR_TEST		= joueurTest

CC 				= gcc
LD 				= gcc

 
ifeq ($(OS),WIN32)
	LIBS 			= -L"C:\code\lib\SDL\lib" -lmingw32 -lSDLmain -lSDL.dll
	INCLUDE		 	= -I$(SRC) -I"C:\code\lib\SDL\include\SDL"
endif
ifeq ($(OS),LINUX)
	LIBS 			= -lSDL -lSDL_image -lSDL_ttf
	INCLUDE		 	= -I/usr/include -I/usr/include/SDL -I$(SRC)
endif


LDFLAGS  		=
CFLAGS 			= $(DEFINE) -Wall -pedantic -ansi -ggdb #-O2   # pour optimiser


all: $(BIN)/$(EXEC) $(BIN)/$(JOUEUR_TEST)


$(BIN)/$(EXEC): $(OBJ)/main.o $(OBJ)/JeuSDL.o $(OBJ)/Outils.o $(OBJ)/Ressource.o $(OBJ)/Joueur.o $(OBJ)/GraphiqueSDL.o $(OBJ)/EntreeSDL.o $(OBJ)/Menu.o $(OBJ)/Scene.o $(OBJ)/ElementScene.o
	$(LD)  $^ $(LDFLAGS) $(LIBS) -o $@

$(BIN)/$(JOUEUR_TEST): $(OBJ)/JoueurMainTest.o $(OBJ)/Joueur.o
	$(LD) $(CFLAGS) $^ -o $@ 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXEC) $(BIN)/$(JOUEUR_TEST)
