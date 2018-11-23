
/*
	In the original pricing model, the function PriceByCRR is like:

	double PriceByCRR(double S0, double U, double D, double R,
						int N, double K)

	we want the ability to add new payoff functions, based on the 
	mechanism speficied by PriceByCRR, i.e. add the KIND of pricing
	into PriceByCRR: add the payoff method as a function pointer
*/

double PriceByCRR(double S0, double U, double D, int N, double K,
					double (*payoff)(double z, double K));


// then in the Options03.h file, the only thing should be changed
// is the parameters of PriceByCRR