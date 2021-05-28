

//Fct ajout sur hash
void ajout_tete_cellHT_airport(struct cellule_airport**, char*);

void ajout_tete_cellHT_compagnie(struct cellule_compagnie**, char*);

void ajout_vol_date(struct cellule_vol_date**, struct vol);

//Fct recherche sur hash, revoie le pointeur de la cellule contenant la table suivante
struct cellule_airport* recherche_cellHT_airport(struct cellule_airport*, char*);

struct cellule_compagnie* recherche_cellHT_compagnie(struct cellule_compagnie*, char*);


