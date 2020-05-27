# Simulation-Reciprocal-Altruism
Game Theoretic Simulation of the Tit-for-tat strategy

This program is supposed to be a simulation to test certain game-theoretic approaches to the evolution of reciprocal altruism.

In its current stage it contains three strategies that an "agent" (in nature rather an organism) can have:
It can be a Cooperator, meaning it will always operate.
It can be a Tit-For-Tatter (shortened TFT in the program), meaning it will cooperate and subsequently copy its opponent's action against that opponent. 
(in other words, if Agents cooperate, TFT will cooperate, if not, it will deflect as a form of vengeance.)
It can also be a Deflector, meaning it will always deflect.

Every round, agents will meet each other and decide which strategy they will use. 
Depending on who deflects/cooperates, the different agents receive different punishments/rewards. 
A negative score for an agent means it dies; A score larger than some reproductionscore means it reproduces.

It is expected that the TFT strategy is most effective, and that as such it will be the largest ratio at the end of the game.
As such, reciprocal altruism can be shown to be an effective strategy.

This theory is one I wanted to check with a program for a biological paper I am writing for school.

The most functional simulation so far is the branch "Merger"
