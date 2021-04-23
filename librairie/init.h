#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_acronym 3
#define SIZE_city 30
#define SIZE_airport 100
#define SIZE_airline 50
#define SIZE_airline_acro 2

struct airports {
	char IATA_CODE[SIZE_acronym];
	char AIRPORT[SIZE_airport];
	char CITY[SIZE_city];
	char STATE[SIZE_city];
	char COUNTRY[SIZE_acronym];
	float LATITUDE;
	float LONGITUDE;
	struct compagnie* pt_comp;
	struct airports* airports_suiv;
};

struct IATA_AIRLINE {
	char IATA_CODE[SIZE_acronym];
	char AIRLINE[SIZE_airline];
	struct IATA_AIRLINE* iata_suiv;
};

struct compagnie {
	char AIRLINE[SIZE_airline_acro];
	struct vol* pt_vol;
	struct compagnie* compagnie_suiv;
};

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
	struct vol* vol_suiv;

};
