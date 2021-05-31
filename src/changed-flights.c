#include "../includes/init.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/condition_function.h"
#include "../includes/hash_algo.h"

void changed_flights (struct cellule_airport *Htable_airport[max_Hairport], int jour, int mois)
{

    int                       cpt_airport, cpt_airline;
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;


    printf ("Voici les vols annulées ou déviées de cet aéroport: \n");
    // parcours des airport
    for (cpt_airport = 0; cpt_airport < max_Hairport; cpt_airport++)
    {
        // parcours de la liste chainer des airports
        Buffairport = Htable_airport[cpt_airport];
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
                        Buffvol = Buffcomp->pt_Htable_date[mois - 1];
                        while (Buffvol != NULL)
                        {
                            if (Buffvol->vol.DAY == jour && (Buffvol->vol.CANCELLED || Buffvol->vol.DIVERTED))
                            {
                                print_normal_flight (Buffvol, Buffcomp->IATA_CODE);
                            }
                            Buffvol = Buffvol->vol_suiv;
                        }

                        Buffcomp = Buffcomp->compagnie_suiv;
                    }
                }
            }
            Buffairport = Buffairport->airport_suiv;
        }
    }
}

void init_changed_flights (struct line_arguments liste, struct cellule_airport *main_HT[max_Hairport])
{
    int   occ_test = 1;
    int   M, J;
    char *date[2];
    if (date_format_test (liste.arg[occ_test], occ_test) == 0)
        return; // Test sur le format de <date>
    // Split date
    date[0] = strtok (liste.arg[occ_test], "-\0\n");
    date[1] = strtok (NULL, "-\0\n");
    M       = (int)strtol (date[0], NULL, 10);
    J       = (int)strtol (date[1], NULL, 10);
    if (day_and_month_valid_test (M, J, occ_test) == 0) return; // Test validité de la date
    // Launch fct
    changed_flights (main_HT, J, M);
}
