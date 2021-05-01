void show_airlines(char IATA_CODE_c[SIZE_airport], struct cellule_airport Htable_airport[max_Hairport], struct IATA_AIRLINE Htable_name_compagnie[max_Hcomp])
{
	int Hcode, cpt_airline, Hcode_name_airline;
	Hcode = 4;//fonction hcode_airport
	char* IATA_comp;
	struct cellule_airport* Buffairport;
	struct compagnie* Buffcomp;
	struct IATA_AIRLINE* Buffnamecomp;
	//recherche dans la table de hachage de l'aeroport .
	Buffairport = &Htable_airport[Hcode];
	//recherche dans la liste chainer des airport 
	printf("recherche des compagnie associer a l'aeroport en cours :");
	while (Buffairport != NULL)
	{
		// si on a trouver l'aeroport rechercher
		if (strcmp(IATA_CODE_c, (Buffairport->airport.IATA_CODE)) == 0)
		{
			//parcours de la Htable des compagnie
			for (cpt_airline = 0; cpt_airline <= max_Hcomp; cpt_airline++)
			{
				Buffcomp = &(Buffairport->pt_Htable_compagnie[cpt_airline]);
				//parcorus dans la liste chainer des compagnies

				while (Buffcomp != NULL)
				{
					IATA_comp = Buffcomp->IATA_CODE;
					Hcode_name_airline = 5; //fonction hcode_name_airline 
					//parcours de la liste chainer des nom des conpagnie

					Buffnamecomp = &(Htable_name_compagnie[Hcode_name_airline]);
					while (strcmp(Buffnamecomp->IATA_CODE, IATA_comp))
					{
						Buffnamecomp = Buffnamecomp->compagnie_suiv;
					}

					//affichage du code + nom
					printf("%s, %s \n", IATA_comp, Buffnamecomp->IATA_CODE);
					Buffcomp = Buffcomp->compagnie_suiv;
				}
			}
			return;//arret du while car bonne airport
		}
		else
		{
			//recherche du suivant 
			Buffairport = Buffairport->airport_suiv;
		}

	}
	printf("l'aeroport n'existe pas fin du programme.")

}