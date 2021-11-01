#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./console.h"
#include "./affichage.h"

WINDOW *platformer;
int xMax, yMax;

// affiche le jeu
void affichage(joueur j, map instanceMap)
{
    //Char maximum qu'on peut afficher dans la fenêtre
    int nbre_char_x = 0;
    int nbre_char_y = 0;

    bool activerCameraX = false;
    bool activerCameraY = false;

    //On determine pour chaque axe le nombre de char maximum qu'on peut afficher et si la carte est trop grande pour la fenêtre 
    if(xMax - 2 < instanceMap.x)
    {
        nbre_char_x = xMax - 2; //-2 pour les bordures
        activerCameraX = true;
    }
    else
    {
        nbre_char_x = instanceMap.x;
    }
    if(yMax - 3 < instanceMap.y)
    {
        nbre_char_y = yMax - 3; //-3 pour les bordures + le titre du jeu
        activerCameraY = true;
    }
    else
    {
        nbre_char_y = instanceMap.y;
    }

    int posJoueurEcranX = -1;
    int posJoueurEcranY = -1;

    //Calcul de la position du joueur dans la fenêtre
    for (int i = 0; i < nbre_char_x; i++)
    {
        if (i == j.posx)
        {
            posJoueurEcranX = i;
        }
    }
    for (int i = 0; i < nbre_char_y; i++)
    {
        if (instanceMap.y - 1 - i == j.posy)
        {
            posJoueurEcranY = i;
        }
    }

    int decalage_x = 0;
    int decalage_y = 0;
       
    bool centrerX = false;
    //bool centrerY = false;

    if(posJoueurEcranX == -1)
    {
        centrerX = true;
    }
    else if(activerCameraX && posJoueurEcranX > nbre_char_x/2)
    {
        centrerX = true;
    }

    /*
    if(posJoueurEcranY == -1)
    {
        centrerY = true;
    }
    else if(activerCameraY && posJoueurEcranY > (nbre_char_y/2 + 1))
    {
        //centrerY = true;
    }
    */

    //Pour x : Si le décalage est activé on décale de façon à avoir le joueur au centre
    if(centrerX)
    {
        while(posJoueurEcranX != nbre_char_x/2)
        {
            decalage_x++;
            for(int i = 0; i < nbre_char_x; i++)
            {
                if(i + decalage_x == j.posx)
                {
                    posJoueurEcranX = i;
                }
            }
        }
    }
    //Pour y : On décale de façon à ce que le joueur soit dans la fenêtre
    if(activerCameraY)
    {
        while(posJoueurEcranY == -1)
        {
            decalage_y++;
            for(int i = 0; i < nbre_char_y; i++)
            {
                if(instanceMap.y - i - decalage_y == j.posy)
                {
                    posJoueurEcranY = i;
                }
            }
        }
    }
        
    int curseurY = yMax - 2;
    for (int i = 0; i < nbre_char_y; i++)
    {
        int curseurX = (xMax / 2) - nbre_char_x / 2;
        int c_y = instanceMap.y - 1 - i - decalage_y; //La position y dans le tableau du char à afficher
        for (int k = 0; k < nbre_char_x; k++)
        {
            int c_x = k + decalage_x;
            if(c_x < instanceMap.x && c_x >= 0)
            {
                char c = instanceMap.ptr_map[c_x][c_y];
                if(c != CHAR_SPAWN)
                {
                    mvwprintw(platformer, curseurY, curseurX, "%c", c);
                }

                //Affichage du joueur
                if(c_x == j.posx && c_y == j.posy)
                {
                    mvwprintw(platformer, curseurY, curseurX, "|");
                }
                if(c_x == j.posx && c_y == j.posy - 1)
                {
                    mvwprintw(platformer, curseurY, curseurX, "|");
                }
            }
            curseurX++;
        }
        curseurY--;
    }


    //Afficher joueur


    //Tests
    //mvwprintw(platformer, posJoueurEcranY - 1, j.posx, "|");
    mvwprintw(platformer, 1, 1, "%d, %d", posJoueurEcranX, posJoueurEcranY);
    mvwprintw(platformer, 2, 1, "%d, %d", decalage_x, decalage_y);
    //mvwprintw(platformer, 3, 1, "%d, %d", activerCameraX, activerCameraY);
    mvwprintw(platformer, 4, 1, "%d, %d", nbre_char_x, nbre_char_y);

    box(platformer, ACS_VLINE, ACS_HLINE);
    wrefresh(platformer);
}

// Initialise l'affichage
void initAffichage()
{
    //On choisit la bonne taille en fonction de la présence de la console
    if (consoleActive == true)
    {
        platformer = subwin(stdscr, LINES - ligneMax - 1, COLS, ligneMax + 1, 0);
    }

    else
    {
        platformer = subwin(stdscr, LINES, COLS, 0, 0);
    }

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

void libererMemoireAffichage()
{
    delwin(platformer);
}