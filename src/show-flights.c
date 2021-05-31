#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/show-flights.h"
#define MAXlimit 2359


void print_normal_flight(struct cellule_vol_date* cell, char airline[SIZE_airline_acro])
{
	printf	("%d,%d,%d,%s,%s,%s,%d,%f,%f,%d,%d,%f,%hd,%hd\n",
			cell->vol.MONTH,
			cell->vol.DAY,
			cell->vol.WEEKDAY,
			airline,
			cell->vol.ORG_AIR,
			cell->vol.DEST_AIR,
			cell->vol.SCHED_DEP,
			cell->vol.DEP_DELAY,
			cell->vol.AIR_TIME,
			cell->vol.DIST,
			cell->vol.SCHED_ARR,
			cell->vol.ARR_DELAY,
			cell->vol.DIVERTED,
			cell->vol.CANCELLED
			);
}

void print_cancelled_flight(struct cellule_vol_date* cell, char airline[SIZE_airline_acro])
{
	printf	("%d,%d,%d,%s,%s,%s,%d,%d,%d,%hd,%hd\n",
			cell->vol.MONTH,
			cell->vol.DAY,
			cell->vol.WEEKDAY,
			airline,
			cell->vol.ORG_AIR,
			cell->vol.DEST_AIR,
			cell->vol.SCHED_DEP,
			cell->vol.DIST,
			cell->vol.SCHED_ARR,
			cell->vol.DIVERTED,
			cell->vol.CANCELLED
			);
}

void print_diverted_flight(struct cellule_vol_date* cell, char airline[SIZE_airline_acro])
{
	printf	("%d,%d,%d,%s,%s,%s,%d,%f,%d,%d,%hd,%hd\n",
			cell->vol.MONTH,
			cell->vol.DAY,
			cell->vol.WEEKDAY,
			airline,
			cell->vol.ORG_AIR,
			cell->vol.DEST_AIR,
			cell->vol.SCHED_DEP,
			cell->vol.DEP_DELAY,
			cell->vol.DIST,
			cell->vol.SCHED_ARR,
			cell->vol.DIVERTED,
			cell->vol.CANCELLED
			);
}

void show_flights(struct cellule_airport *main_HT[max_Hairport], char AIRPORT[SIZE_acronym], int M, int J, int time, int limit, char mask)
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
	int compt=0;
	if(!(mask & 0x01))limit=-1;
	if(!(mask & 0x02))time=-1;
	else if(time<0 || time>MAXlimit)
	{
		printf("Given time is over 23h59, please write a correct time\n");
		return;
	}
	int index = get_hash_index_airport(AIRPORT,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],AIRPORT);
	if(Buffairport == NULL)
	{
		printf("This airport does not exists, please check syntaxe\n");
		return;
	}
	if(Buffairport->is_empty)
	{
		printf("There are no flights from this departure airport\n");
		return;
	}
	for(int i=0;i<max_Hcomp;i++)
	{
		Buffairline = Buffairport->pt_Htable_compagnie[i];
		while(Buffairline!=NULL)
		{
			Buffvol = Buffairline->pt_Htable_date[M-1];
			while(Buffvol != NULL)
			{
				if( (Buffvol->vol.DAY == J) && (Buffvol->vol.SCHED_DEP > time) )//La condition sera toujours valide à time = -1
				{
					if(Buffvol->vol.DIVERTED)print_diverted_flight(Buffvol,Buffairline->IATA_CODE);
					else if(Buffvol->vol.CANCELLED)print_cancelled_flight(Buffvol,Buffairline->IATA_CODE);
					else print_normal_flight(Buffvol,Buffairline->IATA_CODE);
					compt++;
					if(compt==limit) //La condition ne sera jamais valide à limit = -1
					{
						printf("limit reached, end of the function\n");
						return;
					}
				}
				Buffvol = Buffvol->vol_suiv;
			}
			Buffairline = Buffairline->compagnie_suiv;
		}
	}
}


