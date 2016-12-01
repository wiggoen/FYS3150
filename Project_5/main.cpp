#include <algorithm>  // std::stable_sort
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>     // std::vector


using namespace std;
ofstream ofile;

// By using long double we get less transaction error, but the program runs slower
#define double long double

// Declaration of functions
void MonteCarloSimulation(vector<double> &m, vector< vector<int> > &exchangeTracker, int N, double m0, int runs, int transactions, double &lambda, double &alpha, double &gamma, int &exchangeCounter);
void moneyExchange(vector<double> &agents, vector< vector<int> > &exchangeTracker, int &i, int &j, double &epsilon, double &lambda, int &exchangeCounter);
void giveMeTheMoney(vector<double> &m, int N);
void noExchange(vector< vector<int> > &exchangeTracker, int N);
void shareTheMoney(vector<double> &agents, int N, double m0);
void stackTheMoney(vector<double> &agents, vector<double> &m, int N);
void showMeTheMoney(vector<double> &money, int N);
void printTheMoney(vector<double> &m, int N, int runs);
bool compareTheMoney(double i, double j);


int main(int numArguments, char **arguments)
{
    // Default if there is no command line arguments
    //string billOfAbundance = "../Project_5/outputs/noEqualityForFatCats_onerun.txt";  // Output file
    string billOfAbundance = "noEqualityForFatCats_run.txt";  // Output file
    int N = 500;             // Number of agents
    double m0 = 1.0;         // Amount of money at start
    int transactions = 1e7;  // Number of transactions
    int runs = 1e4;          // Monte Carlo cycles ([1e3, 1e4] runs)
    double alpha = 0.0;      // {0.0, 0.5, 1.0, 1.5, 2.0}
    double lambda = 0.0;     // {0.0, 0.25, 0.5, 0.9}
    double gamma = 0.0;      // {0.0, 1.0, 2.0, 3.0, 4.0}

    // If command line arguments are defined
    //if (numArguments >= 2) billOfAbundance = "../Project_5/outputs/"+string(arguments[1]);
    if (numArguments >= 2) billOfAbundance = string(arguments[1]);
    if (numArguments >= 3) N = atoi(arguments[2]);
    if (numArguments >= 4) m0 = atof(arguments[3]);
    if (numArguments >= 5) transactions = atoi(arguments[4]);
    if (numArguments >= 6) runs = atoi(arguments[5]);
    if (numArguments >= 7) alpha = atof(arguments[6]);
    if (numArguments >= 8) lambda = atof(arguments[7]);
    if (numArguments >= 9) gamma = atof(arguments[8]);


    // Initialize counter, money vector, open file for writing and start timer
    int exchangeCounter = 0;                // Counts the number of exchanges
    vector<double> m;                       // Vector of money
    giveMeTheMoney(m, N);                   // Initialize money vector
    vector< vector<int> > exchangeTracker;  // Matrix that keep track of exchanges
    noExchange(exchangeTracker, N);         // Initialize exchangeTracker

    ofile.open(billOfAbundance);            // Open file for writing

    MonteCarloSimulation(m, exchangeTracker, N, m0, runs, transactions, lambda, alpha, gamma, exchangeCounter);

    printTheMoney(m, N, runs);              // Writes m to file
    ofile.close();                          // Close file

    cout << "\n" << "The program is finished running." << "\n" << endl;
    return 0;
}

void giveMeTheMoney(vector<double> &m, int N) {
    m.resize(N, 0.0); // Make money vector, initializing it with zeros
}

void noExchange(vector< vector<int> > &exchangeTracker, int N) {
    exchangeTracker.resize(N, vector<int>(N, 0)); // Make exchange matrix, initializing it with zeros
}

void shareTheMoney(vector<double> &agents, int N, double m0) {
    agents.resize(N, m0); // Make agents vector, initializing it with m0
}

void MonteCarloSimulation(vector<double> &m, vector< vector<int> > &exchangeTracker, int N, double m0, int runs, int transactions, double &lambda, double &alpha, double &gamma, int &exchangeCounter) {
    random_device rd;                                                   // Initialize the seed
    mt19937_64 gen(rd());                                               // Call the Mersenne twister random number engine
    uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);  // Set up the uniform distribution for x in [0, 1]
    for (int i = 0; i < runs; i++) {
        vector<double> agents;                                          // Vector that keep track of the agents money before sorting and stacking
        shareTheMoney(agents, N, m0);                                   // Initialize / restart agents vector
        for (int cycles = 1; cycles <= transactions; cycles++) {
            double epsilon = RandomNumberGenerator(gen);                // Random number
            int i = RandomNumberGenerator(gen)*N;                       // Find a random pair of agents (i, j) to exchange money
            int j = RandomNumberGenerator(gen)*N;
            double r = RandomNumberGenerator(gen);
            double c;
            // Only using the upper triangle of the exchangeTracker matrix ij = ji
            if (i > j) {
                c = exchangeTracker.at(j).at(i) + 1;
            } else {
                c = exchangeTracker.at(i).at(j) + 1;
            }
            double p = pow(fabs(agents.at(i)-agents.at(j)), -alpha)*pow(c, gamma);
            if (i != j && r < p) moneyExchange(agents, exchangeTracker, i, j, epsilon, lambda, exchangeCounter);  // If i different from j; exchange money
        }
        stackTheMoney(agents, m, N); // Sort and stack the money in vector m
    }
}

void moneyExchange(vector<double> &agents, vector< vector<int> > &exchangeTracker, int &i, int &j, double &epsilon, double &lambda, int &exchangeCounter) {
    //double agents_i = agents.at(i);
    ////double agents_j = agents.at(j); // No need
    //agents.at(i) = epsilon*(agents.at(i) + agents.at(j));
    //agents.at(j) = (1 - epsilon)*(agents_i + agents.at(j));

    double dm = (1.0 - lambda)*(epsilon*agents.at(j) - (1.0 - epsilon)*agents.at(i));
    agents.at(i) = agents.at(i) + dm;
    agents.at(j) = agents.at(j) - dm;

    exchangeTracker.at(i).at(j) += 1;

    /*
    if ( (agents[i] + agents[j]) != (agents_i + agents_j) ) {
        //cout << agents[i] + agents[j] << endl;
        //cout << agents_i + agents_j << endl;
        cout << "Someone is draining the bank." << endl;
        cout << (agents[i] + agents[j])-(agents_i + agents_j) << endl;
    }*/
}

void stackTheMoney(vector<double> &agents, vector<double> &m, int N) {
    stable_sort(agents.begin(), agents.end());            // Sorts the money in ascending order
    reverse(agents.begin(), agents.end());                // Sets the money in descending order for stacking
    for (int i = 0; i < N; i++) m.at(i) += agents.at(i);  // Stacks the sorted money in m
}

void showMeTheMoney(vector<double> &money, int N) {
    for(int i = 0; i < N; i++) cout << money.at(i) << endl;
}

void printTheMoney(vector<double> &m, int N, int runs) {
    double normalize = 1.0/runs; // Normalize the money when writing to file
    for (int i = 0; i < N; i++) ofile << setw(15) << setprecision(8) << m.at(i) * normalize;
}
