#!/bin/bash

#On a bien data.csv en argument
if [ $# -eq 0 ]; then
    echo "Le fichier data n'existe pas"
    exit 1
fi

#temps actuel en nanosecondes
start_time=$(date +%s.%N)

#On utilise un tableau qui prend en entrée les ID et ajoute les distances pour chaque ID puis on le trie et l'affiche sur un fichier texte resultat3.txt
awk -F';' '{ID[$1] += $5} END {for (j in ID) printf "%ld %.5f\n", j, ID[j]}' $1 | sort -nr -k2,2 | head -n10 | sort -nr -k1,1 | awk '{if (!seen[$1]++) print $1 ":" $2}' > resultat3.txt

#On affiche le résultat avec gnuplot : on configure les paramètres du graphique (description des axes, valeurs des axes, largeur des boîtes...) puis on créé le graphique
gnuplot << EOF
set terminal png size 1920,1080
set output 'l.png'
set datafile separator ':'
set xlabel 'ID'
set ylabel 'DISTANCES'
set title 'Option -l'
set yrange [0:*]
set style fill solid
set boxwidth 0.5
unset key

plot 'resultat3.txt' using 2:xtic(1) with boxes lc rgb 'green'
EOF

rm resultat3.txt

#temps actuel en nanosecondes
end_time=$(date +%s.%N)

#Calcul de la différence de temps
execution_time=$(echo "$end_time - $start_time" | bc)

#Affichage du temps d'execution
echo "Temps d'exécution du script : $execution_time secondes"
