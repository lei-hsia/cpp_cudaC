
#include<iostream>
using namespace std;

class Complex {
private:
	int real, img;
public:
	// normal constructor
	Complex (int r = 0, int i = 0) {real = r; img = i;}

	// this is automatically called when '+' is used with
	// between two COmplex objects ; version: const: back
	Complex operator + (Complex const &obj) {
		Complex res;
		res.real = real + obj.real;
		res.img = img + obj.img;
		return res;
	}
	void print() { cout << real << " + " << img << " i "<< endl;}
}; 
// should have ; after class

int main() {
	Complex c1(10, 5), c2(2, 4);
	Complex c3 = c1 + c2;
	c3.print();
}