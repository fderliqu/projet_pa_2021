void show_flights(char IATA_CODE_c[SIZE_airport], int J, int M, int time, int limit, struct cellule_airport Htable_airport[max_Hairport])
{
	int Hcode_port, Hcode_date, cpt_vol, cpt_airline, cpt_date, cpt_chaine, stop_while;
	struct cellule_airport* Buffairport;
	struct cellule_compagnie* Buffcomp;
	struct cellule_vol_date* Buffdate;
	struct vol volaffiche;

	if (limit != NULL)
	{
		cpt_vol = limit;
	}

	Hcode_port = 4;//fonction hcode_airport
	Hcode_date = 4;//fonction hcode_airport
	Buffairport = Htable_airport[Hcode_port];
	printf("recherche des vols au depart de l'aerport : \n");
	//parcours des airport
	while (Buffairport != NULL)
	{
		// si on a trouver l'aeroport rechercher
		if (strcmp(IATA_CODE_c, (Buffairport->airport.IATA_CODE)) == 0)
		{
			//parcours de la Htable des compagnie
			for (cpt_airline = 0; cpt_airline <= max_Hcomp; cpt_airline++)
			{
				Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
				//parcorus dans la liste chainer des compagnies
				while (Buffcomp != NULL)
				{
					//parcours dans la Htables des dates
					Buffdate = Buffcomp->pt_Htable_date[Hcode_date];
					cpt_chaine = 0;
					stop_while = 0;
					while (Buffdate != NULL && stop_while = 0;)
					{
						volaffiche = Buffdate->vol;
						//si on est sur la bonne date
						if (volaffiche.MONTH == M && volaffiche.DAY == J)
						{
							if (time != NULL && limit != NULL)
							{
								if (volaffiche.SCHED_DEP == time)
								{
									printf("%d %d %d %s %s ", volaffiche.DAY, volaffiche.MONTH, volaffiche.WEEKDAY, volaffiche.ORG_AIR, volaffiche.DEST_AIR);
									printf("%d %f %f %d %d ", volaffiche.SCHED_DEP, volaffiche.DEP_DELAY, volaffiche.AIR_TIME, volaffiche.DIST, volaffiche.SCHED_ARR);
									printf("%f %d %d \n", volaffiche.ARR_DELAY, volaffiche.DIVERTED, volaffiche.CANCELLED);
									cpt_vol--;
									cpt_chaine++;
								}
								if (cpt_vol == 0)
								{
									return;
								}
							}
							else if (time != NULL)
							{
								if (volaffiche.SCHED_DEP == time)
								{
									printf("%d %d %d %s %s ", volaffiche.DAY, volaffiche.MONTH, volaffiche.WEEKDAY, volaffiche.ORG_AIR, volaffiche.DEST_AIR);
									printf("%d %f %f %d %d ", volaffiche.SCHED_DEP, volaffiche.DEP_DELAY, volaffiche.AIR_TIME, volaffiche.DIST, volaffiche.SCHED_ARR);
									printf("%f %d %d \n", volaffiche.ARR_DELAY, volaffiche.DIVERTED, volaffiche.CANCELLED);
									cpt_chaine++;
								}
							}
							else
							{
								printf("%d %d %d %s %s ", volaffiche.DAY, volaffiche.MONTH, volaffiche.WEEKDAY, volaffiche.ORG_AIR, volaffiche.DEST_AIR);
								printf("%d %f %f %d %d ", volaffiche.SCHED_DEP, volaffiche.DEP_DELAY, volaffiche.AIR_TIME, volaffiche.DIST, volaffiche.SCHED_ARR);
								printf("%f %d %d \n", volaffiche.ARR_DELAY, volaffiche.DIVERTED, volaffiche.CANCELLED);
								cpt_chaine++;
							}
						}
						else //si non si on a deja fait le debut de la chaine (qui est trier alors on change de compagnie
						{
							if (cpt_chaine != 0)
							{
								stop_while == 1;
							}

						}
						Buffdate = Buffdate->vol_suiv;
					}

					Buffcomp = Buffcomp->compagnie_suiv;
				}
			}
		}
		else
		{
			//recherche si le suivant airport est le bon  
			Buffairport = Buffairport->airport_suiv;
		}

	}
	printf("l'aeroport n'existe pas fin du programme.");
}