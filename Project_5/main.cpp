#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <stdlib.h> /* qsort */
#include "time.h"

using namespace std;
ofstream ofile;

// By using long double we get less transaction error, but the program runs slower
#define double long double

// Declaration of functions
void MonteCarloSimulation(double *m, int N, double m0, int runs, int transactions, int &exchangeCounter);
void moneyExchange(double *workTheMoney, int &i, int &j, double &epsilon, int &exchangeCounter);
double *giveMeTheMoney(int N);
double *shareTheMoney(int N, double m0);
void stackTheMoney(double *workTheMoney, double *m, int N);
void showMeTheMoney(double *money, int N);
void printTheMoney(double *m, int N);
int compareMoney(const void * a, const void * b);

int main(int numArguments, char **arguments)
{
    // Default if there is no command line arguments
    string billOfAbundance = "../Project_5/outputs/noEqualityForFatCats.txt";  // Output file
    int N = 500;             // Number of agents
    double m0 = 1e5;         // Amount of money at start
    int transactions = 100;//1e7;  // Number of transactions
    int runs = 10;//1e3;          // Monte Carlo cycles ([1e3, 1e4] runs)
    double alpha = 1;        // [1, 2]
    double lambda = 0.25;    // {0.25, 0.5, 0.9}

    // If command line arguments are defined
    if (numArguments >= 2) billOfAbundance = "../Project_5/outputs/"+string(arguments[1]);
    if (numArguments >= 3) N = atoi(arguments[2]);
    if (numArguments >= 4) m0 = atof(arguments[3]);
    if (numArguments >= 5) transactions = atoi(arguments[4]);
    if (numArguments >= 6) runs = atoi(arguments[5]);
    if (numArguments >= 7) alpha = atof(arguments[6]);
    if (numArguments >= 8) lambda = atof(arguments[7]);

    int exchangeCounter = 0;        // Counts the number of exchanges
    double *m = giveMeTheMoney(N);  // Initialize money vector
    ofile.open(billOfAbundance);    // Open file for writing

    //showMeTheMoney(m, N);

    clock_t start, finish;
    start = clock();                // Start clock

    MonteCarloSimulation(m, N, m0, runs, transactions, exchangeCounter);

    finish = clock();               // End clock

    //showMeTheMoney(m, N);
    //cout << "Money has been exchanged " << exchangeCounter << " times." << endl;

    printTheMoney(m, N);            // Writes m to file
    ofile.close();                  // Close file

    cout << endl; cout << "The program is finished running." << endl; cout << endl;
    return 0;
}

double *giveMeTheMoney(int N) {
    double *m = new double[N];                // Make money vector
    for (int i = 0; i < N; i++) m[i] = 0.0;   // Set same amount of money to agents
    return m;
}

double *shareTheMoney(int N, double m0) {
    double *workTheMoney = new double[N];              // Make money vector
    for (int i = 0; i < N; i++) workTheMoney[i] = m0;  // Set same amount of money to agents
    return workTheMoney;
}

int compareMoney(const void * a, const void * b)  // Check which money is larger
{
    if (*(double*)a > *(double*)b) return -1;
    else if (*(double*)a < *(double*)b) return 1;
    else return 0;
}

void MonteCarloSimulation(double *m, int N, double m0, int runs, int transactions, int &exchangeCounter) {
    random_device rd;                                                    // Initialize the seed
    mt19937_64 gen(rd());                                                // Call the Mersenne twister random number engine
    uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);   // Set up the uniform distribution for x in [0, 1]
    for (int i = 0; i < runs; i++) {
        double *workTheMoney = shareTheMoney(N, m0);                     // Initialize and restart work money vector
        for (int cycles = 1; cycles <= transactions; cycles++) {
            double epsilon = RandomNumberGenerator(gen);                 // Random number
            int i = RandomNumberGenerator(gen)*N;                        // Find a random pair of agents (i, j) to exchange money
            int j = RandomNumberGenerator(gen)*N;
            if (i != j) moneyExchange(workTheMoney, i, j, epsilon, exchangeCounter);  // If i different from j; exchange money
        }
        //showMeTheMoney(workTheMoney, N); cout << endl;

        stackTheMoney(workTheMoney, m, N);

        //cout << endl; showMeTheMoney(workTheMoney, N); cout << endl;
    }
}

void moneyExchange(double *workTheMoney, int &i, int &j, double &epsilon, int &exchangeCounter) {
    double workTheMoney_i = workTheMoney[i];
    double workTheMoney_j = workTheMoney[j]; // No need
    workTheMoney[i] = epsilon*(workTheMoney[i] + workTheMoney[j]);
    workTheMoney[j] = (1 - epsilon)*(workTheMoney_i + workTheMoney[j]);
/*
    if ( (workTheMoney[i] + workTheMoney[j]) != (workTheMoney_i + workTheMoney_j) ) {
        //cout << workTheMoney[i] + workTheMoney[j] << endl;
        //cout << workTheMoney_i + workTheMoney_j << endl;
        cout << "Someone is draining the bank." << endl;
        cout << (workTheMoney[i] + workTheMoney[j])-(workTheMoney_i + workTheMoney_j) << endl;
    }*/
}

void stackTheMoney(double *workTheMoney, double *m, int N) {
    qsort(workTheMoney, N, sizeof(double), compareMoney);   // Sorts the money for stacking
    for (int i = 0; i < N; i++) m[i] += workTheMoney[i];    // Stacks the sorted money in m
}

void showMeTheMoney(double *money, int N) {
    for(int i = 0; i < N; i++) cout << money[i] << endl;
}

void printTheMoney(double *m, int N) {
    for (int i = 0; i < N; i++) ofile << setw(15) << setprecision(8) << m[i];
}
