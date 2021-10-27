#include <stdlib.h>
#include <stdio.h>

#include "../affichage/affichage.h"
#include "../affichage/console.h"

char* initTableau(int x, int y)
{
    char* map = NULL;

    //Réservation pour le stockage de la map en mémoire
    map = malloc((x * y) * sizeof(char));

    return map;
}

char* chargementMap()
{
    FILE* fichierMap = NULL;
    char* map = NULL;
    fichierMap = fopen("map/map.txt", "r");

    if(fichierMap == NULL)
    {
        afficherMessageConsole("Le fichier map.txt n'existe pas ou est invalide", ERRMSG);
        return NULL;
    }

    map = initTableau(8, 8);

    if(map == NULL)
    {
        afficherMessageConsole("Erreur d'allocation memoire", ERRMSG);
        return NULL;
    }

    //Chargement map
    afficherMessageConsole("Chargement map effectue", INFOMSG);

    return map;
}