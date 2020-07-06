# Simulation-Reciprocal-Altruism
Game Theoretic Simulation of the Tit-for-tat strategy

This program is supposed to be a simulation to test certain game-theoretic approaches to the evolution of reciprocal altruism by analyzing the iterated prisoner's dilemma.
The question it attempts to analyze is how a world of defectors - people unwilling to cooperate - could ever allow any cooperation to be fruitful.

Normally, it is known that the strategy All-D is collectively stable, meaning if any other strategy enters the population it will do just as well or likely worse. 
Larger amounts of invading strategies also are unlikely to take over the native All-D. The independent variable this program seeks to analyze is whether a clustering coefficient c could affect the final results. 

The program does this as follows:
First, it allows the user to set the following variables:
Initial Amount of All-D (or Defectors - normally set to 2000, though this does not change the results as long as it is big enough)
Initial Amount of Tit-for-tatters (best kept small to properly reflect reality)
Amount of rounds played
Amount of trials (this replays the whole iterated prisoner's dilemma to allow for more accurate and less stochastic statistics)
Clustering coefficient

It then plays the iterated prisoner's dilemma with the starting values 3/3 if both cooperate, 1/1 if both defect, and 5/0 if someone defects but the other cooperates.
Two agents are randomly chosen (depending on the clustering coefficient) to play against each other, this is repeated for the user-specified amount of rounds.
The game is then reset and the game is repeated for the user-specified amount of trials.

Finally, the program outputs some raw data and some primitive statistics including the mean and average score per meeting as well as the standard deviation.

This theory is one I wanted to check with a program for a biological paper I am writing for school.


Acknowledgements:
This project would not have been possible without the extremely helpful ideas from Albinopapa and Slidy of the planetchili.net forum!
