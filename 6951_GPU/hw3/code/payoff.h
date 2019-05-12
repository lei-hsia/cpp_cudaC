#ifndef _PAY_OFF_HPP
#define _PAY_OFF_HPP

#include <algorithm>

class payoff
{
public:
	payoff();
	// virtual destructor
	virtual ~payoff();
	
	// Overloaded () operator, turns the PayOff into an abstact function object
	virtual double operator() (const double& S) const = 0;
};

class PayOffCall : public PayOff {
private:
	double K; // strike price

public:
	PayOffCall(const double& K_);
	virtual ~PayOffCall() {};

	// override 
	virtual double operator() (const double& S) const;
};

class PayOffPut : public PayOff {
private:
	double K; // strike price

public:
	PayOffPut(const double& K_);
	virtual ~PayOffPut() {};

	// override 
	virtual double operator() (const double& S) const;
};

#endif