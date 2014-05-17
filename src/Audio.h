/**
* @file AudioSDL.h
* @brief Fichier d'en tete du module Audio qui va gerer le son grace a la librairie fmod
* @author Mohamed El Mouctar HAIDARA - Yann Cortial
*/
#ifndef _AUDIO_H
#define _AUDIO_H

#include <stdlib.h>
#include <stdio.h>
#include "Ressource.h"

#include "../lib/inc/fmod.h"
#include "../lib/inc/fmodlinux.h"
#include "../lib/inc/fmod_errors.h"

/**
* @struct AudioFMOD
* @brief Structure qui nous permettra de gerer le système audio
*/
typedef struct
{
    /** Objet système : variable qui nous servira à définir les paramètres de la librairie fmod **/
    FMOD_SYSTEM *system;
    /** Tableau de pointeurs sur les sons initialisés **/
    FMOD_SOUND ** sons;

} AudioFMOD;

/**
* @brief Initialise le système audio
* @param [in, out] audio
* @param [in] res : initialisé
*/
void audioInit(AudioFMOD *audio, Ressource *res);

/**
* @brief libere le systeme audio
* @param [in, out] audi : initialisé
*/
void audioLibere(AudioFMOD *audio);

/**
* @brief Joue le son dont l'indice est passé en paramètre
* @param [in] audio : initialisé
* @param [in] indice : correspond à l'indice du son (0<=son<nombre de sons chargé)
*/
void audioJoueSon(AudioFMOD * audio, int son);

/**
* @fn FMOD_SOUND * chargeSon(AudioFMOD *audio, char * nomFichier, int typeSon)
* @brief Charge en memoire un son dont le nom est passé à paramètre
* @param [in] audio : utile pour la fonction qui charge le son
* @param [in] nomFichier : correspond au nom du fichier, pas le chemin
* @param [in] typeSon : 0 pour un son court et 1 pour un son long. Utile car fmod ne les charge pas de la meme manière
*/
FMOD_SOUND * chargeSon(AudioFMOD *audio, char * nomFichier, int typeSon);

/**
* @fn void audioVerifieErreur(FMOD_RESULT resultat)
* @brief Verifie s'il y'a eu une erreur lors de l'appel de certaines fonction et quitte le programme si necessaire
* @param [in] resultat
*/
void audioVerifieErreur(FMOD_RESULT resultat);

/**
* @fn void audioStopSon(Audio * audio, int index)
* @brief Arrete un son en cours de lecture
* @param [in, out] audio
* @param [in] index
*/
void audioStopSon(AudioFMOD * audio, int index);

/**
* @fn FMOD_CHANNEL * audioGetCanal(AudioFMOD * audio, int index)
* @brief Renvoie le canal sur lequel le son correspondant à index est joué
* @param [in] audio : intialisé
*/
FMOD_CHANNEL * audioGetCanal(AudioFMOD * audio, int index);

/**
* @fn FMOD_BOOL audioGetStatutSon(AudioFMOD *audio, int index)
* @brief Test si le son est en lecture
* @return Renvoie vrai si le son est en lecture, faux sinon
*/
FMOD_BOOL audioGetStatutSon(AudioFMOD *audio, int index);

#endif
