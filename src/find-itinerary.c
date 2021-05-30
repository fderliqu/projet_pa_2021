#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/find-initerary.h"

#define MAXlimit 2359


void suppr_tete_itinerary(struct cellule_vol** pL)
{
    if(*pL == NULL)return;
    struct cellule_vol *tmp;
    tmp = *pL;
    *pL = tmp->suiv;
    free(tmp);
}

void ajout_tete_itinerary(struct cellule_vol** pL, struct vol data, char airline[SIZE_airline_acro])
{
    struct cellule_vol *new;
    new = malloc(sizeof(struct cellule_vol));
    new->data = data;
    strncpy(new->airline,airline,SIZE_airline_acro);
    new->suiv = *pL;
    *pL = new;
    return;
}

void print_itinerary(struct cellule_vol* L)
{

    if(L!=NULL)print_itinerary(L->suiv);
    else return;
	print_data_cellule_vol(L);
    return;
}

void find_itinerary(   
    struct cellule_airport *main_HT[max_Hairport], 
    struct cellule_vol** pItinerary,
    char ORG_AIR[SIZE_acronym], 
    char DEST_AIR[SIZE_acronym],
    int M,
    int J,
    int time,
    int* limit,
    char mask
)
{
    if(J<0 || J>31)
	{
		printf("Please write a correct day\n");
		return;
	}
	if(M<0 || M>12)
	{
		printf("Please write a correct month\n");
		return;
	}
	struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
	if(!(mask & timeON))time=-1;
	else if(time<0 || time>MAXlimit)
	{
        suppr_tete_itinerary(pItinerary);
		return;
	}
	int index = get_hash_index_airport(ORG_AIR,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],ORG_AIR);
    if(Buffairport == NULL)
	{
		suppr_tete_itinerary(pItinerary);
        printf("no exist : return\n");
		return;
	}
	if(Buffairport->is_empty)
	{
        suppr_tete_itinerary(pItinerary);
        //printf("no flight on airport : return\n");
		return;
	}
    for(int i=0;i<max_Hcomp;i++)
	{
		Buffairline = Buffairport->pt_Htable_compagnie[i];
		while(Buffairline!=NULL)
		{
			Buffvol = Buffairline->pt_Htable_date[M-1];
            while(Buffvol!=NULL)
            {
                if  ( (Buffvol->vol.CANCELLED == 0) && 
                    (Buffvol->vol.DIVERTED == 0) && 
                    (Buffvol->vol.SCHED_DEP > time) && 
                    (Buffvol->vol.DAY == J) &&
                    (*limit>0))
                    {
                        //print_itinerary(*pItinerary);
                        //printf("%s %s %s %d \n",Buffairline->IATA_CODE,Buffvol->vol.ORG_AIR,Buffvol->vol.DEST_AIR,Buffvol->vol.SCHED_ARR);
                        if(strncmp(Buffvol->vol.DEST_AIR,DEST_AIR,SIZE_acronym) == 0)
                        {
                            ajout_tete_itinerary( pItinerary , Buffvol->vol , Buffairline->IATA_CODE );
                            print_itinerary(*pItinerary);
                            printf("\n");
                            if(mask & limitON)(*limit)--;
                            suppr_tete_itinerary(pItinerary);
                        }
                        else 
                        {
                            if(Buffvol->vol.SCHED_DEP < Buffvol->vol.SCHED_ARR)
                            {
                                ajout_tete_itinerary( pItinerary , Buffvol->vol , Buffairline->IATA_CODE );
                                if(!(mask & limitON))mask = timeON; //si limit est desacctivée -> time on, limit off
                                else mask = timeON_limitON; //sinon time and limit on
                                find_itinerary(
                                    main_HT,
                                    pItinerary,
                                    Buffvol->vol.DEST_AIR,
                                    DEST_AIR,
                                    M,
                                    J,
                                    Buffvol->vol.SCHED_ARR,
                                    limit,
                                    mask
                                );
                            }
                        }
                    }
                Buffvol = Buffvol->vol_suiv;
            }
            Buffairline = Buffairline->compagnie_suiv;
		}
	}
    //printf("no match : return\n");
    suppr_tete_itinerary(pItinerary);
    return;
}