
#include "../includes/hash_algo.h"
#include"../includes/cell_function.h"

int compare(struct vol v1, struct vol v2) { return v1.DAY - v2.DAY; }

//Fonction ajout sur les cellules de tables de hash
void ajout_tete_cellHT_airport(struct cellule_airport **pl,
                                char str[SIZE_acronym]) {
  struct cellule_airport *cell = malloc(sizeof(struct cellule_airport));
  strncpy(cell->IATA_CODE, str, SIZE_acronym);
  init_ht_comp(cell->pt_Htable_compagnie);
  cell->airport_suiv = *pl;
  *pl = cell;
}

void ajout_tete_cellHT_compagnie(struct cellule_compagnie **pl,
                                  char str[SIZE_airline_acro]) {
  struct cellule_compagnie *cell = malloc(sizeof(struct cellule_compagnie));
  strncpy(cell->IATA_CODE, str, SIZE_acronym);
  init_ht_date(cell->pt_Htable_date);
  cell->compagnie_suiv = *pl;
  *pl = cell;
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

//Fonction de recherche sur les tables de hash

struct cellule_airport *
recherche_cellHT_airport(struct cellule_airport *pl,
                                char str[SIZE_acronym]) {
  if ( pl == NULL ) {
    return pl;
  }
  if (!strncmp(pl->IATA_CODE, str, SIZE_acronym)) {
    return pl;
  }
  return recherche_cellHT_airport(pl->airport_suiv, str);
}

struct cellule_compagnie *
recherche_cellHT_compagnie(struct cellule_compagnie *pl,
                                char str[SIZE_airline_acro]) {
  if ( pl == NULL ) {
    return pl;
  }
  if (!strncmp(pl->IATA_CODE, str, SIZE_airline_acro)) {
    return pl;
  }
  return recherche_cellHT_compagnie(pl->compagnie_suiv, str);
}


