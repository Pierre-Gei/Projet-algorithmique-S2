/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int x_absolute(int x_centre, int x_relatif);

/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int y_absolute(int x_centre, int x_relatif);

/* Renvoie la coordonée x d'un point sur un cercle de rayon 1 en fonction du temps avec 1 sec = 1 jour*/
float calculAbscisse(double secondes);

/* Renvoie la coordonée x d'un point sur un cercle de rayon 1 en fonction du temps avec 1 sec = 1 jour*/
float calculOrdonee(double secondes);

/* Donne le facteur temps d'un objet en fonction de sa période orbitale en années*/
float facteur_temps(Planete planete);

/* Donne le facteur d'échelle des orbites*/
float echelle_orbite(double distance_reel);

/* Donne le facteur d'échelle des planetes*/
float echelle_planete(double rayon_reel, float coefficient);

/* Initialise le tableau de planètes à 0*/
void initTab(Planete tab[], int taille);

/* Affiche le tableau de planete*/
void afficheTab(Planete tab[], int taille);

/*Remplir le tableau de planete*/
void setTab(Planete tab[], int position, char nom[], double masseP, float orbit_periode, double distance_orbitale, double rayon, int r, int v, int b, float x, float y, float vx, float vy);

/*Remplir les echelles du tableaux*/
void echelle_tab(Planete tab[], int taille, float planet_coeff, float zoom);

/*Déplacement Haut*/
Planete deplacementH(Planete astre);

/*Déplacement Bas*/
Planete deplacementB(Planete astre);

/*Déplacement Gauche*/
Planete deplacementG(Planete astre);

/*Déplacement Droite*/
Planete deplacementD(Planete astre);

/*Calcul des coordonnées en temps réel*/
void calculPosition(Planete tab[], double temps, int taille);

/*Focus sur les planètes*/
float focus(Planete tab[],int nbr_planete,double temps);

/*rayon reel*/
float rayon_echelle(double rayon_reel, double orbit_reel, double echelle_orbit);

double delta_temps(float facteur, int etat_pause);

void ellipse(Planete tab[],int taille, double delta_temps, float zoom);
