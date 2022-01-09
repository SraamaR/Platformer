#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../affichage/console.h"
#include "./frames.h"


FILE* logFile; // fichier de log


/* Ouvre le fichier de log */
void initFichierLog() {

    logFile = fopen("./log.txt", "w");

    if (logFile == NULL) {
        afficherMessageConsole("Erreur lors de l'ouverture du fichier de log", ERRMSG);
    }
    else {
    
        time_t t = time(NULL);
        struct tm tActuel = *localtime(&t);
        fprintf(logFile, "Platformer %d:%d\n", tActuel.tm_hour, tActuel.tm_min);
        
        afficherMessageConsole("Fichier de log ouvert correctement", INFOMSG);
    
    }

    return;

}


/* ajoute un message au fichier de log */
void nouveauLog(char* message) {

    if (logFile != NULL) {
        fprintf(logFile, "%d : %s \n", compteurFrame, message);
    }

    return;

}


/* referme le fichier de log */
void fermerFichierLog() {

    if (logFile != NULL) {
        fclose(logFile);
    }

    return;

}