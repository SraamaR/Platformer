platformer: main.o affichage.o 
	gcc main.o affichage.o -o platformer -lncurses -Wall

main.o: main.c affichage/affichage.h	
	gcc -c main.c

affichage.o: affichage/affichage.c
	gcc -c affichage/affichage.c

clean:
	rm -f *.o
	rm -f platformer