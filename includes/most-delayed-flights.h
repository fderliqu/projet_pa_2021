#define maxmostflights 5
#define nb_arg_most_delayed_flights 0

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

void init_most_delayed_flights(struct line_arguments, struct cellule_airport**);