/*
RESTE A FAIRE :
-> ajouter non pas que le iatacode de l'aeroport mais toute la structure
-> c'est tout je crois
*/
#include "../includes/hash_algo.h"
#define max_colonne 14
#define max_strtab_lenght 10

int compare(struct vol v1, struct vol v2) { return v1.DAY - v2.DAY; }

void ajout_tete_cellule_airport(struct cellule_airport **pl,
                                char str[SIZE_acronym]) {
  struct cellule_airport *cell = malloc(sizeof(struct cellule_airport));
  strncpy(cell->airport.IATA_CODE, str, SIZE_acronym);
  init_ht_comp(cell->pt_Htable_compagnie);
  cell->airport_suiv = *pl;
  *pl = cell;
}

void ajout_tete_cellule_compagnie(struct cellule_compagnie **pl,
                                  char str[SIZE_airline_acro]) {
  struct cellule_compagnie *cell = malloc(sizeof(struct cellule_compagnie));
  strncpy(cell->IATA_CODE, str, SIZE_acronym);
  init_ht_date(cell->pt_Htable_date);
  cell->compagnie_suiv = *pl;
  *pl = cell;
}

struct cellule_airport *
recherche_et_ajout_cell_airport(struct cellule_airport **pl,
                                char str[SIZE_acronym]) {
  if ((*pl == NULL) || (strcmp(str, (*pl)->airport.IATA_CODE) < 0)) {
    ajout_tete_cellule_airport(pl, str);
    return *pl;
  }
  if (!strncmp((*pl)->airport.IATA_CODE, str, SIZE_acronym)) {
    return *pl;
  }
  return recherche_et_ajout_cell_airport(&((*pl)->airport_suiv), str);
}

struct cellule_compagnie *
recherche_et_ajout_cell_airline(struct cellule_compagnie **pl,
                                char str[SIZE_airline_acro]) {
  if ((*pl == NULL) || (strcmp(str, (*pl)->IATA_CODE) < 0)) {
    ajout_tete_cellule_compagnie(pl, str);
    return *pl;
  }
  if (!strncmp((*pl)->IATA_CODE, str, SIZE_airline_acro)) {
    return *pl;
  }
  return recherche_et_ajout_cell_airline(&((*pl)->compagnie_suiv), str);
}

void ajout_vol_date(struct cellule_vol_date **pl, struct vol vol) {
  if ((*pl == NULL) || (compare(vol, (*pl)->vol) < 0)) {
    struct cellule_vol_date *new;
    new = malloc(sizeof(struct cellule_vol_date));
    new->vol = vol;
    new->vol_suiv = *pl;
    *pl = new;
    return;
  }
  ajout_vol_date(&((*pl)->vol_suiv), vol);
}

void my_strtok(char *str, char strtab[max_colonne][max_strtab_lenght]) {
  char c = *str++;
  int pos = 0;
  int emplacement = 0;
  while (c != '\0') {
    if (c == ',') {
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

void conversion(char strtab[max_colonne][max_strtab_lenght],
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

// test

int get_hash_index(char iata_code[SIZE_acronym]) {
  return iata_code[2] - 'A' + (iata_code[1] - 'A') * (MAX_LETTER) +
         (iata_code[0] - 'A') * (MAX_LETTER * MAX_LETTER);
}

// fin test

void charge_vol(struct cellule_airport *ht_ap[max_Hairport]) {
  FILE *fp = fopen("../data/flights.csv", "r");
  if (fp != NULL) {
    struct cellule_airport *Buffairport;
    struct cellule_compagnie *Buffairline;
    char strtab[max_colonne][max_strtab_lenght];
    char tmp[200];
    struct vol vol;
    // 1er fscanf = la ligne des nom de données -> poubelle
    fscanf(fp, "%s", tmp);
    // 2ème fscanf à faire avant le while
    fscanf(fp, "%s", tmp);
    while (!feof(fp)) {
      my_strtok(tmp, strtab);   // Ma fonction strtok qui permet de prendre en
                                // compte les valeurs manquantes
      conversion(strtab, &vol); // Fonction de conversion char en int ou float
                                // car strtok marche avec des chars*
      char IATA_code[SIZE_airline_acro]; // On stocke l'iata code ici car on ne
                                         // le met pas dans la struct vol = gain
                                         // de place
      strncpy(IATA_code, strtab[3], SIZE_airline_acro);
      Buffairport = recherche_et_ajout_cell_airport(
          &(ht_ap[get_hash_index_airport(vol.ORG_AIR)]), vol.ORG_AIR);
      // Buffairport pointe vers la cellule de la table de hash des aéroport
      // Recherche_et_ajout_cell renvoie le pointeur pointant vers Buffairport
      // (voir ci-dessus), si la cellule n'existe pas (soit si c'est la 1er fois
      // qu'on rencontre cet aéroport, on l'ajoute entête et on renvoie le
      // pointeur)
      Buffairline = recherche_et_ajout_cell_airline(
          &(Buffairport
                ->pt_Htable_compagnie[get_hash_index_airline(IATA_code)]),
          IATA_code);
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
    printf("fin\n");
  }
}

struct cellule_airport *
recherche_cell_airport(struct cellule_airport *pl,
                                char str[SIZE_acronym]) {
  if ( pl == NULL ) {
    return pl;
  }
  if (!strncmp(pl->airport.IATA_CODE, str, SIZE_acronym)) {
    return pl;
  }
  return recherche_cell_airport(pl->airport_suiv, str);
}

struct cellule_compagnie *
recherche_cell_airline(struct cellule_compagnie *pl,
                                char str[SIZE_airline_acro]) {
  if ( pl == NULL ) {
    return pl;
  }
  if (!strncmp(pl->IATA_CODE, str, SIZE_airline_acro)) {
    return pl;
  }
  return recherche_cell_airline(pl->compagnie_suiv, str);
}

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
            if(Buff_vol != NULL) { printf("Month %d | Begin airport : %s | Airline : %s\n",Buff_vol->vol.MONTH, Buffairport->airport.IATA_CODE, Buffairline->IATA_CODE); }
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
  Buffairport = recherche_cell_airport(HT[get_hash_index_airport(airport)], airport);
  if(Buffairport == NULL){
    printf("There are no flight with the given value of begin airport\n");
    return;
  }
  Buffairline = recherche_cell_airline(Buffairport->pt_Htable_compagnie[get_hash_index_airline(airline)], airline);
  if(Buffairline == NULL){
    printf("There is no flight with the given value of airline on this begin airport\n");
    return;
  }
  Buff_vol = Buffairline->pt_Htable_date[month-1];
  printf("Month %d | Begin airport : %s | Airline : %s\n",month, airport, airline); 
  while(Buff_vol != NULL){
    print_flight_cell(Buff_vol,airline);
    Buff_vol = Buff_vol->vol_suiv;
  }
}

// le main chargement des flights
int main() {
  struct cellule_airport *HT[max_Hairport];
  // Initialisation de la premiere table de hash (par aéroport de départ)
  init_ht_airport(HT);
  charge_vol(HT);
  //print_all_flight(HT);
  print_specifique_flight(HT,"MSP","US",4);
}
