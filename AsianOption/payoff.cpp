/*
 real meat: source file: PayOff.cpp

*/

#ifndef _PAY_OFF_CPP
#define _PAY_OFF_CPP

#include "payoff.h"

PayOff::PayOff() {}

// ==============
// PayOffCall
// ==============

// Constructor w. single strike parameter
PayOffCall::PayOffCall(const double& K) { K = _K; }

// Over-ridden operator() method, which turns PayOffCall into a function object
// 这里相当于是第二重重载,因为header file中已经有PayOffCall/Put重载了
// PayOff中的PayOff, 所以这里继续重载PayOffCall中的operator是第二重重载
double PayOffCall::operator() (const double& S) const {
	return std::max(S-K, 0.0);  // Euro Call
}

//  PayOffPut
PayOffPut::PayOffPut(const double& _K) { K = _K; }

// 重载operator() method, which turns PayOffPut into a function object
double PayOffPut::operator() (const double& S) const {
	return std::max(K-S, 0.0);
}

#endif
