
/*
A friend function of a class is defined OUSIDE that class' scope 
but it has the right to access all private and protected members 
of the class. 

Even though the prototypes for friend functions appear 
in the class definition, friends are not member functions.

如果没有friend关键字, 那个function就是一个member function;
是friend of a class, friend xxx也要定义在class中,但是这个friend并不是
这个class的member function了

*/

class Box {
   double width;
   
   public:
      double length;
      friend void printWidth( Box box );
      void setWidth( double wid );
};


// to declare all member functions of class ClassTwo as friends
// of class ClassOne, place a 
friend class ClassTwo;
// in the definition of class ClassOne

// 是哪个class的friend, 就要定义在那个class中; 
// 但是这个friend并不是这个class的member function;
// 虽然这个friend也可以访问这个所在的class中的private登fields
#include <iostream>
using namespace std;

class Box {
	double width;

public:
	friend void printWidth(Box box);
	void setWidth(double wid);
};  // class finish后面要加;

// member function definition
void Box::setWidth(double wid) {
	width = wid;
}

// Note: printWidth(), a friend of class Box,
// is not a member function of any class
void printWidth(Box box) {
	/* Because printWidth() is a friend of Box, it can
	directly access any member of this class */
	cout << "Width of box: " << box.width << endl; 
}

int main() {
	Box box;

	// set box width without member function
	box.setWidth(10.0);

	// Use friend function to print the width
	// 因为不是member function,所以没有类对应的object来调用这个函数,
	// 所以用起来看起来跟static method一样
	printWidth(box);  

	return 0;
}















