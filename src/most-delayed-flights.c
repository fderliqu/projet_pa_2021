void show_flights(struct cellule_airport Htable_airport[max_Hairport])
{
	int cpt_airport,cpt_airline,cpt_date,cpt_vol;
	struct cellule_airport* Buffairport;
	struct cellule_compagnie* Buffcomp;
	struct cellule_vol_date* Buffvol;
	struct vol* volaffiche[5];
	cpt_vol = 0;

	printf("Voici les 5 vols qui on subis le plus longs retard a l'arrivé : \n");
	//parcours des airport
	for(cpt_airport = 0; cpt_airport <= max_Hairport; cpt_airport++)
	{
		// parcours de la liste chainer des airports
		Buffairport = Htable_airport[cpt_airport];
		while (Buffairport != NULL)
		{
			//parcours de la Htable des compagnie
			for (cpt_airline = 0; cpt_airline <= max_Hcomp; cpt_airline++)
			{
				Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
				while (Buffcomp != NULL)
				{
					for (cpt_date = 0; cpt_date <= max_Hdate; cpt_date++)
					{
						Buffvol= Buffcomp->pt_Htable_date[cpt_date]
							while (Buffvol != NULL)
							{
								most_delay(&volaffiche, vol, &cpt_vol);
								cpt_vol++;
								Buffvol = Buffvol->vol_suiv;
							}

					}
					Buffcomp = Buffcomp->compagnie_suiv;
				}
			}
			Buffairport = Buffairport->airport_suiv;
		}

	}
}

void most_delay(struct vol** volaffiche[5],struct vol vol ,int *cpt_vol)
{
	if (cpt_vol = 0)
	{

	}

}