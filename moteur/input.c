#include <ncurses.h>
#include <stdbool.h>

#include "../affichage/console.h"
#include "../gameplay/gameplay.h"
#include "../gameplay/joueur.h"
#include "../main.h"


/* Permet d'effectuer des actions celon l'entree clavier utilisee */
void inputControle(int entree, bool *enCours, joueur *j, map instanceMap) {

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
            if (consoleActive) {
                mortJoueur(j, instanceMap);
            }
            break;
        
        case 'v':
            //DEVMODE
            if (consoleActive) {
                victoireJoueur(j, instanceMap);
            }
            break;
        
        default:
            break;
        
    }
    return;

}