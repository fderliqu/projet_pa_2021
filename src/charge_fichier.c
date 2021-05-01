#include"../includes/init.h"
#include"./hash_algo.h"

int trouve_cell(struct cellule_airport* pCell,char str[SIZE_acronym])
{
    if(pCell == NULL)
    {
        return 0;
    }
    if(!strncmp(pCell->airport,str,SIZE_acronym))return 1;
    else trouve_airport(pCell->airport_suiv,str);
}

void ajout_vol()
{

}

void charge_vol(Htable_airport ht_ap)
{
    FILE *fp = fopen("../data/flights.csv","r");
    if(fp!=NULL)
    {
        char tmp[200];
        struct vol vol;
        const int nb_lire = 1;
        fscanf(fp,"%s",str);
        while(
            fscanf(fp,"%d,%d,%d,%2s,%3s,%3s,%d,%f,%f,%d,%d,%f,%hd,%hd",
		    &vol.MONTH,
		    &vol.DAY,
		    &vol.WEEKDAY,
		    vol.ORG_AIR,
		    vol.DEST_AIR,
		    tmp,
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
                struct compagnie* Buffairline;
                struct cellule_vol_date* pt_vol;
                Buffairport = ht_ap[get_hash_index_airport(vol.ORG_AIR)];
                int trouve = trouve_cell(Buffairport,vol.ORG_AIR);
                if(!trouve)ajout_cellule_airport();
                Buffairline = Buffairport->pt_Htable_compagnie[get_hash_index_airline(tmp)];
                trouve = trouve_cell(Buffairline,tmp);
                if(!trouve)ajout_cellule_airplane();
                pt_vol = Buffairline->pt_Htable_date[vol.MONTH];
                ajout_vol();
            }
    }
}

