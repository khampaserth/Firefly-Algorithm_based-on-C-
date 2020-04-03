set xrange [0:55]
set xtics 10
set yrange [-4:10]
set ytics 1
set mytics 2
#set xtics 1
#set format y "%2.1t"
set xlabel "Iteration"
set ylabel "fitness"
set key right bottom 
set size ratio 0.707
set size 0.66, 0.66

plot 'Fitness_value_sphere.txt' u 1:2 wi li lw 1 title "Sphere"
replot 'Fitness_value_Rast.txt' u 1:2 wi li lw 1 title "Rastrigin"
replot 'Fitness_value_rosenbrock.txt' u 1:2 wi li lw 1 title "Rosenbrock"

#set style line 2 lt 2 lw 2 pt 3 ps 0.5
set terminal postscript eps color enhanced dash "Helvetica" 16 lw 1
set output "convergen_two.eps"
rep
