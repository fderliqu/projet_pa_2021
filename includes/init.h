#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_acronym 3
#define SIZE_city 30
#define SIZE_airport 100
#define SIZE_airline 50
#define SIZE_airline_acro 2

#define max_Hairport 375
#define max_Hcomp 52
#define max_Hnamecomp 2626 //premier lettre + 2eme *100
#define max_Hdate 12 

// Table airport

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
	struct compagnie pt_Htable_compagnie[max_Hcomp];
	struct cellule_airport* airport_suiv;
};

typedef struct cellule_airport Htable_airport[max_Hairport];


//IATA_AIRLINE

//table de hachage ici 


struct IATA_AIRLINE {
	char IATA_CODE[SIZE_airline_acro];
	char AIRLINE[SIZE_airline];
	struct IATA_AIRLINE *compagnie_suiv;
};


struct IATA_AIRLINE Htable_name_compagnie[max_Hcomp];

//Table compagnie

struct compagnie {
	char IATA_CODE[SIZE_airline_acro];// nous avons choisie de garder la compagnie ici et pas de poitneur car trois octet vs 8
	struct cellule_vol_date pt_Htable_date[max_Hdate];
	struct compagnie* compagnie_suiv;
};

struct compagnie Htable_compagnie[max_Hcomp];



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

struct cellule_vol_date Htable_date[max_Hdate];
