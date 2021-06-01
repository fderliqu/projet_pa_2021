#include "../includes/init.h"
#include "../includes/hash_algo.h"
#include "../includes/cell_function.h"
#include "../includes/charge_fichier.h"
#include "../includes/main_function.h"


int main() {
  struct cellule_airport *HT[max_Hairport];
  struct cellule_compagnieDATA *HTalData[max_Hdatacomp];      
  const char* separators = " \n";
  char*       ligne = NULL;
  size_t      n = 0;
  struct line_arguments liste;
  liste.dernier = -1;
  int fin = 0;
  init_ht_airport(HT);
  charge_vol(HT);
  init_ht_datacomp(HTalData, max_Hdatacomp);
  charge_dataCompagnie(HTalData);
  printf(">");
  while(getline(&ligne,&n,stdin) != -1)
  {
    printf("%s\n", ligne);
    liste.dernier++;
    liste.arg[liste.dernier] = strtok(ligne,separators);
    while(liste.arg[liste.dernier]!=NULL)
    {
      liste.dernier++;
      liste.arg[liste.dernier] = strtok(NULL,separators);
    }
    liste.dernier--;
    if(strcmp(liste.arg[0],"quit") == 0)fin = 1;
    launch_function(liste,HT,HTalData);
    if(fin==1)return 0;
    liste.dernier = -1;
    printf("\n");
    printf(">");
  }
}
