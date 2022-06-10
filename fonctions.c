#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"

int x_absolute(int x_centre, int x_relatif)
{
    return (x_relatif + x_centre);
}

int y_absolute(int y_centre, int y_relatif)
{
    return (y_relatif + y_centre);
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

void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[])
{
    int taille = tailleChaine(nom_objet, 15);
    afficheChaine(nom_objet, 15, (x_objet - (taille / 2)), (((y_objet) + rayon_objet) + 20));
}

float echelle_orbite(double distance_reel)
{

    return ((0.5 * hauteurFenetre() - 30) * distance_reel) / 4498396441;
}

float echelle_planete(double rayon_reel, float coefficient)
{
    return ((coefficient * largeurFenetre()) * (rayon_reel / 696342));
}
float facteur_temps(Planete planete)
{
    return (1 / planete.Orbit_periode);
}

Planete initplanete(char nomP[], float Distance_OrbitP, float rayonP, float masseP, float Orbit_periodeP)
{
    Planete plane;
    strcpy(plane.nom, nomP);
    plane.Distance_orbit = Distance_OrbitP;
    plane.rayon = rayonP;
    plane.masse = masseP;
    plane.Orbit_periode = Orbit_periodeP;
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
void initTab(Planete tab[], int taille) // OK
{
    for (int i = 0; i < taille; i++)
    {
        tab[i].x = 0;
        tab[i].y = 0;
        tab[i].vx = 0;
        tab[i].vy = 0;
        tab[i].Distance_orbit = 0;
        tab[i].rayon = 0;
        tab[i].masse = 0;
        tab[i].Orbit_periode = 0;
        memset(tab[i].nom, 0, 20);
    }
}

void afficheTab(Planete tab[], int taille) // OK
{
    for (int i = 0; i < taille; i++)
    {
        printf("Nom : %s\n", tab[i].nom);
        printf("x = %f\n", tab[i].x);
        printf("y = %f\n", tab[i].y);
        printf("Distance orbite : %lf\n", tab[i].Distance_orbit);
        printf("Rayon : %lf\n", tab[i].rayon);
        printf("Masse : %.2E\n", tab[i].masse);
        printf("Orbit periode : %f\n", tab[i].Orbit_periode);
    }
}

void setTab(Planete tab[], int position, char nom[],double masseP,float orbit_periode)
{
    strcpy(tab[position].nom, nom);
    tab[position].masse = masseP;
    tab[position].Orbit_periode = orbit_periode;
}

void echelle_tab(Planete tab[], int position, double distance_orbitale, double rayon, float planet_coeff,float zoom)
{
    tab[position].Distance_orbit = (echelle_orbite(distance_orbitale))*zoom;
    tab[position].rayon = echelle_planete(rayon, planet_coeff)*zoom;
}

Planete deplacementH(Planete astre){
	astre.y=astre.y-10;
	return astre;
}

Planete deplacementB(Planete astre){
	astre.y=astre.y+10;
	return astre;
}

Planete deplacementG(Planete astre){
	astre.x=astre.x+10;
	return astre;
}

Planete deplacementD(Planete astre){
	astre.x=astre.x-10;
	return astre;
}	

