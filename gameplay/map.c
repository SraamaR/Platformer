#include <stdlib.h>
#include <stdio.h>

#include "../affichage/affichage.h"

void initTableau(char* map, int x, int y)
{
    //Réservation pour le stockage de la map en mémoire
    map = malloc((x * y) * sizeof(char));
}

void chargementMap(char* map)
{
    FILE* fichierMap = NULL;
    fichierMap = fopen("map.txt", "r");

    if (fichierMap == NULL)
    {
        afficherMessageConsole("Le fichier map.txt n'existe pas ou est invalide");
        return;
    }

    initTableau(map, 8, 8);

    if(map == NULL)
    {
        afficherMessageConsole("Erreur d'allocation mémoire");
        return;
    }

    //Chargement map
    afficherMessageConsole("Chargement map effectué");
}