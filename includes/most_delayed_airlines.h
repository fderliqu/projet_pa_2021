#define maxmost_delayed_airlines 5
#define maxmostat 3

struct cellule_comp_most
{
    float retardtotal;
    float nbvol;
    float moyenne;
};

struct liste_most_airline
{
    int maxIATA[maxmost_delayed_airlines];
    int dernier;
};

struct liste_most_airline_at_airport
{
    int maxIATA[maxmostat];
    int dernier;
};
