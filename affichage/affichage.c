#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../main.h"
#include "./console.h"
#include "../gameplay/joueur.h"
#include "../gameplay/gameplay.h"
#include "../map/map.h"


WINDOW* titre;
WINDOW* jeu;


int nbColonneTerminal, nbLigneTerminal;
int jxMax, jyMax;
int txMax, tyMax;


const int base = 0;
const int bleu = 1;
const int violet = 2;
const int rouge = 3;
const int vert = 4;
const int blanc = 5;
const int noir = 6;
const int cyan = 7;


typedef struct s_camera {

    int centrex;
    int centrey;
    int longueur;
    int largeur;

} camera;

const char* logo1[] = {
    "  _____ ",
    " |  __ \\",
    " | |__) ",
    " |  ___/",
    " | |    ",
    " |_|    "
};

const char* logo2[] = {
    " ______                               \n",
    "|  ____|                               \n",
    "| |__ ___  _ __ _ __ ___   ___ _ __   \n",
    "|  __/ _ \\| '__| '_ ` _ \\ / _ | '__|  \n",
    "| | | (_) | |  | | | | | |  __| |     \n",
    "|_|  \\___/|_|  |_| |_| |_|\\___|_|     \n",
};


/* Initialise les paires de couleurs */
void initCouleur() {

    init_pair(base, COLOR_WHITE, COLOR_BLACK); // Couleur de base
    init_pair(bleu, COLOR_BLUE, COLOR_BLACK); // Mur
    init_pair(violet, COLOR_MAGENTA, COLOR_BLACK); // Sol
    init_pair(rouge, COLOR_RED, COLOR_BLACK); // Pique, message de mort
    init_pair(vert, COLOR_GREEN, COLOR_BLACK); // Message de victoire
    init_pair(blanc, COLOR_WHITE, COLOR_WHITE); // Personnage
    init_pair(cyan, COLOR_CYAN, COLOR_BLACK); // DEVMODE
    init_pair(noir, COLOR_BLACK, COLOR_BLACK); // Invisible

    return;

}


/* Initialise la bibliotèque NCurses et les paires de couleurs*/
void initCurses() {

    initscr();
    start_color();
    initCouleur();
    noecho(); // Permet de ne pas afficher l'entrée utilisateur
    curs_set(0); // Curseur invisible

    return;

}


/* Affiche le menu */
void afficherMenu() {

    // Affichage du logo
    for (int y = 0; y < 6 ; y++) {
    
        attron(COLOR_PAIR(violet));
        mvprintw((LINES/2)-4+y, (COLS/2)-24, logo1[y]); // P
        attroff(COLOR_PAIR(violet));
    
        attron(COLOR_PAIR(bleu));
        mvprintw((LINES/2)-4+y, (COLS/2)-16, logo2[y]); // latformer
        attroff(COLOR_PAIR(bleu));
    
    }
    attron(A_BLINK); // Clignotement
    mvprintw((LINES/2)+4, (COLS/2)-23, "Veuillez appuyer sur une touche pour jouer !");
    attroff(A_BLINK);

    attron(COLOR_PAIR(violet));
    mvprintw(LINES-6, 2, "Controles :");
    attroff(COLOR_PAIR(violet));

    attron(COLOR_PAIR(bleu));
    mvprintw(LINES-4, 2, "Mouvement Droite/Gauche :");
    mvprintw(LINES-3, 2, "Saut :");
    mvprintw(LINES-2, 2, "Quitter le jeu :");
    attroff(COLOR_PAIR(bleu));

    mvprintw(LINES-4, 28, "Fleche Droite/Gauche");
    mvprintw(LINES-3, 9, "Fleche Haut ou Barre Espace");
    mvprintw(LINES-2, 19, "Touche Echap");

    refresh();

    return;

}


/* Ecrit le titre du jeu (fenetre titre) */
void ecrireTitre() {

    getmaxyx(titre, tyMax, txMax);

    // changement couleur vordure celon menu du jeu
    if (mortJoueurActif) {
    
        wattron(titre, COLOR_PAIR(rouge));
        box(titre, ACS_VLINE, ACS_HLINE);
        wattroff(titre, COLOR_PAIR(rouge));
    
    }
    else if (victoireJoueurActive) {
    
        wattron(titre, COLOR_PAIR(vert));
        box(titre, ACS_VLINE, ACS_HLINE);
        wattroff(titre, COLOR_PAIR(vert));
    
    }
    // [DEVMODE]
    else if (consoleActive) {
    
        wattron(titre, COLOR_PAIR(cyan));
        box(titre, ACS_VLINE, ACS_HLINE);
        wattroff(titre, COLOR_PAIR(cyan));
    
    }
    else {
        box(titre, ACS_VLINE, ACS_HLINE);
    }

    wattron(titre, COLOR_PAIR(violet));
    mvwprintw(titre, 1, (txMax/2)-4, "P");
    wattroff(titre, COLOR_PAIR(violet));

    wattron(titre, COLOR_PAIR(bleu));
    mvwprintw(titre, 1, (txMax/2)-3, "latformer");
    wattroff(titre, COLOR_PAIR(bleu));

    wrefresh(titre);
    return;

}


