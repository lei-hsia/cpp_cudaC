
#ifndef Options03_h
#define Options03_h

// input and desplay option data
// N: expiration date; K: strike price
int GetInputData(int &N, int &K);

// pricing European option
double PriceByCRR(double S0, double U, double D, double R, int N, double K,
				  double (*payoff)(double z, double K));

// compute call payoff
double CallPayoff(double z, double K);

// compute call payoff
double PutPayoff(double z, double K);

#endif
