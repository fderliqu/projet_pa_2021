#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct airports{ 
	char IATA_CODE;
	char AIRPORT;
	char CITY;
	char STATE;
	char COUNTRY;
	char LATITUDE;
	char LONGITUDE;
	struct compagnie *pt_comp;
}

struct IATA_AIRLINE
{
	char IATA_CODE;
	char AIRLINE;

}

struct compagnie
{
	char AIRLINE;
	struct vol *pt_vol;
}

struct vol
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
