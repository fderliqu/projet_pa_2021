#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/condition_function.h"
#include "../includes/find-initerary.h"

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
	struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
	if(!(mask & timeON))time=1;
	else if(time<0 || time>MAXtimelimite)
	{
        suppr_tete_itinerary(pItinerary);
		return;
	}
	int index = get_hash_index_airport(ORG_AIR,max_Hairport);
	Buffairport = recherche_cellHT_airport(main_HT[index],ORG_AIR);
    if(Buffairport == NULL)
	{
		suppr_tete_itinerary(pItinerary);
		return;
	}
	if(Buffairport->is_empty)
	{
        suppr_tete_itinerary(pItinerary);
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
                    (*limit > 0))
                    {
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
    suppr_tete_itinerary(pItinerary);
    return;
}

void init_find_itinerary(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport])
{
    //Conditions de lancement 
	int J,M,limit = 1,time = 1;
	int occ_test = 0;
	char* token;
	char* date[2];
	char mask = build_mask_time_limit(liste,nb_arg_find_itinerary);	//Build du masque
    if(number_parameter_test(liste,nb_arg_find_itinerary,nb_optionnal_arg_find_itinerary) == 0)return;	//Test sur le nombre de paramètre
	occ_test++; //1
    if(lenght_parameter_test(liste,SIZE_acronym-1,occ_test) == 0)return; //Test sur la longueur du paramètre "<port_id1>"
    if(number_parameter_test(liste,nb_arg_find_itinerary,nb_optionnal_arg_find_itinerary) == 0)return;	//Test sur le nombre de paramètre
	occ_test++; //2
    if(lenght_parameter_test(liste,SIZE_acronym-1,occ_test) == 0)return; //Test sur la longueur du paramètre "<port_id1>"
	occ_test++; //3
	if(date_format_test(liste.arg[occ_test],occ_test) == 0)return; //Test sur le format de <date>
	//Split date
	date[0] = strtok(liste.arg[occ_test],"-\0\n");
	date[1] = strtok(NULL,"-\0\n");
	M = (int)strtol( date[0], NULL, 10);
	J = (int)strtol( date[1], NULL, 10);
	if(day_and_month_valid_test(M,J,occ_test) == 0)return; //Test validité de la date
	if(mask & timeON){
		occ_test++; //4
		if(wrong_int_test(liste.arg[occ_test],occ_test) == 0)return; //Test sur type avant conversion
		time = (int)strtol(liste.arg[occ_test],NULL,10);
		if(time_test(time,occ_test) == 0)return; //Test sur la validité du temps
	}
	if(mask & limitON){
		occ_test++; //4 ou 5
		//On prend que après "=" de "limit=X"
		token = strtok(liste.arg[occ_test],"=" );
		token = strtok(NULL,"=");
		if(wrong_int_test(token,occ_test) == 0)return; //Test sur type avant conversion
		limit = (int)strtol(token,NULL,10);
		if(limit_test(limit,occ_test)==0)return; //Test sur la validité de la limite > 0
	}
    //Lancement
    struct cellule_vol *PTvol = NULL;
    find_itinerary(main_HT,&PTvol,liste.arg[1],liste.arg[2],M,J,time,&limit,mask);
}