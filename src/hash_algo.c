#include"../includes/init.h"
#include"../includes/hash_algo.h"

int my_pow(int a,int b)
{
    if(b==0)return 1;
    return a * my_pow(a,b-1);
}

int get_hash_index_airport(char iata_code[SIZE_acronym])
{
    return 
    (iata_code[2]-A_ascii + 
    (iata_code[1]-A_ascii)*(MAX_LETTER) + 
    (iata_code[0]-A_ascii)*my_pow(MAX_LETTER,2))%max_Hairport;
}

void init_ht_airport(struct cellule_airport* Ht_comp[max_Hairport])
{
    for(int i=0; i<max_Hairport; i++)Ht_comp[i] = NULL;
}

void init_ht_comp(struct cellule_compagnie* Ht_comp[max_Hcomp])
{
    for(int i=0; i<max_Hcomp; i++)Ht_comp[i] = NULL;
}

void init_ht_date(struct cellule_airport* Ht_comp[max_Hdate])
{
    for(int i=0; i<max_Hdate; i++)Ht_comp[i] = NULL;
}

void init_ht_namecomp(struct cellule_airport* Ht_comp[max_Hnamecomp])
{
    for(int i=0; i<max_Hnamecomp; i++)Ht_comp[i] = NULL;
}