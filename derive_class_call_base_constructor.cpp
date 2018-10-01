#include<iostream>
using namespace std;

// Constructor Rules for Derived Classes
/*
	The default constructor and the destructor of the
	base clas are always called when a new object of 
	a derived class is created or destroyed.
	*/
int main(){
		class A{
	public:
		A(){
			cout << "A:default" << endl;
		}
		A(int a){
			cout << "A:parameter" << endl;
		}
	}

	class B : public A{
	public:
		// no A constructor w. parameter call
		B(int a){
			cout << "B" << endl;
		}
	}

	class C : public A{
	public:
		C(int a):A(a){
			cout << "C" << endl;
		}
	}

	return 0; 
}
