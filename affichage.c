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
	if (etat == 1)
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

void affichage(Planete tab[], int taille, float zoom)
{
	if (zoom < 110)
	{
		if (zoom < 10)
		{
			couleurCourante(tab[0].color[0], tab[0].color[1], tab[0].color[2]);
			epaisseurDeTrait(4);
			point(tab[0].x, tab[0].y);
			epaisseurDeTrait(1);
			centre_text(tab[0].x, tab[0].y, tab[0].rayon, tab[0].nom);
		}
		else
		{
			couleurCourante(tab[0].color[0], tab[0].color[1], tab[0].color[2]);
			cercle(tab[0].x, tab[0].y, tab[0].rayon);
			centre_text(tab[0].x, tab[0].y, tab[0].rayon, tab[0].nom);
		}
		for (int i = 1; i < taille; i++)
		{
			couleurCourante(tab[i].color[0], tab[i].color[1], tab[i].color[2]);
			epaisseurDeTrait(4);
			point(tab[i].x, tab[i].y);
			epaisseurDeTrait(1);
			centre_text(tab[i].x, tab[i].y, tab[i].rayon, tab[i].nom);
		}
	}
	else
	{
		for (int i = 0; i < taille; i++)
		{
			couleurCourante(tab[i].color[0], tab[i].color[1], tab[i].color[2]);
			cercle(tab[i].x, tab[i].y, tab[i].rayon);
			centre_text(tab[i].x, tab[i].y, tab[i].rayon, tab[i].nom);
		}
	}
}

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

void affichage_help(void)
{
	couleurCourante(255, 255, 255);
	epaisseurDeTrait(3);
	afficheChaine(" Menu commandes :", 20, 0, hauteurFenetre()-20);
	epaisseurDeTrait(2);
	afficheChaine(" Zoom + = P", 15, 0, hauteurFenetre()-45);
	afficheChaine(" Zoom - = M", 15, 0, hauteurFenetre()-65);
	afficheChaine(" Accelerer = S", 15, 0, hauteurFenetre()-85);
	afficheChaine(" Decelerer = D", 15, 0, hauteurFenetre()-105);
	afficheChaine(" Inverser le temps = R", 15, 0, hauteurFenetre()-125);
	afficheChaine(" Pause = espace", 15, 0, hauteurFenetre()-145);
	afficheChaine(" Haut = ^", 15, 0, hauteurFenetre()-165);
	afficheChaine(" Bas = V", 15, 0, hauteurFenetre()-185);
	afficheChaine(" Gauche = <", 15, 0, hauteurFenetre()-205);
	afficheChaine(" Droite = >", 15, 0, hauteurFenetre()-225);
	afficheChaine(" Focus = X", 15, 0, hauteurFenetre()-245);
	afficheChaine(" Se rapprocher du soleil = <", 15, 0, hauteurFenetre()-265);
	afficheChaine(" S'eloigner du soleil = >", 15, 0, hauteurFenetre()-285);
	afficheChaine(" Plein ecran = F", 15, 0, hauteurFenetre()-305);
	afficheChaine(" Quiter gfxlib = Q", 15, 0, hauteurFenetre()-325);
}
