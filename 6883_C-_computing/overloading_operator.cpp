
class Complex{
private:
	int real;
	int img;
public:
	Complex():real(10), img(0){ }
	Complex(int real_, int img_): real(real_), img(img_) { }
	Complex(const Complex &c): real(c.real), img(c.img) { }
	~Complex() { }

	// solve:
	Complex operator+(const Complex &c); 
	Complex operator+(int b_);

	// operator(int b_, const...): outside Complex,
	// cannot access private fields real/img,
	// declare as friend
	friend Complex operator+(int b_, const Complex &c);

	friend ostream & operator<<(ofstream & out, const Complex & c);
}

void main(){
	Complex c1;
	Complex c2(2,3);
	Complex c3(c2);

	// cannot: add objects
	// 2 operations: assign, add
	c1 = c2 + c3; 

	// after overloading operator: 
	// equivalent:  c1  = c2.+(c3); 

	int b = 4;
	c1 = c2 + b;  // Complex Complex::operator+(int b_){
	c1 = b + c2;  

	cout << c1; // <=>  cout.<<(c1); 
}

// operator overloading

/*
	for assigment operator, of no overloading, C++ would do memcpy:
	memcpy( &Dest.object, &source.object, sizeof(source.object ))
*/

// call Constructor twice:
// 1. inside function, call Constructor, live within scope;
// 2. return a Complex, create complex outside function, 
//	  called the copy constructor
Complex Complex::operator+(const Complex &c){
	return Complex(real + c.real, img + c.img);
}

Complex Complex::operator+(int b_){
	return Complex(real+b, img);
}

// no "Complex::", so should declare this function as friend
Complex operator+(int b_, const Complex &c){
	return Complex(b_ + c.real, c.img);
}


ostream & operator<<(ostream &out, const Complex &c){
	out << "real: " << c.real << "img: " << c.img << endl;
	return out;
}


