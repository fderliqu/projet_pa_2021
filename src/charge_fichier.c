#include "../includes/init.h"
#include "../includes/charge_fichier.h"
#include "../includes/cell_function.h"
#include "../includes/hash_algo.h"

#define max_colonne 14
#define max_strtab_lenght 100

void my_strtok (char *str, char strtab[max_colonne][max_strtab_lenght])
{
    char c           = *str++;
    int  pos         = 0;
    int  emplacement = 0;
    while (c != '\0')
    {
        if (c == ',')
        {
            strtab[emplacement][pos] = '\0';
            emplacement++;
            pos = 0;
        }
        else
        {
            strtab[emplacement][pos] = c;
            pos++;
        }
        c = *str++;
    }
    strtab[emplacement][pos] = '\0';
}

void conversion_vol (char strtab[max_colonne][max_strtab_lenght], struct vol *PTvol)
{
    PTvol->MONTH   = (int)strtol (strtab[0], NULL, 10);
    PTvol->DAY     = (int)strtol (strtab[1], NULL, 10);
    PTvol->WEEKDAY = (int)strtol (strtab[2], NULL, 10);
    strcpy (PTvol->ORG_AIR, strtab[4]);
    strcpy (PTvol->DEST_AIR, strtab[5]);
    PTvol->SCHED_DEP = (int)strtol (strtab[6], NULL, 10);
    PTvol->DEP_DELAY = 0;
    PTvol->AIR_TIME  = -1.0;
    PTvol->DIST      = (int)strtol (strtab[9], NULL, 10);
    PTvol->SCHED_ARR = (int)strtol (strtab[10], NULL, 10);
    PTvol->ARR_DELAY = 0;
    PTvol->CANCELLED = (int)strtol (strtab[13], NULL, 10);
    PTvol->DIVERTED  = (int)strtol (strtab[12], NULL, 10);
    if (PTvol->CANCELLED == 0)
    {
        PTvol->DEP_DELAY = strtof (strtab[7], NULL);
    }
    if (PTvol->DIVERTED == 0 && PTvol->CANCELLED == 0)
    {
        PTvol->AIR_TIME  = strtof (strtab[8], NULL);
        PTvol->ARR_DELAY = strtof (strtab[11], NULL);
    }
}

void conversion_airport (char strtab[max_colonne][max_strtab_lenght], struct airport *PTairport)
{
    strcpy (PTairport->AIRPORT, strtab[0]);
    strcpy (PTairport->CITY, strtab[1]);
    strcpy (PTairport->STATE, strtab[2]);
    strcpy (PTairport->COUNTRY, strtab[3]);
    PTairport->LATITUDE  = strtof (strtab[4], NULL);
    PTairport->LONGITUDE = strtof (strtab[5], NULL);
}

int charge_dataAirport (struct cellule_airportDATA *ht_apData[max_Hdataairport], char *fichier)
{
    FILE *fd = fopen (fichier, "r");
    if (fd != NULL)
    {
        printf("fichier %s ouvert\n",fichier);
        char           tmp[200];
        char           strtab[max_colonne][max_strtab_lenght];
        struct airport airport;
        int            index;
        fscanf (fd, "%*[^\n]\n"); //on skip la première ligne
        while (fscanf (fd, "%[^,],", airport.IATA_CODE) == 1) //On prend jusqua ',' dans iata_code
        {
	  fscanf (fd, "%[^\n]\n", tmp); //On prend le reste
            my_strtok (tmp, strtab); //split des mots
            conversion_airport (strtab, &airport); //algo de conversion
            index = get_hash_index_airport (airport.IATA_CODE, max_Hdataairport); //index de la table
            ajout_airport (&(ht_apData[index]), airport); //ajout
        }
    }
    if (fd != NULL)
    {
        fclose (fd);
        return 1;
    }
    printf ("error changement de %s\n", fichier);
    return 0;
}

int charge_dataCompagnie (struct cellule_compagnieDATA *ht_alData[max_Hdatacomp], char *fichier)
{
    FILE *fd;
    fd = fopen (fichier, "r");
    if (fd != NULL)
    {
        printf("fichier %s ouvert\n",fichier);
        char IATA_CODE[SIZE_airline_acro];
        char AIRLINE[SIZE_airline];
        int  index;
        fscanf (fd, "%*[^\n]\n"); //On skip la premiere ligne
        while (fscanf (fd, "%[^,],", IATA_CODE) == 1) //On prend jusque ','
        {
	    fscanf (fd, "%[^\n]\n", AIRLINE); //On prend jusqu'a \n
            index = get_hash_index_airline (IATA_CODE, max_Hdatacomp);
            ajout_compagnie (&(ht_alData[index]), IATA_CODE, AIRLINE);
        }
    }
    if (fd != NULL)
    {
        fclose (fd);
        return 1;
    }
    printf ("error changement de %s", fichier);
    return 0;
}

