set term jpeg size 1024, 768
set output "SARSA.jpeg"
set xlabel "Time steps"
set ylabel "Episodes"
plot "4action.txt" using 2:1 notitle with points, \
"4action.txt" using 2:1 smooth csplines linetype 50 with lines title "SARSA performance in Windy Gridworld with 4 action" 
