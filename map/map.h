#ifndef MAP_H
#define MAP_H

extern const char CHAR_BORD;
extern const char CHAR_SPAWN;

typedef struct map {
    char** ptr_map;
    int x;  //Longueur ligne
    int y;  //Nombre lignes
} map;

map chargementMap();

void posSpawnJoueur(int* x, int* y, map instanceMap);

void libererMemoireMap(map instanceMap);

#endif