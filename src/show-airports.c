#include <init.h>

void show_airports(char IATA_CODE_c[SIZE_airline_acro], struct cellule_airport Htable_airport[max_Hairport])
{
	//Hcode

	int Hcode;
	int cpt_airport;
	struct cellule_airport* Buff;
	struct compagnie* Buffcomp;

	Hcode = //fonction hcode_airline

	// parcours de la Htable des airports
		printf("aeroport dans la quelle opere cette compagnie : ");
	for (cpt_airport = 0; cpt_airport <= max_Hairport; cpt_airport++)
	{
		// parcours de la liste chainer des airports
		Buff = &Htable_airport[cpt_airport];
		while (Buff != NULL)
		{
			//recherche dans la table de h des compagnie
			Buffcomp = &(Buff->pt_Htable_compagnie[Hcode]);
			if (Buffcomp != NULL)
			{
				//parcorus dans la liste chainer des compagnies
				while (Buffcomp != NULL)
				{
					if (strcmp(IATA_CODE_c, (Buffcomp->IATA_CODE)) == 0)
					{
						printf("%s, %s, %s, %s", Buff->airport.IATA_CODE, Buff->airport.AIRPORT, Buff->airport.CITY, Buff->airport.CITY);
					}
					else // si ce n'est pas la bonne compagnie on continue de rechercher 
					{
						Buffcomp = Buffcomp->compagnie_suiv;
					}
				}

			}
			// si non cette compagnie n'est pas dans l'aeroport 
			Buff = Buff->airport_suiv;
		}
	}
}

