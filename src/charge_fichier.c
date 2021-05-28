/*
RESTE A FAIRE :
-> ajouter non pas que le iatacode de l'aeroport mais toute la structure
-> c'est tout je crois
*/
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#define max_colonne 14
#define max_strtab_lenght 100

void my_strtok(char *str, char strtab[max_colonne][max_strtab_lenght]) {
  char c = *str++;
  int pos = 0;
  int emplacement = 0;
  while (c != '\0') {
    if (c == 44) { 
      strtab[emplacement][pos] = '\0';
      emplacement++;
      pos = 0;
    } else {
      strtab[emplacement][pos] = c;
      pos++;
    }
    c = *str++;
  }
  strtab[emplacement][pos] = '\0';
}

void conversion_vol(char strtab[max_colonne][max_strtab_lenght],
                struct vol *PTvol) {
  PTvol->MONTH = (int)strtol(strtab[0], NULL, 10);
  PTvol->DAY = (int)strtol(strtab[1], NULL, 10);
  PTvol->WEEKDAY = (int)strtol(strtab[2], NULL, 10);
  strncpy(PTvol->ORG_AIR, strtab[4], SIZE_acronym);
  strncpy(PTvol->DEST_AIR, strtab[5], SIZE_acronym);
  PTvol->SCHED_DEP = (int)strtol(strtab[6], NULL, 10);
  PTvol->DEP_DELAY = -5000000.0;
  PTvol->AIR_TIME = -1.0;
  PTvol->DIST = (int)strtol(strtab[9], NULL, 10);
  PTvol->SCHED_ARR = (int)strtol(strtab[10], NULL, 10);
  PTvol->ARR_DELAY = -5000000.0;
  PTvol->CANCELLED = (int)strtol(strtab[13], NULL, 10);
  PTvol->DIVERTED = (int)strtol(strtab[12], NULL, 10);
  if (PTvol->CANCELLED == 0) {
    PTvol->DEP_DELAY = strtof(strtab[7], NULL);
  }
  if (PTvol->DIVERTED == 0 && PTvol->CANCELLED == 0) {
    PTvol->AIR_TIME = strtof(strtab[8], NULL);
    PTvol->ARR_DELAY = strtof(strtab[11], NULL);
  }
}

void conversion_airport(char strtab[max_colonne][max_strtab_lenght], struct airport *PTairport)
{
  strncpy(PTairport->AIRPORT,strtab[0],SIZE_city);
  strncpy(PTairport->CITY,strtab[1],SIZE_city);
  strncpy(PTairport->STATE,strtab[2],SIZE_state);
  strncpy(PTairport->COUNTRY,strtab[3],SIZE_acronym);
  PTairport->LATITUDE = strtof(strtab[4],NULL);
  PTairport->LONGITUDE = strtof(strtab[5],NULL);
}


void charge_dataAirport(struct cellule_airportDATA *ht_apData[max_Hdataairport])
{
  FILE *fp = fopen("../data/airports.csv", "r");
  if(fp != NULL) {
    char tmp[200];
    char strtab[max_colonne][max_strtab_lenght];
    struct airport airport;
    int index;
    fscanf(fp, "%*[^\n]\n");
    while(fscanf(fp, "%[^,],", airport.IATA_CODE) == 1)
    {
      fscanf(fp, "%[^\n]\n",tmp);
      my_strtok(tmp,strtab);
      conversion_airport(strtab,&airport);
      index = get_hash_index_airport(airport.IATA_CODE,max_Hdataairport);
      ajout_airport(&(ht_apData[index]),airport);
    }
    fclose(fp);
  }
}

void charge_dataCompagnie(struct cellule_compagnieDATA *ht_alData[max_Hdatacomp])
{
  FILE *fp = fopen("../data/airlines.csv", "r");
  if(fp != NULL) {
    char IATA_CODE[SIZE_airline_acro];
	  char AIRLINE[SIZE_airline];
    int index;
    fscanf(fp, "%*[^\n]\n");
    while(fscanf(fp, "%[^,],", IATA_CODE) == 1)
    {
      fscanf(fp, "%[^\n]\n", AIRLINE);
      index = get_hash_index_airline(IATA_CODE,max_Hdatacomp);
      ajout_compagnie(&(ht_alData[index]),IATA_CODE,AIRLINE);
    }
  }
}

