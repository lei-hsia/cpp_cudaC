/*
	separating the math formula of PDE with FDM that solves it
	leads to the creation of the ConvectionDiffusionPDE and 
	BlackScholesPDE classes. 
	ConvectionDiffusionPDE is an abstarct base class, providing
	an interface for all subsequent inherited classes.


	BlackScholesPDE contains a public pointer member to a 
	VanillaOption class

*/

#ifndef _PDE_H
#define _PDE_H

#include "option.h"

// Convection Diffusion Equation - 2nd order PDE
class ConvectionDiffusionPDE {
public:
	// PDE coefficients
	virtual double diff_coeff(double t, double x) const = 0;
	virtual double conv_coeff(double t, double x) const = 0;
	virtual double zero_coeff(double t, double x) const = 0;
	virtual double src_coeff(double t, double x) const = 0;

	// Boundary and initial conditions
	virtual double boundary_left(double t, double x) const = 0;
	virtual double boundary_right(double t, double x) const = 0;
	virtual double init_cond(double x) const = 0;

};

class BlackScholesPDE : public ConvectionDiffusionPDE {
public:
	VanillaOption* option;
	// 成员变量: 在构造函数初始化的时候要作为参数传递进去
	BlackScholesPDE(VanillaOption* _option);

	virtual double diff_coeff(double t, double x) const ;
	virtual double conv_coeff(double t, double x) const ;
	virtual double zero_coeff(double t, double x) const ;
	virtual double src_coeff(double t, double x) const ;

	virtual double boundary_left(double t, double x) const ;
	virtual double boundary_right(double t, double x) const ;
	virtual double init_cond(double x) const ;

};

#endif