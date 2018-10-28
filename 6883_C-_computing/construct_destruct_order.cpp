#include <iostream>
using namespace std;
/* call order of destructor & constructor:
	Base constructor,
	Derived constructor,
	Derived destructor,
	Base constructor
*/

class B{
public:
	B(){
		cout << "construct B" << endl;
	}

	virtual ~B(){
		cout << "destruct B" << endl;
	}
};

class D : public B{
public:
	D(){
		cout << "construct D" << endl;
	}

	virtual ~D(){
		cout << "destruct D" << endl;
	}
};

int main(int argc, char const *argv[])
{
	D d;
	return 0;
}

