
//Return : 
//  show-flights <main_HT> <AIRPORT> <M> <J> [<time>] [limit=<xx>] <mask>: 
//  affiche les vols qui partent de l'aéroport à la date, 
//  avec optionnellement une heure de début, et limité à xx vols
//Parameters : 
//  <main_HT>=table de hash des données des vols
//  <AIRPORT>=aéroport de départ
//  <J>=nombre du jour
//  <M>=nombre du mois
//  [<time>] = temps début départ (option) 
//  [limit=<xx>] = limite d'affichage (option)
//  <mask> masque pour parametre optionnel
void show_flights(struct cellule_airport**, char*, int, int, int, int, char);