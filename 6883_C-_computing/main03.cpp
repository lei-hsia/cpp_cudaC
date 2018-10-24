#include <iostream>
#include <cmath>
using namespace std;

// computing risk-neutral probability
double RiskNeutProb(double U, double D, double R){
	return (R-D)/(U-D);
}

// computing the stock price at node n,i
double S(double S0, double U, double D, int n, int i){
	return S0 * pow(1+U, i) * pow(1+D, n-i);
}

// input, display and checking data
int GetInputData(double& S0, double& U, double& D, double& R){
	// enter data
	cout << "enter S0: "; cin >> S0;
	cout << "enter U: "; cin >> U;
	cout << "enter D: "; cin >> D;
	cout << "enter R: "; cin >> R;
	cout << endl;

	// make sure: S0>0, -1 < D < U, -1 < R
	if (S0<=0.0 || U <=-1.0 || D <=-1.0 || U <= D || R <= -1.0){
		cout << "illegal data ranges" << endl;
		cout << "Terminating program" << endl;
		return 1;
	}

	// checking arbitrage
	if(R>=U || R<=D){
		cout << "Arbitrage exists" << endl;
		cout << "Terminating program" << endl;
		return 1;
	}

	cout << "input data checked" << endl;
	cout << "There's no arbitrage" << endl << endl;
	return 0;
}

int main(){

	double S0, U, D, R;

	if(GetInputData(S0, U, D, R)==1) return 1;

	// compute risk-neutral probability
	cout << "q= " << RiskNeutProb(U,D,R) << endl;

	// compute stock price at node n=3, i=2
	int n=3; int i=2;
	cout << "n= " << n << endl;
	cout << "i= " << i << endl;
	cout << "S(n,i)= " << S(S0,U,D,n,i) << endl;

	return 0;

}