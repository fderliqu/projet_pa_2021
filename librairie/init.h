#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct airports {
	char IATA_CODE[];
	char AIRPORT[];
	char CITY[];
	char STATE[];
	char COUNTRY[];
	float LATITUDE[];
	float LONGITUDE[];
	struct compagnie* pt_comp;
	struct airports* airports_suiv;
}

struct IATA_AIRLINE
{
	char IATA_CODE[];
	char AIRLINE[];
	struct IATA_AIRLINE* iata_suiv;
}

struct compagnie
{
	char AIRLINE[];
	struct vol* pt_vol;
	struct compagnie* compagnie_suiv;
}

struct vol
{

	int MONTH;
	int DAY;
	int WEEKDAY;
	char ORG_AIR[];
	char DEST_AIR[];
	int SCHED_DEP[];
	float DEP_DELAY[];
	float AIR_TIME[];
	int DIST[];
	int SCHED_ARR[];
	float ARR_DELAY[];
	short DIVERTED[];
	short CANCELLED[];
	struct vol* vol_suiv;

}
