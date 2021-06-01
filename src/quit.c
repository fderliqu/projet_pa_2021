#include "../includes/init.h"
#include "../includes/quit.h"
#include "../includes/condition_function.h"
#include "../includes/hash_algo.h"

void quit (struct cellule_airport *HT_main[max_Hairport], struct cellule_compagnieDATA *HT_data[max_Hdatacomp], struct cellule_airportDATA *ht_apDATA[max_Hdataairport])
{
    int                       cpt_airport, cpt_airline;
    struct cellule_airport *  Buffairport, *Buffairportsuiv;
    struct cellule_compagnie *Buffcomp, *Buffcompsuiv;
    for (cpt_airport = 0; cpt_airport < max_Hairport; cpt_airport++)
    {
        Buffairport = HT_main[cpt_airport];
        while (Buffairport != NULL)
        {
            if (Buffairport != NULL) Buffairportsuiv = Buffairport->airport_suiv;
            if (Buffairport->is_empty == 0)
            {
                for (cpt_airline = 0; cpt_airline < max_Hcomp; cpt_airline++)
                {
                    Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
                    while (Buffcomp != NULL)
                    {
                        if (Buffcomp != NULL) Buffcompsuiv = Buffcomp->compagnie_suiv;
                        desaloc_ht_vol (Buffcomp->pt_Htable_date);
                        Buffcomp = Buffcompsuiv;
                    }
                }
                desaloc_ht_airline (Buffairport->pt_Htable_compagnie);
            }
            Buffairport = Buffairportsuiv;
        }
    }
    desaloc_ht_airport (HT_main);
    desaloc_ht_dataairline (HT_data, max_Hdatacomp);
    desaloc_ht_dataairport (ht_apDATA, max_Hdataairport);
    printf ("All data is cleared, end of the function\n");
}
