#include"../includes/init.h"
#include"../includes/hash_algo.h"

struct cellule_airport* recherche_et_ajout_cell_airport(struct cellule_airport** pl,char str[SIZE_acronym])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->airport) <= 0) )
    {
        ajout_tete_cellule_airport(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->airport,str,SIZE_acronym ) )
    {
        return *pl;
    }
    else recherche_et_ajout_cell_airport( (*pl)->airport_suiv,str);
}

struct cellule_compagnie* recherche_et_ajout_cell_airline(struct cellule_compagnie** pl,char str[SIZE_acronym])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->IATA_CODE) <= 0) )
    {
        ajout_tete_cellule_airline(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->IATA_CODE,str,SIZE_acronym ) )
    {
        return *pl;
    }
    else recherche_et_ajout_cell_airport( (*pl)->compagnie_suiv,str);
}

void ajout_tete_cellule_airport(struct cellule_airport** pl, char str[SIZE_acronym])
{
    struct cellule_airport* cell = malloc(sizeof(struct celulle_airport));
    strcpy(cell->airport,str);
    init_ht_comp(cell->pt_Htable_compagnie);
    cell->airport_suiv = *pl;
    *pl = cell;
}

void ajout_tete_cellule_compagnie(struct cellule_compagnie** pl, char str[SIZE_acronym])
{
    struct cellule_compagnie* cell = malloc(sizeof(struct celulle_compagnie));
    strcpy(cell->IATA_CODE,str);
    init_ht_date(cell->pt_Htable_date);
    cell->compagnie_suiv = *pl;
    *pl = cell;
}

void ajout_vol()
{
    //TODO
}

void charge_vol(Htable_airport ht_ap)
{
    FILE *fp = fopen("../data/flights.csv","r");
    if(fp!=NULL)
    {
        char tmp[200];
        struct vol vol;
        const int nb_lire = 1;
        fscanf(fp,"%s",tmp);
        while(
            fscanf(fp,"%d,%d,%d,%2s,%3s,%3s,%d,%f,%f,%d,%d,%f,%hd,%hd",
		    &vol.MONTH,
		    &vol.DAY,
		    &vol.WEEKDAY,
            tmp,
		    vol.ORG_AIR,
		    vol.DEST_AIR,
		    &vol.SCHED_DEP,
		    &vol.DEP_DELAY,
		    &vol.AIR_TIME,
		    &vol.DIST,
		    &vol.SCHED_ARR,
		    &vol.ARR_DELAY,
		    &vol.DIVERTED,
		    &vol.CANCELLED) == nb_lire)
            {
                struct cellule_airport* Buffairport;
                struct cellule_compagnie* Buffairline;
                struct cellule_vol_date* pt_vol;
                Buffairport = ht_ap[get_hash_index_airport(vol.ORG_AIR)];
                Buffairport = recherche_et_ajout_cell_airport(&Buffairport,vol.ORG_AIR);
                Buffairline = Buffairport->pt_Htable_compagnie[get_hash_index_airline(tmp)];
                Buffairline = recherche_et_ajout_cell_airline(&Buffairline,tmp);
                pt_vol = Buffairline->pt_Htable_date[vol.MONTH];
                ajout_vol();
            }
    }
}

