
#ifndef Options01_h
#define Options01_h

// input and desplay option data
// N: expiration date; K: strike price
int GetInputData(int &N, int &K);

// pricing European option
double PriceByCRR(double S0, double U, double D, double R, int N, double K);

// compute call payoff
double CallPayoff(double z, double K);

#endif
