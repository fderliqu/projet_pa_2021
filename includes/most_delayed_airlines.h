#define maxmost_delayed_airlines 5
#define maxmostat 3
#define nb_arg_most_delayed_airline 0

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

void init_most_delayed_airlines(struct line_arguments, struct cellule_airport**,struct cellule_compagnieDATA**);

//Fct utile pour most_delayed_airlines-airlines-id
void init_table_most(struct cellule_comp_most*);

void ajout_moyenne(struct cellule_comp_most*, struct vol, int);

void afficheliste_airlines_moy(struct liste_most_airline*, struct cellule_comp_most*, struct cellule_compagnieDATA**);

void affichemax(struct liste_most_airline*, struct cellule_comp_most*, int, int);



