#include <ncurses.h>
#include <stdbool.h>

#include "../affichage/console.h"
#include "../gameplay/gameplay.h"
#include "../gameplay/joueur.h"
#include "../main.h"

void inputControle(int entree, bool *enCours, joueur *j) {
    switch(entree) {
        case 27: // 27 => echap
            arretJeu();
            break;
        case KEY_UP:
            mouvSaut(j);
            break;
        case ' ':
            mouvSaut(j);
            break;        
        case KEY_RIGHT:
            mouvDroite(j);
            break;
        case KEY_LEFT:
            mouvGauche(j);
            break;
        case 'f':
            //DEVMODE
            if(consoleActive)
            {
                mortJoueur(j);
            }
            break;
        case 'v':
            //DEVMODE
            if (consoleActive)
            {
                victoireJoueur(j);
            }
            break;
        default:
            break;
    }
    return;
}