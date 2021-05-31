#include"../includes/init.h"
#include"../includes/hash_algo.h"
#include"../includes/delayed-airline-airline_id.h"
#include"../includes/condition_function.h"

void delayed_airline (struct cellule_airport *Htable_airport[max_Hairport], char IATA_CODE[SIZE_airline_acro])
{
    int                       cpt_airport, cpt_date, indexcomp, cpt;
    float                     totalretard, nbtotal;
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;
    totalretard = 0;
    nbtotal     = 0;
    indexcomp   = get_hash_index_airline (IATA_CODE, max_Hcomp);
    cpt         = 0;


    printf ("Voici la moyenne de retard de la compagnie %s : \n", IATA_CODE);
    // parcours des airport
    for (cpt_airport = 0; cpt_airport < max_Hairport; cpt_airport++)
    {
        // parcours de la liste chainer des airports
        Buffairport = Htable_airport[cpt_airport];
        while (Buffairport != NULL)
        {
            if (Buffairport->is_empty != 1)
            {
                // parcours de la liste chainer des compagnies
                Buffcomp = Buffairport->pt_Htable_compagnie[indexcomp];
                while (Buffcomp != NULL)
                {
                    if (strcmp (Buffcomp->IATA_CODE, IATA_CODE) == 0)
                    {
                        for (cpt_date = 0; cpt_date < max_Hdate; cpt_date++)
                        {
                            Buffvol = Buffcomp->pt_Htable_date[cpt_date];
                            while (Buffvol != NULL)
                            {
                                if (Buffvol->vol.CANCELLED != 1 && Buffvol->vol.DIVERTED != 1)
                                {
                                    cpt++;
                                    // printf("AIr delay %f \n ", Buffvol->vol.ARR_DELAY);
                                    if (Buffvol->vol.ARR_DELAY > 0)
                                    {
                                        // printf("AIr retenue %f \n ", Buffvol->vol.ARR_DELAY);
                                        nbtotal += 1;
                                        totalretard += Buffvol->vol.ARR_DELAY;
                                    }
                                }
                                Buffvol = Buffvol->vol_suiv;
                            }
                        }
                    }
                    Buffcomp = Buffcomp->compagnie_suiv;
                }
            }

            Buffairport = Buffairport->airport_suiv;
        }
    }
    printf ("la compagnie %s a en moyenne %f \n", IATA_CODE, totalretard / nbtotal);
    // printf("nbtotal %f \n", nbtotal);
    // printf("cpt %d\n", cpt);
}

void init_delayed_airlines(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport])
{
    //Conditions de lancement 
    if(number_parameter_test(liste,nb_arg_delayed_airlines,0) == 0)return;
    if(lenght_parameter_test(liste,SIZE_airline_acro-1,1) == 0)return;
    //Lancement
    delayed_airline(main_HT,liste.arg[1]);
}
