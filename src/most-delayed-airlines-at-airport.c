#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/condition_function.h"

#include "../includes/most_delayed_airlines.h"
#include "../includes/most-delayed-airlines-at-airport.h"

void show_most_delayed_airline_at_airport(struct cellule_airport* Htable_airport[max_Hairport],
    struct cellule_compagnieDATA* NAMEcomp[max_Hdatacomp],
    char IATA_airport[SIZE_airline_acro])
{

    int                       cpt_airline, cpt_date, indexcomp, cpttab;
    struct cellule_comp_most      tablecomp[max_Hdatacomp];
    struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffcomp;
    struct cellule_vol_date* Buffvol;

    struct liste_most_airline lmax;
    lmax.dernier = -1;

    // initialisation du tableau
    init_table_most(tablecomp);

    printf("Voici les 5 compagnie qui on subis le plus longs retard moyen a l'arrivee de %s : \n", IATA_airport);
    // parcours des airport

    // parcours de la liste chainer des airports
    Buffairport = Htable_airport[get_hash_index_airport(IATA_airport, max_Hairport)];
    while (Buffairport != NULL)
    {
        if (Buffairport->is_empty != 1)
        {
            // parcours de la Htable des compagnie
            for (cpt_airline = 0; cpt_airline < max_Hcomp; cpt_airline++)
            {
                Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
                // parcours de la liste chainer des compagnie
                while (Buffcomp != NULL)
                {
                    // parcours des vols
                    indexcomp = get_hash_index_airline(Buffcomp->IATA_CODE, max_Hdatacomp);
                    for (cpt_date = 0; cpt_date < max_Hdate; cpt_date++)
                    {
                        Buffvol = Buffcomp->pt_Htable_date[cpt_date];

                        while (Buffvol != NULL)
                        {
                            if (Buffvol->vol.CANCELLED != 1 && Buffvol->vol.DIVERTED != 1)
                            {
                                if (Buffvol->vol.ARR_DELAY > 0)
                                {
                                    ajout_moyenne(tablecomp, Buffvol->vol, indexcomp);
                                }
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

    cpttab = 0;
    while (cpttab < max_Hdatacomp)
    {
        // printf("cpttab= %d \n", cpttab);
        // printf(" nb vol %d \n", tablecomp[cpttab].nbvol);
        if (tablecomp[cpttab].nbvol != -1)
        {
            affichemax(&lmax, tablecomp, cpttab, maxmostat);
            // afficheliste(&lmax, tablecomp, NAMEcomp);
            // printf("----------------------------\n");
        }
        cpttab++;
    }
    afficheliste_airlines_moy(&lmax, tablecomp, NAMEcomp);
}

void init_show_most_delayed_airline_at_airport(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport],struct cellule_compagnieDATA* data_HT[max_Hdatacomp])
{
    //Conditions de lancement 
	int test;
	test = number_parameter_test(liste,nb_arg_most_delayed_airline_at_airport,0);
    if(test == 0)return;
	test = lenght_parameter_test(liste,SIZE_acronym-1,1);
    if(test == 0)return;
    //Lancement
    show_most_delayed_airline_at_airport(main_HT,data_HT,liste.arg[1]);
}
