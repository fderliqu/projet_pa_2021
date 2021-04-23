#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_acronym 3
#define SIZE_city 30
#define SIZE_airport 100
#define SIZE_airline 50
#define SIZE_airline_acro 2

#define max_Hairport 78
#define max_Hcomp 52
#define max_Hdate 365


struct airport {
	char IATA_CODE[SIZE_acronym];
	char AIRPORT[SIZE_airport];
	char CITY[SIZE_city];
	char STATE[SIZE_city];
	char COUNTRY[SIZE_acronym];
	float LATITUDE;
	float LONGITUDE;
};

struct cellule_airport {
	struct airport airport;
	struct compagnie* pt_comp;
	struct airport* airport_suiv;
};


struct cellule_airport Htable_airport[max_Hairport];



struct IATA_AIRLINE {
	char IATA_CODE[SIZE_airline_acro];
	char AIRLINE[SIZE_airline];
	struct IATA_AIRLINE* iata_suiv;
};



struct compagnie {
	char IATA_CODE[SIZE_airline_acro];// nous avons choisie de garder la compagnie ici et pas de poitneur car trois octet vs 8
	struct vol* pt_vol;
	struct compagnie* compagnie_suiv;
};

struct compagnie Htable_compagnie[max_Hcomp];


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

struct cellule_vol
{
	struct vol vol;
	struct vol *vol_suiv;
};

struct vol Htable_vol[max_Hdate];
