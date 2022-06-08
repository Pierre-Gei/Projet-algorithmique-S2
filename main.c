#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h" // Pour utiliser valeurAleatoire()
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
    static double temps = 0;
	static time_t temps_reel = 0;
    static int rayon_orbite_mercure=100;
    static int rayon_orbite_venus=200;
    static int rayon_orbite_terre=300;
    static int rayon_orbite_lune=75;
    static int rayon_orbite_mars=400;
    static int rayon_orbite_jupiter=500;
    static int rayon_orbite_saturn=600;
    static int rayon_orbite_uranus=700;
    static int rayon_orbite_neptune=800;
    
    static int rayon_soleil=75;
    static int rayon_mercure=15;
    static int rayon_venus=15;
    static int rayon_terre=20;
    static int rayon_lune=10;
    static int rayon_mars=15;
    static int rayon_jupiter=15;
    static int rayon_saturn=15;
    static int rayon_uranus=15;
    static int rayon_neptune=15;
    
	static int x_soleil=0;
	static int y_soleil=0;
	static int x_mercure=0;
	static int y_mercure=0;
	static int x_venus=0;
	static int y_venus=0;
	static int x_terre=0;
	static int y_terre=0;
	static int x_lune=0;
	static int y_lune=0;
	static int x_mars=0;
	static int y_mars=0;
	static int x_jupiter=0;
	static int y_jupiter=0;
	static int x_saturn=0;
	static int y_saturn=0;
	static int x_uranus=0;
	static int y_uranus=0;
	static int x_neptune=0;
	static int y_neptune=0;
	
	switch (evenement)
	{
		case Initialisation:
			temps_reel = time(NULL);
			temps = (double) difftime( temps_reel, 0 );
			demandeTemporisation(20);
			break;
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			x_soleil=(0.5*largeurFenetre());
			y_soleil=(0.5*hauteurFenetre());
			
			x_mercure=(x_absolute(x_soleil,(rayon_orbite_mercure*calculAbscisse(temps))));
			y_mercure=(y_absolute(y_soleil,(rayon_orbite_mercure*calculOrdonee(temps))));
			
			x_venus=(x_absolute(x_soleil,(rayon_orbite_venus*calculAbscisse(temps))));
			y_venus=(y_absolute(y_soleil,(rayon_orbite_venus*calculOrdonee(temps))));
			
			x_terre=(x_absolute(x_soleil,(rayon_orbite_terre*calculAbscisse(temps))));
			y_terre=(y_absolute(y_soleil,(rayon_orbite_terre*calculOrdonee(temps))));
			
			x_lune=(x_absolute(x_terre,(rayon_orbite_lune*calculAbscisse(temps*13.3593607))));
			y_lune=(y_absolute(y_terre,(rayon_orbite_lune*calculOrdonee(temps*13.3593607))));
			
			x_mars=(x_absolute(x_soleil,(rayon_orbite_mars*calculAbscisse(temps))));
			y_mars=(y_absolute(y_soleil,(rayon_orbite_mars*calculOrdonee(temps))));
			
			x_jupiter=(x_absolute(x_soleil,(rayon_orbite_jupiter*calculAbscisse(temps))));
			y_jupiter=(y_absolute(y_soleil,(rayon_orbite_jupiter*calculOrdonee(temps))));
			
			x_saturn=(x_absolute(x_soleil,(rayon_orbite_saturn*calculAbscisse(temps))));
			y_saturn=(y_absolute(y_soleil,(rayon_orbite_saturn*calculOrdonee(temps))));
			
			x_uranus=(x_absolute(x_soleil,(rayon_orbite_uranus*calculAbscisse(temps))));
			y_uranus=(y_absolute(y_soleil,(rayon_orbite_uranus*calculOrdonee(temps))));
			
			x_neptune=(x_absolute(x_soleil,(rayon_orbite_neptune*calculAbscisse(temps))));
			y_neptune=(y_absolute(y_soleil,(rayon_orbite_neptune*calculOrdonee(temps))));
			
			
			
			effaceFenetre (0, 0, 0);
			
				couleurCourante(255, 255, 0);
				cercle(x_soleil,y_soleil,(rayon_soleil));
				centre_text(x_soleil,y_soleil,rayon_soleil,"Soleil");
			
				couleurCourante(125, 125, 125);
           		cercle(x_mercure,y_mercure,rayon_mercure);
           		centre_text(x_mercure,y_mercure,rayon_mercure,"Mercure");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_venus,y_venus,rayon_venus);
           		centre_text(x_venus,y_venus,rayon_venus,"Venus");
           		
            	couleurCourante(0, 0, 255);
            	cercle(x_terre,y_terre,rayon_terre);
            	centre_text(x_terre,y_terre,rayon_terre,"Terre");

           		cercle(x_lune,y_lune,rayon_lune);
           		centre_text(x_lune,y_lune,rayon_lune,"Lune");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_mars,y_mars,rayon_mars);
           		centre_text(x_mars,y_mars,rayon_mars,"Mars");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_jupiter,y_jupiter,rayon_jupiter);
           		centre_text(x_jupiter,y_jupiter,rayon_jupiter,"Jupiter");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_saturn,y_saturn,rayon_saturn);
           		centre_text(x_saturn,y_saturn,rayon_saturn,"Saturn");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_uranus,y_uranus,rayon_uranus);
           		centre_text(x_uranus,y_uranus,rayon_uranus,"Uranus");
           		
           		couleurCourante(125, 125, 125);
           		cercle(x_neptune,y_neptune,rayon_neptune);
           		centre_text(x_neptune,y_neptune,rayon_neptune,"Neptune");
            
				temps=temps+0.04;
			
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
