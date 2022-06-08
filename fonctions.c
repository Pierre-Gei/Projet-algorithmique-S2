#include <math.h> 
#include <stdio.h>
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"

int x_absolute(int x_centre, int x_relatif){
    return(x_relatif+x_centre);
}

int y_absolute(int y_centre, int y_relatif){
    return(y_relatif+y_centre);
}

float calculAbscisse(double secondes)
{
    float longueurAbscisse;
    double angle = (2 * M_PI * secondes) / 365.25;
    longueurAbscisse = cos(angle);
    return longueurAbscisse;
}

float calculOrdonee(double secondes)
{
    float longueurOrdonne;
    double angle = (2 * M_PI * secondes) / 365.25;
    longueurOrdonne = sin(angle);
    return longueurOrdonne;
}

void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[]){
    int taille = tailleChaine(nom_objet,15);
    afficheChaine(nom_objet,15,(x_objet-(taille/2)),(((y_objet)+rayon_objet)+20));
}

float echelle_orbite(double distance_reel)
{
  
    return ((0.5*hauteurFenetre()- 20)*distance_reel)/4498396441;
}

float echelle_planete(double distance_reel, double rayon_reel)
{
    return (echelle_orbite(distance_reel)*rayon_reel)/distance_reel;
}