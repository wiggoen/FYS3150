#include <algorithm>  // std::stable_sort
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>     // std::vector


using namespace std;
ofstream ofile;
ofstream ofile2;

// By using long double we get less transaction error, but the program runs slower
#define double long double

// Declaration of functions
void MonteCarloSimulation(vector<double> &m, int N, double m0, int runs, int transactions, double &lambda, double &alpha, double &gamma);
void moneyExchange(vector<double> &agents, vector< vector<int> > &exchangeTracker, int &i, int &j, double &epsilon, double &lambda);
void giveMeTheMoney(vector<double> &m, int N);
void noExchange(vector< vector<int> > &exchangeTracker, int N);
void shareTheMoney(vector<double> &agents, int N, double m0);
void stackTheMoney(vector<double> &agents, vector<double> &m, int N);
void showMeTheMoney(vector<double> &money, int N);
void printTheMoney(vector<double> &m, int N, int runs);


int main(int numArguments, char **arguments)
{
    // Default if there is no command line arguments
    //string billOfAbundance = "../Project_5/outputs/noEqualityForFatCats_onerun.txt";  // Output file
    string billOfAbundance = "noEqualityForFatCats_testrun2_N1000_L0_a2_g1.txt";  // Output file
    int N = 1000;//500;             // Number of agents
    double m0 = 1.0;         // Amount of money at start
    int transactions = 1e5;//1e7;  // Number of transactions
    int runs = 1e3;//1e4;          // Monte Carlo cycles ([1e3, 1e4] runs)
    double lambda = 0.0;     // {0.0, 0.25, 0.5, 0.9}
    double alpha = 2.0;      // {0.0, 0.5, 1.0, 1.5, 2.0}
    double gamma = 1.0;      // {0.0, 1.0, 2.0, 3.0, 4.0}

    // If command line arguments are defined
    //if (numArguments >= 2) billOfAbundance = "../Project_5/outputs/"+string(arguments[1]);
    if (numArguments >= 2) billOfAbundance = string(arguments[1]);
    if (numArguments >= 3) N = atoi(arguments[2]);
    if (numArguments >= 4) m0 = atof(arguments[3]);
    if (numArguments >= 5) transactions = atoi(arguments[4]);
    if (numArguments >= 6) runs = atoi(arguments[5]);
    if (numArguments >= 7) lambda = atof(arguments[6]);
    if (numArguments >= 8) alpha = atof(arguments[7]);
    if (numArguments >= 9) gamma = atof(arguments[8]);


    vector<double> m;                       // Vector of money
    giveMeTheMoney(m, N);                   // Initialize money vector

    ofile.open(billOfAbundance);            // Open data file for writing

    MonteCarloSimulation(m, N, m0, runs, transactions, lambda, alpha, gamma);

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

void MonteCarloSimulation(vector<double> &m, int N, double m0, int runs, int transactions, double &lambda, double &alpha, double &gamma) {
    random_device rd;                                                   // Initialize the seed
    mt19937_64 gen(rd());                                               // Call the Mersenne twister random number engine
    uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);  // Set up the uniform distribution for x in [0, 1]

    double c = 0;
    double p = 0;

    for (int run = 1; run <= runs; run++) {
        if (run == 1) ofile2.open("variance.txt");                      // Open variance file for writing
        vector<double> agents;                                          // Vector that keep track of the agents money before sorting and stacking
        shareTheMoney(agents, N, m0);                                   // Initialize / restart agents vector
        vector< vector<int> > exchangeTracker;                          // Matrix that keep track of exchanges
        noExchange(exchangeTracker, N);                                 // Initialize / restart exchangeTracker

        for (int interaction = 1; interaction <= transactions; interaction++) {
            double epsilon = RandomNumberGenerator(gen);                // Random number
            int i = RandomNumberGenerator(gen)*N;                       // Find a random pair of agents (i, j) to exchange money
            int j = RandomNumberGenerator(gen)*N;
            double r = RandomNumberGenerator(gen);
            //double c;
            // Only using the upper triangle of the exchangeTracker matrix ij = ji
            if (i > j) {
                c = exchangeTracker.at(j).at(i) + 1;
            } else {
                c = exchangeTracker.at(i).at(j) + 1;
            }
            if ((agents.at(i) - agents.at(j)) == 0) {
                p = 1.0;
            } else {
                p = pow(fabs(agents.at(i)-agents.at(j)), -alpha)*pow(c, gamma);
            }
            //cout << c << setw(15) << agents.at(i) << setw(15) << agents.at(j) << setw(15) << p << endl;

            //double p = pow(fabs(agents.at(i)-agents.at(j)), -alpha)*pow(c, gamma);
            if (i != j && r < p) moneyExchange(agents, exchangeTracker, i, j, epsilon, lambda);  // If i different from j; exchange money


            if (run == 1) {
                double var = 0;
                for (int k = 0; k < N; k++) {
                    var += (agents.at(k) - m0)*(agents.at(k) - m0);
                }
                double variance = var/N;
                ofile2 << variance << endl;
                //cout << variance << endl; // << interaction << setw(15)
            }
        }
        if (run == 1) ofile2.close();

        stackTheMoney(agents, m, N); // Sort and stack the money in vector m

        //averageMoney

        //printTheMoney(agents, N, run); // Printing mean values per run
    }
}

void moneyExchange(vector<double> &agents, vector< vector<int> > &exchangeTracker, int &i, int &j, double &epsilon, double &lambda) {
    //double agents_i = agents.at(i);
    ////double agents_j = agents.at(j); // No need

    double dm = (1.0 - lambda)*(epsilon*agents.at(j) - (1.0 - epsilon)*agents.at(i));
    agents.at(i) = agents.at(i) + dm;
    agents.at(j) = agents.at(j) - dm;

    // Registrating transaction, only using the upper triangle of the exchangeTracker matrix ij = ji
    // (condition) ? (if_true) : (if_false)
    (i > j) ? (exchangeTracker.at(j).at(i) += 1) : (exchangeTracker.at(i).at(j) += 1);

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
    for (int i = 0; i < N; i++) ofile << setw(15) << setprecision(8) << m.at(i) * normalize << endl;
}