int charge_vol (struct cellule_airport *ht_ap[max_Hairport], struct cellule_airportDATA *ht_apDATA[max_Hdataairport], char *fichier2)
{
    FILE *fd;
    fd = fopen (fichier2, "r");
    if (fd != NULL)
    {
        printf("fichier %s ouvert\n",fichier2);
        struct cellule_airport *  Buffairport;
        struct cellule_compagnie *Buffairline;
        struct airport            dataAPtmp;
        char                      strtab[max_colonne][max_strtab_lenght];
        char                      tmp[200];
        struct vol                vol;
        int                       index;
        // 1er fscanf = la ligne des nom de données -> poubelle
        fscanf (fd, "%s", tmp);
        // 2ème fscanf à faire avant le while
        fscanf (fd, "%s", tmp);
        while (!feof (fd))
        {
            my_strtok (tmp, strtab);           // Ma fonction strtok qui permet de prendre en
                                               // compte les valeurs manquantes
            conversion_vol (strtab, &vol);     // Fonction de conversion char en int ou float
                                               // car strtok marche avec des chars*
            char IATA_code[SIZE_airline_acro]; // On stocke l'iata code ici car on ne
                                               // le met pas dans la struct vol = gain
                                               // de place
            strcpy (IATA_code, strtab[3]);
            index       = get_hash_index_airport (vol.ORG_AIR, max_Hairport);
            Buffairport = recherche_cellHT_airport (ht_ap[index], vol.ORG_AIR);
            if (Buffairport == NULL)
            {
                ajout_tete_cellHT_airport (
                &(ht_ap[index]), ht_apDATA[get_hash_index_airport (vol.ORG_AIR, max_Hdataairport)]->data, 0);
                Buffairport = ht_ap[index];
            }
            // Buffairport pointe vers la cellule de la table de hash des aéroport
            // Recherche_et_ajout_cell renvoie le pointeur pointant vers Buffairport
            // (voir ci-dessus), si la cellule n'existe pas (soit si c'est la 1er fois
            // qu'on rencontre cet aéroport, on l'ajoute entête et on renvoie le
            // pointeur)
            index       = get_hash_index_airline (IATA_code, max_Hcomp);
            Buffairline = recherche_cellHT_compagnie (Buffairport->pt_Htable_compagnie[index], IATA_code);
            if (Buffairline == NULL)
            {
                ajout_tete_cellHT_compagnie (&(Buffairport->pt_Htable_compagnie[index]), IATA_code);
                Buffairline = Buffairport->pt_Htable_compagnie[index];
            }
            // Buffairline pointe vers la cellule de la table de hash des compagnies
            // selon l'aéroport Recherche_et_ajout_cell renvoie le pointeur pointant
            // vers Buffairline (voir ci-dessus), si la cellule n'existe pas (soit si
            // c'est la 1er fois qu'on rencontre cette compagnie dans cet aéroport de
            // départ, on l'ajoute entête et on renvoie le pointeur)
            ajout_vol_date (&(Buffairline->pt_Htable_date[vol.MONTH - 1]), vol);
            // Rangement de la cellule du vol triée par date, accède à une 3ème
            // hashtable selon le mois (on pourrait faire par jour et mois aussi mais
            // bcp trop gourmand?)
            fscanf (fd, "%s", tmp);
        }
        // ajout des derniere airports dans la table
        for (int i = 0; i < max_Hdataairport; i++)
        {
            if (ht_apDATA[i] != NULL)
            {
                strncpy (tmp, ht_apDATA[i]->data.IATA_CODE, SIZE_acronym);
                index       = get_hash_index_airport (tmp, max_Hairport);
                Buffairport = recherche_cellHT_airport (ht_ap[index], tmp);
                if (Buffairport == NULL)
                {
                    dataAPtmp = ht_apDATA[i]->data;
                    ajout_tete_cellHT_airport (&(ht_ap[index]), dataAPtmp, 1);
                }
            }
        }
    }
    if (fd != NULL)
    {
        fclose (fd);
        return 1;
    }
    printf ("error changement de %s", fichier2);
    return 0;
}
