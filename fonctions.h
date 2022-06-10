/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int x_absolute(int x_centre, int x_relatif);

/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int y_absolute(int x_centre, int x_relatif);

/* Renvoie la coordonée x d'un point sur un cercle de rayon 1 en fonction du temps avec 1 sec = 1 jour*/
float calculAbscisse(double secondes);

/* Renvoie la coordonée x d'un point sur un cercle de rayon 1 en fonction du temps avec 1 sec = 1 jour*/
float calculOrdonee(double secondes);

/* Affiche le nom d'un objet au dessus de celui-ci */
void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[]);

/* Donne le facteur temps d'un objet en fonction de sa période orbitale en années*/
float facteur_temps(Planete planete);

/* Donne le facteur d'échelle des orbites*/
float echelle_orbite(double distance_reel);

/* Donne le facteur d'échelle des planetes*/
float echelle_planete(double rayon_reel, float coefficient);

/* premet de mettre en pause l'avencement du temps ainsi que de modifer la vitesse de la simulation*/
double button_pause(int etat, double temps, float facteur);

/* Affiche la date correspondant a la simulation actuelle*/
void affiche_date(double temps, time_t temps_reel);
/* Initialise le tableau de planètes à 0*/
void initTab(Planete tab[], int taille);

/* Affiche le tableau de planete*/
void afficheTab(Planete tab[], int taille);

/*Remplir le tableau de planete*/
void setTab(Planete tab[], int position, char nom[], double masse, float orbit_periode);

/*Remplir les echelles du tableaux*/
void echelle_tab(Planete tab[], int position, double distance_orbitale, double rayon, float planet_coeff, float zoom);

/*Déplacement Haut*/
Planete deplacementH(Planete astre);

/*Déplacement Bas*/
Planete deplacementB(Planete astre);

/*Déplacement Gauche*/
Planete deplacementG(Planete astre);

/*Déplacement Droite*/
Planete deplacementD(Planete astre);