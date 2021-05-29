#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/show-airport.h"
#define sizeHT 100

void print_show_airport(struct cellule_airportDATA *HT[sizeHT])
{
    struct cellule_airportDATA *tmp;
    for(int i=0;i<sizeHT;i++)
    {
        tmp = HT[i];
        while(tmp != NULL)
        {
            printf("%s,%s,%s,%s,%s\n",tmp->data.IATA_CODE, tmp->data.AIRPORT, tmp->data.CITY, tmp->data.STATE, tmp->data.COUNTRY);
            tmp = tmp->suiv;
        }
    }
}

void show_airport(struct cellule_airport* main_HT[max_Hairport], char AIRLINE[SIZE_airline_acro])
{
    struct cellule_airport* Buffairport;
    struct cellule_compagnie* Buffairline;
    struct cellule_vol_date* Buffvol;
    struct cellule_airportDATA *show_airport_HT[sizeHT];
    struct airport org_air;
    struct airport dest_air;
    int indexHTairline, indexHTshow_airport;
    init_ht_dataairport(show_airport_HT,sizeHT);
    for(int i=0;i<max_Hairport;i++)
    {
        Buffairport = main_HT[i];
        while(Buffairport != NULL)
        {
            if(Buffairport->is_empty != 1)
            {
                indexHTairline = get_hash_index_airline(AIRLINE,max_Hcomp);
                Buffairline = recherche_cellHT_compagnie( Buffairport->pt_Htable_compagnie[ indexHTairline ], AIRLINE );
                if(Buffairline != NULL)
                {
                    for(int j=0;j<max_Hdate;j++)
                    {
                        Buffvol = Buffairline->pt_Htable_date[j];
                        while(Buffvol!=NULL)
                        {
                            org_air = recherche_cellHT_airport(main_HT[ get_hash_index_airport(Buffvol->vol.ORG_AIR, max_Hairport) ],Buffvol->vol.ORG_AIR)->data;
                            dest_air = recherche_cellHT_airport(main_HT[ get_hash_index_airport(Buffvol->vol.DEST_AIR, max_Hairport) ],Buffvol->vol.DEST_AIR)->data;
                            indexHTshow_airport = get_hash_index_airport(org_air.IATA_CODE, sizeHT);
                            if(recherche_cell_airport(show_airport_HT[ indexHTshow_airport ], org_air.IATA_CODE ) == NULL) {
                                ajout_airport(&(show_airport_HT[ indexHTshow_airport ]), org_air);
                            }
                            indexHTshow_airport = get_hash_index_airport(dest_air.IATA_CODE, sizeHT);
                            if(recherche_cell_airport(show_airport_HT[ indexHTshow_airport ], dest_air.IATA_CODE ) == NULL) {
                                ajout_airport(&(show_airport_HT[ indexHTshow_airport ]), dest_air);
                            }
                            Buffvol = Buffvol->vol_suiv;
                        }
                    }
                }
            }
            Buffairport = Buffairport->airport_suiv;
        }
    }
    print_show_airport(show_airport_HT);
    desaloc_ht_dataairport(show_airport_HT, sizeHT);
}


