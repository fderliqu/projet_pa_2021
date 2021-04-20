#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Struct airports{ 
	char IATA_CODE;
	char AIRPORT;
	char CITY;
	char STATE;
	char COUNTRY;
	char LATITUDE;
	char LONGITUDE;
	struct compagnie *pt_comp;
}

Struct IATA_AIRLINE
{
	char IATA_CODE;
	char AIRLINE;

}

Struct compagnie
{
	char AIRLINE;
	struct vol* pt_vol;
}

Struct vol
{

char MONTH;
char DAY;
char WEEKDAY;
char ORG_AIR;
char DEST_AIR;
char SCHED_DEP;
char DEP_DELAY;
char AIR_TIME;
char DIST;
char SCHED_ARR;
char ARR_DELAY;
char DIVERTED;
char CANCELLED;

}
