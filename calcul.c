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

float echelle_orbite(double distance_reel)
{

    return ((0.5 * hauteurFenetre() - 30) * distance_reel) / 4498396441;
}

void echelle_tab(Planete tab[], int taille, float zoom)
{

    for (int i = 0; i < taille; i++)
    {
        tab[i].rayon = echelle_orbite(tab[i].rayon_reel) * zoom;
    }
}

void initTab(Planete tab[], int taille) 
{
    for (int i = 0; i < taille; i++)
    {
        tab[i].x = 0;
        tab[i].x_absolu = 0;
        tab[i].y = 0;
        tab[i].y_absolu = 0;
        tab[i].vx = 0;
        tab[i].vy = 0;
        tab[i].ax = 0;
        tab[i].ay = 0;
        tab[i].Distance_orbit = 0;
        tab[i].rayon = 0;
        tab[i].masse = 0;
        tab[i].Distance_reelle = 0;
        tab[i].rayon_reel = 0;
        for (int j = 0; j < 2; j++)
        {
            tab[i].color[j] = 0;
        }
        memset(tab[i].nom, 0, 20);
        memset(tab[i].type, 0, 20);
    }
}

void setTab(Planete tab[], int position, char nom[], double masseP, double distance_orbitale, double rayon, int r, int v, int b, float x, float y, float vx, float vy,char type[])
{
    strcpy(tab[position].nom, nom);
    tab[position].masse = masseP;
    tab[position].Distance_reelle = distance_orbitale;
    tab[position].rayon_reel = rayon;
    tab[position].color[0] = r;
    tab[position].color[1] = v;
    tab[position].color[2] = b;
    tab[position].x = x;
    tab[position].y = y;
    tab[position].vx = vx;
    tab[position].vy = vy;
    strcpy(tab[position].type,type);
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

float focus(Planete tab[], int nbr_planete, double temps)
{
    float x, y;
    float liste_zoom[12] = {3852, 1050000, 420000, 10500, 0, 815000, 40000, 46000, 109000, 109000, 250000, 300000};
    if (nbr_planete == 0)
    {
        tab[0].x = 0.5 * largeurFenetre();
        tab[0].y = 0.5 * hauteurFenetre();
    }
    else
    {
        tab[0].x = 0.5 * largeurFenetre();
        tab[0].y = 0.5 * hauteurFenetre();
        x = x_absolute(tab[0].x, liste_zoom[nbr_planete] * (echelle_orbite(tab[nbr_planete].x * pow(10, -3))));
        y = y_absolute(tab[0].y, liste_zoom[nbr_planete] * (echelle_orbite(tab[nbr_planete].y * pow(10, -3))));
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
        delta = ((0.04 * facteur) * 86400);
        return (delta);
    }
}

void ellipse(Planete tab[], int taille, double delta_temps, float zoom)
{
    float deltaVx = 0, deltaVy = 0, deltaMx = 0, deltaMy = 0;
    double temps = (double)(delta_temps / 4000.0);
    for (int j = 0; j < 4000; j = j + 1)
    {
        for (int i = 1; i < taille; i++)
        {
            if (i == 4)
            {
                tab[i].Distance_reelle = sqrt(pow((tab[i].x), 2) + pow((tab[i].y), 2));
                tab[i].ax = (((6.67E-11) * tab[3].masse * (-tab[i].x)) / pow(tab[i].Distance_reelle, 3)); 
                tab[i].ay = ((6.67E-11) * tab[3].masse * (-tab[i].y)) / pow(tab[i].Distance_reelle, 3);   
            }
            else
            {
                tab[i].Distance_reelle = sqrt(pow(tab[i].x, 2) + pow(tab[i].y, 2));
                tab[i].ax = ((6.67E-11) * tab[0].masse * (-tab[i].x)) / pow(tab[i].Distance_reelle, 3);
                tab[i].ay = ((6.67E-11) * tab[0].masse * (-tab[i].y)) / pow(tab[i].Distance_reelle, 3);
            }
        }
        for (int i = 1; i < taille; i++)
        {
            deltaVx = temps * tab[i].ax;
            deltaVy = temps * tab[i].ay;
            deltaMx = tab[i].vx * temps + (tab[i].ax * pow(temps, 2)) / 2;
            deltaMy = tab[i].vy * temps + (tab[i].ay * pow(temps, 2)) / 2;
            tab[i].x = tab[i].x + deltaMx;
            tab[i].y = tab[i].y + deltaMy;
            tab[i].vx = tab[i].vx + deltaVx;
            tab[i].vy = tab[i].vy + deltaVy;
        }
    }
}

void coordonnee_absolu(Planete tab[], int taille, float zoom)
{
    for (int i = 0; i < taille; i++)
    {
        if (i == 4)
        {
            tab[i].x_absolu = x_absolute(tab[3].x_absolu, echelle_orbite(tab[i].x * 0.001) * zoom);
            tab[i].y_absolu = y_absolute(tab[3].y_absolu, echelle_orbite(tab[i].y * 0.001) * zoom);
        }
        else
        {
            tab[i].x_absolu = x_absolute(tab[0].x, echelle_orbite(tab[i].x * 0.001) * zoom);
            tab[i].y_absolu = y_absolute(tab[0].y, echelle_orbite(tab[i].y * 0.001) * zoom);
        }
    }
}
