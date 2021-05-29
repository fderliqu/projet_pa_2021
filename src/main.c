#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/show-airport.h"

int main() {
  struct cellule_airport *HT[max_Hairport];
  struct cellule_compagnieDATA *HTalData[max_Hdatacomp];
  struct cellule_compagnieDATA *tmp;
  // Initialisation de la premiere table de hash (par aéroport de départ)
  init_ht_airport(HT);
  charge_vol(HT);
  //print_airport(HT);
  print_specifique_flight(HT,"LAX","HA",1);
  init_ht_datacomp(HTalData, max_Hdatacomp);
  charge_dataCompagnie(HTalData);/*
  for(int i=0;i<max_Hdatacomp;i++)
  {
    if(HTalData[i]!=NULL)
    {
      tmp = HTalData[i];
      printf("[%d] :\n",i);
      while(tmp != NULL)
      {
        printf("%s,%s\n",tmp->IATA_CODE,tmp->AIRLINE);
        tmp = tmp->compagnie_suiv;
      }
    }
  }*/
  show_airport(HT,"HA");
}