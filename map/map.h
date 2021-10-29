#ifndef MAP_H
#define MAP_H

typedef struct map{
    char** ptr_map;
    int x;  //Longueur
    int y;  //Hauteur
} map;

map chargementMap();

void libererMemoireMap(map instanceMap);

#endif
