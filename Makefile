#OS				= WIN32
OS				= LINUX
VERBOSE 		= JEU_VERBOSE

DEFINE 			= -D$(OS) -D$(VERBOSE)

OBJ		 		= obj
SRC		 		= src
BIN		 		= bin
EXEC 			= test00

CC 				= gcc
LD 				= gcc

 
ifeq ($(OS),WIN32)
	LIBS 			= -L"C:\code\lib\SDL\lib" -lmingw32 -lSDLmain -lSDL.dll
	INCLUDE		 	= -I$(SRC) -I"C:\code\lib\SDL\include\SDL"
endif
ifeq ($(OS),LINUX)
	LIBS 			= -lSDL -lSDL_image
	INCLUDE		 	= -I/usr/include -I/usr/include/SDL -I$(SRC)
endif


LDFLAGS  		=
CFLAGS 			= $(DEFINE) -Wall -pedantic -ansi # -ggdb   #-O2   # pour optimiser





default: $(BIN)/$(EXEC)


$(BIN)/$(EXEC): $(OBJ)/main.o $(OBJ)/JeuSDL.o $(OBJ)/Ressource.o $(OBJ)/GraphiqueSDL.o $(OBJ)/EntreeSDL.o $(OBJ)/Scene.o $(OBJ)/ElementScene.o
	$(LD)  $^ $(LDFLAGS) $(LIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXEC)
