#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../affichage/console.h"
#include "./map.h"


const int LONGUEUR_MIN_MAP = 21;
const int LONGUEUR_MAX_MAP = 255;
const int NBRE_LIGNES_MIN_MAP = 7;
const int NBRE_LIGNES_MAX_MAP = 255;


const char CHAR_BORD  = '#';
const char CHAR_SPAWN = '%';
const char CHAR_VIDE  = ' ';
const char CHAR_PLEIN = '.';
const char CHAR_MUR = '|';
const char CHAR_COIN = '+';
const char CHAR_PLATFORME = '-';
const char CHAR_PIQUEHAUT = 'v';
const char CHAR_PIQUEBAS = '^';
const char CHAR_PIQUEDROITE = '<';
const char CHAR_PIQUEGAUCHE = '>';
const char CHAR_FIN = '\\';


const char COLLISION = 'a';
const char PAS_COLLISION = ' ';


/* Renvoie un tableau vide de dimensions (x, y)
Renvoie NULL si une erreur d'allocation mémoire est rencontrée */
char** initTableau(int x, int y) {

    char** ptr_map = NULL;

    // Réservation pour la première ligne du tableau
    ptr_map = malloc(x * sizeof(char*));

    if (ptr_map == NULL) {
    
        afficherMessageConsole("Erreur d'allocation memoire", ERRMSG);
        return NULL;
    
    }
    
    // Réservation pour chaque colonne du tableau
    for (int i = 0; i < x; i++) {
    
        ptr_map[i] = malloc(y * sizeof(char));
    
        if (ptr_map[i] == NULL) {
        
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


/* Renvoie les dimensions de la carte */
void tailleMap(FILE* fichierMap, int* x, int* y) {

    // Stocke la première ligne
    char ligne[LONGUEUR_MAX_MAP];
    fgets(ligne, LONGUEUR_MAX_MAP, fichierMap);

    int longueurLignes = 0;
    int nbreLignes = 0;

    /* On compte la longueur des lignes de la carte
    en comptant le nombre de charactères bord de la premère ligne */
    for (int i = 0; i < LONGUEUR_MAX_MAP; i++) {
    
        if (ligne[i] == CHAR_BORD) {
            longueurLignes++;
        }
    
    }

    char c = CHAR_VIDE;
    char c_precedent = c;

    //On place le curseur à la position 0
    fseek(fichierMap, 0, SEEK_SET);

    //On incrémente le nombre de lignes à chaque fois qu'on trouve un saut de ligne
    while (c != EOF) {
    
        c_precedent = c;
        c = fgetc(fichierMap);
        if (c == '\n') {
            nbreLignes++;
        }
    
    }

    /* Si le dernier char du texte n'est pas un saut de ligne on corrige le nombre de lignes
    Cela permet de d'éviter d'avoir un nombre de lignes trop petit dans le cas où il n'y a pas
    de saut de ligne à la fin du fichier texte */
    if (c_precedent == CHAR_BORD) {
        nbreLignes++;
    }

    *x = longueurLignes;
    *y = nbreLignes;

    return;

}


/* Renvoie true si le format de la carte dans le fichier .txt est valide */
bool verifFormat(FILE* fichierMap, map instanceMap) {

    // La longueur ne peut pas depasser LONGUEUR_MAX_MAP en raison du fonctionnement de fgets pas besoin de vérifier donc
    if ((instanceMap.x < LONGUEUR_MIN_MAP) || (instanceMap.y < NBRE_LIGNES_MIN_MAP) || (instanceMap.x > NBRE_LIGNES_MAX_MAP)) {
        return false;
    }

    // Verif des bords de chaque ligne
    for (int j = 0; j < instanceMap.y; j++) {
    
        char c1 = instanceMap.ptr_map[0][j];
        char c2 = instanceMap.ptr_map[instanceMap.x-1][j];
        if ((c1 != CHAR_BORD) || (c2 != CHAR_BORD)) {
            return false;
        }
    
    }

    // Verif des bords de chaque colonne
    for (int j = 0; j < instanceMap.x; j++) {
    
        char c1 = instanceMap.ptr_map[j][0];
        char c2 = instanceMap.ptr_map[j][instanceMap.y-1];
        if ((c1 != CHAR_BORD) || (c2 != CHAR_BORD)) {
            return false;
        }
    
    }

    //On compte le nombre de charactères spawn de la carte
    int nbreSpawn = 0;
    for (int i = 0; i < instanceMap.x; i++) {
    
        for (int j = 0; j < instanceMap.y; j++) {
        
            if (instanceMap.ptr_map[i][j] == CHAR_SPAWN) {
                nbreSpawn++;
            }
        
        }
    
    }

    if (nbreSpawn == 0) {
    
        afficherMessageConsole("Aucun point d'apparition trouve", ERRMSG);
        return false;
    
    } 
    else if (nbreSpawn > 1) {
    
        afficherMessageConsole("Plusieurs points d'apparition trouves", ERRMSG);
        return false;
    
    }

    return true;

}


/* Lit un fichier texte puis renvoie ses données sous la forme d'un struct map lisible par le jeu */
map chargementMap() {

    FILE* fichierMap = NULL;
    map instanceMap;
    instanceMap.ptr_map = NULL;

    // Ouverture du fichier texte
    fichierMap = fopen("map/map.txt", "r");
    if (fichierMap == NULL) {
    
        afficherMessageConsole("Le fichier map.txt n'existe pas ou sa lecture est impossible", ERRMSG);
        fclose(fichierMap);
        exit(1);
    
    }

    // Calcul de la taille de la carte à partir du fichier texte
    tailleMap(fichierMap, &(instanceMap.x), &(instanceMap.y));

    instanceMap.ptr_map = initTableau(instanceMap.x, instanceMap.y);
    instanceMap.collision_map = initTableau(instanceMap.x, instanceMap.y);

    if ((instanceMap.ptr_map == NULL) || (instanceMap.collision_map == NULL)) {
    
        fclose(fichierMap);
        exit(1);
    
    }

    // Chargement map
    for (int i = 0; i < instanceMap.x; i++) {
    
        for (int j = 0; j < instanceMap.y; j++) {
        
            fseek(fichierMap, i+(j*(instanceMap.x+1)), SEEK_SET);
        
            char courant = fgetc(fichierMap);
        
            instanceMap.ptr_map[i][j] = courant;
        
            if ((courant == ' ') || (courant == '%') || (courant == CHAR_FIN)) {
                instanceMap.collision_map[i][j] = PAS_COLLISION;
            }
            else {
                instanceMap.collision_map[i][j] = COLLISION;
            }
        
        }
    
    }

    if (verifFormat(fichierMap, instanceMap) == false) {
    
        afficherMessageConsole("Le format du fichier map.txt est invalide", ERRMSG);
        fclose(fichierMap);
        exit(1);
    
    }

    afficherMessageConsole("Chargement map effectue", INFOMSG);
    fclose(fichierMap);

    return instanceMap;

}


/* Libère la mémoire occupée par les tableaux */
void libererMemoireMap(map instanceMap) {

    // On libère la mémoire pour chaque colonne
    for (int i = 0; i < instanceMap.x; i++) {
    
        free(instanceMap.ptr_map[i]);
        free(instanceMap.collision_map[i]);
    
    }
    // On libère la mémoire pour la première ligne
    free(instanceMap.ptr_map);
    free(instanceMap.collision_map);

    return;

}


/* Renvoie les coordonées du point d'apparition du joueur 
puis supprime le charactère spawn de la carte envoyée en argument */
void posSpawnJoueur(int* x, int* y, map instanceMap) {

    for (int i = 0; i < instanceMap.x; i++) {
    
        for (int j = 0; j < instanceMap.y; j++) {
        
            if (instanceMap.ptr_map[i][j] == CHAR_SPAWN) {
            
                *x = i;
                *y = j;
                return;
            
            }
        
        }
    
    }

    return;

}


/* Renvoie les coordonées de la ligne de victoire
puis supprime le charactère fin de la carte envoyée en argument */
int posFin(map instanceMap) {

    for (int i = 0; i < instanceMap.x; i++) {
    
        for (int j = 0; j < instanceMap.y; j++) {
        
            if (instanceMap.ptr_map[i][j] == CHAR_FIN) {
                return i;
            }
        
        }
    
    }

    return instanceMap.x -2;

}