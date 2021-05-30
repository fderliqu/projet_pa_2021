#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/most-delayed-flights.h"
/*
void afficheliste(struct liste lc)
{
	int cpt = lc.dernier;
	while (cpt >= 0)
	{
		printf("%d %d %d %s %s ", lc.volaffiche[cpt].DAY, lc.volaffiche[cpt].MONTH, lc.volaffiche[cpt].WEEKDAY, lc.volaffiche[cpt].ORG_AIR, lc.volaffiche[cpt].DEST_AIR);
		printf("%d %f %f %d %d ", lc.volaffiche[cpt].SCHED_DEP, lc.volaffiche[cpt].DEP_DELAY, lc.volaffiche[cpt].AIR_TIME, lc.volaffiche[cpt].DIST, lc.volaffiche[cpt].SCHED_ARR);
		printf("%f %d %d \n", lc.volaffiche[cpt].ARR_DELAY, lc.volaffiche[cpt].DIVERTED, lc.volaffiche[cpt].CANCELLED);
	}

}
*/
int compare_arrdelay(struct vol v1, struct vol v2) { return v1.ARR_DELAY - v2.ARR_DELAY; }

void ajout_delayed(struct cellule_vol **pl, struct vol vol, char airline[SIZE_airline]) {
  if ((*pl == NULL) || (compare_arrdelay(vol, (*pl)->data) > 0)) {
    struct cellule_vol *new;
    new = malloc(sizeof(struct cellule_vol));
    new->data = vol;
	strncpy(new->airline,airline,SIZE_airline_acro);
    new->suiv = *pl;
    *pl = new;
    return;
  }
  ajout_delayed(&((*pl)->suiv), vol, airline);
}

void suppr_fin_delayed(struct cellule_vol** pL)
{
    if(*pL == NULL)return;
	if((*pL)->suiv == NULL){
    struct cellule_vol *tmp;
    tmp = *pL;
    *pL = NULL;
    free(tmp);
	return;
	}
	suppr_fin_delayed( &((*pL)->suiv) );
}

/*
void most_delay(struct liste *lc, struct vol vol)
{
	int cpt = 0;
	struct vol buff;
	//initialisation de la liste
    if (lc->dernier < maxmostflights)
	{
		lc->dernier++;
		while (cpt < lc->dernier - 1)
		{
			if (vol.ARR_DELAY > lc->volaffiche[(lc->dernier) - 1].ARR_DELAY)
			{
				lc->volaffiche[lc->dernier] = vol;
			}
			else if (vol.ARR_DELAY < lc->volaffiche[cpt].ARR_DELAY)
			{
				buff = lc->volaffiche[cpt];
				lc->volaffiche[cpt] = vol;
			}
			else
			{
				lc->volaffiche[lc->dernier] = lc->volaffiche[cpt];
				lc->volaffiche[cpt] = buff;
				buff = lc->volaffiche[lc->dernier];
			}
			cpt++;
		}
		if (lc->dernier == 0)
		{
			lc->volaffiche[lc->dernier] = vol;
		}
		return;
	}
	if (vol.ARR_DELAY < lc->volaffiche[0].ARR_DELAY) { return; }
	//parcours de la liste
	cpt = 1;
    while (cpt < maxmostflights)
	{
		if (vol.ARR_DELAY < lc->volaffiche[cpt].ARR_DELAY) { break; }
		cpt++;
	}
	//modification de la liste 
	buff = lc->volaffiche[cpt-1];
	lc->volaffiche[cpt-1] = vol;
	cpt--;

	while (cpt >= 0)
	{
		vol = lc->volaffiche[cpt];
		lc->volaffiche[cpt] = buff;
		buff = vol;
		cpt--;
	}

}
*/

void show_most_delayed_flights(struct cellule_airport *Htable_airport[max_Hairport])
{
	int cpt_airport,cpt_airline,cpt_date;
	struct cellule_airport* Buffairport;
	struct cellule_compagnie* Buffcomp;
	struct cellule_vol_date* Buffvol;
	struct cellule_vol* L = NULL;
	struct cellule_vol* tmp;
	int compt=0;
	printf("Voici les 5 vols qui on subis le plus longs retard a l'arrivé : \n");
	//parcours des airport
	for(cpt_airport = 0; cpt_airport < max_Hairport; cpt_airport++)
	{
		// parcours de la liste chainée des airports
		Buffairport = Htable_airport[cpt_airport];
		while (Buffairport != NULL)
		{
			if(Buffairport->is_empty != 1)
			{
				//parcours de la Htable des compagnie
				for (cpt_airline = 0; cpt_airline < max_Hcomp; cpt_airline++)
				{
					Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
					while (Buffcomp != NULL)
					{
						for (cpt_date = 0; cpt_date < max_Hdate; cpt_date++)
						{
							Buffvol = Buffcomp->pt_Htable_date[cpt_date];
							while (Buffvol != NULL)
							{
                            	if ( (Buffvol->vol.CANCELLED == 0) && (Buffvol->vol.DIVERTED == 0) )
                            	{
									ajout_delayed(&L,Buffvol->vol, Buffcomp->IATA_CODE);
									compt++;
									if(compt>5)suppr_fin_delayed(&L);
                            	}
								Buffvol = Buffvol->vol_suiv;
							}
						}
						Buffcomp = Buffcomp->compagnie_suiv;
					}
				}
			}
			Buffairport = Buffairport->airport_suiv;
		}
	}
	tmp = L;
	while(tmp!=NULL)
	{
		print_data_cellule_vol(tmp);
		tmp = tmp->suiv;
	}
}
