/**
* @file Niveau.c
* @brief Fichier d'implementation du module Niveau
* @author Mohamed Haidara
*
* Copyright 2014, Yann Cortial, Mohamed Haidara.
* Tous droits reservés
*/
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <libxml/parser.h>

#include "Niveau.h"
#include "Ressource.h"


/**
 * @fn static void *parseElementNiveau(Niveau *niveau, xmlDocPtr doc, xmlNodePtr cur)
 * @brief Parse un noeud niveau et intialise le niveau
 * @param [in,out] niveau : niveau à completer
 * @param [in] doc : pointeur sur le document xml
 */
static void *parseElementNiveau(Niveau *niveau, xmlDocPtr doc, xmlNodePtr cur)
{
    xmlChar *key;
    xmlNodePtr descGroupe;
    cur = cur->xmlChildrenNode;

    while (cur != NULL) {
        /* description */
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "description"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            strcpy(niveau->description, (const char *) key);
            xmlFree(key);
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) "composition"))) { /* composition du niveau*/

            xmlNodePtr gNiveau = cur->xmlChildrenNode;
            while (gNiveau != NULL) {
                /* groupe niveau */
                if ((!xmlStrcmp(gNiveau->name, (const xmlChar *) "groupeNiveau"))) {
                    GroupeNiveau * groupe=(GroupeNiveau*) malloc(sizeof(GroupeNiveau));
                    xmlChar *typeGroupe =  xmlGetProp(gNiveau, (const xmlChar *) "type");
                    if (!xmlStrcmp(typeGroupe,(const xmlChar *) "Asteroides")) {
                        groupe->type = NIVEAU_GROUPE_ASTEROIDES;
                    } else if (!xmlStrcmp(typeGroupe,(const xmlChar *) "Eclaireurs")) {
                        groupe->type = NIVEAU_GROUPE_ECLAIREURS;
                    } else if (!xmlStrcmp(typeGroupe,(const xmlChar *) "Chasseurs")) {
                        groupe->type = NIVEAU_GROUPE_CHASSEURS;
                    } else if (!xmlStrcmp(typeGroupe,(const xmlChar *) "Croiseurs")) {
                        groupe->type = NIVEAU_GROUPE_CROISEURS;
                    }

                    xmlFree(typeGroupe);

                    /* composition du groupeNiveau*/
                    descGroupe = gNiveau->xmlChildrenNode;
                    while (descGroupe != NULL) {

                        if ((!xmlStrcmp(descGroupe->name, (const xmlChar *) "nombreEnnemis"))) {/* nombre d'enemis */
                            key = xmlNodeListGetString(doc, descGroupe->xmlChildrenNode, 1);
                            groupe->nombre = (int) strtol((const char*)key,NULL,10);
                            xmlFree(key);
                        } else if ((!xmlStrcmp(descGroupe->name, (const xmlChar *) "xmin"))) { /* xmin */
                            key = xmlNodeListGetString(doc, descGroupe->xmlChildrenNode, 1);
                            groupe->xmin = (int)strtol((const char*)key,NULL,10);
                            xmlFree(key);
                        } else if ((!xmlStrcmp(descGroupe->name, (const xmlChar *) "xmax"))) { /* xmax */
                            key = xmlNodeListGetString(doc, descGroupe->xmlChildrenNode, 1);
                            groupe->xmax = (int)strtol((const char*)key,NULL,10);
                            xmlFree(key);
                        }
                        descGroupe = descGroupe->next;
                    }

                    tabDynAjoute(&niveau->composition,(void*)groupe);
                } /* fin if groupeNiveau */
                gNiveau = gNiveau->next;
            } /* fin du while des groupeNiveau */
        } /* fin while de la composition */

        cur = cur->next;
    } /* fin du while principale */

    return NULL;
}

/**
 * @fn static Niveau *parseFichier(char *docname)
 * @brief : Charge, valide et parse le fichier xml
 * @param [in] docname : nom du fichier xml
 */
