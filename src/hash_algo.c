#include "../includes/hash_algo.h"

int my_pow(int a, int b) {
  if (b == 0) {
    return 1;
  }
  return a * my_pow(a, b - 1);
}

int get_hash_index_airport(char const iata_code[SIZE_acronym], int intModulo) {
  return (iata_code[2] - 'A' + (iata_code[1] - 'A') * (MAX_LETTER) +
          (iata_code[0] - 'A') * my_pow(MAX_LETTER, 2)) % intModulo;
}

int get_hash_index_airline(char const iata_code[SIZE_acronym], int intModulo) {
  int code = 0;
  for (int i = 0; i < SIZE_airline_acro - 1; i++) {
    if (iata_code[i] >= 'A') {
      code += (iata_code[i] - 'A' + 10)*my_pow(MAX_LETTERandNUMBER,i);
    } 
    else {
      code += (iata_code[i] - '0')*my_pow(MAX_LETTERandNUMBER,i);
    }
  }
  return code % intModulo;
}

void init_ht_airport(struct cellule_airport *Ht_comp[max_Hairport]) {
  for (int i = 0; i < max_Hairport; i++) {
    Ht_comp[i] = NULL;
  }
}

void init_ht_comp(struct cellule_compagnie *Ht_comp[max_Hcomp]) {
  for (int i = 0; i < max_Hcomp; i++) {
    Ht_comp[i] = NULL;
  }
}

void init_ht_date(struct cellule_vol_date *Ht_comp[max_Hdate]) {
  for (int i = 0; i < max_Hdate; i++) {
    Ht_comp[i] = NULL;
  }
}

void init_ht_datacomp(struct cellule_compagnieDATA *Ht_comp[], int size) {
  for (int i = 0; i < size; i++) {
    Ht_comp[i] = NULL;
  }
}

void init_ht_dataairport(struct cellule_airportDATA *Ht_comp[], int size) {
  for (int i = 0; i < size; i++) {
    Ht_comp[i] = NULL;
  }
}

void desaloc_ht_dataairport(struct cellule_airportDATA *HT[], int sizeHT)
{
    struct cellule_airportDATA *tmp;
    for(int i=0;i<sizeHT;i++)
    {
        while(HT[i]!=NULL)
        {
            tmp = HT[i];
            HT[i] = tmp->suiv;
            free(tmp);
        }
    }
}
