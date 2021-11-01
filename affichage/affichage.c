#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./console.h"
#include "./affichage.h"

WINDOW *platformer;
int xMax, yMax;

//Calcule la position du joueur dans la fenêtre, retourne -1 si le joueur n'est pas visible
int calculPosEcranX(int decalage_x, int nbre_char_x, int joueurPosX)
{
    for (int i = 0; i < nbre_char_x; i++)
    {
        if (i + decalage_x == joueurPosX)
        {
            return i;
        }
    }
    return -1;
}
//Calcule la position du joueur dans la fenêtre, retourne -1 si le joueur n'est pas visible
//On calcule la position du char du haut du joueur pour qu'il ne soit pas tronqué
int calculPosEcranY(int decalage_y, int nbre_char_y, int joueurPosY, int mapY)
{
    for (int i = 0; i < nbre_char_y; i++)
    {
        if (mapY - 1 - i - decalage_y == joueurPosY - 1)
        {
            return i;
        }
    }
    return -1;
}

//Rafraîchi l'affichage à chaque frame
void affichage(joueur j, map instanceMap)
{
    //Nombre de char maximum qu'on peut afficher dans la fenêtre
    int nbre_char_x = 0;
    int nbre_char_y = 0;

    bool activerCameraX = false;
    bool activerCameraY = false;

    //On determine pour chaque axe le nombre de char maximum qu'on peut afficher et si la carte est trop grande pour la fenêtre 
    if(xMax < instanceMap.x)
    {
        nbre_char_x = xMax;
        activerCameraX = true;
    }
    else
    {
        nbre_char_x = instanceMap.x;
    }
    if(yMax - 1 < instanceMap.y)
    {
        nbre_char_y = yMax - 1; //-1 pour le titre du jeu
        activerCameraY = true;
    }
    else
    {
        nbre_char_y = instanceMap.y;
    }

    int decalage_x = 0;
    int decalage_x_max = instanceMap.x - nbre_char_x;
    int decalage_y = 0;
    int decalage_y_max = instanceMap.y - nbre_char_y;

    //Calcul de la position du joueur dans la fenêtre
    int posJoueurEcranX = calculPosEcranX(decalage_x, nbre_char_x, j.position.x);
    int posJoueurEcranY = calculPosEcranY(decalage_y, nbre_char_y, j.position.y, instanceMap.y);

    bool centrerX = false;
    if(posJoueurEcranX == -1)
    {
        centrerX = true;
    }
    //On centre le joueur à partir du moment où il se trouve suffisament loin du bord
    else if(activerCameraX && j.position.x > nbre_char_x/2)
    {
        centrerX = true;
    }

    //Pour x : Si le décalage est activé on décale de façon à avoir le joueur au centre
    if(centrerX)
    {
        while(posJoueurEcranX != nbre_char_x/2)
        {
            decalage_x++;
            posJoueurEcranX = calculPosEcranX(decalage_x, nbre_char_x, j.position.x);
            
            //Lorsqu'on arrive à la fin de la map on ne décale plus
            if(decalage_x == decalage_x_max)
            {
                break;
            }
        }
    }
    //Pour y : On décale de façon à ce que le haut du joueur soit dans la fenêtre
    if(activerCameraY)
    {
        while(posJoueurEcranY == -1)
        {
            decalage_y++;
            posJoueurEcranY = calculPosEcranY(decalage_y, nbre_char_y, j.position.y, instanceMap.y);

            //Lorsqu'on arrive à la fin de la map on ne décale plus
            if(decalage_y == decalage_y_max)
            {
                break;
            }
        }
    }
    
    //On print ligne par ligne du bas vers le haut
    int curseurY = yMax - 1;
    for (int i = 0; i < nbre_char_y; i++)
    {
        int curseurX = (xMax / 2) - nbre_char_x / 2;
        int c_y = instanceMap.y - 1 - i - decalage_y; //La position y dans le tableau du char à afficher
        for (int k = 0; k < nbre_char_x; k++)
        {
            int c_x = k + decalage_x;
            char c = instanceMap.ptr_map[c_x][c_y];
            if(c != CHAR_SPAWN)
            {
                mvwprintw(platformer, curseurY, curseurX, "%c", c);
            }
            else
            {
                mvwprintw(platformer, curseurY, curseurX, " ");
            }

            //Affichage du joueur
            if(c_x == j.position.x && c_y == j.position.y)
            {
                mvwprintw(platformer, curseurY, curseurX, "|");
            }
            else if(c_x == j.position.x && c_y == j.position.y - 1)
            {
                mvwprintw(platformer, curseurY, curseurX, "|");
            }
            curseurX++;
        }
        curseurY--;
    }

    /*Tests
    mvwprintw(platformer, 2, 1, "%d, %d", decalage_x, decalage_y);
    mvwprintw(platformer, 3, 1, "%d, %d", activerCameraX, activerCameraY);
    mvwprintw(platformer, 4, 1, "%d, %d", nbre_char_x, nbre_char_y);
    mvwprintw(platformer, 1, 1, "%d, %d", yMax, posJoueurEcranY);
    */

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
    mvwprintw(platformer, 0, xMax / 2 - 5, "Platformer\n");
    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);

    return;
}

void libererMemoireAffichage()
{
    delwin(platformer);
}