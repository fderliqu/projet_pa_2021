# Tutorat de Programmation Avancée (SE3 - 2020/2021)

Ce dépôt `GIT` contient le sujet et les données utiles pour la réalisation du
_petit_ projet du module de Programmation Avancée.

> __Attention__: ce dépôt risque d'évoluer au cours de l'avancée des projets.
N'hésitez pas à le consulter régulièrement.

## Résumé

L'objectif de ce projet est de vérifier que vous maîtrisez les principes vus en
cours de programmation avancée : structures de données complexes,
lecture / écriture de fichiers, compilation séparée et automatique, utilisation
de gestionnaire de version...

Pour cela, le travail demandé est de réaliser une application qui permet d'analyser 58592 vols aux États Unis en 2014. Votre travail est de charger ces fichiers pour effectuer un certain nombre de requêtes (lister des vols selon plusieurs critères, lister l'aeroligne avec plus de retards, trouver un itinéraire, ...)

## Contexte

Les données sont stockées dans trois fichiers `CSV` (_comma-separated values_) qui est un format texte permettant de stocker des tableaux. Chaque ligne du fichier correspond à une ligne du tableau et les différents éléments d'une ligne sont
séparés par un élément particulier (en général une virgule `,` mais d'autres sont possibles `\t`, `;`...). La première ligne sert à décrire le nom des différents champs.
Par exemple, le fichier `flights.csv`, qui contient les vols, a la structure suivante :

~~~
MONTH,DAY,WEEKDAY,AIRLINE,ORG_AIR,DEST_AIR,SCHED_DEP,DEP_DELAY,AIR_TIME,DIST,SCHED_ARR,ARR_DELAY,DIVERTED,CANCELLED
1,1,4,WN,LAX,SLC,1625,58.0,94.0,590,1905,65.0,0,0
1,1,4,UA,DEN,IAD,823,7.0,154.0,1452,1333,-13.0,0,0
1,1,4,MQ,DFW,VPS,1305,36.0,85.0,641,1453,35.0,0,0
1,1,4,AA,DFW,DCA,1555,7.0,126.0,1192,1935,-7.0,0,0
1,1,4,WN,LAX,MCI,1720,48.0,166.0,1363,2225,39.0,0,0
~~~
Les premiers trois champs correspondent aux mois (`1` ou janvier), jour (`1`) et jour de la semaine (`4` ou mercredi), le quatrième à la compagnie aérienne suivant les codes IATA (`WN` ou Southwest Airlines Co.), `ORG_AIR` correspond à l'aéroport d'origine ou départ (`LAX`), `DEST_AIR` correspond à l'aéroport destination ou d'arrivée (`SLC`), `SCHED_DEP` correspond à l'heure de départ prévu (`1625`), `DEP_DELAY` correspond au délais de départ en minutes (`58.0`), `AIR_TIME` correspond à la durée du vol en minutes (`94.0`), `DIST` correspond à la distance en miles (`590`), `SCHED_ARR` correspond à l'heure d'arrivée prévu (`1905`), `ARR_DELAY` correspond au retard à l'arrivée en minutes (`65.0`), `DIVERTED` est un booléen qui indique si le vol a été déviée (`0`), et `CANCELLED` est un booléen qui indique si le vol a été annulé (`0`).



De la même façon, le fichier `airports.csv` décrit les aéroports et villes correspondent aux code IATA de la façon suivante :
```
IATA_CODE,AIRPORT,CITY,STATE,COUNTRY,LATITUDE,LONGITUDE
ABE,Lehigh Valley International Airport,Allentown,PA,USA,40.652359999999994,-75.4404
ABI,Abilene Regional Airport,Abilene,TX,USA,32.41132,-99.6819
ABQ,Albuquerque International Sunport,Albuquerque,NM,USA,35.04022,-106.60918999999998
```

ainsi que le fichier `airlines.csv` qui contient les codes IATA pour chaque compagnie aérienne :
```
IATA_CODE,AIRLINE
UA,United Air Lines Inc.
AA,American Airlines Inc.
US,US Airways Inc.
```


## Cahier des charges

Il vous est demandé de réaliser un programme qui charge les fichiers de données `CSV` (ils sont disponibles dans le répertoire `data`) et qui permet de les interroger facilement. 

Le volume de données est relativement important, par conséquent un soin particulier devra être apporté aux structures de données utilisées et à la rapidité d'exécution de votre programme. Les choix algorithmiques devront obligatoirement être expliqués et justifiés dans votre rapport.

Pour permettre d'évaluer automatiquement la performance de votre programme et permettre une utilisation automatique par redirection, votre programme devra fonctionner de la manière suivante :

1. charger le fichier de données
2. attendre une commande
3. traiter la commande
4. afficher le résultat de cette commande
5. revenir à l'étape 2

Les commandes seront les suivantes:

**TODO: À TRAVAILLER  LES REQUETTES !!!**


- `show-airports <airline_id>`  : liste tous les aéroports depuis lesquels la compagnie aérienne `<airline_id>` 
- `show-airlines <port_id>`: liste l'ensemble des compagnie aeriénnes depuis l'aéroport passé en paramètre
- `show-flights <port_id> <date> [<time>] [limit=xx]` : lister les vols qui partent de l'aéroport à la date, avec optionnellement une heure de début, et limité à xx vols
- `latest-flights`     : donne les 5 vols qui ont subis les plus longs retards à l'arrivée 
- `latest-airlines`    : donne les 5 compagnies aériennes qui ont, en moyenne, le plus de retards 
opère des vols
- `airlines <port_id>` : recherche compagnies aériens qui ont des vols qui départent l'aeroport `IATA_AIRPORT`
- `changed-flights <date>` : les vols annulés ou déviés à la date <date> (format M-D)
- CALCULATE_DURATION OF FLIGHTS
- ¡¡¡FIND AN ITINERARY!!!
- `9`       : quit

Ainsi si votre exécutable s'appelle `projet_pa` il doit être possible de l'utiliser de la manière suivante:

~~~
$ ./projet_pa < data/requetes.txt
~~~

avec le fichier `requetes.txt` qui contient par exemple:

~~~
**TODO: design très spécifique des requettes !!!**
~~~

## Précisions sur les requêtes

TODO: Donner une structure pour les requêtes qui permet de les noter presque automatiquement!


## Déliverables

**La date de fin de projet est le xx mai 2021 23:59 CEST. Tout retard entraînera des pénalités.**

Vous n'avez rien à imprimer, ni des documents à envoyer par e-mail. Il faudra donner l'accès du dépôt à votre correcteur et celui-ci corrigera à partir de la dernière version du dépôt ou de la branche `release` (si elle existe) avant la date limite. Les `push` qui suivraient la date limite ne seront pas considérés.

Sur votre dépôt devront figurer :

- le code source correctement commenté et indenté
- un `Makefile` pour la compilation automatique
- un `README.md` décrivant l'utilisation de votre programme
- Un fichier `Rapport.md` ou un rapport au format PDF (les autres formats ne sont pas acceptés) de 6 pages maximum qui explique vos choix de structures de données, vos choix de conception algorithmique et les principales étapes du déroulement de votre programme.

# Annexes

## Pour démarrer

Pour commencer à travailler, vous pouvez faire un fork du dépôt qui contient le fichier `README.md` que vous êtes en train de lire. Ne pas oublier d'ajouter les quatre intervenants dans la liste des personnes ayant accès à votre dépôt (menu `Settings` à droite puis Menu `Members` puis bouton `New Projet Member`).

On rappelle brièvement les commandes `GIT` que vous serez amené à utiliser :

- `git help cmd` : pour avoir de l'aide sur la commande `cmd`
- `git add fichier` : pour ajouter au dépôt un nouveau fichier ou un fichier modifié
- `git commit -m "message qui explique les modifications"` : pour sauvegarder les modifications dans le dépôt local
- `git push` : pour mettre à jour le serveur avec votre version du dépôt
- `git pull` : pour récupérer la dernière version du serveur
- `git status`: pour voir l'état de votre dépôt local par rapport au serveur
- `git log --pretty=format:"%h - %an, %ar : %s"`: afficher le log des commits

N'hésitez pas à vous référer au polycopié de programmation avancée ou le 'cheat sheet' pour git pour les détails de chacune des commandes.

## Évaluation
L’évaluation de ce projet sera faite en utilisant de manière intensive les outils de traitement automatique. D’une part parce que ce sont des outils qui sont utilisés dans le monde professionnel (et autant les maîtriser le plus tôt possible) et d’autre part puisque cela permet d’évaluer objectivement une partie de votre travail.

- Respect des conventions de codage avec `clang-format`
- Compilation automatique avec `Makefile`
- Qualité de code avec `clang-tidy` et `cppcheck`
- Respect des conventions des nommage des commits avec `commitlint` (optionnel)
- Détection automatique de plagiat avec `moss`
- Intégration continue avec `GitLab-CI`, `check`, `llvm-cov` / `gcov` (optionnel)
- Un exemple de dépôt GitLab conforme à ce qui est attendu est disponible à l’adresse suivante [https://gitlab.com/jeremie.dequidt/ima_prog_adv](https://gitlab.com/jeremie.dequidt/ima_prog_adv).

## Convention de nommage des commits
Pour etre plus facilement lisible, vos commits devront suivre une convention de nommage. La convention utilisée par AngularJS est devenue très populaire. Elle est décrite à l’adresse suivante [Commit Message Conventions](https://gist.github.com/stephenparish/9941e89d80e2bc58a153).
















