#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./console.h"
#include "../gameplay/joueur.h"
#include "../map/map.h"


WINDOW* titre;
WINDOW* jeu;


int nbColonneTerminal, nbLigneTerminal;
int jxMax, jyMax;
int txMax, tyMax;


typedef struct s_camera {

    int centrex;
    int centrey;
    int longueur;
    int largeur;

} camera;


const char logo[] = 
"  _____  ______                               \n"
" |  __ \\|  ____|                             \n"
" | |__) | |__ ___  _ __ _ __ ___   ___ _ __   \n"
" |  ___/|  __/ _ \\| '__| '_ ` _ \\ / _ | '__|\n"
" | |    | | | (_) | |  | | | | | |  __| |     \n"
" |_|    |_|  \\___/|_|  |_| |_| |_|\\___|_|   \n"
;


/* Initialise la bibliotèque NCurses */
void initCurses() {

    initscr();
    start_color();
    noecho(); // Permet de ne pas afficher l'entrée utilisateur
    curs_set(0); // Curseur invisible

    return;

}


/* Affiche le menu */
void afficherMenu() {

    printw(logo);
    mvprintw(7, 1, "Bienvenue, appuyez sur une touche pour jouer !");
    mvprintw(LINES-4, 1, "Controles :");
    mvprintw(LINES-3, 1, "Mouvement Droite/Gauche : Fleche Droite/Gauche");
    mvprintw(LINES-2, 1, "Saut : Fleche Haut ou Barre Espace");
    mvprintw(LINES-1, 1, "Quitter le jeu : Touche Echap");

    return;

}


/* Initialise l'affichage */
void initAffichageJeu() {

    nbColonneTerminal = COLS;
    nbLigneTerminal = LINES;

    // création des fenêtres
    //DEVMODE
    if (consoleActive) {
    
        titre = subwin(stdscr, 3, nbColonneTerminal,  0, 0);
        init_pair(consoleActive, COLOR_CYAN, COLOR_BLACK);
        wattron(titre, COLOR_PAIR(consoleActive));
        
        jeu = subwin(stdscr, nbLigneTerminal-3-nbLigneConsole, nbColonneTerminal, 3+nbLigneConsole, 0);
    
    }
    else {

        titre = subwin(stdscr, 3, nbColonneTerminal,  0, 0);
        jeu = subwin(stdscr, nbLigneTerminal-3, nbColonneTerminal, 3, 0);

    }

    // initialisation titre
    getmaxyx(titre, tyMax, txMax);
    
    box(titre, ACS_VLINE, ACS_HLINE);
    mvwprintw(titre, 1, (txMax/2)-4, "Platformer");

    // initialisation jeu
    getmaxyx(jeu, jyMax, jxMax);

    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);

    return;

}


/* Redimensionne les différentes fenêtres */
void redimensionnerFenetre() {

    //DEVMODE
    if (consoleActive) {
    
        wresize(titre, tyMax, nbColonneTerminal);
    
        werase(console);
        delwin(console);
        initFenetreConsole();

        wrefresh(console);
    
        wresize(jeu, nbLigneTerminal-tyMax-nbLigneConsole, nbColonneTerminal);
        box(titre, ACS_VLINE, ACS_HLINE);
    
    }
    else {
    
        wresize(titre, tyMax, nbColonneTerminal);
        wresize(jeu, nbLigneTerminal-tyMax, nbColonneTerminal);
    
    }

    return;

}


/* Positionne le centre de la camera en fonction de la map et de la position du joueur */
void positionnerCamera(camera* cam, joueur* j, map* instanceMap) {

    // axe x (bordures)
    if (j->position.x < cam->longueur/2) {
        cam->centrex = cam->longueur/2;
    }
    else if (j->position.x > instanceMap->x-(cam->longueur/2)) {
        cam->centrex = instanceMap->x-(cam->longueur/2);
    }
    else {
        cam->centrex = j->position.x; // par défaut centré sur le joueur
    }
    
    // axe y
    if (j->position.y < cam->largeur/2) {
        cam->centrey = cam->largeur/2;
    }
    else if (j->position.y > instanceMap->y-(cam->largeur/2)) {
        cam->centrey = instanceMap->y-(cam->largeur/2);
    }
    else {
        cam->centrey = j->position.y; // par défaut centré sur le joueur
    }

    return;

}


