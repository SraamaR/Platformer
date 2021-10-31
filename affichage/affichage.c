#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./console.h"
#include "./affichage.h"

WINDOW* platformer;
// WINDOW* jeu;

// Positionne le centre de la camera en fonction de la map et de la position du joueur
void positionnerCamera(camera* cam, joueur* j, map* instanceMap) {
    // bord gauche
    if (j->posx < 10)
        cam->centrex = 10;
    // bord droit
    else if (j->posx > instanceMap->x-11) // 10+1 car instanceMap.x représente la longueur et non le dernier indice
        cam->centrex = instanceMap->x-11;
    // centrée
    else
        cam->centrex = j->posx;
    
    // bord haut
    if (j->posy < 3)
        cam->centrey = 3;
    // bord bas
    else if (j->posy > instanceMap->y-4)
        cam->centrey = instanceMap->y-4;
    // centrée
    else
        cam->centrey = j->posy;
}

// affiche le jeu
void affichage(joueur j, map instanceMap)
{
    int wxMax, wyMax;
    getmaxyx(platformer, wyMax, wxMax);
    
    camera cam;
    positionnerCamera(&cam, &j, &instanceMap);
    
    // mvwprintw(platformer, 1, 1, "coordonnées joueur : (%d,%d) \t wxMax = %d", j.posx, j.posy, wxMax);
    // mvwprintw(platformer, 2, 1, "coordonnées cam : (%d,%d) \t wyMax = %d", cam.centrex, cam.centrey, wyMax);
    
    // affichage jeu
    int wx;
    int wy = (wyMax/2)-3;
    for (int y = cam.centrey-3; y < cam.centrey+4; y++) {
        wx = (wxMax/2)-10;
        for (int x = cam.centrex-10; x < cam.centrex+11; x++) {
            if (x == j.posx && y == j.posy)
                mvwprintw(platformer, wy, wx, "J");
            // else if (x == cam.centrex && y == cam.centrey)
                // mvwprintw(platformer, wy, wx, "C");
            else
                mvwprintw(platformer, wy, wx, "%c", instanceMap.ptr_map[x][y]);
            wx++;
        }
        wy++;
    }
    
    wrefresh(platformer);
}

// Initialise l'affichage
void initAffichage()
{
    //On choisit la bonne taille en fonction de la présence de la console
    if(consoleActive == true)
    {
        platformer = subwin(stdscr, LINES - ligneMax - 1, COLS, ligneMax + 1, 0);
    }
    
    else
    {
        platformer = subwin(stdscr, LINES, COLS, 0, 0);
    }
    
    
    int xMax, yMax;
    getmaxyx(platformer, yMax, xMax);
    
    /* Tests pour créer une fenêtre de jeu 
    mvwprintw(platformer, 3, 1, "x = %d, y = %d", xMax, yMax);
    mvwprintw(platformer, 4, 1, "h = %d, w = %d",(yMax/2)-(WINDOW_HEIGHT/2), (xMax/2)-(WINDOW_WIDTH/2));
    jeu = subwin(stdscr, WINDOW_WIDTH, WINDOW_HEIGHT, (yMax/2)-(WINDOW_HEIGHT/2), (xMax/2)-(WINDOW_WIDTH/2));
    box(jeu, ACS_VLINE, ACS_HLINE);
    */
    
    //Contour blanc
    box(platformer, ACS_VLINE, ACS_HLINE);
    
    mvwprintw(platformer, 1, xMax / 2 - 5, "Platformer\n");
    
    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);
    
    return;
}