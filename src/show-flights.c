#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/show-flights.h"
#include "../includes/condition_function.h"

//Return : 
//  show-flights <main_HT> <AIRPORT> <M> <J> [<time>] [limit=<xx>] <mask>: 
//  affiche les vols qui partent de l'aéroport à la date, 
//  avec optionnellement une heure de début, et limité à xx vols
//Parameters : 
//  <main_HT>=table de hash des données des vols
//  <AIRPORT>=aéroport de départ
//  <J>=nombre du jour
//  <M>=nombre du mois
//  [<time>] = temps début départ (option) 
//  [limit=<xx>] = limite d'affichage (option)
//  <mask> masque pour parametre optionnel
void show_flights(struct cellule_airport *main_HT[max_Hairport], char AIRPORT[SIZE_acronym], int M, int J, int time, int limit, char mask)
{
	struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
	int compt=0;
	//Utilisation du masque
	if(!(mask & 0x01))limit=-1;
	if(!(mask & 0x02))time=-1;
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

void init_show_flights(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport])
{
	//Conditions de lancement 
	int J,M,limit = 5,time = 0;
	int occ_test = 0;
	char* token;
	char* date[2];
	char mask = build_mask_time_limit(liste,nb_arg_show_flights);	//Build du masque
    if(number_parameter_test(liste,nb_arg_show_flights,nb_optionnal_arg_show_flights) == 0)return;	//Test sur le nombre de paramètre
	occ_test++; //1
    if(lenght_parameter_test(liste,SIZE_acronym-1,occ_test) == 0)return; //Test sur la longueur du paramètre "<port_id>"
	occ_test++; //2
	if(date_format_test(liste.arg[occ_test],occ_test) == 0)return; //Test sur le format de <date>
	//Split date
	date[0] = strtok(liste.arg[occ_test],"-\0\n");
	date[1] = strtok(NULL,"-\0\n");
	M = (int)strtol( date[0], NULL, 10);
	J = (int)strtol( date[1], NULL, 10);
	if(day_and_month_valid_test(M,J,occ_test) == 0)return; //Test validité de la date
	if(mask & timeON){
		occ_test++; //3
		if(wrong_int_test(liste.arg[occ_test],occ_test) == 0)return; //Test sur type avant conversion
		time = (int)strtol(liste.arg[occ_test],NULL,10);
		if(time_test(time,occ_test) == 0)return; //Test sur la validité du temps
	}
	if(mask & limitON){
		occ_test++; //3 ou 4
		//On prend que après "=" de "limit=X"
		token = strtok(liste.arg[occ_test],"=" );
		token = strtok(NULL,"=");
		if(wrong_int_test(token,occ_test) == 0)return; //Test sur type avant conversion
		limit = (int)strtol(token,NULL,10);
		if(limit_test(limit,occ_test)==0)return; //Test sur la validité de la limite > 0
	}
    //Lancement
    show_flights(main_HT,liste.arg[1],M,J,time,limit,mask);
}
	


