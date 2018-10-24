
// Options02.h: 
// the only difference is that InputData function
// now has parameters list elements of pointers


#ifndef Options02_h
#define Options02_h

// input and desplay option data
// N: expiration date; K: strike price
int GetInputData(int *PtrN, int *PtrK);

// pricing European option
double PriceByCRR(double S0, double U, double D, double R, int N, double K);

// compute call payoff
double CallPayoff(double z, double K);

#endif