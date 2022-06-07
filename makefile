main: main.o GFXlib/libisentlib.a fonctions.o
	gcc -Wall main.o -o main GFXlib/libisentlib.a -lm -lglut -lGL -lX11 fonctions.o -lm
main.o: main.c GFXlib/GfxLib.h GFXlib/BmpLib.h GFXlib/ESLib.h
	gcc -Wall -c main.c
fonctions.o: fonctions.c
	gcc -g -Wall -c fonctions.c
clean:
	rm -f *~ *.o