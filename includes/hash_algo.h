//Variables
#include"init.h"
#define MAX_LETTER 26
#define A_ascii 65
#define chiffre_ascii 11

//Fonction donnant l'indice de la table de hash
int get_hash_index_airport(char *);

int get_hash_index_airline(char *);

void init_ht_airport(struct cellule_airport**);

void init_ht_comp(struct cellule_compagnie**);

void init_ht_date(struct cellule_vol_date**);

void init_ht_namecomp(struct cellule_IATA_AIRLINE**);