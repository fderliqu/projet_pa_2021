#include "../includes/init.h"
#include "../includes/cell_function.h"
#include "../includes/hash_algo.h"

int compare (struct vol v1, struct vol v2) { return v1.DAY - v2.DAY; }

// Fonction ajout sur les cellules de tables de hash
void ajout_tete_cellHT_airport (struct cellule_airport **pl, struct airport data, int choix)
{
    struct cellule_airport *cell = malloc (sizeof (struct cellule_airport));
    cell->data                   = data;
    cell->is_empty               = choix;
    if (choix <= 0)
    {
        init_ht_comp (cell->pt_Htable_compagnie);
    }
    cell->airport_suiv = *pl;
    *pl                = cell;
}

void ajout_tete_cellHT_compagnie (struct cellule_compagnie **pl, char str[SIZE_airline_acro])
{
    struct cellule_compagnie *cell = malloc (sizeof (struct cellule_compagnie));
    strcpy (cell->IATA_CODE, str);
    init_ht_date (cell->pt_Htable_date);
    cell->compagnie_suiv = *pl;
    *pl                  = cell;
}

// Fct ajout cellules de données

void ajout_vol_date (struct cellule_vol_date **pl, struct vol vol)
{
    if ((*pl == NULL) || (compare (vol, (*pl)->vol) < 0))
    {
        struct cellule_vol_date *new;
        new           = malloc (sizeof (struct cellule_vol_date));
        new->vol      = vol;
        new->vol_suiv = *pl;
        *pl           = new;
        return;
    }
    ajout_vol_date (&((*pl)->vol_suiv), vol);
}

void ajout_airport (struct cellule_airportDATA **pl, struct airport airport)
{
    struct cellule_airportDATA *new;
    new       = malloc (sizeof (struct cellule_airportDATA));
    new->data = airport;
    new->suiv = *pl;
    *pl       = new;
    return;
}

void ajout_compagnie (struct cellule_compagnieDATA **pl, char IATA_CODE[SIZE_airline_acro], char AIRLINE[SIZE_airline])
{
    struct cellule_compagnieDATA *new;
    new = malloc (sizeof (struct cellule_compagnieDATA));
    strcpy (new->IATA_CODE, IATA_CODE);
    strcpy (new->AIRLINE, AIRLINE);
    new->compagnie_suiv = *pl;
    *pl                 = new;
    return;
}


// Fonction de recherche sur les tables de hash

struct cellule_airport *recherche_cellHT_airport (struct cellule_airport *pl, char str[SIZE_acronym])
{
    if (pl == NULL)
    {
        return pl;
    }
    if (!strncmp (pl->data.IATA_CODE, str, SIZE_acronym))
    {
        return pl;
    }
    return recherche_cellHT_airport (pl->airport_suiv, str);
}

struct cellule_compagnie *recherche_cellHT_compagnie (struct cellule_compagnie *pl, char str[SIZE_airline_acro])
{
    if (pl == NULL)
    {
        return pl;
    }
    if (!strncmp (pl->IATA_CODE, str, SIZE_airline_acro))
    {
        return pl;
    }
    return recherche_cellHT_compagnie (pl->compagnie_suiv, str);
}

struct cellule_airportDATA *recherche_cell_airport (struct cellule_airportDATA *pl, char str[SIZE_acronym])
{
    if (pl == NULL)
    {
        return pl;
    }
    if (!strncmp (pl->data.IATA_CODE, str, SIZE_acronym))
    {
        return pl;
    }
    return recherche_cell_airport (pl->suiv, str);
}

// fct print


void print_data_cellule_vol (struct cellule_vol *Buff_vol)
{
    printf ("%d,%d,%d,%s,%s,%s,%d,%.2f,%.2f,%d,%d,%.2f,%hd,%hd\n", Buff_vol->data.MONTH,
            Buff_vol->data.DAY, Buff_vol->data.WEEKDAY, Buff_vol->airline, Buff_vol->data.ORG_AIR,
            Buff_vol->data.DEST_AIR, Buff_vol->data.SCHED_DEP, Buff_vol->data.DEP_DELAY,
            Buff_vol->data.AIR_TIME, Buff_vol->data.DIST, Buff_vol->data.SCHED_ARR,
            Buff_vol->data.ARR_DELAY, Buff_vol->data.DIVERTED, Buff_vol->data.CANCELLED);
}

void print_normal_flight (struct cellule_vol_date *cell, char airline[SIZE_airline_acro])
{
    if (cell->vol.DIVERTED)
    {
        printf ("%d,%d,%d,%s,%s,%s,%d,%.2f,N/A,%d,%d,N/A,%hd,%hd\n", cell->vol.MONTH, cell->vol.DAY,
                cell->vol.WEEKDAY, airline, cell->vol.ORG_AIR, cell->vol.DEST_AIR,
                cell->vol.SCHED_DEP, cell->vol.DEP_DELAY, cell->vol.DIST, cell->vol.SCHED_ARR,
                cell->vol.DIVERTED, cell->vol.CANCELLED);
        return;
    }
    if (cell->vol.CANCELLED)
    {
        printf ("%d,%d,%d,%s,%s,%s,%d,N/A,N/A,%d,%d,N/A,%hd,%hd\n", cell->vol.MONTH, cell->vol.DAY,
                cell->vol.WEEKDAY, airline, cell->vol.ORG_AIR, cell->vol.DEST_AIR, cell->vol.SCHED_DEP,
                cell->vol.DIST, cell->vol.SCHED_ARR, cell->vol.DIVERTED, cell->vol.CANCELLED);
        return;
    }
    printf ("%d,%d,%d,%s,%s,%s,%d,%.2f,%.2f,%d,%d,%.2f,%hd,%hd\n", cell->vol.MONTH, cell->vol.DAY,
            cell->vol.WEEKDAY, airline, cell->vol.ORG_AIR, cell->vol.DEST_AIR, cell->vol.SCHED_DEP,
            cell->vol.DEP_DELAY, cell->vol.AIR_TIME, cell->vol.DIST, cell->vol.SCHED_ARR,
            cell->vol.ARR_DELAY, cell->vol.DIVERTED, cell->vol.CANCELLED);
    return;
}
