FYS3150/FYS4150 - Project 5 Monte Carlo Modeling of Transactions
============

This program simulates financial transactions among agents using Monte Carlo methods. It
generates a histogram for agents with different amounts of money. The bin size is chosen 
to be 0.01 times m0.  
The program can be executed by the python script "Project_5_run.py". If the program is 
executed without any command line arguments, it will run on a set of default values 
stated in the top of the main function. The outfile variable is called "billOfAbundance",
and the variance is written to a separate file for the first run. The different parameters 
of the program are:
* N: Number of agents.
* m0: Amount of money given to each agent before a run.
* transactions: Number of transactions you want for each run. 
* runs: Number of runs you want an average over. 
* lambda: The fraction of saving. Let this be 0 or 0 < lambda < 1. We have used lambda 
= {0, 0.25 0.5, 0.9}.
* alpha: The exponent of the likelyhood of agents with similar amount of money will 
interact. We have used alpha = {0, 0.5, 1, 1.5, 2}.
* gamma: The exponent of the likelyhood of agents that have interacted before will do so 
again. We have used gamma = {0, 1, 2, 3, 4}.