static Niveau *parseFichier(const char *docname)
{
    Niveau *lesNiveaux = NULL;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlParserCtxtPtr context;

    /* création du context*/
    context = xmlNewParserCtxt();
    if (context == NULL) {
        fprintf(stderr, "Impossible d'allouer le context du Parseur.\n");
        exit(EXIT_FAILURE);
    }

    /* validation et parsing */
    doc = xmlCtxtReadFile(context, docname, NULL, XML_PARSE_DTDVALID);
    if (doc == NULL) {
        fprintf(stderr, "Impossible de parser le document : %s.\n", docname);
        fprintf(stderr, "Vous devez fournir un fichier de niveau valide pour pouvoir jouer\n");
        exit(EXIT_FAILURE);
    } else { /* parsing ok */
        if (context->valid == 0) {
            fprintf(stderr, "Le fichier de niveau : %s n'est pas valide\n.", docname);
            fprintf(stderr, "Consulter le DTD pour fournir un fichier valide");
            xmlFreeDoc(doc);
            exit(EXIT_FAILURE);
        } else { /* document valide */

            cur = xmlDocGetRootElement(doc);
            if (cur == NULL) {
                fprintf(stderr, "Le document est vide!.\n");
                xmlFreeDoc(doc);
                exit(EXIT_FAILURE);
            }

            int nbNiveaux = (int) xmlChildElementCount(cur);
            lesNiveaux = (Niveau *) malloc(sizeof(Niveau) * nbNiveaux);
            int j;
            /* initialisation des tableaux dynamiques */
            for(j=0;j<nbNiveaux;j++){
                tabDynInit(&lesNiveaux[j].composition);
            }
            int i = 0;
            /* parsing des niveaux */
            cur = cur->xmlChildrenNode;
            while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "niveau"))) {
                    /* récuperation de l'id */
                    xmlChar *idChar = xmlGetProp(cur, (const xmlChar *) "id");
                    idChar++;
                    unsigned int idInt = (unsigned int) strtol((const char *) idChar, NULL, 10);
#ifdef JEU_VERBOSE
        printf("Creation niveau %d\n", idInt);
#endif
                    lesNiveaux[i].numero = idInt;
                    idChar--;
                    xmlFree(idChar);
                    parseElementNiveau(&lesNiveaux[i], doc, cur);
                    i++;
                }
                cur = cur->next;
            }
        }
        /* liberation */
        xmlFreeDoc(doc);
    }

    xmlFreeParserCtxt(context);

    return lesNiveaux;
}


/* -------------------------- Interface du module ------------------------------ */

void niveauInit(Niveau *niveau, unsigned int numero)
{

    assert(niveau != NULL);
    niveau->numero = numero;
    niveau->imageFond = 0;
    tabDynInit(&niveau->composition);
}

void niveauLibere(Niveau *niveau)
{
    int i;
    GroupeNiveau *g;
    assert(niveau != NULL);

    for (i = 0; i < niveau->composition.tailleUtilisee; i++) {
        g = (GroupeNiveau *) tabDynGetElement(&niveau->composition, i);
        if (g != NULL)
            free(g);
    }
    tabDynLibere(&niveau->composition);
}

void niveauSetImageFond(Niveau *niveau, int indexImage)
{
    assert(niveau != NULL);
    niveau->imageFond = indexImage;
}

int niveauGetNumGroupes(const Niveau *niveau)
{
    assert(niveau != NULL);
    return niveau->composition.tailleUtilisee;
}

Niveau * niveauCreate()
{
    char nomFichier[128];
    strcpy(nomFichier, RESS_DIR_NIVEAU);
    strcat(nomFichier,RESS_NIVEAU_XML);
    return parseFichier(nomFichier);
}

void niveauTestDeRegression()
{
    Niveau niveau;
    printf("-----------------Test de niveauInit----------------\n");
    niveauInit(&niveau, 7);
    assert(niveau.numero == 7);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("-------------- Test de niveauSetImageFond -------------\n");
    niveauSetImageFond(&niveau, RESS_IMG_FOND_NIVEAU_7);
    assert(niveau.imageFond == RESS_IMG_FOND_NIVEAU_7);
    printf("=========> Resultat : OK \n");
    printf("\n");

    printf("--------------- Test de niveauGetNumGroupes---------------\n");
    assert(niveauGetNumGroupes(&niveau) == 4);
    printf("=========> Resultat : OK \n");
    printf("\n");


    /* Les test de liberations sont à effecter avec valgrind de préferences */
    printf("-----------------Test de niveauLibere----------------\n");
    niveauLibere(&niveau);
    printf("=========> Resultat : OK \n");
    printf("\n");
}

