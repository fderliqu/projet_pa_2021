 # Projet de Programmation Avancée (Systèmes Embarqués 3 S6)

Ce dépôt `GIT` contient les livrables du projet de Florian DERLIQUE et Corentin GIELEN du projet du module de Programmation Avancée.
Projet qui a pour but de realiser des requetes permetant a un utilisateurs d'analyser une base de données de vols.


## CONTENU
Ce depot contient dans la branche master differents répertoires dans les quelles ce trouve l'ensemble des fonctions nécessaires a notre livrable 
- **data** :
	- `LICENSE` : Certificat de droit de libre accès aux données.
	- `airlines.csv` : Donnéess des compagnies aériennes.
	- `airports.csv` : Données des aéroport.
	- `flights.csv` : Données des vols.
	- `requetes.txt ` : Requetes de tests.

- **includes** :
	- `avg-flight-duration.h` : Declaration de la fonction associer au .c du meme nom.
	- `cell_function.h` :  Declaration des fonctions et structures de données associer au .c du meme nom.
	- ` changed-flights.h` : Declaration de la fonction associer au .c du meme nom.
	- ` charge_fichier.h ` : Declaration de la fonction associer au .c du meme nom.
	- ` condition_function.h ` : Declaration des fonctions associer au .c du meme nom.
	- ` delayed-airline-airline_id.h ` : Declaration de la fonction associer au .c du meme nom.
	- ` find-initerary.h` : Declaration de la fonction associer au .c du meme nom.
	- ` hash_algo.h` : Declaration des fonctions associer au .c du meme nom.
	- `init.h` : Declaration des structures de notre structures de données.
	- `main_function.h ` :   Declaration de la fonction associer au .c du meme nom.
	- ` most-delayed-airlines-at-airport.h ` : Declaration de la fonction associer au .c du meme nom.
	- ` most-delayed-flights.h  ` : Declaration des fonctions et structures de données associer au .c du meme nom.
	- ` most_delayed_airlines.h ` : Declaration des fonctions et structures de données associer au .c du meme nom.
	- ` quit.h ` :   Declaration de la fonction associer au .c du meme nom.
	- ` show-airlines.h` : Declaration de la fonction associer au .c du meme nom.
	- ` show-airport.h ` : Declaration de la fonction associer au .c du meme nom.
	- ` show-flights.h ` : Declaration des fonctions associer au .c du meme nom.

- **src** :
	- `avg-flight-duration.c `: **requet** requet du meme nom.
	- `cell_function.c` : fichier qui contient les fonctions permetant de rechercher et de modifier notre structures de données.
	- ` changed-flights.c` : **requet** requet du meme nom.
	- ` charge_fichier.c ` : fichier qui contient les fonctions permetant d'extraire les donnés des fichiers et de les placer dans notre base de données. 
	- ` condition_function.c ` : fichier contenant les condition permetant d'eviter des erreurs de saisi de l'utilisateur.
	- ` delayed-airline-airline_id.c ` : **requet** requet du meme nom.
	- ` find-initerary.c` : **requet** requet du meme nom.
	- ` hash_algo.c` : fichier contenant les fonctions de hachage de nos differentes tables de hachage.
	- `main.c` : fichier contenant les  fonction necesaire a main function.
	- `main_function.c ` :  fichier contenant le corps de notre projet l'interface avec l'utilisateur.
	- ` most-delayed-airlines-at-airport.c ` : **requet** requet du meme nom.
	- ` most-delayed-flights.c  ` : **requet** requet du meme nom.
	- ` most_delayed_airlines.c ` : **requet** requet du meme nom.
	- ` quit.c` :   fichier contenant les fonction permetant de libérée la memoire et de quitté le programe.
	- ` show-airlines.c` : **requet** requet du meme nom.
	- ` show-airport.c ` : **requet** requet du meme nom.
	- ` show-flights.c ` : **requet** requet du meme nom.
	- ` test.c ` : fichier contenant nos tests de fonction.

- Pour finir :
	- **Makefile** :  Fichier permetant la compilation automatique
	- **Rapport.pdf** :  Compte-rendu du projet 
	- **clang-format** :  fichier contenant les regles de formatage du langage C

## COMPILATION
	La compilation est a realiser la premiere fois que l'utilisateur recupère les fichiers.
	Pour ce faire l'uilisateur doit taper la commande ` Make `.
	Il peut aussi taper la commande ` make clean` pour supprimier les fichiers realiser par make.

## UTILISATION DU PROGRAMME
Pour executer le programme l'utilisateur a deux choix


Le programme ce ferme lorsque l'utilisateur effectue la requet ` quit ` .