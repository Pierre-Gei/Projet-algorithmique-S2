#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "structure.h"
#include "calcul.h"
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
			point(tab[i].x_absolu, tab[i].y_absolu);
			epaisseurDeTrait(1);
			centre_text(tab[i].x_absolu, tab[i].y_absolu, tab[i].rayon, tab[i].nom);
		}
	}
	else
	{
		for (int i = 0; i < taille; i++)
		{
			couleurCourante(tab[i].color[0], tab[i].color[1], tab[i].color[2]);
			cercle(tab[i].x_absolu, tab[i].y_absolu, tab[i].rayon);
			centre_text(tab[i].x_absolu, tab[i].y_absolu, tab[i].rayon, tab[i].nom);
		}
	}
}

void affichage_focus(Planete tab[], int Nbr , DonneesImageRGB* imtab[])
{
	if (imtab[Nbr] != NULL) {
		ecrisImage(0, 120, imtab[Nbr]->largeurImage, imtab[Nbr]->hauteurImage, imtab[Nbr]->donneesRGB);
	}
	char chaine[40];
	couleurCourante(255, 255, 0);
	sprintf(chaine, "Nom : %s", tab[Nbr].nom);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) / 2 + 40));
	sprintf(chaine, "Rayon : %.0lf km", tab[Nbr].rayon_reel);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) / 2));
	sprintf(chaine, "Masse : %.2E kg", tab[Nbr].masse);
	afficheChaine(chaine, 20, 20, ((hauteurFenetre()) / 2 - 40));
	

}

void affichage_help(void)
{
	couleurCourante(255, 255, 255);
	epaisseurDeTrait(3);
	afficheChaine(" Menu commandes :", 20, 0, hauteurFenetre() - 20);
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
	afficheChaine(" Retour au menu = Tab", 15, 0, hauteurFenetre()-325);
}


void menu(int etat_menu){
	if(etat_menu == 1){
		couleurCourante(125,125,125);
		rectangle(largeurFenetre()*0.25,hauteurFenetre()*0.95,largeurFenetre()*0.75,hauteurFenetre()*0.81);
		rectangle(largeurFenetre()*0.25,hauteurFenetre()*0.76,largeurFenetre()*0.75,hauteurFenetre()*0.62);
		rectangle(largeurFenetre()*0.25,hauteurFenetre()*0.57,largeurFenetre()*0.75,hauteurFenetre()*0.43);
		rectangle(largeurFenetre()*0.25,hauteurFenetre()*0.38,largeurFenetre()*0.75,hauteurFenetre()*0.24);
		rectangle(largeurFenetre()*0.25,hauteurFenetre()*0.20,largeurFenetre()*0.75,hauteurFenetre()*0.05);
		couleurCourante(0,0,0);
		afficheChaine("Creer une nouvelle simulation",18,((largeurFenetre()*0.5)-(tailleChaine("Creer une nouvelle simulation",18)/2)),0.88*hauteurFenetre());
		afficheChaine("Reprendre la simulation ",18,((largeurFenetre()*0.5)-(tailleChaine("Reprendre la simulation ",18)/2)),0.69*hauteurFenetre());
		afficheChaine("Charger une simulation enregistree",18,((largeurFenetre()*0.5)-(tailleChaine("Charger une simulation enregistree",18)/2)),0.50*hauteurFenetre());
		afficheChaine("Sauvegarder la simulation en cours",18,((largeurFenetre()*0.5)-(tailleChaine("Sauvegarder la simulation en cours",18)/2)),0.31*hauteurFenetre());
		afficheChaine("Quitter",18,((largeurFenetre()*0.5)-(tailleChaine("Quitter",18)/2)),0.12*hauteurFenetre());
	}
}

int bouton_new_sim(void){
	int new_sim = 0;
	if((abscisseSouris()>largeurFenetre()*0.25) && (abscisseSouris()<largeurFenetre()*0.75) && (ordonneeSouris()<hauteurFenetre()*0.95) && (ordonneeSouris()>hauteurFenetre()*0.81)){
		new_sim = 1;
	}
	return new_sim;
}

int bouton_continue(void){
	int continuer = 0;
	if((abscisseSouris()>largeurFenetre()*0.25) && (abscisseSouris()<largeurFenetre()*0.75) && (ordonneeSouris()<hauteurFenetre()*0.76) && (ordonneeSouris()>hauteurFenetre()*0.62)){
		continuer = 1;
	}
	return continuer;
}

int bouton_load(void){
	int load_sim = 0;
	if((abscisseSouris()>largeurFenetre()*0.25) && (abscisseSouris()<largeurFenetre()*0.75) && (ordonneeSouris()<hauteurFenetre()*0.57) && (ordonneeSouris()>hauteurFenetre()*0.43)){
		load_sim = 1;
	}
	return load_sim;
}

int bouton_save(int etat_menu){
	int save_sim = 0;
	if((abscisseSouris()>largeurFenetre()*0.25) && (abscisseSouris()<largeurFenetre()*0.75) && (ordonneeSouris()<hauteurFenetre()*0.38) && (ordonneeSouris()>hauteurFenetre()*0.24)){
		save_sim = 1;
	}
	return save_sim;
}

void bouton_quit(void){
	if((abscisseSouris()>largeurFenetre()*0.25) && (abscisseSouris()<largeurFenetre()*0.75) && (ordonneeSouris()<hauteurFenetre()*0.20) && (ordonneeSouris()>hauteurFenetre()*0.05)){
		termineBoucleEvenements();
	}
}

void affiche_zone_de_texte(char name_file[], int cptchar){
	couleurCourante(255,255,255);
	afficheChaine("Entrez le nom du fichier et appuyez le boutton",18,((largeurFenetre()/2)-(tailleChaine("Entrez le nom du fichier et appuyez sur le bouton",18)/2)), (hauteurFenetre()/2)+30);
	afficheChaine(name_file,18,((largeurFenetre()/2)-(tailleChaine(name_file,18)/2)), hauteurFenetre()/2);
	couleurCourante(125,125,125);
	rectangle(0.35*largeurFenetre(),0.37*hauteurFenetre(),0.45*largeurFenetre(),0.47*hauteurFenetre());
	rectangle(0.55*largeurFenetre(),0.37*hauteurFenetre(),0.65*largeurFenetre(),0.47*hauteurFenetre());
	couleurCourante(255,255,255);
	afficheChaine("Valider",18,((largeurFenetre()*0.4)-(tailleChaine("Valider",18)/2)), hauteurFenetre()*0.42);
	afficheChaine("Annuler",18,((largeurFenetre()*0.6)-(tailleChaine("Annuler",18)/2)), hauteurFenetre()*0.42);
}

int boutton_valider(char name_file[]){
	if((abscisseSouris()>0.35*largeurFenetre()) && (abscisseSouris()<0.45*largeurFenetre()) && (ordonneeSouris()>0.37*hauteurFenetre()) && (ordonneeSouris()<0.47*hauteurFenetre()) && (name_file[0] != '\0')){
		return 0;
	}
	else{
		return 1;
	}

}

int boutton_annuler(char name_file[], int* cptchar){
	if((abscisseSouris()>0.55*largeurFenetre()) && (abscisseSouris()<0.65*largeurFenetre()) && (ordonneeSouris()>0.37*hauteurFenetre()) && (ordonneeSouris()<0.47*hauteurFenetre())){
		memset(name_file, '\0', 20);
		*cptchar = 0;
		return 0;
	}
	else{
		return 1;
	}
}