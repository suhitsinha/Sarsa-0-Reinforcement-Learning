Algorithm Used: SARSA [TD(0)] using epsilon greedy

1. Intialize the state action values.
2. calculate the next action.
3. For each episode run from step 4 to 7
4. Run step 5 to 7 until episode reaches the goal state.
5. Calculate the next states.
6. Run TD(0) algorithm to update the value.
7. Choose next state using epsilon greedy.
8. Plot the performance graph.

How to run:

Execute the script execute.sh from the submission directory.
Inside the script Number of episodes can be changed using the parameter to C executable file.
The plot for 4 action grid will be generated with the name of SARSA.jpeg
The plot for 8 action grid will be generated with the name of SARSA_8action.jpeg
The plot for 8 action grid with stochastic wind will be generated with the name of SARSA_8action_stochastic.jpeg

Reference:
http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node64.html
