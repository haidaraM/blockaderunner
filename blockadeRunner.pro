TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#Repertoire des fichiers obj générés
OBJECTS_DIR   = ./obj

#Nom du fichier executable de sortie
TARGET = bin/blockadeRunner

#Ajout des librairies externes
INCLUDEPATH += /usr/include
LIBS += -lSDL -lSDL_image -lSDL_ttf -lfmodex64 -lSDL_gfx -L/usr/LIBS

HEADERS += \
    src/Animation.h \
    src/Audio.h \
    src/ElementScene.h \
    src/EntreeSDL.h \
    src/GraphiqueSDL.h \
    src/JeuSDL.h \
    src/Joueur.h \
    src/Menu.h \
    src/Niveau.h \
    src/Outils.h \
    src/Ressource.h \
    src/Scene.h \
    src/Vaisseau.h

SOURCES += \
    src/Animation.c \
    src/Audio.c \
    src/ElementScene.c \
    src/EntreeSDL.c \
    src/GraphiqueSDL.c \
    src/JeuSDL.c \
    src/Joueur.c \
    src/main.c \
    src/Menu.c \
    src/Niveau.c \
    src/Outils.c \
    src/Ressource.c \
    src/Scene.c \
    src/Vaisseau.c