void charge_vol(struct cellule_airport *ht_ap[max_Hairport]) {
  struct cellule_airportDATA *ht_apDATA[max_Hdataairport];
  init_ht_dataairport(ht_apDATA);
  charge_dataAirport(ht_apDATA);
  FILE *fp = fopen("../data/flights.csv", "r");
  if (fp != NULL) {
    struct cellule_airport *Buffairport;
    struct cellule_compagnie *Buffairline;
    struct airport dataAPtmp;
    char strtab[max_colonne][max_strtab_lenght];
    char tmp[200];
    struct vol vol;
    int index;
    // 1er fscanf = la ligne des nom de données -> poubelle
    fscanf(fp, "%s", tmp);
    // 2ème fscanf à faire avant le while
    fscanf(fp, "%s", tmp);
    while (!feof(fp)) {
      my_strtok(tmp, strtab);   // Ma fonction strtok qui permet de prendre en
                                // compte les valeurs manquantes
      conversion_vol(strtab, &vol); // Fonction de conversion char en int ou float
                                // car strtok marche avec des chars*
      char IATA_code[SIZE_airline_acro]; // On stocke l'iata code ici car on ne
                                         // le met pas dans la struct vol = gain
                                         // de place
      strncpy(IATA_code, strtab[3], SIZE_airline_acro);
      index = get_hash_index_airport(vol.ORG_AIR, max_Hairport);
      Buffairport = recherche_cellHT_airport(ht_ap[index], vol.ORG_AIR);
      if(Buffairport==NULL)
      {
        ajout_tete_cellHT_airport(&(ht_ap[index]), ht_apDATA[ get_hash_index_airport(vol.ORG_AIR, max_Hdataairport) ]->data, 1);
        Buffairport = ht_ap[index];
      }
      // Buffairport pointe vers la cellule de la table de hash des aéroport
      // Recherche_et_ajout_cell renvoie le pointeur pointant vers Buffairport
      // (voir ci-dessus), si la cellule n'existe pas (soit si c'est la 1er fois
      // qu'on rencontre cet aéroport, on l'ajoute entête et on renvoie le
      // pointeur)
      index = get_hash_index_airline(IATA_code,max_Hcomp);
      Buffairline = recherche_cellHT_compagnie(Buffairport->pt_Htable_compagnie[index],IATA_code);
      if(Buffairline == NULL)
      {
        ajout_tete_cellHT_compagnie(&(Buffairport->pt_Htable_compagnie[index]),IATA_code);
        Buffairline = Buffairport->pt_Htable_compagnie[index];
      }
      // Buffairline pointe vers la cellule de la table de hash des compagnies
      // selon l'aéroport Recherche_et_ajout_cell renvoie le pointeur pointant
      // vers Buffairline (voir ci-dessus), si la cellule n'existe pas (soit si
      // c'est la 1er fois qu'on rencontre cette compagnie dans cet aéroport de
      // départ, on l'ajoute entête et on renvoie le pointeur)
      ajout_vol_date(&(Buffairline->pt_Htable_date[vol.MONTH - 1]), vol);
      // Rangement de la cellule du vol triée par date, accède à une 3ème
      // hashtable selon le mois (on pourrait faire par jour et mois aussi mais
      // bcp trop gourmand?)
      fscanf(fp, "%s", tmp);
    }
    fclose(fp);
    //ajout des derniere airports dans la table
    for(int i=0;i<max_Hdataairport;i++)
    {
      if(ht_apDATA[i]!=NULL)
      {
        strncpy(tmp,ht_apDATA[i]->data.IATA_CODE,SIZE_acronym);
        index = get_hash_index_airport(tmp,max_Hairport);
        Buffairport = recherche_cellHT_airport(ht_ap[index] , tmp);
        if(Buffairport==NULL)
        {
          dataAPtmp = ht_apDATA[i]->data;
          ajout_tete_cellHT_airport(&(ht_ap[index]), dataAPtmp, 0);
        }
      }
    }
  }
}

