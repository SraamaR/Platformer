#ifndef LOGGER_H
#define LOGGER_H

/* logger : permet d'ecrire dans un .txt des messageList d'erreurs et de deboguer le programme (version developpement) */


/* Ouvre le fichier de log */
void initFichierLog();

/* Ajoute un message au fichier de log */
void nouveauLog(char* message);

/* Referme le fichier de log */
void fermerFichierLog();


#endif
