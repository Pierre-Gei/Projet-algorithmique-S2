/*Sauvegarder le nom de chaque fichier de sauvegarde*/
void save_nom(char nom[]);

/*Sauvegarde les données de la planètes*/
void save(Planete tab[], int taille, char nom[], double* temps_simulation);

/*Charger les données d'une partie enregistrée*/
void chargement(char nom[], Planete tab[], int taille, double* temps_simulation);