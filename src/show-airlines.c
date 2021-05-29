#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/show-airport.h"

void show_airlines(struct cellule_airport* main_HT[max_Hairport], struct cellule_compagnieDATA* data_HT[max_Hdatacomp], char AIRPORT[SIZE_acronym])
{
	struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_compagnieDATA* Buffdata;
	int index = get_hash_index_airport(AIRPORT,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],AIRPORT);
	if(Buffairport->is_empty)
	{
		printf("No company operates flights at this airport\n");
		return;
	}
	for(int i=0;i<max_Hcomp;i++)
	{
		Buffairline = Buffairport->pt_Htable_compagnie[i];
		while(Buffairline!=NULL)
		{
			index = get_hash_index_airline(Buffairline->IATA_CODE,max_Hdatacomp);
			Buffdata = data_HT[index];
			printf("%s,%s\n",Buffdata->IATA_CODE,Buffdata->AIRLINE);
			Buffairline = Buffairline->compagnie_suiv;
		}
	}
}
	