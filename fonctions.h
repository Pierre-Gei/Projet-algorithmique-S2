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
float facteur_temps(float periode);

/* Donne le facteur d'échelle des orbites*/
float echelle_orbite(double distance_reel);

/* Donne le facteur d'échelle des planetes*/
float echelle_planete(double rayon_reel, int valeur_fixe, float coefficient);

/* premet de mettre en pause l'avencement du temps ainsi que de modifer la vitesse de la simulation*/
double button_pause(int etat, double temps, float facteur);