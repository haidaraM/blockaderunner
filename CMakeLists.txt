cmake_minimum_required(VERSION 2.8.4)
project(blockaderunner)

#Macros preprocesseur : A décommenter pour désactiver l'option
#add_definitions(-DJEU_VERBOSE)
add_definitions(-DNO_REPETE_EXPLOSION)
add_definitions(-DMODE_NORMAL)

#repetoire des includes
include_directories( ./libs/fmod/inc)

#Repertoires exectuble et obj
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(OBJECT_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/obj")

set(SOURCE_FILES
    src/Animation.c
    src/Animation.h
    src/Audio.c
    src/Audio.h
    src/ElementScene.c
    src/ElementScene.h
    src/EntreeSDL.c
    src/EntreeSDL.h
    src/GraphiqueSDL.c
    src/GraphiqueSDL.h
    src/JeuSDL.c
    src/JeuSDL.h
    src/Joueur.c
    src/Joueur.h
    src/main.c
    src/Menu.c
    src/Menu.h
    src/Niveau.c
    src/Niveau.h
    src/Outils.c
    src/Outils.h
    src/Ressource.c
    src/Ressource.h
    src/Scene.c
    src/Scene.h
    src/Vaisseau.c
    src/Vaisseau.h)

add_executable(blockaderunner ${SOURCE_FILES})

target_link_libraries(blockaderunner -lSDL -lxml2 -lm -lSDL_image -lSDL_ttf -lfmodex64 -lSDL_gfx)