/**
* @file Audio.h
* @brief Fichier d'en tete du module Audio qui va gerer le son grace à la librairie FMOD Ex.
*
*  FMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2014.
*
*  @author Mohamed El Mouctar HAIDARA
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#ifndef _AUDIO_H
#define _AUDIO_H

#include "Ressource.h"
#include "Scene.h"

#include "fmod.h"

/**
* @struct AudioFMOD
* @brief Permettra de gerer le système audio.
*/
typedef struct {
    /** Objet système : variable qui nous servira à définir les paramètres de la librairie fmod **/
    FMOD_SYSTEM *system;
    /** Tableau de pointeurs sur les sons initialisés **/
    FMOD_SOUND **sons;
    /** booleen indicant si le son est activé ou pas */
    int isEnabled;

} AudioFMOD;

/**
* @fn void audioInit(AudioFMOD *audio, Ressource *res);
* @brief Initialise le système audio
* @param [in, out] audio
* @param [in] res : initialisé
*/
void audioInit(AudioFMOD *audio, const Ressource *res);

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
void audioJoueSon(const AudioFMOD *audio, int index);

/**
* @fn void audioStopSon(const Audio * audio, int index)
* @brief Arrete un son en cours de lecture
* @param [in] audio : initialisé
* @param [in] index
*/
void audioStopSon(const AudioFMOD *audio, int index);

/**
* @fn void audioPauseSon(const AudioFMOD *audio, int index)
* @brief Met un son en pause
* @param [in] audio : initialisé
* @param [in] index
*/
void audioPauseSon(const AudioFMOD *audio, int index);

/**
* @fn void audioReprendSon(const AudioFMOD *audio, int index)
* @brief Reprend un son qui a été mis en pause
* @param [in] audio : initialisé
* @param [in] index
*/
void audioReprendSon(const AudioFMOD *audio, int index);

/**
* @fn void audioJoueScene(const AudioFMOD *audio, const Scene *scene)
* @brief Joue les sons qui correspondent au evenements survenus sur la scene
* @param [in] audio : initialisé
* @param [in] scene : initialisé
*/
void audioJoueScene(const AudioFMOD *audio, const Scene *scene);

/**
 * @fn void audioDisableSon(AudioFMOD * audioFMOD)
 * @brief Désactive le système audio
 */
void audioDesactiveSon(AudioFMOD * audioFMOD);

/**
 * @fn void audioDisableSon(AudioFMOD * audioFMOD)
 * @brief Active le système audio
 */
void audioActiveSon(AudioFMOD * audioFMOD);
#endif
