/**
* @file AudioSDL.h
* @brief Fichier d'en tete du module Audio qui va gerer le son grace à la librairie FMOD Ex.
* @author Mohamed El Mouctar HAIDARA
*/
#ifndef _AUDIO_H
#define _AUDIO_H

#include <stdlib.h>
#include <stdio.h>
#include "Ressource.h"
#include "Scene.h"

#include "../lib/inc/fmod.h"
#include "../lib/inc/fmodlinux.h"
#include "../lib/inc/fmod_errors.h"

/**
* @struct AudioFMOD
* @brief Structure qui nous permettra de gerer le système audio. On utilise FMOD d'une façon assez simple.
*/
typedef struct
{
    /** Objet système : variable qui nous servira à définir les paramètres de la librairie fmod **/
    FMOD_SYSTEM *system;
    /** Tableau de pointeurs sur les sons initialisés **/
    FMOD_SOUND ** sons;

} AudioFMOD;

/**
* @fn void audioInit(AudioFMOD *audio, Ressource *res);
* @brief Initialise le système audio
* @param [in, out] audio
* @param [in] res : initialisé
*/
void audioInit(AudioFMOD *audio,const Ressource *res);

/**
* @fn void audioLibere(AudioFMOD *audio)
* @brief libere le systeme audio
* @param [in, out] audi : initialisé
*/
void audioLibere(AudioFMOD *audio);

/**
* @fn void audioJoueSon(const AudioFMOD * audio, int index
* @brief Joue le son dont l'indice est passé en paramètre
* @param [in] audio : initialisé
* @param [in] index : correspond à l'indice du son (0<=son<nombre de sons chargé)
*/
void audioJoueSon(const AudioFMOD * audio, int index);

/**
* @fn FMOD_SOUND * chargeSon(const AudioFMOD *audio, char * nomFichier, int typeSon)
* @brief Charge en memoire un son dont le nom est passé à paramètre
* @param [in audio : utile pour la fonction qui charge le son
* @param [in] nomFichier : correspond au nom du fichier, pas le chemin
* @param [in] typeSon : 0 pour un son court et 1 pour un son long. Utile car fmod ne les charge pas de la meme manière
*/
FMOD_SOUND * chargeSon(const AudioFMOD *audio, char * nomFichier, int typeSon);

/**
* @fn void audioVerifieErreur(const FMOD_RESULT resultat)
* @brief Verifie s'il y'a eu une erreur lors de l'appel de certaines fonction et quitte le programme si necessaire
* @param [in] resultat
*/
void audioVerifieErreur(const FMOD_RESULT resultat);

/**
* @fn void audioStopSon(const Audio * audio, int index)
* @brief Arrete un son en cours de lecture
* @param [in] audio
* @param [in] index
*/
void audioStopSon(const AudioFMOD * audio, int index);

/**
* @fn FMOD_CHANNEL * audioGetCanal(const AudioFMOD * audio, int index)
* @brief Recupere le canal sur lequel le son correspondant à index est joué
* @param [in] audio : intialisé
* @param [in] index
* @return Pointeur vers un canal
*/
FMOD_CHANNEL * audioGetCanal(const AudioFMOD * audio, int index);

/**
* @fn FMOD_BOOL audioGetStatutSon(const AudioFMOD *audio, int index)
* @brief Test si le son est en lecture
* @param [in] audio
* @return Renvoie vrai si le son est en lecture, faux sinon
*/
FMOD_BOOL audioGetStatutSon(const AudioFMOD *audio, int index);

/**
* @fn void audioJoueScene(const AudioFMOD *audio, const Scene *scene)
* @brief Joue les sons qui correspondent au evenemnts de la scene
* @param [in] audio : initialisé
* @param [in] scene : initialisé
*/
void audioJoueScene(const AudioFMOD *audio, const Scene *scene);

#endif
