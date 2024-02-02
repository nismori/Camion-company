#!/bin/bash

#On a bien data.csv en argument
if [ $# -eq 0 ]; then
    echo "Le fichier data n'existe pas"
    exit 1
fi

#temps actuel en nanosecondes 
start_time=$(date +%s.%N)

#On utilise un programme C pour trier les résultats et les envoyer dans le fichier t.txt
cat < $1 | cut -d';' -f1,2,3,4 > data.txt
sed -i 's/ //g' data.txt
sed -i 's/;/ /g' data.txt
exec t.c > t.txt
rm data.txt

#On affiche le résultat avec gnuplot : on configure les paramètres du graphique (description des axes, valeurs des axes, largeur des boîtes) puis on créé le graphique
gnuplot << EOF
set terminal png size 1920,1080
set output 't.png'
set datafile separator ';'
set xlabel 'NOM DES VILLES'
set ylabel 'NOMBRES DE ROUTES'
set title 'Option -t'
set yrange [0:*]
set style fill solid
set boxwidth 0.5
set key font ",20"

plot 't.txt' using 2:xtic(1) title 'routes totales' with boxes, '' using 3:xtic(1) title 'première ville' with boxes
EOF

#temps actuel en nanosecondes 
end_time=$(date +%s.%N)

#Calcul de la différence de temps
execution_time=$(echo "$end_time - $start_time" | bc)

#Affichage du temps d'execution
echo "Temps d'exécution du script : $execution_time secondes"

