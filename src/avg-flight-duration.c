#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/avg-flight-duration.h"
#include "../includes/condition_function.h"

void avg_flight_duration(struct cellule_airport *main_HT[max_Hairport], char ORG_AIR[SIZE_acronym], char DEST_AIR[SIZE_acronym])
{
    struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
	int nb_flight=0;
    float somme_airtime=0;
    //On cherche la bonne table avec le paramtre org_air
    int index = get_hash_index_airport(ORG_AIR,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],ORG_AIR);
    //Tests
	if(Buffairport == NULL)
	{
		printf("This departure airport does not exists, please check syntaxe\n");
		return;
	}
	if(Buffairport->is_empty)
	{
		printf("There are no flights from this departure airport\n");
		return;
	}
    //Parcours table airline de <org_air>
    for(int i=0;i<max_Hcomp;i++)
    {
        Buffairline = Buffairport->pt_Htable_compagnie[i];
		while(Buffairline!=NULL)
		{
            //Parcours table date de table de table airline pointé de <org_air>
            for(int j=0;j<max_Hdate;j++)
            {
                Buffvol = Buffairline->pt_Htable_date[j];
                while(Buffvol != NULL)
                {
                    //Condition <dest_air> = vol.dest_air, cancelled == 0, diverted == 0
                    if((strncmp(Buffvol->vol.DEST_AIR,DEST_AIR,SIZE_acronym) == 0) && (Buffvol->vol.CANCELLED == 0) && (Buffvol->vol.DIVERTED == 0)){
                        somme_airtime = somme_airtime + Buffvol->vol.AIR_TIME;
                        nb_flight++;
                    }
                    Buffvol = Buffvol->vol_suiv;
                }
            }
            Buffairline = Buffairline->compagnie_suiv;
        }
    }
    if(nb_flight==0)
    {
        printf("There are no flights from this departure airport to this arrival airport\n");
        return;
    }
    printf("average : %f minutes (%d flights)\n", somme_airtime/(float)nb_flight, nb_flight);
}

void init_avg_flight_duration(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport])
{
    if(number_parameter_test(liste,nb_arg_avg_flight_duration,0) == 0)return;
    int occ_test=1; //1
    if(lenght_parameter_test(liste,SIZE_acronym-1,occ_test) == 0)return;
    occ_test++; //2
    if(lenght_parameter_test(liste,SIZE_acronym-1,occ_test) == 0)return;
    //Launch 
    avg_flight_duration(main_HT,liste.arg[1],liste.arg[2]);
}