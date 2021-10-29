#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "../affichage/affichage.h"
#include "../affichage/console.h"

const int LONGUEUR_MAX_MAP = 255;

void libererMemoireMap(map instanceMap)
{
    free(instanceMap.ptr_map);
}

char** initTableau(int x, int y)
{
    char** ptr_map = NULL;

    ptr_map = malloc(x * sizeof(char*));

    for(int i = 0; i < x; i++)
    {
        //Réservation pour chaque colone du tableau
        ptr_map[i] = malloc(y * sizeof(char));

        if(ptr_map[i] == NULL)
        {
            afficherMessageConsole("Erreur d'allocation memoire colone", ERRMSG);
            //Fuite mémoire : Il faudra free chaque conlone
            //libererMemoireMap(ptr_map);
            return NULL;
        }
    }

    return ptr_map;
}

map chargementMap()
{
    FILE* fichierMap = NULL;
    
    map instanceMap;
    instanceMap.ptr_map = NULL;
    instanceMap.x = 0;
    instanceMap.y = 0;

    fichierMap = fopen("map/map.txt", "r");

    if(fichierMap == NULL)
    {
        afficherMessageConsole("Le fichier map.txt n'existe pas ou est invalide", ERRMSG);
        fclose(fichierMap);
        exit(1);
    }

    char ligne[LONGUEUR_MAX_MAP];
    fgets(ligne, LONGUEUR_MAX_MAP, fichierMap);

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    mvprintw(yMax / 2, xMax / 2 - 5, "%sM", ligne);

    instanceMap.ptr_map = initTableau(8, 8);
    if(instanceMap.ptr_map == NULL)
    {
        afficherMessageConsole("Erreur d'allocation memoire", ERRMSG);
        fclose(fichierMap);
        exit(1);
    }

    //Chargement map
    afficherMessageConsole("Chargement map effectue", INFOMSG);

    fclose(fichierMap);
    return instanceMap;
}