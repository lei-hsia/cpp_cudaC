#include "BinModel01.h"
#include <iostream>
#include <cmath>

using namespace std;

double RiskNeutProb(double U, double D, double R){

	return (R-D)/(U-D);
}

double S(double S0, double U, double D, int n, int i){
	return S0 * pow(1+U,i) * pow(i+D, n-i);
}

int GetInputData(double &S0, double &U, double &D, double &R){

}

