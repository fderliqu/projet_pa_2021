#define maxmostflights 5

struct liste
{
    struct vol volaffiche[maxmostflights];
    int dernier;
};

void afficheliste (struct liste *);

void most_delay (struct liste *, struct vol);

void show_most_delayed_flights (struct cellule_airport **);