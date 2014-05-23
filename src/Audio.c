/**
* @file AudioSDL.c
* @brief Fichier d'implementation du module Audio
*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Audio.h"

/* Fonctions internes  */

FMOD_SOUND * chargeSon(const AudioFMOD *audio, char * nomFichier, int typeSon)
{
    FMOD_SOUND * son=NULL;
    FMOD_RESULT resultat;
    char file[64], dir[64];
    assert(typeSon == 0 || typeSon == 1);
    assert(audio!=NULL);

    if (nomFichier == NULL)
        return NULL;
    strcpy(file, nomFichier);
    strcpy(dir, RESS_DIR_SONS);

    if(typeSon == 0)
    {
        /* Chargement son court */
        resultat=FMOD_System_CreateSound(audio->system, strcat(dir, file), FMOD_CREATESAMPLE, NULL, &son);
    }
    else
    {
        /* chargement son long*/
        resultat=FMOD_System_CreateSound(audio->system, strcat(dir, file),FMOD_SOFTWARE|FMOD_CREATESTREAM | FMOD_LOOP_NORMAL | FMOD_2D, NULL, &son);
    }
    /* On verifie qu'il n'y a pas eu d'erreur */
    if(resultat==FMOD_ERR_FILE_NOTFOUND)
    {
        printf("Impossible de trouvez le fichier %s", file);
        exit(-1);
    }
    else audioVerifieErreur(resultat);

    return son;
}

void audioInit(AudioFMOD *audio, const Ressource *res)
{

    FMOD_RESULT resultat;
    int i, nbSons;
    char **fichiersSons;
    assert(audio!=NULL);
#ifdef JEU_VERBOSE
    printf("Audio :\n    initialisation ...\n");
#endif

    nbSons=RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS;
    /* Allocation de l'objet systeme dans la memoire */
    resultat=FMOD_System_Create(&audio->system);
    audioVerifieErreur(resultat);

    /* Initialisation du systeme audio */
    resultat=FMOD_System_Init(audio->system, nbSons, FMOD_INIT_NORMAL, NULL);
    audioVerifieErreur(resultat);

#ifdef JEU_VERBOSE
    printf("	chargement des sons.\n");
#endif
    /* Chargement des sons en memoire */
    fichiersSons=res->sons;
    audio->sons=(FMOD_SOUND **) malloc(nbSons * sizeof(FMOD_SOUND *));
    /* chargment des sons longs */
    for(i=0; i<RESS_NUM_SONS_LONGS; i++)
    {
        audio->sons[i]=chargeSon(audio, fichiersSons[i],1);
    }
    /* chargement des sons courts */
    for(i=RESS_NUM_SONS_LONGS; i<nbSons; i++)
    {
        audio->sons[i]=chargeSon(audio, fichiersSons[i],0);
    }
#ifdef JEU_VERBOSE
    printf("	initialisation OK.\n");
#endif
}

void audioLibere(AudioFMOD *audio)
{
    int i;
    FMOD_RESULT resultat;
    assert(audio!=NULL);
    /* liberation des sons chargés en memoire */
    for(i=0; i<RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS; i++)
    {
        resultat=FMOD_Sound_Release(audio->sons[i]);
        audioVerifieErreur(resultat);
        audio->sons[i]=NULL;
    }
    free(audio->sons);

    /* fermeture et liberation du systeme audio */
    resultat=FMOD_System_Close(audio->system);
    audioVerifieErreur(resultat);
    resultat=FMOD_System_Release(audio->system);
    audioVerifieErreur(resultat);
}

void audioVerifieErreur(const FMOD_RESULT resultat)
{
    if (resultat != FMOD_OK)
    {
        printf("Erreur FMOD (%d)! %s\n",resultat, FMOD_ErrorString(resultat));
        exit(-1);
    }
}

void audioJoueSon(const AudioFMOD * audio, int index)
{
    FMOD_RESULT resultat;
    FMOD_BOOL etat;
    assert(audio!=NULL);
    /* On verifie que l'index est bien correcte */
    assert(0<=index && index < RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS);
    /* on recupere l'etat du son */
    etat=audioGetStatutSon(audio, index);
    /* On joue ensuite le son s'il n'est pas deja en lecture*/
    if(0<=index && index < RESS_NUM_SONS_LONGS) /* son long */
    {
        if(!etat) /* on test son etat et on le joue seulement s'il n'est pas en lecture*/
        {
            resultat=FMOD_System_PlaySound(audio->system, index, audio->sons[index], 0, NULL);
            audioVerifieErreur(resultat);
        }
    }
    else /* on joue les sons courts en ne tenant pas compte de leurs etats */
    {
        resultat=FMOD_System_PlaySound(audio->system, index, audio->sons[index], 0, NULL);
        audioVerifieErreur(resultat);
    }
}

void audioStopSon(const AudioFMOD * audio, int index)
{
    FMOD_CHANNEL * canal;
    /* recuperation de l'etat du son */
    FMOD_BOOL etat=audioGetStatutSon(audio, index);
    /* recuperation de son canal, utile pour arreter le son */
    canal=audioGetCanal(audio, index);

    if(etat)
        audioVerifieErreur(FMOD_Channel_Stop(canal)); /* on arrete le son alors */

}

FMOD_BOOL audioGetStatutSon(const AudioFMOD *audio, int index)
{
    FMOD_BOOL etat;
    FMOD_CHANNEL *canal;
    /* on recupere le canal sur lequel le son est sensé etre jouer */
    canal=audioGetCanal(audio, index);
    /* on recupere l'etat du canal pour voir si le son est en lecture */
    FMOD_Channel_IsPlaying(canal, &etat);
    return etat;
}

FMOD_CHANNEL * audioGetCanal(const AudioFMOD * audio, int index)
{
    FMOD_CHANNEL * channel;
    FMOD_RESULT resultat;
    /* On verifie que l'index est bien correcte */
    assert(0<=index && index < RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS);
    resultat=FMOD_System_GetChannel(audio->system, index, &channel);
    audioVerifieErreur(resultat);
    return channel;
}

void audioJoueScene(const AudioFMOD *audio, const Scene *scene)
{
    assert(audio!=NULL);
    assert(scene!=NULL);

    /* laser ennemi */
    if(scene->evenements.ennemi_tir_laser==1)
        audioJoueSon(audio, RESS_SON_TIR_LASER_ENNEMI);
    /* bonus score trouvé */
    if(scene->evenements.joueur_bonus_score==1)
        audioJoueSon(audio, RESS_SON_BONUS_SCORE);
    /* bonus missile */
    if(scene->evenements.joueur_bonus_missile==1)
        audioJoueSon(audio, RESS_SON_BONUS_MISSILE);
    /* laser joueur */
    if(scene->evenements.joueur_tir_laser==1)
        audioJoueSon(audio, RESS_SON_TIR_LASER);
    /* missile joueur */
    if(scene->evenements.joueur_tir_missile==1)
        audioJoueSon(audio, RESS_SON_MISSILE);
    /* plus de munitions */
    if(scene->evenements.joueur_tir_erreur==1)
        audioJoueSon(audio, RESS_SON_ERREUR);
    /* explosion asteroide */
    if(scene->evenements.asteroide_explosion==1)
        audioJoueSon(audio, RESS_SON_EXPLOSION_ASTEROIDE);
    /* explosion ennemi*/
    if(scene->evenements.ennemi_explosion==1)
        audioJoueSon(audio, RESS_SON_EXPLOSION_ENNEMI);
    if(scene->evenements.joueur_degats_laser==1)
        audioJoueSon(audio, RESS_SON_DEGAT_LASER_J);

}



