/*
RESTE A FAIRE :
-> ajouter non pas que le iatacode de l'aeroport mais toute la structure
-> c'est tout je crois
*/
#include"../includes/hash_algo.h"
#define max_colonne 14
#define max_strtab_lenght 10
#define max_hash 17575

int compare(struct vol v1, struct vol v2)
{
    return v1.DAY - v2.DAY;
}

void ajout_tete_cellule_airport(struct cellule_airport** pl, char str[SIZE_acronym])
{
    struct cellule_airport* cell = malloc(sizeof(struct cellule_airport));
    strcpy(cell->airport.IATA_CODE,str);
    init_ht_comp(cell->pt_Htable_compagnie);
    cell->airport_suiv = *pl;
    *pl = cell;
    return;
}

void ajout_tete_cellule_compagnie(struct cellule_compagnie** pl, char str[SIZE_airline_acro])
{
    struct cellule_compagnie* cell = malloc(sizeof(struct cellule_compagnie));
    strcpy(cell->IATA_CODE,str);
    init_ht_date(cell->pt_Htable_date);
    cell->compagnie_suiv = *pl;
    *pl = cell;
    return;
}

struct cellule_airport* recherche_et_ajout_cell_airport(struct cellule_airport** pl,char str[SIZE_acronym])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->airport.IATA_CODE) < 0) )
    {
        ajout_tete_cellule_airport(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->airport.IATA_CODE,str,SIZE_acronym ) )
    {
        return *pl;
    }
    else return recherche_et_ajout_cell_airport( &((*pl)->airport_suiv),str);
}

struct cellule_compagnie* recherche_et_ajout_cell_airline(struct cellule_compagnie** pl,char str[SIZE_airline_acro])
{
    if( (*pl == NULL) || (strcmp(str,(*pl)->IATA_CODE) < 0) )
    {
        ajout_tete_cellule_compagnie(pl,str);
        return *pl;
    }
    if( !strncmp( (*pl)->IATA_CODE,str,SIZE_airline_acro ) )
    {
        return *pl;
    }
    else return recherche_et_ajout_cell_airline( &((*pl)->compagnie_suiv),str);
}

void ajout_vol_date(struct cellule_vol_date** pl, struct vol vol)
{
    if( (*pl == NULL) || ( compare(vol,(*pl)->vol) < 0) )
    {
        struct cellule_vol_date* new;
        new = malloc(sizeof(struct cellule_vol_date));
        new->vol = vol;
        new->vol_suiv = *pl;
        *pl = new;
        return;
    }
    ajout_vol_date(&((*pl)->vol_suiv),vol);
}

