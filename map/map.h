#ifndef MAP_H
#define MAP_H

typedef struct map {
    char** ptr_map;
    int x;  //Longueur ligne
    int y;  //Nombre lignes
} map;

map chargementMap();

void posSpawnJoueur(int* x, int* y, map instanceMap);

void libererMemoireMap(map instanceMap);

#endif