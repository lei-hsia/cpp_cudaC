
/*

Using binomial Pricer for asset pricing
stock price: S(n, i) = S(0)*(1+U)^i *(1+D^(n-i)
cout << "S(n,i)= " << S0 * pow(1+U,i) * pow(1+D, n-i) << endl;

*/



#include <iostream>
#include <cmath>
using namespace std;

int main(){
	double S0, U, D, R;

	// enter data
	cout << "enter S0: "; cin >> S0;
	cout << "enter U: "; cin >> U;
	cout << "enter D: "; cin >> D;
	cout << "enter R: "; cin >> R;

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

	// compute risk-neutral probability
	cout << "q= " << (R-D)/(U-D) << endl;

	// compute stock price at node n=3, i=2
	int n=3; int i=2;
	cout << "n= " << n << endl;
	cout << "i= " << i << endl;
	cout << "S(n,i)= " << S0 * pow(1+U,i)*pow(1+D, n-i) << endl;
	return 0; 
}