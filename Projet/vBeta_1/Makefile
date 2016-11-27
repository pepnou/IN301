all: vBeta_1
	

run: all
	./vBeta_1

vBeta_1: gestion_event.o affichage.o lecture_ecriture.o manipulation_liste.o vBeta_1.o
	gcc -Wall -g -o vBeta_1 vBeta_1.o gestion_event.o affichage.o lecture_ecriture.o manipulation_liste.o `sdl-config --libs` -lm -lSDL_ttf

vBeta_1.o: vBeta_1.c constantes.h
	gcc -c `sdl-config --cflags` vBeta_1.c

gestion_event.o: gestion_event.c constantes.h
	gcc -c `sdl-config --cflags` gestion_event.c

affichage.o: affichage.c constantes.h
	gcc -c `sdl-config --cflags` affichage.c
	
lecture_ecriture.o: lecture_ecriture.c constantes.h
	gcc -c lecture_ecriture.c

manipulation_liste.o: manipulation_liste.c constantes.h
	gcc -c manipulation_liste.c

clean:
	rm -f *.o
	rm -f vBeta_1
