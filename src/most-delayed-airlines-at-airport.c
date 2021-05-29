
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_acronym 4
#define SIZE_city 50
#define SIZE_airport 100
#define SIZE_airline 50
#define SIZE_airline_acro 3
#define SIZE_state 3

#define max_Hairport 375
#define max_Hcomp 70
#define max_Hdatacomp 1296 //36*36 possibilité
#define max_Hdate 12 
#define max_Hdataairport 17576 //26*26*26 possibilité

// Table airport

struct airport {
	char IATA_CODE[SIZE_acronym];
	char AIRPORT[SIZE_airport];
	char CITY[SIZE_city];
	char STATE[SIZE_state];
	char COUNTRY[SIZE_acronym];
	float LATITUDE;
	float LONGITUDE;
};

struct cellule_airport {
	struct airport data;
	struct cellule_compagnie* pt_Htable_compagnie[max_Hcomp];
	struct cellule_airport* airport_suiv;
	int is_empty;
};

typedef struct cellule_airport Htable_airport[max_Hairport];

//Table compagnie

struct cellule_compagnie {
	char IATA_CODE[SIZE_airline_acro];// nous avons choisie de garder la compagnie ici et pas de poitneur car trois octet vs 8
	struct cellule_vol_date* pt_Htable_date[max_Hdate];
	struct cellule_compagnie* compagnie_suiv;
};

//Table des données des compagnie

struct cellule_compagnieDATA {
	char IATA_CODE[SIZE_airline_acro];
	char AIRLINE[SIZE_airline];
	struct cellule_compagnieDATA* compagnie_suiv;
};

//Table des données des airports

struct cellule_airportDATA {
	struct airport data;
	struct cellule_airportDATA* suiv;
};

//Table date 

struct vol {

	int MONTH;
	int DAY;
	int WEEKDAY;
	char ORG_AIR[SIZE_acronym];
	char DEST_AIR[SIZE_acronym];
	int SCHED_DEP;
	float DEP_DELAY;
	float AIR_TIME;
	int DIST;
	int SCHED_ARR;
	float ARR_DELAY;
	short DIVERTED;
	short CANCELLED;

};

struct cellule_vol_date
{
	struct vol vol;
	struct cellule_vol_date* vol_suiv;
};









#define maxdelayedcomp 3

struct cellule_comp {
	float retardtotal;
	int nbvol;
	float moyenne;
};

struct liste {
	int maxIATA[maxdelayedcomp];
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

void ajout_moyenne(struct cellule_comp tablecomp[max_Hdatacomp], struct vol vol, int index)
{
	tablecomp[index].nbvol++;
	tablecomp[index].retardtotal += vol.ARR_DELAY;
}


void afficheliste(struct liste* lc, struct cellule_comp tablecomp[max_Hdatacomp], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp])
{
	int cpt = lc->dernier;
	int index;
	while (cpt >= 0)
	{
		index = lc->maxIATA[cpt];
		printf("%s %s  retard moyen :%f", NAMEcomp[index].IATA_CODE, NAMEcomp[index].AIRLINE, tablecomp[index].moyenne);
	}

}


void affichemax(struct cellule_comp tablecomp[max_Hdatacomp], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp])
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
		if (lmax.dernier < maxdelayedcomp)
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
		while (cpt < maxdelayedcomp)
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

void show_most_delayed_flights(struct cellule_airport* Htable_airport[max_Hairport], struct cellule_compagnieDATA NAMEcomp[max_Hdatacomp], IATA_CODE[SIZE_acronym])
{

	int cpt_airport, cpt_airline, cpt_date, indexcomp;
	struct cellule_comp tablecomp[max_Hdatacomp];
	struct cellule_airport* Buffairport;
	struct cellule_compagnie* Buffcomp;
	struct cellule_vol_date* Buffvol;

	Hcode = get_hash_index_airport(IATA_CODE,375)

	//initialisation du tableau 
	init_table(tablecomp);

	printf("Voici les 3 compagnies qui on subis le plus longs retard moyen a l'arrivé dans l'aeroport demander: \n");

	// parcours de la liste chainer des airports
	Buffairport = Htable_airport[Hocode];

	while (Buffairport->IATA_CODE != IATA_CODE || Buffairport != NULL)
	{
		Buffairport = Buffairport->airport_suiv;
	}
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
	affichemax(tablecomp, NAMEcomp);
}
