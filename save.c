#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "GFXlib/GfxLib.h"
#include "GFXlib/BmpLib.h"
#include "GFXlib/ESLib.h"

void save_nom(char nom[])
{
    FILE *fichier = NULL;
    fichier = fopen("save.txt", "a");
    if (fichier != NULL)
    {
        fprintf(fichier, "%s\n", nom);
        fclose(fichier);
    }
}

void save(Planete tab[], int taille, int i)
{
    FILE *fichier = NULL;
    char fin[] = ".txt";
    char debut[30];
    printf("entrer \n");
    scanf("%s", debut);
    strcat(debut, fin);
    fichier = fopen(debut, "w");

    if (fichier != NULL)
    {
        for (int i = 0; i < taille; i++)
        {
            fprintf(fichier, "Nom: %s\n", tab[i].nom);
            fprintf(fichier, "Couleur: %d %d %d\n", tab[i].color[0], tab[i].color[1], tab[i].color[2]);
            fprintf(fichier, "Rayon: %lf\n", tab[i].rayon_reel);
            fprintf(fichier, "Distance orbitale: %.2E\n", tab[i].Distance_reelle);
            fprintf(fichier, "Masse: %.2E\n", tab[i].masse);
            fprintf(fichier, "x= %f\n", tab[i].x);
            fprintf(fichier, "y= %f\n\n\n", tab[i].y);
        }
        fclose(fichier);
    }
    save_nom(debut);
}

void chargement(char nom[], Planete tab[], int taille)
{
    FILE *fichier = NULL;
    fichier = fopen(nom, "r");

    if (fichier != NULL)
    {
        for (int i = 0; i < taille; i++)
        {
            fscanf(fichier, "Nom: %s\n", tab[i].nom);
            fscanf(fichier, "Couleur: %d %d %d\n", &tab[i].color[0], &tab[i].color[1], &tab[i].color[2]);
            fscanf(fichier, "Rayon: %lf\n", &tab[i].rayon_reel);
            fscanf(fichier, "Distance orbitale: %lf\n", &tab[i].Distance_reelle);
            fscanf(fichier, "Masse: %lf\n", &tab[i].masse);
            fscanf(fichier, "x= %f\n", &tab[i].x);
            fscanf(fichier, "y= %f\n\n\n", &tab[i].y);
        }
        fclose(fichier);
    }
}
