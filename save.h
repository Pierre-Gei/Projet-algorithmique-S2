/*Sauvegarde les données de la planètes*/
void save(Planete tab[], int taille, char nom[], double* temps_simulation,time_t* temps_reel);

/*Charger les données d'une partie enregistrée*/
void chargement(char nom[], Planete tab[], int taille, double* temps_simulation, time_t* temps_reel);