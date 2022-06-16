#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"
#include "structure.h"

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
        tab[i].Distance_reelle = 0;
        tab[i].rayon_reel = 0;
        for (int j = 0; j < 2; j++)
        {
            tab[i].color[j] = 0;
        }
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

void setTab(Planete tab[], int position, char nom[], double masseP, float orbit_periode, double distance_orbitale, double rayon, int r, int v, int b, float x, float y, float vx, float vy)
{
    strcpy(tab[position].nom, nom);
    tab[position].masse = masseP;
    tab[position].Orbit_periode = orbit_periode;
    tab[position].Distance_reelle = distance_orbitale;
    tab[position].rayon_reel = rayon;
    tab[position].color[0] = r;
    tab[position].color[1] = v;
    tab[position].color[2] = b;
    tab[position].x = x;
    tab[position].y = y;
    tab[position].vx = vx;
    tab[position].vy = vy;
}

void echelle_tab(Planete tab[], int taille, float planet_coeff, float zoom)
{

    for (int i = 0; i < taille; i++)
    {
        // tab[i].Distance_orbit = (echelle_orbite(tab[i].Distance_reelle)) * zoom;
        tab[i].rayon = echelle_orbite(tab[i].rayon_reel) * zoom;
    }
}

Planete deplacementH(Planete astre)
{
    astre.y = astre.y - 10;
    return astre;
}

Planete deplacementB(Planete astre)
{
    astre.y = astre.y + 10;
    return astre;
}

Planete deplacementG(Planete astre)
{
    astre.x = astre.x + 10;
    return astre;
}

Planete deplacementD(Planete astre)
{
    astre.x = astre.x - 10;
    return astre;
}

void calculPosition(Planete tab[], double temps, int taille)
{
    int position = 0;
    for (int i = 1; i < taille; i++)
    {
        position = 0;
        if (i == 4)
        {
            position = 3;
        }

        tab[i].x = (x_absolute(tab[position].x, (tab[i].Distance_orbit * calculAbscisse(temps * facteur_temps(tab[i])))));
        tab[i].y = (y_absolute(tab[position].y, (tab[i].Distance_orbit * calculOrdonee(temps * facteur_temps(tab[i])))));
    }
}

float focus(Planete tab[], int nbr_planete, double temps)
{
    float x, y;
    float liste_zoom[10] = {3852, 1050000, 420000, 420000, 0, 815663, 40000, 46000, 109000, 109000};
    if (nbr_planete == 0)
    {
        tab[0].x = 0.5 * largeurFenetre();
        tab[0].y = 0.5 * hauteurFenetre();
    }
    else
    {
        tab[0].x = 0.5 * largeurFenetre();
        tab[0].y = 0.5 * hauteurFenetre();
        x = x_absolute(tab[0].x, echelle_orbite(tab[nbr_planete].x * pow(10, -3)));
        y = y_absolute(tab[0].y, echelle_orbite(tab[nbr_planete].y * pow(10, -3)));
        printf("x : %f , y : %f \n", x, y);
        tab[0].x = ((0.5 * largeurFenetre()) - x + (0.5 * largeurFenetre()));
        tab[0].y = ((0.5 * hauteurFenetre()) - y + (0.5 * hauteurFenetre()));
    }
    return liste_zoom[nbr_planete];
}

double delta_temps(float facteur, int etat_pause)
{
    if (etat_pause == 1)
    {
        return 0;
    }
    else
    {
        double delta;
        delta = ((0.02 * facteur) * 86400)/365.25;
        return (delta);
    }
}

void ellipse(Planete tab[], int taille, double delta_temps, float zoom)
{
    float ax = 0, ay = 0, deltaVx = 0, deltaVy = 0, deltaMx = 0, deltaMy = 0;
    float temps = delta_temps / 100.0;
    printf("%f\n", temps);
    for (int j = 0; j < delta_temps; j = j + temps)
    {
        for (int i = 1; i < taille; i++)
        {
            tab[i].Distance_reelle = sqrt(pow(tab[i].x, 2) + pow(tab[i].y, 2));
            ax = ((6.67E-11) * tab[0].masse * (-tab[i].x)) / pow(tab[i].Distance_reelle, 3);
            ay = ((6.67E-11) * tab[0].masse * (-tab[i].y)) / pow(tab[i].Distance_reelle, 3);
            deltaVx = delta_temps * ax;
            deltaVy = delta_temps * ay;
            deltaMx = tab[i].vx * delta_temps + (ax * pow(delta_temps, 2)) / 2;
            deltaMy = tab[i].vy * delta_temps + (ay * pow(delta_temps, 2)) / 2;
            tab[i].x = tab[i].x + deltaMx;
            tab[i].y = tab[i].y + deltaMy;
            tab[i].vx = tab[i].vx + deltaVx;
            tab[i].vy = tab[i].vy + deltaVy;
        }
    }
}