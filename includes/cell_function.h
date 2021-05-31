

//Fct ajout sur hash
void ajout_tete_cellHT_airport(struct cellule_airport**, struct airport, int);

void ajout_tete_cellHT_compagnie(struct cellule_compagnie**, char*);

//Fct ajout cell de données

void ajout_vol_date(struct cellule_vol_date**, struct vol);

void ajout_airport(struct cellule_airportDATA**, struct airport);

void ajout_compagnie(struct cellule_compagnieDATA**, char*, char*);

//Fct recherche sur hash, revoie le pointeur de la cellule contenant la table suivante
struct cellule_airport* recherche_cellHT_airport(struct cellule_airport*, char*);

struct cellule_compagnie* recherche_cellHT_compagnie(struct cellule_compagnie*, char*);

//Fct recherche sur autres tables de hash

struct cellule_airportDATA* recherche_cell_airport(struct cellule_airportDATA*, char*);

//fct print

void print_data_cellule_vol(struct cellule_vol* );

void print_normal_flight(struct cellule_vol_date*, char*);
