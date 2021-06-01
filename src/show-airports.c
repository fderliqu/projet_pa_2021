#include "../includes/init.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/condition_function.h"
#include "../includes/hash_algo.h"
#include "../includes/show-airport.h"

void print_show_airport (struct cellule_airportDATA *HT[sizeHT])
{
    struct cellule_airportDATA *tmp;
    int                         compt = 0;
    for (int i = 0; i < sizeHT; i++)
    {
        tmp = HT[i];
        while (tmp != NULL)
        {
            compt++;
            printf ("%s,%s,%s,%s,%s\n", tmp->data.IATA_CODE, tmp->data.AIRPORT, tmp->data.CITY,
                    tmp->data.STATE, tmp->data.COUNTRY);
            tmp = tmp->suiv;
        }
    }
    if (compt == 0)
        printf (
        "No flight found, The airline does not exist or the airline does not operate any flight\n");
}

void show_airport (struct cellule_airport *main_HT[max_Hairport], char AIRLINE[SIZE_airline_acro])
{
    struct cellule_airport *    Buffairport;
    struct cellule_compagnie *  Buffairline;
    struct cellule_vol_date *   Buffvol;
    struct cellule_airportDATA *show_airport_HT[sizeHT];
    struct airport              org_air;
    struct airport              dest_air;
    int                         indexHTairline, indexHTshow_airport;
    init_ht_dataairport (show_airport_HT, sizeHT);
    // Parcourt de la tables des aéroports puisque aéroport non en parametre
    for (int i = 0; i < max_Hairport; i++)
    {
        Buffairport = main_HT[i];
        while (Buffairport != NULL)
        {
            // Check si l'aéroport est un aéroport de départ
            if (Buffairport->is_empty != 1)
            {
                // Comme airline en parametre, on cherche l'index, et on pointe directement sur la bonne cellule
                indexHTairline = get_hash_index_airline (AIRLINE, max_Hcomp);
                Buffairline =
                recherche_cellHT_compagnie (Buffairport->pt_Htable_compagnie[indexHTairline], AIRLINE);
                if (Buffairline != NULL)
                {
                    // Parcourt de la tables des mois puisque mois non en parametre
                    for (int j = 0; j < max_Hdate; j++)
                    {
                        Buffvol = Buffairline->pt_Htable_date[j];
                        while (Buffvol != NULL)
                        {
                            // Stock org_air et dest_air de la cellule pointé
                            org_air =
                            recherche_cellHT_airport (main_HT[get_hash_index_airport (Buffvol->vol.ORG_AIR, max_Hairport)],
                                                      Buffvol->vol.ORG_AIR)
                            ->data;
                            dest_air =
                            recherche_cellHT_airport (main_HT[get_hash_index_airport (Buffvol->vol.DEST_AIR, max_Hairport)],
                                                      Buffvol->vol.DEST_AIR)
                            ->data;
                            // But : On cherche dans la table de hash crée au début, si nous avons déja rencontré l'aéroport (si il est dedans)
                            indexHTshow_airport = get_hash_index_airport (org_air.IATA_CODE, sizeHT);
                            if (recherche_cell_airport (show_airport_HT[indexHTshow_airport],
                                                        org_air.IATA_CODE) == NULL)
                            {
                                ajout_airport (&(show_airport_HT[indexHTshow_airport]), org_air);
                            }
                            indexHTshow_airport = get_hash_index_airport (dest_air.IATA_CODE, sizeHT);
                            if (recherche_cell_airport (show_airport_HT[indexHTshow_airport],
                                                        dest_air.IATA_CODE) == NULL)
                            {
                                ajout_airport (&(show_airport_HT[indexHTshow_airport]), dest_air);
                            }
                            Buffvol = Buffvol->vol_suiv;
                        }
                    }
                }
            }
            Buffairport = Buffairport->airport_suiv;
        }
    }
    // Print de fin
    print_show_airport (show_airport_HT);
    // On libère la table temporaire crée au début
    desaloc_ht_dataairport (show_airport_HT, sizeHT);
}

void init_show_airport (struct line_arguments liste, struct cellule_airport *main_HT[max_Hairport])
{
    int test;
    // Conditions de lancement
    test = number_parameter_test (liste, nb_arg_show_airport, 0);
    if (test == 0) return;
    test = lenght_parameter_test (liste, SIZE_airline_acro - 1, 1);
    if (test == 0) return;
    // Lancement
    show_airport (main_HT, liste.arg[1]);
}
