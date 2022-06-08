#include <math.h> 
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"

int x_absolute(int x_centre, int x_relatif){
    return(x_relatif+x_centre);
}

int y_absolute(int y_centre, int y_relatif){
    return(y_relatif+y_centre);
}

float calculAbscisse(float secondes)
{
    float longueurAbscisse;
    float angle = (2 * M_PI * secondes) / 18262.5;
    longueurAbscisse = cos(angle);
    return longueurAbscisse;
}

float calculOrdonee(float secondes)
{
    float longueurOrdonne;
    float angle = (2 * M_PI * secondes) / 18262.5;
    longueurOrdonne = sin(angle);
    return longueurOrdonne;
}

void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[]){
    int taille = tailleChaine(nom_objet,15);
    afficheChaine(nom_objet,15,(x_objet-(taille/2)),(((y_objet)+rayon_objet)+20));
}