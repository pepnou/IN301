all: test
	./test
	
test: test.o
	#~ gcc -o test test.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
	gcc -o test test.o `sdl-config --libs` -lm -lSDL_ttf
	
test.o: test.c
	gcc -c `sdl-config --cflags` test.c

clean:
	rm -f *.o
	rm -f test
