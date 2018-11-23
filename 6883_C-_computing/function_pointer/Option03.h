
#ifndef Option03_h
#define Option03_h

// input and display option data
int GetInputDat(int &N, double &K);

// pricing European option
double PriceByCRR(double S0, double U, double D, int N, double K,
					double (*payoff)(double z, double K));

// compute the call payoff
double CallPayoff(double z, double K);

// compute the put payoff
double PutPayoff(double z, double K);