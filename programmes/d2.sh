#!/bin/bash

#On a bien data.csv en argument
if [ $# -eq 0 ]; then
    echo "Le fichier data n'existe pas"
    exit 1
fi

#temps actuel en nanosecondes
start_time=$(date +%s.%N)

#On utilise un tableau qui prend en entrée les conducteurs et ajoute les distances pour chaque conducteur puis on le trie et l'affiche sur un fichier texte resultat2.txt
awk -F';' '{distances[$6] += $5} END {for (i in distances) printf "%s %.5f\n", i, distances[i]}' $1 | sort -nr -k3,3 | awk '{if (!seen[$1$2]++) print $1 " " $2 ":" $3 " trajets"}' | head -n10 > resultat2.txt

#On affiche le résultat avec gnuplot : on configure les paramètres du graphique (description des axes, valeurs des axes, largeur des boîtes, décalages...) puis on créé le graphique pivoté lors de l'affichage
gnuplot << EOF
set terminal png size 1920,1080
set output 'd2.png'
set datafile separator ':'
set xlabel 'DISTANCES'
set ylabel 'CONDUCTEURS'
set title 'Option -d2'
set yrange [0:*] reverse
set style fill solid
unset key
width = 0.8
set offsets 0, 0, 0.5, 0.9

plot 'resultat2.txt' using (0.5 * column(2)):0:(0.5 * column(2)):(0.4):ytic(1) with boxxy lc rgb 'green'
EOF

rm resultat2.txt

#temps actuel en nanosecondes
end_time=$(date +%s.%N)

#Calcul de la différence de temps
execution_time=$(echo "$end_time - $start_time" | bc)

#Affichage du temps d'execution
echo "Temps d'exécution du script : $execution_time secondes"
