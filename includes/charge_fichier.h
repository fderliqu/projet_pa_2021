//Charge le fichier airports.csv dans la base
int charge_dataAirport(struct cellule_airportDATA**, char*);

//Charge le fichier airlines.csv dans la base
int charge_dataCompagnie(struct cellule_compagnieDATA**, char*);

//Charge le fichier flights.csv dans la base
int charge_vol(struct cellule_airport **,struct cellule_airportDATA **, char*);

