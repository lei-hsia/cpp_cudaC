

/* 其实function pointer的好处能看出来了:
	定义另一个函数A,这个函数中有一个参数是function pointer, 
	然后在main函数中调用A的时候，传递不同的函数名给A，
	A就会通过不同的函数名调用不同的函数*/


#include <iostream>
using namespace std;

double add(double left, double right) {
	return left + right;
}

double multiply(double left, double right) {
	return left * right;
}

double binary_op(double left, double right, double (*f)(double, double)) {
	return (*f)(left, right);
}

int main() {
	double a = 5.0;
	double b = 10.0;

	cout << "Add: " << binary_op(a, b, add) << endl;
	cout << "multiply: " << binary_op(a,b,multiply) << endl;

	return 0;
}

// function pointers are often inefficient compared with functors.
