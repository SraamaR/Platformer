#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./console.h"
#include "./affichage.h"


WINDOW* titre;
WINDOW* jeu;


/* Redimensionne les différentes fenêtres */
void redimensionnerWindow() 
{
    //DEVMODE (version d'essaie, ne fonctionne pas très bien)
    if (consoleActive)
    {
        nbLigneConsole = LINES/6;
        if (nbLigneConsole > 5) 
        {
            nbLigneConsole = 5;
        }
        wresize(console, nbLigneConsole+1, COLS);
        
        wresize(titre, 3, COLS);
        wresize(jeu, LINES-nbLigneConsole-4, COLS);
    }
    
    else 
    {
        wresize(titre, 3, COLS);
        wresize(jeu, LINES-3, COLS);
    }

    return;
}


/* Positionne le centre de la camera en fonction de la map et de la position du joueur */
void positionnerCamera(camera* cam, joueur* j, map* instanceMap) 
{
    // axe x (bordures)
    if (j->position.x < cam->longueur/2) 
    {
        cam->centrex = cam->longueur/2;
    }
    else if (j->position.x > instanceMap->x-(cam->longueur/2)-1)
    {
        cam->centrex = instanceMap->x-(cam->longueur/2)-1;
    }
    else 
    {
        cam->centrex = j->position.x;
    }
    
    // axe y
    if (j->position.y < cam->largeur/2) 
    {
        cam->centrey = cam->largeur/2;
    }
    else if (j->position.y > instanceMap->y-(cam->largeur/2)-1) 
    {
        cam->centrey = instanceMap->y-(cam->largeur/2)-1;
    }
    else 
    {
        cam->centrey = j->position.y;
    }

    return;
}


/* affiche le jeu */
void affichage(joueur j, map instanceMap) 
{
    // redimension des fenêtres
    redimensionnerWindow();
    
    int jxMax, jyMax;
    getmaxyx(jeu, jyMax, jxMax);
    
    wclear(jeu);
    


    // définition de la camera
    camera cam;
    
    cam.longueur = jxMax;
    if (jxMax > instanceMap.x) 
    {
        cam.longueur = instanceMap.x;
    }
    
    cam.largeur = jyMax;
    if (jyMax > instanceMap.y) 
    {
        cam.largeur = instanceMap.y;
    }
    
    positionnerCamera(&cam, &j, &instanceMap);


    // affichage du jeu
    int jx;
    int jy = (jyMax/2)-(cam.largeur/2);
    
    for (int y = cam.centrey-(cam.largeur/2); y < cam.centrey+(cam.largeur/2)+1; y++) 
    {
        jx = (jxMax/2)-(cam.longueur/2);
        
        for (int x = cam.centrex-(cam.longueur/2); x < cam.centrex+(cam.longueur/2)+1; x++) 
        {
            if (x == j.position.x && y == j.position.y) 
            {
                mvwprintw(jeu, jy, jx, "|");
            }
            
            //DEVMODE
            else if ((consoleActive) && ((x == cam.centrex) && (y == cam.centrey))) 
            {
                mvwprintw(jeu, jy, jx, "C");
            }
            
            else 
            {
                mvwprintw(jeu, jy, jx, "%c", instanceMap.ptr_map[x][y]);
            }
            
            jx++;
        }
        
        jy++;
    }


    wrefresh(jeu);
    return;
}


/* Initialise l'affichage */
void initAffichage()
{
    //DEVMODE (version d'essaie, ne fonctionne pas très bien)
    if (consoleActive == true)
    {
        titre = subwin(stdscr, 3, COLS,  nbLigneConsole+1, 0);
        jeu = subwin(stdscr, LINES-nbLigneConsole-4, COLS, nbLigneConsole+4, 0);
    }
    
    else
    {
        titre = subwin(stdscr, 3, COLS,  0, 0);
        jeu = subwin(stdscr, LINES-3, COLS, 3, 0);
    }

    // titre
    int txMax;
    txMax = getmaxx(titre);

    box(titre, ACS_VLINE, ACS_HLINE);
    mvwprintw(titre, 1, (txMax/2)-4, "Platformer");


    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);
    return;
}


/* Libère la mémoire de l'affichage (window) */
void libererMemoireAffichage()
{
    wclear(titre);
    delwin(titre);

    wclear(jeu);
    delwin(jeu);

    return;
}