
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/hash_algo.h"


void changed_flights (struct cellule_airport *Htable_airport[max_Hairport], int jour, int mois)
{

    int                       cpt_airport, cpt_airline;
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;


    printf ("Voici les voles annuler de cet aeroport: \n");
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
                            if (Buffvol->vol.DAY == jour && Buffvol->vol.CANCELLED == 1)
                            {
                                printf ("%d %d %d %s %s %s ", Buffvol->vol.DAY, Buffvol->vol.MONTH,
                                        Buffvol->vol.WEEKDAY, Buffcomp->IATA_CODE,
                                        Buffvol->vol.ORG_AIR, Buffvol->vol.DEST_AIR);
                                printf ("%d %d %d ", Buffvol->vol.SCHED_DEP, Buffvol->vol.DIST,
                                        Buffvol->vol.SCHED_ARR);
                                printf (" %hd %hd \n", Buffvol->vol.DIVERTED, Buffvol->vol.CANCELLED);
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
