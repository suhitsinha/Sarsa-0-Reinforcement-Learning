#!/bin/sh

g++ SARSA.cpp -o SARSA.o
./SARSA.o 170
gnuplot SARSA.plot

g++ SARSA_8action.cpp -o SARSA_8action.o
./SARSA_8action.o 170
gnuplot SARSA_8action.plot

g++ SARSA_8action_stochastic.cpp -o SARSA_8action_stochastic.o
./SARSA_8action_stochastic.o 170
gnuplot SARSA_8action_stochastic.plot

