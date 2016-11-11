all: vAlpha_2
	

run: all
	./vAlpha_2

vAlpha_2: vAlpha_2.o
	gcc -o vAlpha_2 vAlpha_2.o `sdl-config --libs` -lm -lSDL_ttf

vAlpha_2.o: vAlpha_2.c
	gcc -c `sdl-config --cflags` vAlpha_2.c

clean:
	rm -f *.o
	rm -f vAlpha_2
