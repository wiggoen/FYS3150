#include <algorithm>  // std::stable_sort
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>     // std::vector
//#include <stdlib.h> /* qsort */
//#include "time.h"


using namespace std;
ofstream ofile;

// By using long double we get less transaction error, but the program runs slower
#define double long double

// Declaration of functions
void MonteCarloSimulation(vector<double> &m, int N, double m0, int runs, int transactions, int &exchangeCounter);
void moneyExchange(vector<double> &agents, int &i, int &j, double &epsilon, int &exchangeCounter);
void giveMeTheMoney(vector<double> &m, int N);
void shareTheMoney(vector<double> &agents, int N, double m0);
void stackTheMoney(vector<double> &agents, vector<double> &m, int N);
void showMeTheMoney(vector<double> &money, int N);
void printTheMoney(vector<double> &m, int N, int runs);
bool compareTheMoney(double i, double j);

int main(int numArguments, char **arguments)
{
    // Default if there is no command line arguments
    string billOfAbundance = "../Project_5/outputs/noEqualityForFatCats_onerun.txt";  // Output file
    int N = 500;             // Number of agents
    double m0 = 1e5;         // Amount of money at start
    int transactions = 1e7;  // Number of transactions
    int runs = 1;//1e3;          // Monte Carlo cycles ([1e3, 1e4] runs)
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


    // Initialize counter, money vector, open file for writing and start timer
    int exchangeCounter = 0;        // Counts the number of exchanges

    vector<double> m;    giveMeTheMoney(m, N);  // Initialize money vector

    ofile.open(billOfAbundance);    // Open file for writing

    //showMeTheMoney(m, N);

    MonteCarloSimulation(m, N, m0, runs, transactions, exchangeCounter);

    //showMeTheMoney(m, N);
    //cout << "Money has been exchanged " << exchangeCounter << " times." << endl;

    printTheMoney(m, N, runs);      // Writes m to file
    ofile.close();                  // Close file

    cout << endl; cout << "The program is finished running." << endl; cout << endl;
    return 0;
}

void giveMeTheMoney(vector<double> &m, int N) {
    m.resize(N); // Make money vector
    for (unsigned int i = 0; i < m.size(); i++) m.at(i) = 0.0; // Initialize money vector with zeros
}

void shareTheMoney(vector<double> &agents, int N, double m0) {
    agents.resize(N); // Make agents vector
    for (unsigned int i = 0; i < agents.size(); i++) agents.at(i) = m0; // Set equal amount of money to agents
}

bool compareTheMoney(double i, double j) {
    return (int(i) > int(j));
}

void MonteCarloSimulation(vector<double> &m, int N, double m0, int runs, int transactions, int &exchangeCounter) {
    random_device rd;                                                    // Initialize the seed
    mt19937_64 gen(rd());                                                // Call the Mersenne twister random number engine
    uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);   // Set up the uniform distribution for x in [0, 1]
    for (int i = 0; i < runs; i++) {
        vector<double> agents;    shareTheMoney(agents, N, m0);          // Initialize and restart agents vector
        for (int cycles = 1; cycles <= transactions; cycles++) {
            double epsilon = RandomNumberGenerator(gen);                 // Random number
            int i = RandomNumberGenerator(gen)*N;                        // Find a random pair of agents (i, j) to exchange money
            int j = RandomNumberGenerator(gen)*N;
            if (i != j) moneyExchange(agents, i, j, epsilon, exchangeCounter);  // If i different from j; exchange money
        }
        //showMeTheMoney(agents, N); cout << endl;

        stackTheMoney(agents, m, N); // Sort and stack the money in vector m

        //cout << endl; showMeTheMoney(agents, N); cout << endl;
    }
}

void moneyExchange(vector<double> &agents, int &i, int &j, double &epsilon, int &exchangeCounter) {
    double agents_i = agents.at(i);
    //double agents_j = agents.at(j); // No need
    agents.at(i) = epsilon*(agents.at(i) + agents.at(j));
    agents.at(j) = (1 - epsilon)*(agents_i + agents.at(j));
/*
    if ( (agents[i] + agents[j]) != (agents_i + agents_j) ) {
        //cout << agents[i] + agents[j] << endl;
        //cout << agents_i + agents_j << endl;
        cout << "Someone is draining the bank." << endl;
        cout << (agents[i] + agents[j])-(agents_i + agents_j) << endl;
    }*/
}

void stackTheMoney(vector<double> &agents, vector<double> &m, int N) {

    //cout << endl; showMeTheMoney(agents,N); cout << endl;

    //qsort(agents, N, sizeof(double), compareMoney);   // Sorts the money for stacking

    stable_sort(agents.begin(), agents.end()); // Sorts the money in ascending order
    reverse(agents.begin(), agents.end()); // Sets the money in descending order for stacking

    //cout << endl; showMeTheMoney(agents,N); cout << endl;

    for (int i = 0; i < N; i++) m.at(i) += agents.at(i);    // Stacks the sorted money in m
}

void showMeTheMoney(vector<double> &money, int N) {
    for(int i = 0; i < N; i++) cout << money.at(i) << endl;
}

void printTheMoney(vector<double> &m, int N, int runs) {
    double normalize = 1.0/runs; // Normalize the money when writing to file
    for (int i = 0; i < N; i++) ofile << setw(15) << setprecision(8) << m.at(i) * normalize;
}
