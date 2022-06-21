/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int x_absolute(int x_centre, int x_relatif);

/* Renvoie la coordonée x d'un point dans le réferentiel de la fenetre */
int y_absolute(int x_centre, int x_relatif);

/* Donne le facteur d'échelle des orbites*/
float echelle_orbite(double distance_reel);

/* Initialise le tableau de planètes à 0*/
void initTab(Planete tab[], int taille);

/*Remplir le tableau de planete*/
void setTab(Planete tab[], int position, char nom[], double masseP, double distance_orbitale, double rayon, int r, int v, int b, float x, float y, float vx, float vy, char type[]);

/*Remplir les echelles du tableaux*/
void echelle_tab(Planete tab[], int taille, float zoom);

/*Déplacement Haut*/
Planete deplacementH(Planete astre);

/*Déplacement Bas*/
Planete deplacementB(Planete astre);

/*Déplacement Gauche*/
Planete deplacementG(Planete astre);

/*Déplacement Droite*/
Planete deplacementD(Planete astre);

/*Focus sur les planètes*/
float focus(Planete tab[], int nbr_planete, double temps);

/*rayon reel*/
float rayon_echelle(double rayon_reel, double orbit_reel, double echelle_orbit);

/*Pour définir le nombre d'itération*/
double delta_temps(float facteur, int etat_pause);

/*Calcul des coordonnées elliptiques*/
void ellipse(Planete tab[], int taille, double delta_temps, float zoom);

/*Calcul des coordonnées par rapport à la fenêtre*/
void coordonnee_absolu(Planete tab[], int taille, float zoom);
