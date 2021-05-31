#define maxmostflights 5

struct vol_IATA
{
    struct vol vol;
    char       IATA_AIRLINE[SIZE_airline_acro];
};

struct liste_delayed_flights
{
    struct vol_IATA volaffiche[maxmostflights];
    int             dernier;
};

void affichelisteflights(struct liste_delayed_flights*);

void show_most_delayed_flights (struct cellule_airport **,int);