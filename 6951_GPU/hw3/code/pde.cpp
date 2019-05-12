/*
	pde.cpp: implements virtual methods for BlackScholesPDE
	class. In particular, the diffusion, convection, zero-term
	and source coefficients are provided, based on the BS
	equation. In this instance, x is the spot price.

*/
#ifndef _PDE_CPP
#define _PDE_CPP

#include "pde.h"
#include <math.h>

BlackScholesPDE::BlackScholesPDE(VanillaOption* _option) : option(_option) {}

// Diffusion coefficient
double BlackScholesPDE::diff_coeff(double t, double x) const {
	double vol = option->sigma;
	return 0.5*vol*vol*x*x; // 1/2 * sigma^2 * S^2
}

double BlackScholesPDE::conv_coeff(double t, double x) const {
	return (option->r)*x;  // rS
}

double BlackScholesPDE::zero_coeff(double t, double x) const {
	return -(option->r); // -r
}

// Source coefficient
double BlackScholesPDE::source_coeff(double t, double x) const {
  return 0.0;
}

// left boundary-condition (vanilla call)
double BlackScholesPDE::boundary_left(double t, double x) const {
	return 0.0; 
}

double BlackScholesPDE::boundary_right(double t, double x) const {
	return (x - (option->K)*exp(-(option->r)*((option->T)-t)));
}

double BlackScholesPDE::init_cond(double x) const {
	return option->pay_off->operator()(x);
}

#endif