#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/avg-flight-duration.h"

void avg_flight_duration(struct cellule_airport *main_HT[max_Hairport], char ORG_AIR[SIZE_acronym], char DEST_AIR[SIZE_acronym])
{
    struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
	int nb_flight=0;
    float somme_airtime=0;
    int index = get_hash_index_airport(ORG_AIR,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],ORG_AIR);
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
            for(int j=0;j<max_Hdate;j++)
            {
                Buffvol = Buffairline->pt_Htable_date[j];
                while(Buffvol != NULL)
                {
                    if((strncmp(Buffvol->vol.DEST_AIR,DEST_AIR,SIZE_acronym) == 0) && (Buffvol->vol.CANCELLED == 0)){
                        somme_airtime = somme_airtime + Buffvol->vol.AIR_TIME;
                        nb_flight++;
                    }
                    Buffvol = Buffvol->vol_suiv;
                }
            }
            Buffairline = Buffairline->compagnie_suiv;
        }
    }
    printf("average : %f minutes (%d flights)\n", somme_airtime/(float)nb_flight, nb_flight);
}