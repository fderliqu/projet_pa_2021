
void show_most_delayed_flights (struct cellule_airport *Htable_airport[max_Hairport],char IATA_CODE[SIZE_airline_acro])
{
    int cpt_airport, cpt_date;
    float totalretard, nbtotal;
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;
    totalretard = 0;
    nbtotal = 0;
    Hcode = get_hash_index_airline (IATA_CODE, 1);


    printf ("Voici les 5 vols qui on subis le plus longs retard a l'arriv : \n");
    // parcours des airport
    for (cpt_airport = 0; cpt_airport <= max_Hairport; cpt_airport++)
    {
        // parcours de la liste chainer des airports
        Buffairport = Htable_airport[cpt_airport];
        while (Buffairport != NULL)
        {
            // parcours de la liste chainer des compagnies
            Buffcomp = Buffairport->pt_Htable_compagnie[Hcode];
            while (Buffcomp->IATA_CODE != IATA_CODE || Buffcomp != NULL)
            {
                Buffcomp = Buffcomp->compagnie_suiv;
            }
            for (cpt_date = 0; cpt_date <= max_Hdate; cpt_date++)
            {
                Buffvol = Buffcomp->pt_Htable_date[cpt_date];
                while (Buffvol != NULL)
                {
                    if (Buffvol->vol.CANCELLED != 1)
                    {
                        nbtotal += 1;
                        totalretard += Buffvol->vol.ARR_DELAY;
                    }
                    Buffvol = Buffvol->vol_suiv;
                }
            }

            Buffairport = Buffairport->airport_suiv;
        }
    }
    printf ("la compagnie %s a en moyenne %f", IATA_CODE, totalretard / nbtotal);
}
