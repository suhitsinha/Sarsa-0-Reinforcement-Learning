set term jpeg size 1024, 768
set output "SARSA_8action_stochastic.jpeg"
set xlabel "Time steps"
set ylabel "Episodes"
plot "8action_stochastic.txt" using 2:1 notitle with points, \
"8action_stochastic.txt" using 2:1 smooth csplines linetype 50 with lines title "SARSA performance in Windy Gridworld with 8 action and stochastic wind" 
