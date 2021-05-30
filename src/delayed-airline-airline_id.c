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
