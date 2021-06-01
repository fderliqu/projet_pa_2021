#include "../includes/init.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/hash_algo.h"
#include "../includes/main_function.h"
#include "../includes/quit.h"


int main ()
{
    struct cellule_airport *      HT[max_Hairport];
    struct cellule_compagnieDATA *HTalData[max_Hdatacomp];
    struct cellule_airportDATA 	*ht_apDATA[max_Hdataairport];
    const char *                  separators = " \n";
    char *                        ligne      = NULL;
    size_t                        n          = 0;
    struct line_arguments         liste;
    char *                        fichier1 = "../data/airports.csv";
    char *                        fichier2 = "../data/flights.csv";
    char *                        fichier3 = "../data/airlines.csv";
    liste.dernier                          = -1;
    int fin                                = 0;
	//init table
    init_ht_airport (HT);
    init_ht_dataairport (ht_apDATA, max_Hdataairport);
    init_ht_datacomp (HTalData, max_Hdatacomp);
	//charge
    if (charge_dataAirport (ht_apDATA, fichier1) == 0) return 0;
    if (charge_vol (HT, ht_apDATA,fichier2) == 0) return 0;
    if (charge_dataCompagnie (HTalData, fichier3) == 0) return 0;
	//debut
    printf (">");
    while (getline (&ligne, &n, stdin) != -1)
    {
        printf ("%s\n", ligne);
        liste.dernier++;
        liste.arg[liste.dernier] = strtok (ligne, separators);
        while (liste.arg[liste.dernier] != NULL)
        {
            liste.dernier++;
            liste.arg[liste.dernier] = strtok (NULL, separators);
        }
        liste.dernier--;
        if (strcmp (liste.arg[0], "quit") == 0) fin = 1;
        launch_function (liste, HT, HTalData, ht_apDATA);
        if (fin == 1)
        {
            free (ligne);
            return 0;
        }
        liste.dernier = -1;
        printf ("\n");
        printf (">");
    }
    quit (HT, HTalData, ht_apDATA);
    free (ligne);
}
