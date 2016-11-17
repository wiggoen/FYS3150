#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
#include "time.h"

using namespace std;
ofstream ofile;

// Declaration of functions
void MonteCarloSimulation(int N, double m0, int runs, int transactions, int &exchangeCounter);
void moneyExchange(double *m, int &i, int &j, double &epsilon, int &exchangeCounter);
double *giveMeTheMoney(int N, double m0);
void showMeTheMoney(double *m, int N);
void printTheMoney(double *m, int N);
int compareMoney(const void * a, const void * b);

int main(int numArguments, char **arguments)
{
    // Default if there is no command line arguments
    string billOfAbundance = "noEqualityForFatCats.txt";  // Output file
    int N = 5;//500;                                          // Number of agents
    double m0 = 1000.0;                                   // Amount of money at start
    int transactions = 10;//1e7;                               // Number of transactions
    int runs = 1;//1e3;                                       // Monte Carlo cycles ([1e3, 1e4] runs)
    double alpha = 1;                                     // [1, 2]
    double lambda = 0.25;                                 // {0.25, 0.5, 0.9}

    // If command line arguments are defined
    if (numArguments >= 2) billOfAbundance = string(arguments[2]);
    if (numArguments >= 3) N = atoi(arguments[3]);
    if (numArguments >= 4) m0 = atof(arguments[4]);
    if (numArguments >= 5) transactions = atoi(arguments[5]);
    if (numArguments >= 6) runs = atoi(arguments[6]);
    if (numArguments >= 7) alpha = atof(arguments[7]);
    if (numArguments >= 8) lambda = atof(arguments[8]);

    int exchangeCounter = 0;      // Counts the number of exchanges

    ofile.open(billOfAbundance);  // Open file for writing

    //showMeTheMoney(m, N);

    clock_t start, finish;
    start = clock();              // Start clock

    MonteCarloSimulation(N, m0, runs, transactions, exchangeCounter);

    finish = clock();             // End clock

    //showMeTheMoney(m, N);
    //cout << "Money has been exchanged " << exchangeCounter << " times." << endl;

    // Time used
    double runtime = ((finish - start)/double(CLOCKS_PER_SEC));
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setw(15) << setprecision(8) << "Runtime = " << runtime << " s" << endl;
    cout << endl;

    ofile.close();                // Close file
    return 0;
}

double *giveMeTheMoney(int N, double m0) {
    double *m = new double[N];              // Make money vector
    for (int i = 0; i < N; i++) m[i] = m0;  // Set same amount of money to agents
    return m;
}

int compareMoney(const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return -1;
    else if (*(double*)a < *(double*)b) return 1;
    else return 0;
}

void MonteCarloSimulation(int N, double m0, int runs, int transactions, int &exchangeCounter) {

    // Trenger en arbeidsvektor for å jobbe med
    // workTheMoney
    // stackMoney <-- vektor som skal printes?

    random_device rd;                                                    // Initialize the seed
    mt19937_64 gen(rd());                                                // Call the Mersenne twister random number engine
    uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);   // Set up the uniform distribution for x in [0, 1]

    //double *m = giveMeTheMoney(N, m0);
    for (int i = 0; i < runs; i++) {
        double *m = giveMeTheMoney(N, m0);                                 // Initialize and restart money vector
        for (int cycles = 1; cycles <= transactions; cycles++) {
            double epsilon = RandomNumberGenerator(gen);                   // Random number
            int i = RandomNumberGenerator(gen)*N;                          // Find a random pair of agents (i, j)
            int j = RandomNumberGenerator(gen)*N;
            if (i != j) moneyExchange(m, i, j, epsilon, exchangeCounter);  // If i different from j: Exchange money
        }
        showMeTheMoney(m, N);
        qsort(m, N, sizeof(double), compareMoney);

        // After sort -> sendMoney to m vector that updates

        cout << endl;
        showMeTheMoney(m, N);
        //printTheMoney(m, N);
    }
}

void moneyExchange(double *m, int &i, int &j, double &epsilon, int &exchangeCounter) {
    double mi = m[i];
    m[i] = epsilon*(m[i] + m[j]);
    m[j] = (1 - epsilon)*(mi + m[j]);
}

void showMeTheMoney(double *m, int N) {
    for(int i = 0; i < N; i++) cout << m[i] << endl;
}

void printTheMoney(double *m, int N) {
    for (int i = 0; i < N; i++) {
        ofile << setw(15) << setprecision(8) << m[i];
    }
    ofile << endl;
}

