#include "../includes/init.h"
#include "../includes/most_delayed_airlines.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/condition_function.h"
#include "../includes/hash_algo.h"

void init_table_most (struct cellule_comp_most tablecomp[max_Hdatacomp])
{
    int cpt = 0;
    while (cpt != max_Hdatacomp)
    {
        tablecomp[cpt].nbvol       = -1;
        tablecomp[cpt].retardtotal = 0;
        cpt++;
    }
}

void ajout_moyenne (struct cellule_comp_most tablecomp[max_Hdatacomp], struct vol vol, int index)
{
    tablecomp[index].nbvol++;
    tablecomp[index].retardtotal += vol.ARR_DELAY;
}


void afficheliste_airlines_moy (struct liste_most_airline *   lc,
                                struct cellule_comp_most      tablecomp[max_Hdatacomp],
                                struct cellule_compagnieDATA *NAMEcomp[max_Hdatacomp])
{
    int cpt = lc->dernier;
    int index;
    while (cpt >= 0)
    {
        index = lc->maxIATA[cpt];
        printf ("%s %s  retard moyen :%f \n", NAMEcomp[index]->IATA_CODE, NAMEcomp[index]->AIRLINE,
                tablecomp[index].moyenne);
        cpt--;
    }
}


void affichemax (struct liste_most_airline *lmax, struct cellule_comp_most tablecomp[max_Hdatacomp], int cpttab, int max_lenght)
{
    int buff, buff2, cpt;
    cpt = 0;

    tablecomp[cpttab].moyenne = (tablecomp[cpttab].retardtotal / (tablecomp[cpttab].nbvol + 1));
    // printf("tablcomp moyenne %f  \n", tablecomp[cpttab].moyenne);
    // printf("dernier %d  \n", lmax->dernier);
    // initialisation de la liste
    if (lmax->dernier < max_lenght - 1)
    {
        lmax->dernier++;

        if (tablecomp[cpttab].moyenne > tablecomp[lmax->maxIATA[(lmax->dernier) - 1]].moyenne)
        {
            lmax->maxIATA[lmax->dernier] = cpttab;
        }
        while (cpt < lmax->dernier)
        {

            if (tablecomp[cpttab].moyenne < tablecomp[lmax->maxIATA[cpt]].moyenne)
            {
                buff               = lmax->maxIATA[cpt];
                lmax->maxIATA[cpt] = cpttab;
                cpt++;
                while (cpt <= lmax->dernier)
                {
                    lmax->maxIATA[lmax->dernier] = lmax->maxIATA[cpt];
                    lmax->maxIATA[cpt]           = buff;
                    buff                         = lmax->maxIATA[lmax->dernier];
                    cpt++;
                }
            }
            cpt++;
        }
        if (lmax->dernier == 0)
        {
            lmax->maxIATA[lmax->dernier] = cpttab;
        }
        return;
    }
    if (tablecomp[cpttab].moyenne < tablecomp[lmax->maxIATA[0]].moyenne)
    {
        return;
    }
    // parcours de la liste
    cpt = 1;
    while (cpt < max_lenght)
    {
        if (tablecomp[cpttab].moyenne < tablecomp[lmax->maxIATA[cpt]].moyenne)
        {
            break;
        }
        cpt++;
    }
    // modification de la liste
    buff                   = lmax->maxIATA[cpt - 1];
    lmax->maxIATA[cpt - 1] = cpttab;
    cpt                    = cpt - 2;

    while (cpt >= 0)
    {
        buff2              = lmax->maxIATA[cpt];
        lmax->maxIATA[cpt] = buff;
        buff               = buff2;
        cpt--;
    }
}

void show_most_delayed_airline (struct cellule_airport *      Htable_airport[max_Hairport],
                                struct cellule_compagnieDATA *NAMEcomp[max_Hdatacomp])
{

    int                       cpt_airport, cpt_airline, cpt_date, indexcomp, cpttab;
    struct cellule_comp_most  tablecomp[max_Hdatacomp];
    struct cellule_airport *  Buffairport;
    struct cellule_compagnie *Buffcomp;
    struct cellule_vol_date * Buffvol;

    struct liste_most_airline lmax;
    lmax.dernier = -1;

    // initialisation du tableau
    init_table_most (tablecomp);

    printf ("Voici les 5 compagnie qui on subis le plus longs retard moyen a l'arrivee : \n");
    // parcours des airport
    for (cpt_airport = 0; cpt_airport < max_Hairport; cpt_airport++)
    {
        // parcours de la liste chainer des airports
        Buffairport = Htable_airport[cpt_airport];
        while (Buffairport != NULL)
        {
            if (Buffairport->is_empty != 1)
            {
                // parcours de la Htable des compagnie
                for (cpt_airline = 0; cpt_airline < max_Hcomp; cpt_airline++)
                {
                    Buffcomp = Buffairport->pt_Htable_compagnie[cpt_airline];
                    // parcours de la liste chainer des compagnie
                    while (Buffcomp != NULL)
                    {
                        // parcours des vols
                        indexcomp = get_hash_index_airline (Buffcomp->IATA_CODE, max_Hdatacomp);
                        for (cpt_date = 0; cpt_date < max_Hdate; cpt_date++)
                        {
                            Buffvol = Buffcomp->pt_Htable_date[cpt_date];

                            while (Buffvol != NULL)
                            {
                                if (Buffvol->vol.CANCELLED != 1 && Buffvol->vol.DIVERTED != 1)
                                {
                                    if (Buffvol->vol.ARR_DELAY > 0)
                                    {
                                        ajout_moyenne (tablecomp, Buffvol->vol, indexcomp);
                                    }
                                }
                                Buffvol = Buffvol->vol_suiv;
                            }
                        }
                        Buffcomp = Buffcomp->compagnie_suiv;
                    }
                }
            }
            Buffairport = Buffairport->airport_suiv;
        }
    }
    cpttab = 0;
    while (cpttab < max_Hdatacomp)
    {
        // printf("cpttab= %d \n", cpttab);
        // printf(" nb vol %d \n", tablecomp[cpttab].nbvol);
        if (tablecomp[cpttab].nbvol != -1)
        {
            affichemax (&lmax, tablecomp, cpttab, maxmost_delayed_airlines);
            // afficheliste(&lmax, tablecomp, NAMEcomp);
            // printf("----------------------------\n");
        }
        cpttab++;
    }
    afficheliste_airlines_moy (&lmax, tablecomp, NAMEcomp);
}

void init_most_delayed_airlines (struct line_arguments         liste,
                                 struct cellule_airport *      main_HT[max_Hairport],
                                 struct cellule_compagnieDATA *data_HT[max_Hdatacomp])
{
    if (number_parameter_test (liste, nb_arg_most_delayed_airline, 0) == 0) return;
    show_most_delayed_airline (main_HT, data_HT);
}
