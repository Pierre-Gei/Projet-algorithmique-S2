menu: menu.o GFXlib/libisentlib.a calcul.o affichage.o save.o
	gcc -Wall menu.o -o menu GFXlib/libisentlib.a -lm -lglut -lGL -lX11 calcul.o affichage.o save.o -lm
menu.o: menu.c GFXlib/GfxLib.h GFXlib/BmpLib.h GFXlib/ESLib.h
	gcc -Wall -c menu.c
calcul.o: calcul.c
	gcc -g -Wall -c calcul.c
affichage.o: affichage.c  
	gcc -g -Wall -c affichage.c
save.o: save.c 
	gcc -g -Wall -c save.c
clean:
	rm -f *~ *.o