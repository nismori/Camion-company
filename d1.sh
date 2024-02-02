#!/bin/bash

#On a bien data.csv en argument
if [ $# -eq 0 ]; then
    echo "Le fichier data n'existe pas"
    exit 1
fi

#temps actuel en nanosecondes 
start_time=$(date +%s.%N)

#On utilise un double tableau qui repère si on a le conducteur et la routeID et qui ajoute un si c'est le cas, on garde seulement les conducteurs et les valeurs du tableau qu'on trie pour l'afficher sur le fichier texte resultat.txt
awk -F';' '{trajets[$6][$2] += 1} END {for (i in trajets) {for (j in trajets[i]) print i, trajets[i][j]}}' $1 | sort -nrk3,3 | awk '{if (!seen[$1$2]++) print $1 " " $2 ":" $3}' | head -n10 > resultat.txt

#On affiche le résultat avec gnuplot : on configure les paramètres du graphique (description des axes, valeurs des axes, largeur des boîtes, décalages...) puis on créé le graphique pivoté lors de l'affichage
gnuplot << EOF
set terminal png size 1920,1080
set output 'd1.png'
set datafile separator ':'
set xlabel 'NOMBRES DE TRAJETS'
set ylabel 'CONDUCTEURS'
set title 'Option -d1'
set yrange [0:*] reverse
set style fill solid
unset key
width = 0.8
set offsets 0, 0, 0.5, 0.9

plot 'resultat.txt' using (0.5 * column(2)):0:(0.5 * column(2)):(0.4):ytic(1) with boxxy lc rgb 'green'
EOF

rm resultat.txt

#temps actuel en nanosecondes 
end_time=$(date +%s.%N)

#Calcul de la différence de temps
execution_time=$(echo "$end_time - $start_time" | bc)

#Affichage du temps d'execution
echo "Temps d'exécution du script : $execution_time secondes"
