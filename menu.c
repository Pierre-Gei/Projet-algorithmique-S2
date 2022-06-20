#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "structure.h"
#include "calcul.h"
#include "affichage.h"
#include "save.h"
#include "menu.h"
#include <time.h>
#include <string.h>
#define LargeurFenetre 800
#define HauteurFenetre 600
#define Taille 12
#define TLune 10


int main(int argc, char **argv)
{
	srand(time(NULL));

	initialiseGfx(argc, argv);

	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);

	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = true;
	static double temps = 0;
	static DonneesImageRGB *image = NULL;
	static time_t temps_reel = 0;
	static Planete tabPlanete[Taille];
	static Planete tabLune[TLune];
	static int etat_pause = 0;
	static float vitesse_simulation = 1;
	static float zoom = 1;
	static int etat_focus = 0;
	static int nbr_focus = 0;
	static int etat_help = 0;
	static int etat_menu = 1;
	static int new_sim = 0;
	static int load_sim = 0;
	static int save_sim = 0;
	static int continuer = 0;
	static char name_file[20];
	static int cptchar = 0;
	static int *ptcptchar = &cptchar;
	static char nombre_objets[40];

	switch (evenement)
	{
	case Initialisation:
		epaisseurDeTrait(2);
		modePleinEcran();
		initTab(tabPlanete, 10);
		memset(name_file,'\0',20);
		image = lisBMPRGB("background1.bmp");
		sprintf(nombre_objets, "Nombre d'objets = %d", Taille);
		demandeTemporisation(20);
		break;
	case Temporisation:
		if(new_sim == 1){
			new_sim = 0;
			etat_menu = 0;
			temps_reel = time(NULL);
			temps = (double)difftime(temps_reel, 0);
			setTab(tabPlanete, 0, "Soleil", (double)1.98E+30, 0.0, (double)0, (double)696342, 255, 255, 0, 0, 0, 0, 0,"Etoile");
			setTab(tabPlanete, 1, "Mercure", (double)3.3E+23, 0.2408467, (double)57909227, (double)2432, 239, 213, 158, 3.594726526628610E+10, -5.308320772035544E+10, 3.061786711527284E+04,  2.969487961696706E+04,"Planète");
			setTab(tabPlanete, 2, "Venus", (double)4.87E+24, 0.61519726, (double)108209475, (double)6051, 238, 140, 65, 1.083351303124208E+11, -6.601895150749428E+09, 1.973551007040168E+03 , 3.479748046438341E+04,"Planète");
			setTab(tabPlanete, 3, "Terre", (double)5.97E+24, 1, (double)149598262, (double)6371, 0, 0, 255, -2.195413736531780E+10, -1.503189593792233E+11, 2.897969704638881E+04, -4.412399716983023E+03,"Planète");
			setTab(tabPlanete, 4, "Lune", (double)7.6E+22, 0.074853881, (double)384400, (double)1734, 125, 125, 125, 9.863920165646482E+07, -3.435845378738694E+08, 1.058023048630052E+03, 2.850613680524981E+02,"Satellite");
			setTab(tabPlanete, 5, "Mars", (double)6.42E+23, 1.8808476, (double)227943824, (double)3389, 215, 72, 38, 1.803420120063720E+11, -1.008312072682970E+11, 1.274510435272690E+04, 2.322329691202391E+04,"Planète");
			setTab(tabPlanete, 6, "Jupiter", (double)1.898E+27, 11.862615, (double)778340821, (double)69911, 246, 212, 145, 7.381350767436030E+11, -8.133858440677193E+10, 1.279258512194355E+03, 1.361634441215909E+04,"Planète");
			setTab(tabPlanete, 7, "Saturne", (double)5.68E+26, 29.447498, (double)1426666422, (double)58232, 249, 223, 172, 1.126286149331401E+12, -9.576415881787971E+11, 5.722017760403925E+03, 7.353978837153003E+03,"Planète");
			setTab(tabPlanete, 8, "Uranus", (double)8.68E+25, 84.016846, (double)2870658186, (double)25362, 82, 191, 219, 2.085282775726888E+12, 2.082241602893633E+12,  -4.860899446758633E+03, 4.515412676455412E+03,"Planète");
			setTab(tabPlanete, 9, "Neptune", (double)1.02E+26, 164.79132, (double)4498396441, (double)24622, 21, 133, 183, 4.442437942853459E+12, -5.353686097326288E+11, 6.174016588041462E+02, 5.444565377510131E+03,"Planète");
			setTab(tabPlanete, 10, "PSP", (double)685 , 0, (double)6.150099824120720E+10, (double)0.001, 125, 125, 125, 2.480492082498334E+10, -5.623332788775445E+10, 3.828529362470469E+04, -2.618792274253275E+04,"Sonde");
			setTab(tabPlanete, 11, "voyager 2", (double)722 , 0, (double) 1.951421713161150E+13, (double)0.001, 125, 125, 125, 5.395883881531995E+12, -1.450898056059902E+13, 4.228713829442690E+03, -9.351932312118578E+03,"Sonde");


			tabPlanete[0].x = (0.5 * largeurFenetre());
			tabPlanete[0].y = (0.5 * hauteurFenetre());

			vitesse_simulation = 1;

		}

		if (continuer == 1 && tabPlanete[0].masse != 0){
			continuer = 0;
			etat_menu = 0;
		}
		
		rafraichisFenetre();
		break;
	case Affichage:
		if(load_sim == 1 || save_sim == 1){
			affiche_zone_de_texte(name_file, cptchar);
		}
		else{
			menu(etat_menu);
		}


		if(etat_menu == 0){
			echelle_tab(tabPlanete, Taille, 0.008, zoom);
			ellipse(tabPlanete,Taille,delta_temps(vitesse_simulation, etat_pause), zoom);
			coordonnee_absolu(tabPlanete, Taille, zoom);
			effaceFenetre(0, 0, 0);
			ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
			couleurCourante(255,255,255);
			afficheChaine(nombre_objets,18,20,20);

			affichage(tabPlanete, Taille, zoom);

			if (etat_focus == 1)
			{
				zoom=focus(tabPlanete, nbr_focus, temps);
				affichage_focus(tabPlanete,nbr_focus);
			}

			if (etat_help == 1)
			{
				affichage_help();
			}

			epaisseurDeTrait(2);

			temps = button_pause(etat_pause, temps, vitesse_simulation);

			affiche_date(temps, temps_reel);

			affiche_zoom(zoom);
		}

		break;
case Clavier:
		if(save_sim == 1){
			if(*ptcptchar<20){
				name_file[cptchar]=caractereClavier();
				cptchar++;
			}
		}
		else if(load_sim == 1){
			if(*ptcptchar<20){
				name_file[cptchar]=caractereClavier();
				cptchar++;
				
			}
		}
		else{
			switch (caractereClavier())
			{
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
			}
			if(etat_menu == 0){
				switch (caractereClavier())
				{
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
					zoom = zoom * 1.25;

					printf("zoom : %.2f\n", zoom);
					break;
				case 'M':
				case 'm':
					if (zoom <= 0.5)
					{
						zoom = 0.50;
					}
					else
					{
						zoom = zoom / 1.25;
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
					break;
				case 'H':
				case 'h':
					switch (etat_help)
					{
					case 0:
						etat_help++;
						break;
					case 1:
						etat_help = 0;
						break;
					default:
						break;
					}
					break;
				case '	':
					etat_menu = 1;
					break;
				default:
					break;
				}
			}
			break;

		}
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
					else if(nbr_focus == 5)
					{
						nbr_focus=nbr_focus-2;
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
					if (nbr_focus == (Taille-1))
					{
						break;
					}
					else if(nbr_focus == 3)
					{
						nbr_focus=nbr_focus+2;
					}
					else{
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
		if(etatBoutonSouris() == GaucheAppuye){
			if(etat_menu == 1){
				if(load_sim == 1){
					load_sim = boutton_valider(name_file);
					if(load_sim == 0){
						chargement(name_file,tabPlanete,Taille,&temps,&temps_reel);
						*ptcptchar = 0;
						memset(name_file, '\0', 20);
					}
					else{
						load_sim = boutton_annuler(name_file, ptcptchar);
					}
				}
				else if(save_sim == 1){
					save_sim = boutton_valider(name_file);
					if(save_sim == 0){
						save(tabPlanete,Taille,name_file,&temps,&temps_reel);
						*ptcptchar = 0;
						memset(name_file, '\0', 20);
					}
					else{
						save_sim = boutton_annuler(name_file, ptcptchar);
					}
					
				}
				else{
					new_sim = bouton_new_sim();
					continuer = bouton_continue();
					load_sim = bouton_load();
					save_sim = bouton_save();
					bouton_quit();
				}
			}
		}
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