//Fct de test toussa toussa
void print_flight_cell(struct cellule_vol_date* Buff_vol, char airline[SIZE_airline_acro])
{
  printf( "%d,%d,%d,%s,%s,%s,%d,%f,%f,%d,%d,%f,%hd,%hd\n",Buff_vol->vol.MONTH, 
                                                            Buff_vol->vol.DAY,
                                                            Buff_vol->vol.WEEKDAY,
                                                            airline,
                                                            Buff_vol->vol.ORG_AIR,
                                                            Buff_vol->vol.DEST_AIR,
                                                            Buff_vol->vol.SCHED_DEP,
                                                            Buff_vol->vol.DEP_DELAY,
                                                            Buff_vol->vol.AIR_TIME,
                                                            Buff_vol->vol.DIST,
                                                            Buff_vol->vol.SCHED_ARR,
                                                            Buff_vol->vol.ARR_DELAY,
                                                            Buff_vol->vol.DIVERTED,
                                                            Buff_vol->vol.CANCELLED
    );
}

void print_all_flight(struct cellule_airport *HT[max_Hairport]){
  int compt = 0;
  struct cellule_airport    *Buffairport;
  struct cellule_compagnie  *Buffairline;
  struct cellule_vol_date   *Buff_vol;
  for(int i = 0; i < max_Hairport; i++) {
    Buffairport = HT[i];
    while(Buffairport != NULL) {
      for(int j = 0; j < max_Hcomp; j++) {
        Buffairline = Buffairport->pt_Htable_compagnie[j];
        while(Buffairline != NULL) {
          for(int k = 0; k < 12; k++) {
            Buff_vol = Buffairline->pt_Htable_date[k];
            if(Buff_vol != NULL) { printf("Month %d | Begin airport : %s | Airline : %s\n",Buff_vol->vol.MONTH, Buffairport->data.IATA_CODE, Buffairline->IATA_CODE); }
            while(Buff_vol != NULL) {
              print_flight_cell(Buff_vol,Buffairline->IATA_CODE);
              Buff_vol = Buff_vol->vol_suiv;
              compt++;
            }
          }
          Buffairline = Buffairline->compagnie_suiv;
        }
      }
      Buffairport = Buffairport->airport_suiv;
    }
  }
  printf("%d lines printed\n",compt);
}

void print_specifique_flight(struct cellule_airport *HT[max_Hairport], char airport[SIZE_acronym], char airline[SIZE_airline_acro], int month)
{
  if(month < 1 || month > 12){
    printf("Month number is incorrect, please enter a correct month\n");
    return;
  }
  struct cellule_airport    *Buffairport;
  struct cellule_compagnie  *Buffairline;
  struct cellule_vol_date   *Buff_vol;
  Buffairport = recherche_cellHT_airport(HT[get_hash_index_airport(airport,max_Hairport)], airport);
  Buffairline = recherche_cellHT_compagnie(Buffairport->pt_Htable_compagnie[get_hash_index_airline(airline,max_Hcomp)], airline);
  if(Buffairline == NULL){
    printf("There is no flight with the given value\n");
    return;
  }
  Buff_vol = Buffairline->pt_Htable_date[month-1];
  printf("Month %d | Begin airport : %s | Airline : %s\n",month, airport, airline); 
  while(Buff_vol != NULL){
    print_flight_cell(Buff_vol,airline);
    Buff_vol = Buff_vol->vol_suiv;
  }
}

void print_airport(struct cellule_airport *HT[max_Hairport])
{
  struct cellule_airport *tmp;
  int compt = 0;
  for(int i=0;i<max_Hairport;i++)
  {
    if(HT[i]!=NULL)
    {
      tmp = HT[i];
      printf("[%d] :\n",i);
      while(tmp != NULL)
      {
        printf("%s,%s,%s,%s,%s,%f,%f\n",tmp->data.IATA_CODE,tmp->data.AIRPORT,tmp->data.CITY,tmp->data.STATE,tmp->data.COUNTRY,tmp->data.LATITUDE,tmp->data.LONGITUDE);
        compt++;
        tmp = tmp->airport_suiv;
      }
    }
  }
  printf("%d\n",compt);
}
/*
int main() {
  struct cellule_airport *HT[max_Hairport];
  struct cellule_compagnieDATA *HTalData[max_Hdatacomp];
  struct cellule_compagnieDATA *tmp;
  // Initialisation de la premiere table de hash (par aéroport de départ)
  init_ht_airport(HT);
  charge_vol(HT);
  print_airport(HT);
  print_specifique_flight(HT,"SHV","US",4);
  init_ht_datacomp(HTalData);
  charge_dataCompagnie(HTalData);
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
}
*/