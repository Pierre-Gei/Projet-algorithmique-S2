/* Affiche le nom d'un objet au dessus de celui-ci */
void centre_text(int x_objet, int y_objet, int rayon_objet, char nom_objet[]);

/* premet de mettre en pause l'avencement du temps ainsi que de modifer la vitesse de la simulation*/
double button_pause(int etat, double temps, float facteur);

/* Affiche la date correspondant a la simulation actuelle*/
void affiche_date(double temps, time_t temps_reel);

/*affiche le zoom actuel*/
void affiche_zoom(float zoom);

/*Fonction de trace de cercle*/
void cercle(float centreX, float centreY, float rayon);

/*Affichage*/
void affichage(Planete tab[], int taille, float zoom);

/*Afiiche focus*/
void affichage_focus(Planete tab[],int Nbr);

/*Affiche les commandes*/
void affichage_help(void);

void menu(int etat_menu);

int bouton_new_sim(void);

int bouton_continue(void);

int bouton_load(void);

int bouton_save(void);

void bouton_quit(void);

void affiche_zone_de_texte(char name_file[], int cptchar);

int boutton_valider(char name_file[]);

int boutton_annuler(char name_file[],int* cptchar );
