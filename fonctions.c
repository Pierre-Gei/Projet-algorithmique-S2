#include <math.h> 
#include <stdio.h>
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"
#include "structure.h"
#include <string.h>
#include <time.h>

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

    return ((0.5*hauteurFenetre() - 30)*distance_reel)/4498396441;
}

float echelle_planete(double rayon_reel, int valeur_fixe, float coefficient)
{
    return ((coefficient * largeurFenetre()) * (rayon_reel / 696342) + valeur_fixe);
}
float facteur_temps(float periode){
    return (1/periode);
}

Planete initplanete(char nomP[],float Distance_OrbitP,float rayonP,float masseP,float Orbit_periodeP)
{
    Planete plane;
    strcpy(plane.nom,nomP);
    plane.Distance_Orbit=Distance_OrbitP;
    plane.rayon=rayonP;
    plane.masse=masseP;
    plane.Orbit_periode=Orbit_periodeP;
    return plane;
}

double button_pause(int etat, double temps, float facteur){
    if(etat==0){
        couleurCourante(255, 255, 0);
        afficheChaine("paused",20,((largeurFenetre()/2)-((tailleChaine("paused",20))/2)),((hauteurFenetre())-20));
        return temps;
    }
    else{
        char chaine[40];
        couleurCourante(255, 255, 0);
        sprintf(chaine, "Vitesse de la simulation = %3.2f", facteur);
        afficheChaine(chaine,20,((largeurFenetre()/2)-((tailleChaine(chaine,20))/2)),((hauteurFenetre())-20));
        return (temps+(0.04*facteur));
    }
}

void affiche_date(double temps, time_t start_time){
    double temps_ecoule_relatif;
    time_t temps_ecoule_absolute;
    temps_ecoule_relatif = difftime(temps,start_time);
    temps_ecoule_absolute = (time_t)((temps_ecoule_relatif*86400)+temps);
    struct tm *date = gmtime(&temps_ecoule_absolute);
    char text_date[40];
    couleurCourante(255, 255, 255);
    sprintf(text_date, "%d/%d/%d", date->tm_mday, (date->tm_mon)+1, (date->tm_year)+1900);
    afficheChaine(text_date,20,((largeurFenetre()/2)-((tailleChaine(text_date,20))/2)),((hauteurFenetre())-50));
}