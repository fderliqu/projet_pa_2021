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
	struct cellule_compagnieDATA *compagnie_suiv;
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

//struct cellule_vol_date* Htable_date[max_Hdate];
