/*
When a class is declared with no constructors,
the compiler automatically assumes default 
constructor and copy constructor for it.

If any constructor with any number of parameters is declared, 
no default constructor will exist, unless you define it
*/

class Rectangle {
private:
	int width;
	int length;
public:
	Rectangle();
	Rectangle(const Rectangle &r);
	Rectangle(int w, int l);

	void set(int w, int l); // method, not constructor
	int area();
}

Rectangle::Rectangle() {};

// copy constructor
Rectangle::Rectangle(const Rectangle &r) {
	width = r.width;
	length = r.length;
}

// initlaize w. default constructor, usual & dynamic
Rectangle r1;
Rectangle *r3 = new Rectangle();


Rectangle r4;
r4.set(60, 80);
// initialize w. copy constructor
Rectangle r5 = r4;  // copy assignment, 用了copy constructor
Rectangle r6(r4);  // 这个最典型!!! 直接用了copy constructor参数形式
Rectangle *r7 = new Rectangle(r4); // dynamic，还是用了copy constructor