void my_strtok(char* str,char strtab[max_colonne][max_strtab_lenght])
{
    char c = *str++;
    int pos = 0;
    int emplacement = 0;
    while(c != '\0')
    {
        if(c == ',')
        {
            strtab[emplacement][pos] = '\0';
            emplacement++;
            pos=0;
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

void conversion(char strtab[max_colonne][max_strtab_lenght], struct vol* PTvol)
{
    PTvol->MONTH = atoi(strtab[0]);
    PTvol->DAY = atoi(strtab[1]);
    PTvol->WEEKDAY = atoi(strtab[2]);
    strcpy(PTvol->ORG_AIR,strtab[4]);
    strcpy(PTvol->DEST_AIR,strtab[5]);
    PTvol->SCHED_DEP = atoi(strtab[6]);
    PTvol->DEP_DELAY = -5000000.0;
    PTvol->AIR_TIME = -1.0;
    PTvol->DIST = atoi(strtab[9]);
    PTvol->SCHED_ARR = atoi(strtab[10]);
    PTvol->ARR_DELAY = -5000000.0;
    PTvol->CANCELLED = atoi(strtab[13]);
    PTvol->DIVERTED = atoi(strtab[12]);
    if(PTvol->CANCELLED == 0)
    {
        PTvol->DEP_DELAY = atof(strtab[7]);
    }
    if(PTvol->DIVERTED == 0 && PTvol->CANCELLED == 0)
    {
        PTvol->AIR_TIME = atof(strtab[8]);
        PTvol->ARR_DELAY = atof(strtab[11]);
    }
}

//test

int get_hash_index(char iata_code[SIZE_acronym])
{
    return 
    iata_code[2]-'A' + 
    (iata_code[1]-'A')*(MAX_LETTER) + 
    (iata_code[0]-'A')*(MAX_LETTER*MAX_LETTER);
}

//fin test

void charge_vol(struct cellule_airport* ht_ap[max_Hairport])
{
    FILE *fp = fopen("../data/flights.csv","r");
    if(fp!=NULL)
    {
        //struct cellule_vol_date* Hashtable[max_hash]; //C'est pour les tests des perfs
        struct cellule_airport* Buffairport;
        struct cellule_compagnie* Buffairline;
        char strtab[max_colonne][max_strtab_lenght];
        char tmp[200];
        struct vol vol;
        //1er fscanf = la ligne des nom de données -> poubelle
        fscanf(fp,"%s",tmp);
        //2ème fscanf à faire avant le while
        fscanf(fp,"%s",tmp);
        while(!feof(fp))
            { 
	            my_strtok(tmp,strtab); //Ma fonction strtok qui permet de prendre en compte les valeurs manquantes
                conversion(strtab,&vol); //Fonction de conversion char en int ou float car strtok marche avec des chars*
                char IATA_code[SIZE_airline_acro];// On stocke l'iata code ici car on ne le met pas dans la struct vol = gain de place
                strcpy(IATA_code,strtab[3]);
                Buffairport = recherche_et_ajout_cell_airport(&( ht_ap[ get_hash_index_airport( vol.ORG_AIR ) ] ),vol.ORG_AIR);
                //Buffairport pointe vers la cellule de la table de hash des aéroport
                //Recherche_et_ajout_cell renvoie le pointeur pointant vers Buffairport (voir ci-dessus), si la cellule n'existe pas (soit si c'est la 1er fois qu'on rencontre
                //cet aéroport, on l'ajoute entête et on renvoie le pointeur)
                Buffairline = recherche_et_ajout_cell_airline(&( Buffairport->pt_Htable_compagnie[ get_hash_index_airline( IATA_code ) ] ),IATA_code);
                //Buffairline pointe vers la cellule de la table de hash des compagnies selon l'aéroport
                //Recherche_et_ajout_cell renvoie le pointeur pointant vers Buffairline (voir ci-dessus), si la cellule n'existe pas (soit si c'est la 1er fois qu'on rencontre
                //cette compagnie dans cet aéroport de départ, on l'ajoute entête et on renvoie le pointeur)
                ajout_vol_date(&(Buffairline->pt_Htable_date[vol.MONTH-1]),vol);
                //Rangement de la cellule du vol triée par date, accède à une 3ème hashtable selon le mois (on pourrait faire par jour et mois aussi mais bcp trop gourmand?)
                fscanf(fp,"%s",tmp);
            }
        fclose(fp);
        printf("fin\n");
    }
}
//Fonctions de test ne pas check
void print_cell_ap(struct cellule_airport* PTcell)
{
    if(PTcell == NULL)return;
    printf("%s,",PTcell->airport.IATA_CODE);
    print_cell_ap(PTcell->airport_suiv);
}

void print_cell_al(struct cellule_compagnie* PTcell)
{
    if(PTcell == NULL)return;
    printf("%s,",PTcell->IATA_CODE);
    print_cell_al(PTcell->compagnie_suiv);
}
void print_ht_ap(struct cellule_airport* ht_ap[max_Hairport])
{
    for(int i=0; i<max_Hairport; i++)
    {
        printf("[%d] -> ",i);
        print_cell_ap(ht_ap[i]);
        printf("\n");
    }
    printf("\n");
}

void print_ht_al(struct cellule_compagnie* ht_al[max_Hcomp])
{
    for(int i=0; i<max_Hcomp; i++)
    {
        printf("[%d] -> ",i);
        print_cell_al(ht_al[i]);
        printf("\n");
    }
    printf("\n");
}

// le main chargement des flights
int main()
{
    struct cellule_airport* HT[max_Hairport];
    //Initialisation de la premiere table de hash (par aéroport de départ)
    init_ht_airport(HT);
    charge_vol(HT);
}
/*
printf("%d,%d,%d,%s,%s,%s,%d,%f,%f,%d,%d,%f,%hd,%hd\n",
		    vol.MONTH,
		    vol.DAY,
		    vol.WEEKDAY,
            IATA_code,
		    vol.ORG_AIR,
		    vol.DEST_AIR,
		    vol.SCHED_DEP,
		    vol.DEP_DELAY,
		    vol.AIR_TIME,
		    vol.DIST,
		    vol.SCHED_ARR
		    ,vol.ARR_DELAY
		    ,vol.DIVERTED
		    ,vol.CANCELLED);
            */
/*
ajout_vol_date( &( Hashtable[ get_hash_index( vol.ORG_AIR ) ] ), vol);
fscanf(fp,"%s",tmp);*/