#!/bin/bash

#On a bien data.csv en argument
if [ $# -eq 0 ]; then
    echo "Le fichier data n'existe pas"
    exit 1
fi

#temps actuel en nanosecondes
start_time=$(date +%s.%N)

#On utilise un AVL dans une fonction c pour trouver les éléments
cat < $1 | cut -d ';' -f1,f5 > data.txt
s.c > s.txt
rm data.txt

#On affiche le résultat avec gnuplot : on configure les paramètres du graphique (description des axes, valeurs des axes, largeur des boîtes, décalages...) puis on créé le graphique pivoté lors de l'affichage
echo $data.txt

#temps actuel en nanosecondes
end_time=$(date +%s.%N)

#Calcul de la différence de temps
execution_time=$(echo "$end_time - $start_time" | bc)

#Affichage du temps d'execution
echo "Temps d'exécution du script : $execution_time secondes"
