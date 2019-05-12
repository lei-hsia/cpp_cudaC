/* 
	In the future we may wish to price many differing types
	of exotic options via FDM. Thus it is sinsible to create a 
	VanillaOption class to encapsulate this functionality.

	In particular, I'm going to encapsulate the storage of 
	parameters of a European vanilla option. 

	Despite the fact that the interest rate r, and the 
	volatility sigma, are not part of an option term sheet,
	I include them as parameters for simplicity.

	Notice: 
	there's a pointer to the PayOff class. This allows us
	to use a call, put or some other form of pay-off without
	needing to expose this to the outside, which in this case
	is the FDM solver.

	It is quite common to include a pointer to the other class
	in another class

*/

#ifndef __VANILLA_OPTION_H
#define __VANILLA_OPTION_H

#include "payoff.h"


class VanillaOption {
public:
	PayOff* pay_off;

	double K;
	double r;
	double T;
	double sigma;

	// only constructors, both are taken care of in the 
	// member initialization list in cpp file
	VanillaOption();
	VanillaOption(double _K, double _r, double _T,
				  double _sigma, PayOff* _pay_off);

};

#endif