#include <stdlib.h>

#include "joueur.h"
#include "../affichage/affichage.h"
#include "../affichage/console.h"


//Initialise un joueur aux positions (0, 0)
joueur initJoueur()
{
    joueur res;

    res.posx = 0;
    res.posy = 0;

    afficherMessageConsole("Initialisation du joueur effectue", INFOMSG);

    return res;
}