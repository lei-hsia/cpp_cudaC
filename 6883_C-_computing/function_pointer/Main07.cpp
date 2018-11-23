
#include "BinModel01.h"
#include "Option03.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double S0, U, D, R;
	if (GetInputData(S0, U, D, R) == 1) return 1;
	double K;
	int N;
	cout << "Enter call optin data: " << endl;
	GetInputData(N, K);
	cout << "European call option price=" << PriceByCRR(S0,U,D,R,N,K,CallPayoff) << endl << endl;

	cout << "Enter put optin data: " << endl;
	GetInputData(N, K);
	cout << "European put option price=" << PriceByCRR(S0,U,D,R,N,K,PutPayoff) << endl << endl;

	return 0;
}