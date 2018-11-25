
// the source file essentially implements the 2 pay_off_price
// methods for the inherited subclasses of AsisnOption:

#ifndef _ASIAN_CPP
#define _ASIAN_CPP

#include <numeric>  // necessary for std::accumulate
#include <cmath>
#include "asian.h"

// =====================
// AsianOption
// =====================
// constructor using :
// it's an initialization list, do it for 2 things:
// 1. Calling base class constructors
// 2. Initializing member variables before the body of constructor executes
AsianOption::AsianOption(PayOff* _pay_off) : pay_off(_pay_off) {}


// =====================
// AsianOptionArithmetic
// =====================
AsianOptionArithmetic::AsianOptionArithmetic(PayOff* _pay_off) : AsianOption(_pay_off) {}

// Arithmetic mean pay-off price
double AsianOptionArithmetic::pay_off_price(const std::vector& spot_prices) const {
	unsigned num_times = spot_prices.size();
	double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), 0); // accumulate algorithm, pass in iterators
	double arith_mean = sum / static_cast<double>(num_times);
	return (*pay_off)(arith_mean);
}

// ====================
// AsianOptionGeometric
// ====================
AsianOptionGeometric::AsianOptionGeometric(PayOff* _pay_off)

// Geometric mean pay-off price
double AsianOptionGeometric::pay_off_price(const std::vector& spot_prices) const {
	unsigned num_times = spot_prices.size();
	double log_sum = 0.0;
	for (int i = 0; i < spot_prices.size(); i++) {
		log_sum += log(spot_prices[i]);
	}
	double geom_mean = exp(log_sum / static_cast<double>(num_times) );
	return (*pay_off)(geom_mean);
}

#endif

/*
	前面的两个class内部的pay_off_price都是被定义成了const method,
	The idea of const functions is not allow them to modify the object 
	on which they are called. It is recommended practice to make
	as many functions const as possible so that accidental changes
	to objects are avoided.
*/






