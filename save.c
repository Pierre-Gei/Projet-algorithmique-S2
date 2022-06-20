#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"


void save(Planete tab[], int taille, char nom[], double *temps_simulation, time_t *temps_reel)
{
	FILE *fichier = NULL;
	char fin[] = ".txt";
	strcat(nom, fin);
	fichier = fopen(nom, "w");

	if (fichier != NULL)
	{
		fprintf(fichier, "Tempsinit: %ld\n", *temps_reel);
		fprintf(fichier, "Temps: %lf\n\n", *temps_simulation);
		for (int i = 0; i < taille; i++)
		{
			fprintf(fichier, "Nom: %s\n", tab[i].nom);
			fprintf(fichier, "Type: %s\n", tab[i].type);
			fprintf(fichier, "Couleur: %d %d %d\n", tab[i].color[0], tab[i].color[1], tab[i].color[2]);
			fprintf(fichier, "Rayon: %lf\n", tab[i].rayon_reel);
			fprintf(fichier, "Distance orbitale: %.2E\n", tab[i].Distance_reelle);
			fprintf(fichier, "Periode: %f\n", tab[i].Orbit_periode);
			fprintf(fichier, "Masse: %.2E\n", tab[i].masse);
			fprintf(fichier, "x= %f\n", tab[i].x);
			fprintf(fichier, "y= %f\n", tab[i].y);
			fprintf(fichier, "vx= %f\n", tab[i].vx);
			fprintf(fichier, "vy= %f\n\n\n", tab[i].vy);
		}
		fclose(fichier);
	}
}

void chargement(char nom[], Planete tab[], int taille, double *temps_simulation, time_t *temps_reel)
{
	FILE *fichier = NULL;
	char fin[] = ".txt";
	strcat(nom, fin);
	fichier = fopen(nom, "r");

	if (fichier != NULL)
	{
		fscanf(fichier, "Tempsinit: %ld\n", temps_reel);
		fscanf(fichier, "Temps: %lf\n\n", temps_simulation);
		for (int i = 0; i < taille; i++)
		{
			fscanf(fichier, "Nom: %s\n", tab[i].nom);
			fscanf(fichier, "Type: %s\n", tab[i].type);
			fscanf(fichier, "Couleur: %d %d %d\n", &tab[i].color[0], &tab[i].color[1], &tab[i].color[2]);
			fscanf(fichier, "Rayon: %lf\n", &tab[i].rayon_reel);
			fscanf(fichier, "Distance orbitale: %lf\n", &tab[i].Distance_reelle);
			fscanf(fichier, "Periode: %f\n", &tab[i].Orbit_periode);
			fscanf(fichier, "Masse: %lf\n", &tab[i].masse);
			fscanf(fichier, "x= %f\n", &tab[i].x);
			fscanf(fichier, "y= %f\n\n\n", &tab[i].y);
			fscanf(fichier, "vx= %f\n", &tab[i].vx);
			fscanf(fichier, "vy= %f\n\n\n", &tab[i].vy);
		}
		fclose(fichier);
	}
}
