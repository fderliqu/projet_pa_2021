#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/main_function.h"
#include "../includes/condition_function.h"

#include "../includes/most-delayed-flights.h"

void affichelisteflights (struct liste_delayed_flights*lc)
{
    int cpt = lc->dernier;
    while (cpt >= 0)
    {
        printf ("%d,%d,%d,%s,%s,%s,", lc->volaffiche[cpt].vol.DAY, lc->volaffiche[cpt].vol.MONTH,
                lc->volaffiche[cpt].vol.WEEKDAY, lc->volaffiche[cpt].IATA_AIRLINE,
                (lc->volaffiche[cpt].vol).ORG_AIR, lc->volaffiche[cpt].vol.DEST_AIR);
        printf ("%d,%f,%f,%d,%d,", lc->volaffiche[cpt].vol.SCHED_DEP,
                lc->volaffiche[cpt].vol.DEP_DELAY, lc->volaffiche[cpt].vol.AIR_TIME,
                lc->volaffiche[cpt].vol.DIST, lc->volaffiche[cpt].vol.SCHED_ARR);
        printf ("%f,%hd,%hd,\n", lc->volaffiche[cpt].vol.ARR_DELAY,
                lc->volaffiche[cpt].vol.DIVERTED, lc->volaffiche[cpt].vol.CANCELLED);
        cpt--;
    }
}

void most_delay (struct liste_delayed_flights*lc, struct vol vol, char IATA[SIZE_airline_acro],int maxflights)
{
    int             cpt = 0;
    struct vol_IATA buff, buff2;
    // initialisation de la liste
    if (lc->dernier < maxflights - 1)
    {
        lc->dernier++;
        if (vol.ARR_DELAY > lc->volaffiche[(lc->dernier) - 1].vol.ARR_DELAY)
        {
            lc->volaffiche[lc->dernier].vol = vol;
            strcpy (lc->volaffiche[lc->dernier].IATA_AIRLINE, IATA);
        }
        while (cpt < (lc->dernier))
        {
            if (vol.ARR_DELAY < lc->volaffiche[cpt].vol.ARR_DELAY)
            {
                buff                    = lc->volaffiche[cpt];
                lc->volaffiche[cpt].vol = vol;
                strcpy (lc->volaffiche[cpt].IATA_AIRLINE, IATA);
                cpt++;
                while (cpt <= lc->dernier)
                {
                    lc->volaffiche[lc->dernier] = lc->volaffiche[cpt];
                    lc->volaffiche[cpt]         = buff;
                    buff                        = lc->volaffiche[lc->dernier];
                    cpt++;
                }
            }
            cpt++;
        }
        if (lc->dernier == 0)
        {
            lc->volaffiche[lc->dernier].vol = vol;
            strcpy (lc->volaffiche[lc->dernier].IATA_AIRLINE, IATA);
        }
        return;
    }
    if (vol.ARR_DELAY < lc->volaffiche[0].vol.ARR_DELAY)
    {
        return;
    }
    // parcours de la liste
    cpt = 1;
    while (cpt < maxflights)
    {
        if (vol.ARR_DELAY < lc->volaffiche[cpt].vol.ARR_DELAY)
        {
            break;
        }
        cpt++;
    }
    // modification de la liste
    buff                        = lc->volaffiche[cpt - 1];
    lc->volaffiche[cpt - 1].vol = vol;
    strcpy (lc->volaffiche[cpt - 1].IATA_AIRLINE, IATA);
    cpt = cpt - 2;
    while (cpt >= 0)
    {
        buff2               = lc->volaffiche[cpt];
        lc->volaffiche[cpt] = buff;
        buff                = buff2;
        cpt--;
    }
}


void show_most_delayed_flights (struct cellule_airport *Htable_airport[max_Hairport],int maxflights)
{
    int                       cpt_airport, cpt_airline, cpt_date;
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;
    struct liste_delayed_flights              lc;
    lc.dernier = -1;

    printf ("Voici les 5 vols qui on subis le plus longs retard a l'arrivee : \n \n");
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
                    while (Buffcomp != NULL)
                    {
                        for (cpt_date = 0; cpt_date < max_Hdate; cpt_date++)
                        {
                            Buffvol = Buffcomp->pt_Htable_date[cpt_date];
                            while (Buffvol != NULL)
                            {
                                if (Buffvol->vol.CANCELLED != 1 && Buffvol->vol.DIVERTED != 1)
                                {
                                    most_delay (&lc, Buffvol->vol, Buffcomp->IATA_CODE, maxflights);
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
    }
    affichelisteflights(&lc);
}

void init_most_delayed_flights(struct line_arguments liste, struct cellule_airport* main_HT[max_Hairport])
{
    if(number_parameter_test(liste,nb_arg_most_delayed_flights,0) == 0)return;
    show_most_delayed_flights(main_HT,maxmostflights);
}
