#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "structure.h"
#include "fonctions.h"
#include <time.h>
#define LargeurFenetre 800
#define HauteurFenetre 600

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);

	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);

	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	return 0;
}

/* Fonction de trace de cercle */
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

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = true;
	static DonneesImageRGB *image = NULL;
	static double temps = 0;
	static time_t temps_reel = 0;
	static Planete tabPlanete[10];
	static int etat_pause = 1;
	static float vitesse_simulation = 1;
	static float zoom = 1;

	switch (evenement)
	{
	case Initialisation:
		modePleinEcran();
		temps_reel = time(NULL);
		temps = (double)difftime(temps_reel, 0);
		initTab(tabPlanete, 10);
		setTab(tabPlanete, 0, "Soleil", (double)1.98E+30, 0.0);
		setTab(tabPlanete, 1, "Mercure", (double)3.3E+23, 0.2408467);
		setTab(tabPlanete, 2, "Venus", (double)4.87E+24, 0.61519726);
		setTab(tabPlanete, 3, "Terre", (double)5.97E+24, 1);
		setTab(tabPlanete, 4, "Lune", (double)7.6E+22, 0.074853881);
		setTab(tabPlanete, 5, "Mars", (double)6.42E+23, 1.8808476);
		setTab(tabPlanete, 6, "Jupiter", (double)1.898E+27, 11.862615);
		setTab(tabPlanete, 7, "Saturne", (double)5.68E+26, 29.447498);
		setTab(tabPlanete, 8, "Uranus", (double)8.68E+25, 84.016846);
		setTab(tabPlanete, 9, "Neptune", (double)1.02E+26, 164.79132);

		tabPlanete[0].x = (0.5 * largeurFenetre());
		tabPlanete[0].y = (0.5 * hauteurFenetre());

		demandeTemporisation(20);

		image = lisBMPRGB("background1.bmp");
		break;
	case Temporisation:
		rafraichisFenetre();
		break;
	case Affichage:
		echelle_tab(tabPlanete, 0, (double)0, (double)696342, 0.002, zoom);
		echelle_tab(tabPlanete, 1, (double)57909227, (double)2432, 0.008, zoom);
		echelle_tab(tabPlanete, 2, (double)108209475, (double)6051, 0.008, zoom);
		echelle_tab(tabPlanete, 3, (double)149598262, (double)6371, 0.008, zoom);
		echelle_tab(tabPlanete, 4, (double)3844000, (double)1734, 0.008, zoom);
		echelle_tab(tabPlanete, 5, (double)227943824, (double)3389, 0.008, zoom);
		echelle_tab(tabPlanete, 6, (double)778340821, (double)69911, 0.008, zoom);
		echelle_tab(tabPlanete, 7, (double)1426666422, (double)58232, 0.008, zoom);
		echelle_tab(tabPlanete, 8, (double)2870658186, (double)25362, 0.008, zoom);
		echelle_tab(tabPlanete, 9, (double)4498396441, (double)24622, 0.008, zoom);

		tabPlanete[1].x = (x_absolute(tabPlanete[0].x, (tabPlanete[1].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[1])))));
		tabPlanete[1].y = (y_absolute(tabPlanete[0].y, (tabPlanete[1].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[1])))));

		tabPlanete[2].x = (x_absolute(tabPlanete[0].x, (tabPlanete[2].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[2])))));
		tabPlanete[2].y = (y_absolute(tabPlanete[0].y, (tabPlanete[2].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[2])))));

		tabPlanete[3].x = (x_absolute(tabPlanete[0].x, (tabPlanete[3].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[3])))));
		tabPlanete[3].y = (y_absolute(tabPlanete[0].y, (tabPlanete[3].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[3])))));

		tabPlanete[4].x = (x_absolute(tabPlanete[3].x, (tabPlanete[4].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[4])))));
		tabPlanete[4].y = (y_absolute(tabPlanete[3].y, (tabPlanete[4].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[4])))));

		tabPlanete[5].x = (x_absolute(tabPlanete[0].x, (tabPlanete[5].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[5])))));
		tabPlanete[5].y = (y_absolute(tabPlanete[0].y, (tabPlanete[5].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[5])))));

		tabPlanete[6].x = (x_absolute(tabPlanete[0].x, (tabPlanete[6].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[6])))));
		tabPlanete[6].y = (y_absolute(tabPlanete[0].y, (tabPlanete[6].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[6])))));

		tabPlanete[7].x = (x_absolute(tabPlanete[0].x, (tabPlanete[7].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[7])))));
		tabPlanete[7].y = (y_absolute(tabPlanete[0].y, (tabPlanete[7].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[7])))));

		tabPlanete[8].x = (x_absolute(tabPlanete[0].x, (tabPlanete[8].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[8])))));
		tabPlanete[8].y = (y_absolute(tabPlanete[0].y, (tabPlanete[8].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[8])))));

		tabPlanete[9].x = (x_absolute(tabPlanete[0].x, (tabPlanete[9].Distance_orbit * calculAbscisse(temps * facteur_temps(tabPlanete[9])))));
		tabPlanete[9].y = (y_absolute(tabPlanete[0].y, (tabPlanete[9].Distance_orbit * calculOrdonee(temps * facteur_temps(tabPlanete[9])))));

		effaceFenetre(0, 0, 0);

		ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);

		couleurCourante(255, 255, 0);
		cercle(tabPlanete[0].x, tabPlanete[0].y, (tabPlanete[0].rayon));
		centre_text(tabPlanete[0].x, tabPlanete[0].y, tabPlanete[0].rayon, "Soleil");

		couleurCourante(239,213,158);
		cercle(tabPlanete[1].x, tabPlanete[1].y, tabPlanete[1].rayon);
		centre_text(tabPlanete[1].x, tabPlanete[1].y, tabPlanete[1].rayon, "Mercure");

		couleurCourante(238,140,65);
		cercle(tabPlanete[2].x, tabPlanete[2].y, tabPlanete[2].rayon);
		centre_text(tabPlanete[2].x, tabPlanete[2].y, tabPlanete[2].rayon, "Venus");

		couleurCourante(0, 0, 255);
		cercle(tabPlanete[3].x, tabPlanete[3].y, tabPlanete[3].rayon);
		centre_text(tabPlanete[3].x, tabPlanete[3].y, tabPlanete[3].rayon, "Terre");

		couleurCourante(125, 125, 125);
		cercle(tabPlanete[4].x, tabPlanete[4].y, tabPlanete[4].rayon);
		centre_text(tabPlanete[4].x, tabPlanete[4].y, tabPlanete[4].rayon, "Lune");

		couleurCourante(215,72,38);
		cercle(tabPlanete[5].x, tabPlanete[5].y, tabPlanete[5].rayon);
		centre_text(tabPlanete[5].x, tabPlanete[5].y, tabPlanete[5].rayon, "Mars");

		couleurCourante(246,212,145);
		cercle(tabPlanete[6].x, tabPlanete[6].y, tabPlanete[6].rayon);
		centre_text(tabPlanete[6].x, tabPlanete[6].y, tabPlanete[6].rayon, "Jupiter");

		couleurCourante(249,223,172);
		cercle(tabPlanete[7].x, tabPlanete[7].y, tabPlanete[7].rayon);
		centre_text(tabPlanete[7].x, tabPlanete[7].y, tabPlanete[7].rayon, "Saturn");

		couleurCourante(82,191,219);
		cercle(tabPlanete[8].x, tabPlanete[8].y, tabPlanete[8].rayon);
		centre_text(tabPlanete[8].x, tabPlanete[8].y, tabPlanete[8].rayon, "Uranus");

		couleurCourante(21,133,183);
		cercle(tabPlanete[9].x, tabPlanete[9].y, tabPlanete[9].rayon);
		centre_text(tabPlanete[9].x, tabPlanete[9].y, tabPlanete[9].rayon, "Neptune");
		temps = button_pause(etat_pause, temps, vitesse_simulation);
		affiche_date(temps, temps_reel);
		break;
	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
		switch (caractereClavier())
		{
		case 'Q': /* Pour sortir quelque peu proprement du programme */
		case 'q':

			termineBoucleEvenements();
			break;

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran; // Changement de mode plein ecran
			if (pleinEcran)
			{
				modePleinEcran();
			}

			else
			{
				redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			}
			break;
		case ' ':
			switch (etat_pause)
			{
			case 0:
				etat_pause++;
				break;
			case 1:
				etat_pause = 0;
				break;
			default:
				break;
			}
			break;
		case 'S':
		case 's':
			if (vitesse_simulation > 100000 || vitesse_simulation < -100000)
			{
				vitesse_simulation = vitesse_simulation;
			}
			else if (vitesse_simulation > 3124 || vitesse_simulation < -3124)
			{
				vitesse_simulation *= 2.5;
			}
			else
			{
				vitesse_simulation *= 5;
			}

			break;
		case 'D':
		case 'd':
			if (vitesse_simulation > 3126 || vitesse_simulation < -3126)
			{
				vitesse_simulation /= 2.5;
			}
			else
			{
				vitesse_simulation /= 5;
			}

			break;
		case 'R':
		case 'r':
			vitesse_simulation *= (-1);
			break;

		case 'P':
		case 'p':
			zoom = zoom + 1;
			printf("zoom : %.0f\n",zoom);
			break;
		case 'M':
		case 'm':
			if (zoom == 1)
			{
				break;
			}
			zoom = zoom - 1;
			printf("zoom : %.0f\n",zoom);
			break;
		default:
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier())
		{
		case 13:
			tabPlanete[0] = deplacementH(tabPlanete[0]);
			
			break;

		case 14:
			tabPlanete[0] = deplacementB(tabPlanete[0]);
			break;

		case 15:
			tabPlanete[0] = deplacementG(tabPlanete[0]);
			break;

		case 16:
			tabPlanete[0] = deplacementD(tabPlanete[0]);
			break;

		default:
			break;
		}
		break;

	case BoutonSouris:
		break;

	case Souris: // Si la souris est deplacee
		break;

	case Inactivite: // Quand aucun message n'est disponible
		break;

	case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		tabPlanete[0].x = (0.5 * largeurFenetre());
		tabPlanete[0].y = (0.5 * hauteurFenetre());
		zoom = 1;
		break;
	}
}
