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
#define Taille 10

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
	static int etat_focus = 0;
	static int nbr_focus = 0;

	switch (evenement)
	{
	case Initialisation:
		modePleinEcran();
		temps_reel = time(NULL);
		temps = (double)difftime(temps_reel, 0);
		initTab(tabPlanete, 10);
		setTab(tabPlanete, 0, "Soleil", (double)1.98E+30, 0.0, (double)0, (double)696342, 255, 255, 0);
		setTab(tabPlanete, 1, "Mercure", (double)3.3E+23, 0.2408467, (double)57909227, (double)2432, 239, 213, 158);
		setTab(tabPlanete, 2, "Venus", (double)4.87E+24, 0.61519726, (double)108209475, (double)6051, 238, 140, 65);
		setTab(tabPlanete, 3, "Terre", (double)5.97E+24, 1, (double)149598262, (double)6371, 0, 0, 255);
		setTab(tabPlanete, 4, "Lune", (double)7.6E+22, 0.074853881, (double)384400, (double)1734, 125, 125, 125);
		setTab(tabPlanete, 5, "Mars", (double)6.42E+23, 1.8808476, (double)227943824, (double)3389, 215, 72, 38);
		setTab(tabPlanete, 6, "Jupiter", (double)1.898E+27, 11.862615, (double)778340821, (double)69911, 246, 212, 145);
		setTab(tabPlanete, 7, "Saturne", (double)5.68E+26, 29.447498, (double)1426666422, (double)58232, 249, 223, 172);
		setTab(tabPlanete, 8, "Uranus", (double)8.68E+25, 84.016846, (double)2870658186, (double)25362, 82, 191, 219);
		setTab(tabPlanete, 9, "Neptune", (double)1.02E+26, 164.79132, (double)4498396441, (double)24622, 21, 133, 183);

		tabPlanete[0].x = (0.5 * largeurFenetre());
		tabPlanete[0].y = (0.5 * hauteurFenetre());

		demandeTemporisation(20);

		image = lisBMPRGB("background1.bmp");
		break;
	case Temporisation:
		rafraichisFenetre();
		break;
	case Affichage:

		echelle_tab(tabPlanete, Taille, 0.008, zoom);
		calculPosition(tabPlanete, temps, Taille);

		effaceFenetre(0, 0, 0);
		if (etat_focus == 1)
		{
			focus(tabPlanete, nbr_focus, temps);
		}

		ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
	// affichage(tabPlanete, Taille);
		for (int i = 0; i < Taille; i++)
		{
			couleurCourante(tabPlanete[i].color[0], tabPlanete[i].color[1], tabPlanete[i].color[2]);
			cercle(tabPlanete[i].x, tabPlanete[i].y, tabPlanete[i].rayon);
			centre_text(tabPlanete[i].x, tabPlanete[i].y, tabPlanete[i].rayon, tabPlanete[i].nom);
		}
		temps = button_pause(etat_pause, temps, vitesse_simulation);

		affiche_date(temps, temps_reel);

		affiche_zoom(zoom);

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
			if (zoom < 10)
			{
				zoom = zoom + 1;
			}
			else
			{
				zoom = zoom + 400;
			}

			printf("zoom : %.0f\n", zoom);
			break;
		case 'M':
		case 'm':
			if (zoom == 1)
			{
				break;
			}
			else if (zoom <= 10)
			{
				zoom = zoom - 1;
			}
			else
			{
				zoom = zoom - 400;
			}

			printf("zoom : %.0f\n", zoom);
			break;
		case 'X':
		case 'x':
			switch (etat_focus)
			{
			case 0:
				etat_focus++;
				nbr_focus = 0;
				break;
			case 1:
				etat_focus = 0;
				break;
			default:
				break;
			}
		default:
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier())
		{
		case 13:
			if (etat_focus == 1)
			{
				break;
			}
			else
			{
				tabPlanete[0] = deplacementH(tabPlanete[0]);
			}
			break;

		case 14:
			if (etat_focus == 1)
			{
				break;
			}
			else
			{
				tabPlanete[0] = deplacementB(tabPlanete[0]);
			}
			break;

		case 15:
			if (etat_focus == 1)
			{
				if (nbr_focus == 0)
				{
					break;
				}
				else
				{
					nbr_focus--;
					break;
				}
			}
			else
			{
				tabPlanete[0] = deplacementG(tabPlanete[0]);
			}
			break;

		case 16:
			if (etat_focus == 1)
			{
				if (nbr_focus == 10)
				{
					break;
				}
				else
				{
					nbr_focus++;
				}
			}
			else
			{
				tabPlanete[0] = deplacementD(tabPlanete[0]);
			}
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
