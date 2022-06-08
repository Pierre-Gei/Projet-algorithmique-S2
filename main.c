#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "fonctions.h"
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
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;
    static float temps = 0;
    static int rayon_orbite_terre=300;
    static int rayon_orbite_lune=75;
    static int rayon_terre=20;
    static int rayon_lune=10;
    static int rayon_soleil=75;
	static int x_soleil=0;
	static int y_soleil=0;
	static int x_terre=0;
	static int y_terre=0;
	static int x_lune=0;
	static int y_lune=0;
	
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(20);
			break;
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			x_soleil=(0.5*largeurFenetre());
			y_soleil=(0.5*hauteurFenetre());
			x_terre=(x_absolute(x_soleil,(rayon_orbite_terre*calculAbscisse(temps))));
			y_terre=(y_absolute(y_soleil,(rayon_orbite_terre*calculOrdonee(temps))));
			x_lune=(x_absolute(x_terre,(rayon_orbite_lune*calculAbscisse(temps*13.3593607))));
			y_lune=(y_absolute(y_terre,(rayon_orbite_lune*calculOrdonee(temps*13.3593607))));
			
			effaceFenetre (0, 0, 0);
			couleurCourante(255, 255, 0);
			cercle(x_soleil,y_soleil,(rayon_soleil));
			centre_text(x_soleil,y_soleil,rayon_soleil,"soleil");
            couleurCourante(0, 0, 255);
            cercle(x_terre,y_terre,rayon_terre);
            centre_text(x_terre,y_terre,rayon_terre,"terre");
			couleurCourante(125, 125, 125);
            cercle(x_lune,y_lune,rayon_lune);
            centre_text(x_lune,y_lune,rayon_lune,"lune");
			temps+= 1;
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
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			break;
	}
}
