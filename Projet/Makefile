CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf
ZIPDIR=UVSQ_graphics


#Cible generique pour Linux
%: graphics.o %.c
	rm -f $@
	$(CC) $(CFLAGS) graphics.o $@.c -o $@ $(LIBS)

graphics.o: graphics.c graphics.h
	rm -f police.h
	touch police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	$(CC) $(CFLAGS) -c graphics.c -o graphics.o

install_sdl:
	sudo apt-get install libsdl1.2-dev
	sudo apt-get install libsdl-ttf2.0-dev


demo: demo_1 demo_2 demo_3
	./demo_1
	./demo_2
	./demo_3

zip: clean
#	rm -f $(ZIPDIR).zip
	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)
	cp demo*.c $(ZIPDIR)
	cp graphics.c $(ZIPDIR)
	cp graphics.h $(ZIPDIR)
	cp couleur.h $(ZIPDIR)
	cp Makefile $(ZIPDIR)
	cp *.ttf $(ZIPDIR)
	cp exo*.c $(ZIPDIR)
	zip -r $(ZIPDIR).zip $(ZIPDIR)
#	tar cvf $(ZIPDIR).tar $(ZIPDIR)
	rm -rf $(ZIPDIR)

clean:
	rm -f *core
	rm -f *.o
	rm -f police.h
	rm -f demo_1
	rm -f demo_2
	rm -f demo_3
	rm -f exo_1
	rm -f *.
	rm -f *.tgz
	rm -rf $(ZIPDIR)
