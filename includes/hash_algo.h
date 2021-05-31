//define constante

#define MAX_LETTER 26
#define MAX_LETTERandNUMBER 36
#define A_ascii 65
#define chiffre_ascii 11

// Fonction donnant l'indice de la table de hash
int get_hash_index_airport(char const *, int);

int get_hash_index_airline(char const *, int);

//Fonctions init table de hash

void init_ht_airport(struct cellule_airport **);

void init_ht_comp(struct cellule_compagnie **);

void init_ht_date(struct cellule_vol_date **);

void init_ht_datacomp(struct cellule_compagnieDATA **, int);

void init_ht_dataairport(struct cellule_airportDATA **, int);

//Fct désalloc de table de hash

void desaloc_ht_dataairport(struct cellule_airportDATA**, int);
