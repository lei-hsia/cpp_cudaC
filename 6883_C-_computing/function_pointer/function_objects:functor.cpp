
// function objects (functors)

#include <iostream>
using namespace std;

// Abstract base class
class BinaryFunction {
public:
	BinaryFunction() { };
	virtual double operator() (double left, double right) = 0; 
};

// Add 2 doubles
class Add : public BinaryFunction {
public:
	Add() {};
	virtual double operator() (double left, double right) {return left + right; }
};

// Multiply 2 doubles
class Multiply : public BinaryFunction {
public:
	Multiply() {};
	virtual double operator() (double left, double right) {return left*right; }
}

// function pointer作为formal parameter: 类型* pointerName
double binary_op(double left, double right, BinaryFunction* bin_func) {
	return (*bin_func)(left, right);
}


// function objects:  objects created from Add, Multiply class
int main() {
	double a = 5.0;
	double b = 10.0;

	BinaryFunction* pAdd = new Add();
	BinaryFunction* pMultiply = new Multiply();

	cout << "Add: " << binary_op(a,b, pAdd) << endl;
	cout << "Multiply: " << binary_op(a, b, pMultiply) << endl;

	delete pAdd;
	delete pMultiply;

	return 0;
}
