#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"


void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[])
{
	int taille = tailleChaine(nom_objet, 15);
	afficheChaine(nom_objet, 15, (x_objet - (taille / 2)), (((y_objet) + rayon_objet) + 20));
}

double button_pause(int etat, double temps, float facteur)
{
	if (etat == 0)
	{
		couleurCourante(255, 255, 0);
		afficheChaine("paused", 20, ((largeurFenetre() / 2) - ((tailleChaine("paused", 20)) / 2)), ((hauteurFenetre()) - 20));
		return temps;
	}
	else
	{
		char chaine[40];
		couleurCourante(255, 255, 0);
		sprintf(chaine, "Vitesse de la simulation = %3.2f", facteur);
		afficheChaine(chaine, 20, ((largeurFenetre() / 2) - ((tailleChaine(chaine, 20)) / 2)), ((hauteurFenetre()) - 20));
		return (temps + (0.04 * facteur));
	}
}

void affiche_date(double temps, time_t start_time)
{
	double temps_ecoule_relatif;
	time_t temps_ecoule_absolute;
	temps_ecoule_relatif = difftime(temps, start_time);
	temps_ecoule_absolute = (time_t)((temps_ecoule_relatif * 86400) + temps);
	struct tm *date = gmtime(&temps_ecoule_absolute);
	char text_date[40];
	couleurCourante(255, 255, 255);
	sprintf(text_date, "%d/%d/%d", date->tm_mday, (date->tm_mon) + 1, (date->tm_year) + 1900);
	afficheChaine(text_date, 20, ((largeurFenetre() / 2) - ((tailleChaine(text_date, 20)) / 2)), ((hauteurFenetre()) - 50));
}

void affiche_zoom(float zoom)
{
	char text_zoom[40];
	couleurCourante(255, 255, 255);
	sprintf(text_zoom, "zoom : x%.0f", zoom);
	afficheChaine(text_zoom, 20, largeurFenetre() - tailleChaine(text_zoom, 20) - 50, hauteurFenetre() - 50);
}

void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 200; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2. * M_PI / Pas;
	int index;

	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2. * M_PI * index / Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX + rayon * cos(angle), centreY + rayon * sin(angle),
				 centreX + rayon * cos(angle + PasAngulaire), centreY + rayon * sin(angle + PasAngulaire));
		// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
}

void affichage(Planete tab[], int taille)
{
	for (int i = 0; i < taille; i++)
	{
		couleurCourante(tab[i].color[0], tab[i].color[1], tab[i].color[2]);
		cercle(tab[i].x, tab[i].y, tab[i].rayon);
		centre_text(tab[i].x, tab[i].y, tab[i].rayon, tab[i].nom);
	}
}

//12200

void affichage_focus(Planete tab[],int Nbr)
{
	char chaine[40];
	couleurCourante(255, 255, 0);
	sprintf(chaine, "Nom : %s", tab[Nbr].nom);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) - 20));
	sprintf(chaine, "Rayon : %.0lf km", tab[Nbr].rayon_reel);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) - 40));
	sprintf(chaine,"Masse : %.2E kg", tab[Nbr].masse);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) - 60));
}