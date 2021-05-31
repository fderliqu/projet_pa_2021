#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/main_function.h"


int main() {
  struct cellule_airport *HT[max_Hairport];
  struct cellule_compagnieDATA *HTalData[max_Hdatacomp];
  //struct cellule_compagnieDATA *tmp;
  // Initialisation de la premiere table de hash (par aéroport de départ)
  //print_airport(HT);
  //print_specifique_flight(HT,"ATL","EV",2);
  /*
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
  }
  int limit=3, time=0;
  char mask = timeON_limitON;
  show_airport(HT,"HA");
  show_airlines(HT,HTalData,"LAX");
  show_flights(HT,"ATL",11,18,time,limit,mask);//mask -> limit on (bit 0) / time on (bit 1)
  avg_flight_duration(HT,"LAX","SFO");
  struct cellule_vol *liste = NULL;
  find_itinerary(HT,&liste,"SFO","BUR",6,15,time,&limit,mask);
  show_most_delayed_flights(HT);
  printf("fin\n");*/       
  const char* separators = " \n";
  char*       ligne = NULL;
  size_t      n = 0;
  int         i = 0;
  struct line_arguments liste;
  liste.dernier = -1;
  init_ht_airport(HT);
  charge_vol(HT);
  init_ht_datacomp(HTalData, max_Hdatacomp);
  charge_dataCompagnie(HTalData);
  while(getline(&ligne,&n,stdin) != -1)
  {
    liste.dernier++;
    liste.arg[liste.dernier] = strtok(ligne,separators);
    while(liste.arg[liste.dernier]!=NULL)
    {
      liste.dernier++;
      liste.arg[liste.dernier] = strtok(NULL,separators);
    }
    liste.dernier--;

    printf(">");
    while(i <= liste.dernier)
    {
      printf("%s ",liste.arg[i]);
      i++;
    }
    printf("\n");
    i=0;
    launch_function(liste,HT,HTalData);
    liste.dernier = -1;
    printf("\n");
  }
}