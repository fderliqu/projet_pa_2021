#include"../includes/hash_algo.h"

void ajout_tete_cellule_airport(struct cellule_airport** pl, char str[SIZE_acronym])
{
    printf("ajout cell\n");
    struct cellule_airport* cell = malloc(sizeof(struct cellule_airport));
    strcpy(cell->airport.IATA_CODE,str);
    init_ht_comp(cell->pt_Htable_compagnie);
    cell->airport_suiv = *pl;
    *pl = cell;
    return;
}

void ajout_tete_cellule_compagnie(struct cellule_compagnie** pl, char str[SIZE_acronym])
{
    printf("ajout cell\n");
    struct cellule_compagnie* cell = malloc(sizeof(struct cellule_compagnie));
    strcpy(cell->IATA_CODE,str);
    init_ht_date(cell->pt_Htable_date);
    cell->compagnie_suiv = *pl;
    *pl = cell;
    return;
}

struct cellule_airport* recherche_et_ajout_cell_airport(struct cellule_airport** pl,char str[SIZE_acronym])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->airport.IATA_CODE) <= 0) )
    {
        ajout_tete_cellule_airport(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->airport.IATA_CODE,str,SIZE_acronym ) )
    {
        printf("trouver\n");
        return *pl;
    }
    else return recherche_et_ajout_cell_airport( &((*pl)->airport_suiv),str);
}

struct cellule_compagnie* recherche_et_ajout_cell_airline(struct cellule_compagnie** pl,char str[SIZE_acronym])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->IATA_CODE) <= 0) )
    {
        ajout_tete_cellule_compagnie(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->IATA_CODE,str,SIZE_acronym ) )
    {
        printf("trouver\n");
        return *pl;
    }
    else return recherche_et_ajout_cell_airline( &((*pl)->compagnie_suiv),str);
}

void ajout_vol(struct cellule_vol_date** pl, struct vol vol)
{
    printf("test\n");
    struct cellule_vol_date* new;
    new = malloc(56);
    new->vol = vol;
    new->vol_suiv = *pl;
    *pl = new;
}

void charge_vol(struct cellule_airport* ht_ap[max_Hairport])
{
    FILE *fp = fopen("../data/flights.csv","r");
    if(fp!=NULL)
    {
        char tmp[200];
        struct vol vol;
        const int nb_lire = 1;
        fscanf(fp,"%s",tmp);
        for(int i=0; i<1; i++)
        {
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
		    &vol.CANCELLED);
            printf("%d\n,%d\n,%d\n,%s\n,%s\n,%s\n,%d\n,%f\n,%f\n,%d\n,%d\n,%f\n,%hd\n,%hd\n",
		    vol.MONTH,
		    vol.DAY,
		    vol.WEEKDAY,
            tmp,
		    vol.ORG_AIR,
		    vol.DEST_AIR,
		    vol.SCHED_DEP,
		    vol.DEP_DELAY,
		    vol.AIR_TIME,
		    vol.DIST,
		    vol.SCHED_ARR
		    ,vol.ARR_DELAY
		    ,vol.DIVERTED
		    ,vol.CANCELLED);
            struct cellule_airport* Buffairport;
            struct cellule_compagnie* Buffairline;
            struct cellule_vol_date* pt_vol;
            printf("hash index airport %s = %d\n",vol.ORG_AIR,get_hash_index_airport(vol.ORG_AIR));
            printf("hash index airline %s = %d\n",tmp,get_hash_index_airline(tmp));
            printf("hash index date = %d\n",vol.MONTH);
            Buffairport = recherche_et_ajout_cell_airport(&( ht_ap[ get_hash_index_airport( vol.ORG_AIR ) ] ),vol.ORG_AIR);
            Buffairline = recherche_et_ajout_cell_airline(&( Buffairport->pt_Htable_compagnie[ get_hash_index_airline( tmp ) ] ),tmp);
            ajout_vol(&(Buffairline->pt_Htable_date[vol.MONTH]),vol);
        }
    }
}
/*
int main()
{
    struct cellule_airport* HT[max_Hairport];
    init_ht_airport(HT);
    charge_vol(HT);
    printf("%s\n",HT[334]->airport.IATA_CODE);
    struct cellule_airport* cell1 = HT[334];
    printf("%s",cell1->pt_Htable_compagnie[get_hash_index_airline("WN")]->IATA_CODE);
    struct cellule_compagnie* cell2 = cell1->pt_Htable_compagnie[get_hash_index_airline("WN")];
    printf("%s\n",cell2->pt_Htable_date[1]->vol.ORG_AIR);
}
*/