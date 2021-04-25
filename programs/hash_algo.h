//Variables
#define MAX_LETTER 26
#define A_ascii 65
#define SIZE_hash_airport 17575

//Table de hash
struct cellule_vol Htable[SIZE_hash_airport];

//Fonction donnant l'indice de la table de hash
int get_hash_index_airport(char *);