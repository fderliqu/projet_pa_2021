

#define max 5

struct cellule_comp {
	float retardtotal;
	int nbvol;
	float moyenne;
};

struct liste {
	int maxIATA[max];
	int dernier;
};

void init_table(struct cellule_comp tablecomp[max_Hdatacomp])
{
	int cpt = 0;
	while (cpt != max_Hdatacomp)
	{
		tablecomp[cpt].nbvol = 0;
		tablecomp[cpt].retardtotal = 0;
		cpt++;
	}
}

void ajout_moyenne(struct cellule_comp tablecomp[max_Hdatacomp],struct vol vol,int index)
{
	tablecomp[index].nbvol++;
	tablecomp[index].retardtotal += vol.ARR_DELAY;
}


void afficheliste(struct liste *lc, struct cellule_comp tablecomp[max_Hdatacomp], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp])
{
	int cpt = lc->dernier;
	int index;
	while (cpt >= 0)
	{
		index=lc->maxIATA[cpt];
		printf("%s %s  retard moyen :%f", NAMEcomp[index].IATA_CODE, NAMEcomp[index].AIRLINE, tablecomp[index].moyenne);
	}

}


void affichemax5(struct cellule_comp tablecomp[max_Hdatacomp], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp])
{
	int buff, buff2, cpttab, cpt;
	cpttab = 0;
	cpt = 0;
	struct liste lmax;
	lmax.dernier = -1;

	while (cpttab != max_Hdatacomp)
	{
		tablecomp[cpttab].moyenne = (tablecomp[cpttab].retardtotal / tablecomp[cpttab].nbvol);


		//initialisation de la liste
		if (lmax.dernier < max)
		{
			lmax.dernier++;
			while (cpt < lmax.dernier - 1)
			{
				if (tablecomp[cpttab].moyenne > tablecomp[lmax.maxIATA[(lmax.dernier) - 1]].moyenne)
				{
					lmax.maxIATA[lmax.dernier] = cpttab;
				}
				else if (tablecomp[cpttab].moyenne < tablecomp[lmax.maxIATA[cpt]].moyenne)
				{
					buff = lmax.maxIATA[cpt];
					lmax.maxIATA[cpt] = cpttab;
				}
				else
				{
					lmax.maxIATA[lmax.dernier] = lmax.maxIATA[cpt];
					lmax.maxIATA[cpt] = buff;
					buff = lmax.maxIATA[lmax.dernier];
				}
				cpt++;
			}
			if (lmax.dernier == 0)
			{
				lmax.maxIATA[lmax.dernier] = cpttab;
			}
			return;
		}

		if (tablecomp[cpttab].moyenne < tablecomp[lmax.maxIATA[0]].moyenne) { return; }
		//parcours de la liste
		cpt = 1;
		while (cpt < max)
		{
			if (tablecomp[cpttab].moyenne < tablecomp[lmax.maxIATA[cpt]].moyenne) { break; }
			cpt++;
		}
		//modification de la liste 
		buff = lmax.maxIATA[cpt - 1];
		lmax.maxIATA[cpt - 1] = cpttab;
		cpt--;

		while (cpt >= 0)
		{
			buff2 = lmax.maxIATA[cpt];
			lmax.maxIATA[cpt] = buff;
			buff = buff2;
			cpt--;
		}
		cpttab++;
	}
	afficheliste(&lmax, tablecomp, NAMEcomp);
}

void show_most_delayed_flights(struct cellule_airport *Htable_airport[max_Hairport], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp])
{

	int cpt_airport, cpt_airline, cpt_date, indexcomp;
	struct cellule_comp tablecomp[max_Hdatacomp];
	struct cellule_airport* Buffairport;
	struct cellule_compagnie* Buffcomp;
	struct cellule_vol_date* Buffvol;

	//initialisation du tableau 
	init_table(tablecomp);

	printf("Voici les 5 compagnie qui on subis le plus longs retard moyen a l'arrivé : \n");
	//parcours des airport
	for (cpt_airport = 0; cpt_airport <= max_Hairport; cpt_airport++)
	{
		// parcours de la liste chainer des airports
		Buffairport = Htable_airport[cpt_airport];
		while (Buffairport != NULL)
		{
			//parcours de la Htable des compagnie
			for (cpt_airline = 0; cpt_airline <= max_Hcomp; cpt_airline++)
			{
				Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
				//parcours de la liste chainer des compagnie
				while (Buffcomp != NULL)
				{
					//parcours des vols
					for (cpt_date = 0; cpt_date <= max_Hdate; cpt_date++)
					{
						Buffvol = Buffcomp->pt_Htable_date[cpt_date];
						indexcomp = get_hash_index_airline(Buffcomp->IATA_CODE, 1);

						while (Buffvol != NULL)
						{
							ajout_moyenne(tablecomp, Buffvol->vol, indexcomp);
							Buffvol = Buffvol->vol_suiv;
						}

					}
					Buffcomp = Buffcomp->compagnie_suiv;
				}
			}
			Buffairport = Buffairport->airport_suiv;
		}
	}
	affichemax5(tablecomp,NAMEcomp);
}