/* Affiche le jeu */
void affichageJeu(joueur j, map instanceMap) {

    // redimension des fenêtres
    if ((nbColonneTerminal != COLS) || (nbLigneTerminal != LINES)) {
    
        nbColonneTerminal = COLS;
        nbLigneTerminal = LINES;
    
        redimensionnerFenetre();
    
        // reinitialisation du titre
        getmaxyx(titre, tyMax, txMax);
        werase(titre);
        box(titre, ACS_VLINE, ACS_HLINE);
        mvwprintw(titre, 1, (txMax/2)-4, "Platformer");
        wrefresh(titre);
    
        getmaxyx(jeu, jyMax, jxMax);
        werase(jeu);

        afficherMessageConsole("Nouveau redimensionnement fenetre", INFOMSG);
    
    }

    // définition de la camera
    camera cam;
    
    cam.longueur = jxMax;
    if (jxMax > instanceMap.x) {
        cam.longueur = instanceMap.x;
    }
    
    cam.largeur = jyMax;
    if (jyMax > instanceMap.y) {
        cam.largeur = instanceMap.y;
    }
    
    positionnerCamera(&cam, &j, &instanceMap);

    // affichage du jeu
    int jx;
    int jy = (jyMax/2)-(cam.largeur/2);
    
    // On affiche la map en fonction du centre de la camera (centre - la moitier de la longeur)
    for (int y = cam.centrey-(cam.largeur/2); y < cam.centrey+(cam.largeur/2); y++) { // axe x
    
        jx = (jxMax/2)-(cam.longueur/2);
    
        for (int x = cam.centrex-(cam.longueur/2); x < cam.centrex+(cam.longueur/2); x++) { //axe y
        
            // affichage du joueur
            if (x == j.position.x && y == j.position.y) {
                mvwprintw(jeu, jy, jx, "&");
            }
        
            //DEVMODE (affichage de la camera)
            else if ((consoleActive) && ((x == cam.centrex) && (y == cam.centrey))) {
            
                wattron(jeu, COLOR_PAIR(consoleActive));
                mvwprintw(jeu, jy, jx, "C");
                wattroff(jeu, COLOR_PAIR(consoleActive));
            
            }
        
            // affichage de la map
            else {
            
                // gestion des bordures de la map
                if (instanceMap.ptr_map[x][y] == CHAR_BORD) {
                
                    //DEVMODE
                    if (consoleActive) {
                    
                        wattron(jeu, COLOR_PAIR(consoleActive));
                        mvwprintw(jeu, jy, jx, "%c", instanceMap.ptr_map[x][y]);
                        wattroff(jeu, COLOR_PAIR(consoleActive));
                    
                    }
                    else {
                        mvwprintw(jeu, jy, jx, "%c", CHAR_VIDE);
                    }
                
                }
                else {
                    mvwprintw(jeu, jy, jx, "%c", instanceMap.ptr_map[x][y]);
                }
            
            }
            
            jx++;
        
        }
        
        jy++;
    
    }

    wrefresh(jeu);

    return;

}


/* Affiche le message de mort */
void afficherMsgMort() {

    mvprintw(LINES/2, (COLS/2)-8, "Vous etes mort !"); 
    mvprintw(LINES/2 + 1, (COLS/2)-17, "Appuyez sur Entree pour reessayer !");

    return;

}


/* Affiche le message de victoire */
void afficherMsgVictoire() {

    mvprintw(LINES/2 - 1, (COLS/2)-13, "Bravo ! Vous avez gagne !"); 
    mvprintw(LINES/2, (COLS/2)-18, "Appuyez sur Entree pour recommencer"); 
    mvprintw(LINES/2 + 1, (COLS/2)-18, "Appuyez sur ECHAP pour quitter le jeu");

    return;

}


/* Libère la mémoire de l'affichage */
void libererMemoireAffichage() {

    //DEVMODE
    if (consoleActive) {
        wattroff(titre, COLOR_PAIR(consoleActive)); // on arrete la couleur pour le titre
    }

    wclear(titre);
    delwin(titre);

    wclear(jeu);
    delwin(jeu);

    return;

}