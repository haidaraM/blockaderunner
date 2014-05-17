/**
* @file AudioSDL.c
*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Audio.h"

/* Fonctions internes  */

FMOD_SOUND * chargeSon(AudioFMOD *audio, char * nomFichier, int typeSon)
{
    FMOD_SOUND * son=NULL;
    FMOD_RESULT resultat;
    char file[64], dir[64];
    assert(typeSon == 0 || typeSon == 1);

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
    audioVerifieErreur(resultat);

    return son;
}

void audioInit(AudioFMOD *audio, Ressource *res)
{
    FMOD_RESULT resultat;
    int i, nbSons;
    char **fichiersSons;
    assert(audio!=NULL);

    nbSons=RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS;
    /* Allocation de l'objet systeme dans la memoire */
    resultat=FMOD_System_Create(&audio->system);
    audioVerifieErreur(resultat);

    /* Initialisation du systeme audio */
    resultat=FMOD_System_Init(audio->system, nbSons, FMOD_INIT_NORMAL, NULL);
    audioVerifieErreur(resultat);

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

void audioVerifieErreur(FMOD_RESULT resultat)
{
    if (resultat != FMOD_OK)
    {
        printf("Erreur FMOD (%d)! %s\n",resultat, FMOD_ErrorString(resultat));
        exit(-1);
    }
}

void audioJoueSon(AudioFMOD * audio, int index)
{
    FMOD_RESULT resultat;
    FMOD_BOOL etat;
    assert(audio!=NULL);
    /* On verifie que l'index est bien correcte */
    assert(0<=index && index < RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS);
    /* on recupere l'etat du son */
    etat=audioGetStatutSon(audio, index);
    /* On joue ensuite le son (que les sons longs) s'il n'est pas deja en lecture*/
    if(0<=index && index < RESS_NUM_SONS_LONGS) /* si c'est un son long */
    {
        if(!etat) /* on test son etat et on le joue seulement s'il n'est pas en lecture*/
        {
            resultat=FMOD_System_PlaySound(audio->system, index, audio->sons[index], 0, NULL);
            audioVerifieErreur(resultat);
        }
    }
    else
    {
        resultat=FMOD_System_PlaySound(audio->system, index, audio->sons[index], 0, NULL);
        audioVerifieErreur(resultat);
    }
}

void audioStopSon(AudioFMOD * audio, int index)
{
    FMOD_CHANNEL * canal;
    FMOD_BOOL etat=audioGetStatutSon(audio, index);

    canal=audioGetCanal(audio, index);

    if(etat)
        audioVerifieErreur(FMOD_Channel_Stop(canal)); /* on arrete le son alors */

}

FMOD_BOOL audioGetStatutSon(AudioFMOD *audio, int index)
{
    FMOD_BOOL etat;
    FMOD_CHANNEL *canal;
    /* on recupere le canal sur lequel le son est sensé etre jouer */
    canal=audioGetCanal(audio, index);
    /* on recupere l'etat du canal pour voir si le son est en lecture */
    FMOD_Channel_IsPlaying(canal, &etat);
    return etat;
}

FMOD_CHANNEL * audioGetCanal(AudioFMOD * audio, int index)
{
    FMOD_CHANNEL * channel;
    FMOD_RESULT resultat;
    /* On verifie que l'index est bien correcte */
    assert(0<=index && index < RESS_NUM_SONS_COURTS + RESS_NUM_SONS_LONGS);
    resultat=FMOD_System_GetChannel(audio->system, index, &channel);
    audioVerifieErreur(resultat);
    return channel;
}