/* Initialise l'affichage */
void initAffichageJeu() {

    nbColonneTerminal = COLS;
    nbLigneTerminal = LINES;

    // création des fenêtres
    // [DEVMODE]
    if (consoleActive) {
    
        titre = subwin(stdscr, 3, nbColonneTerminal,  0, 0);
        wattron(titre, COLOR_PAIR(cyan));
        
        jeu = subwin(stdscr, nbLigneTerminal-3-nbLigneConsole, nbColonneTerminal, 3+nbLigneConsole, 0);
    
    }
    else {

        titre = subwin(stdscr, 3, nbColonneTerminal,  0, 0);
        jeu = subwin(stdscr, nbLigneTerminal-3, nbColonneTerminal, 3, 0);

    }

    // initialisation titre
    ecrireTitre();

    // initialisation jeu
    getmaxyx(jeu, jyMax, jxMax);

    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);

    return;

}


/* Redimensionne les différentes fenêtres */
void redimensionnerFenetre() {

    // [DEVMODE]
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
        cam->centrey = j->position.y;
    }

    return;

}

/* Permet de définir la constante couleur correspondante au caractere */
int definirCouleur(map instanceMap, int x, int y) {

    char c = instanceMap.ptr_map[x][y];

    // caracteres seulement visibles en [DEVMODE]
    if ((c == CHAR_BORD) || (c == CHAR_SPAWN) || (c == CHAR_FIN)) {
    
        if (consoleActive) {
            return cyan;
        }
        return noir;
    
    }
    // zone de victoire
    if (x >= x_fin) {
    
        if (victoireJoueurActive) { // menu de victoire
            return vert;
        }
        return base;
    
    }
    // piques
    if ((c == CHAR_PIQUEHAUT) || (c == CHAR_PIQUEBAS) || (c == CHAR_PIQUEGAUCHE) || (c == CHAR_PIQUEDROITE)) {
    
        if (mortJoueurActif) { // menu de mort
            return rouge;
        }
        return base;
    
    }
    // sol et delimitations
    if ((c == CHAR_COIN) || (c == CHAR_PLATFORME)) {
    
        if ((y > 0) && ((instanceMap.ptr_map[x][y-1] == ' ') || (instanceMap.ptr_map[x][y-1] == '%'))) { // On regarde s'il y a du vide au dessus
            return violet;
        }
        return bleu;
    
    }
    // murs
    if ((c == CHAR_MUR) || (c == CHAR_PLEIN)) {
        return bleu;
    }

    return base;

}


/* Affiche le jeu */
void affichageJeu(joueur j, map instanceMap) {

    // redimension des fenêtres
    if ((nbColonneTerminal != COLS) || (nbLigneTerminal != LINES)) {
    
        nbColonneTerminal = COLS;
        nbLigneTerminal = LINES;
    
        redimensionnerFenetre();
    
        werase(titre);
        ecrireTitre();
    
        getmaxyx(jeu, jyMax, jxMax);
        werase(jeu);

        afficherMessageConsole("Nouveau redimensionnement fenetre", INFOMSG);
    
    }

    // définition de la camera
    camera cam;
    
    cam.longueur = jxMax;
    if (jxMax > instanceMap.x) { // on limite la taille de la camera à celle de la map
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
    int couleur;
    
    // on affiche la map en fonction du centre de la camera (centre - la moitier de la longeur)
    for (int y = cam.centrey-(cam.largeur/2); y < cam.centrey+(cam.largeur/2); y++) { // axe x
    
        jx = (jxMax/2)-(cam.longueur/2);
    
        for (int x = cam.centrex-(cam.longueur/2); x < cam.centrex+(cam.longueur/2); x++) { // axe y
        
            // affichage du joueur
            if (x == j.position.x && y == j.position.y) {
            
                wattron(jeu, COLOR_PAIR(blanc));
                mvwaddch(jeu, jy, jx, '&');
                wattroff(jeu, COLOR_PAIR(blanc));
            
            }
            // [DEVMODE] affichage de la camera
            else if ((consoleActive) && ((x == cam.centrex) && (y == cam.centrey))) {
            
                wattron(jeu, COLOR_PAIR(cyan));
                mvwaddch(jeu, jy, jx, 'C');
                wattroff(jeu, COLOR_PAIR(cyan));
            
            }
            // affichage de la carte
            else {
            
                couleur = definirCouleur(instanceMap, x, y); // on définit la couleur à utiliser
            
                wattron(jeu, COLOR_PAIR(couleur));
                mvwaddch(jeu, jy, jx, instanceMap.ptr_map[x][y]);
                wattroff(jeu, COLOR_PAIR(couleur));
            
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

    ecrireTitre();

    attron(COLOR_PAIR(rouge));
    mvprintw(LINES/2, (COLS/2)-8, "Vous etes mort !"); 
    mvprintw(LINES/2 + 1, (COLS/2)-17, "Appuyez sur Entree pour reessayer !");
    attroff(COLOR_PAIR(rouge));

    return;

}


/* Affiche le message de victoire */
void afficherMsgVictoire() {

    ecrireTitre();

    attron(COLOR_PAIR(vert));
    mvprintw(LINES/2 - 1, (COLS/2)-13, "Bravo ! Vous avez gagne !"); 
    mvprintw(LINES/2, (COLS/2)-18, "Appuyez sur Entree pour recommencer"); 
    mvprintw(LINES/2 + 1, (COLS/2)-18, "Appuyez sur ECHAP pour quitter le jeu");
    attroff(COLOR_PAIR(vert));

    return;

}


/* Libère la mémoire de l'affichage */
void libererMemoireAffichage() {

    wclear(titre);
    delwin(titre);

    wclear(jeu);
    delwin(jeu);

    return;

}