
// BinModel01.h
// 头文件相当于interface, 在implement函数之前写好，
// 这样别人一看就知道有哪些东西

/*
	to minimize the potential for errors, C++ has adopted the
	convention of using header files to contain declarations.
	You make the declasrations in a header file ,then use the 
	#include directive in every .cpp file or other header file
	requires that declaration.
*/

/* 
	header files contain definitions of Functions & Variables, 
	which in IMPORTED or USED in any C++ program by using the 
	pre-processor #include statement. Header files have an 
	extension ".h" which contains C++ function declaration and
	macro definition
*/
#ifndef BinModel01_h
#define BinModel01_h

// compute risk-neutral prob
double RiskNeulProb(double U, double D, double R);

// compute the stock price at node n,i
double S(double S0, double U, double D, int n, int i);

// input, display and check model data
int GetInputData(double &S0, double &U, double &D, double &R);

#endif