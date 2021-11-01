#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>

#include "../affichage/console.h"
# include "./map.h"

const int LONGUEUR_MIN_MAP = 21;
const int LONGUEUR_MAX_MAP = 255;
const int NBRE_LIGNES_MIN_MAP = 7;
const int NBRE_LIGNES_MAX_MAP = 255;

const char CHAR_BORD  = '+';
const char CHAR_SPAWN = '#';

void libererMemoireMap(map instanceMap)
{
    //On libère chaque ligne
    for(int i = 0; i < instanceMap.x; i++)
    {
        free(instanceMap.ptr_map[i]);
    }
    free(instanceMap.ptr_map);
}

char** initTableau(int x, int y)
{
    char** ptr_map = NULL;

    ptr_map = malloc(x * sizeof(char*));

    if(ptr_map == NULL)
    {
        afficherMessageConsole("Erreur d'allocation memoire", ERRMSG);
        return NULL;
    }
    
    for(int i = 0; i < x; i++)
    {
        //Réservation pour chaque colonne du tableau
        ptr_map[i] = malloc(y * sizeof(char));
        if(ptr_map[i] == NULL)
        {
            afficherMessageConsole("Erreur d'allocation memoire colonne", ERRMSG);

            map instanceMap;
            instanceMap.ptr_map = ptr_map;
            instanceMap.x = i;
            instanceMap.y = y;

            //On libère toutes les lignes précédentes de la mémoire
            libererMemoireMap(instanceMap);

            return NULL;
        }
    }

    return ptr_map;
}

void tailleMap(FILE* fichierMap, map instanceMap, int* x, int* y)
{
    char ligne[LONGUEUR_MAX_MAP];
    int longueurLignes = 0;
    int nbreLignes = 0;

    //On verifie si la ligne commence par + et on commence à la lire
    fgets(ligne, LONGUEUR_MAX_MAP, fichierMap);
    if(ligne[0] == CHAR_BORD) //On verifie si la ligne commence par + et on commence à la lire
    {
        for(int i = 0; i < LONGUEUR_MAX_MAP; i++)
        {
            if(ligne[i] != CHAR_BORD)
            {
                longueurLignes = i;
                break;
            }
        }
    }

    char c = ' ';
    char c_precedent = c;
    //On place le curseur à la position 0
    fseek(fichierMap, 0, SEEK_SET);

    while(c != EOF)
    {
        c_precedent = c;
        c = fgetc(fichierMap);
        if(c == '\n')
        {
            nbreLignes++;
        }
    }

    //Si le dernier char du texte n'est pas un saut de ligne on corrige le nb de lignes
    if(c_precedent == CHAR_BORD)
    {
        nbreLignes++;
    }

    *x = longueurLignes;
    *y = nbreLignes;
}

//Renvoie true si le format de la map dans le fichier .txt est valide
bool verifFormat(FILE* fichierMap, map instanceMap)
{
    //La longueur ne peut pas depasser LONGUEUR_MAX_MAP en raison du fonctionnement de fgets pas besoin de vérifier donc
    if(instanceMap.x < LONGUEUR_MIN_MAP || instanceMap.y < NBRE_LIGNES_MIN_MAP || instanceMap.x > NBRE_LIGNES_MAX_MAP)
    {
        return false;
    }

    //Verif des bords de chaque ligne
    for(int j = 0; j < instanceMap.y; j++)
    {
        char c1 = instanceMap.ptr_map[0][j];
        char c2 = instanceMap.ptr_map[instanceMap.x - 1][j];
        if(c1 != CHAR_BORD || c2 != CHAR_BORD)
        {
            return false;
        }
    }

    //Verif des bords de chaque colonne
    for(int j = 0; j < instanceMap.x; j++)
    {
        char c1 = instanceMap.ptr_map[j][0];
        char c2 = instanceMap.ptr_map[j][instanceMap.y - 1];
        if(c1 != CHAR_BORD || c2 != CHAR_BORD)
        {
            return false;
        }
    }

    //Verif du spawn
    int nbreSpawn = 0;
    for(int i = 0; i < instanceMap.x; i++)
    {
        for(int j = 0; j < instanceMap.y; j++)
        {
            if(instanceMap.ptr_map[i][j] == CHAR_SPAWN)
            {
                nbreSpawn++;
            }
        }
    }

    if(nbreSpawn == 0)
    {
        afficherMessageConsole("Aucun point d'apparition trouve", ERRMSG);
        return false;
    }

    if(nbreSpawn > 1)
    {
        afficherMessageConsole("Plusieurs points d'apparition trouves", ERRMSG);
        return false;
    }

    return true;
}

map chargementMap()
{
    FILE* fichierMap = NULL;
    map instanceMap;
    instanceMap.ptr_map = NULL;

    fichierMap = fopen("map/map.txt", "r");
    if(fichierMap == NULL)
    {
        afficherMessageConsole("Le fichier map.txt n'existe pas ou sa lecture est impossible", ERRMSG);
        fclose(fichierMap);
        exit(1);
    }

    tailleMap(fichierMap, instanceMap, &(instanceMap.x), &(instanceMap.y));

    instanceMap.ptr_map = initTableau(instanceMap.x, instanceMap.y);
    if(instanceMap.ptr_map == NULL)
    {
        fclose(fichierMap);
        exit(1);
    }

    //Chargement map
    for(int i = 0; i < instanceMap.x; i++)
    {
        for(int j = 0; j < instanceMap.y; j++)
        {
            fseek(fichierMap, i + j*(instanceMap.x + 1), SEEK_SET);
            instanceMap.ptr_map[i][j] = fgetc(fichierMap);
        }
    }

    if(verifFormat(fichierMap, instanceMap) == false)
    {
        afficherMessageConsole("Le format du fichier map.txt est invalide", ERRMSG);
        fclose(fichierMap);
        exit(1);
    }

    /* Tests
    mvprintw(LINES / 2 - 1, 1, "x = %d", *x);
    mvprintw(LINES / 2    , 1, "y = %d", *y);
    for(int i = 0; i < instanceMap.y; i++)
    {
        mvprintw(LINES / 2 + 4 + i, 1, "");
        for(int j = 0; j < instanceMap.x; j++)
        {
            c = instanceMap.ptr_map[j][i];
            printw("%c", c);
        }
    } */

    afficherMessageConsole("Chargement map effectue", INFOMSG);
    fclose(fichierMap);

    return instanceMap;
}

//Renvoie les coordonées du point d'apparition
void posSpawnJoueur(int* x, int* y, map instanceMap)
{
    for(int i = 0; i < instanceMap.x; i++)
    {
        for(int j = 0; j < instanceMap.y; j++)
        {
            if(instanceMap.ptr_map[i][j] == CHAR_SPAWN)
            {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}