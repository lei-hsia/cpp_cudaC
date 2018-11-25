
// PayOff-Classes: header file
#ifndef _PAY_OFF_HPP
#define _PAY_OFF_HPP

#include <algorithm> // for std::max comparison, used in payoff calculation

class PayOff {
public:
	PayOff();
	virtual ~PayOff() {}; 

	// overload operator(), turns PayOff into an abstract function object
	virtual double operator() (const double& S) const = 0;
	// set: const = 0: says this method CANNOT be implemented 
	// within this class(= 0): it should be overridden by an 
	// inherited class(virtual).
}

class PayOffCall : public PayOff {
private:
	double K; 
public:
	PayOffCall(const double& K_);
	virtual ~PayOffCall() {};

	// virtual function os now overridden(not pure-virtual anymore)
	// 不是pure virtual: 因为没有const =0; 但是还是const,表明这个函数
	// 不修改任何东西，只是take/return value
	virtual double operator() (const double& S) const;
};

class PayOffPut : public PayOff {
private:
	double K; 
public:
	PayOffPut(const double& K_);
	virtual ~PayOffPut() {};

	// virtual function os now overridden(not pure-virtual anymore)
	virtual double operator() (const double& S) const;
};

#endif
