
class Rectangle{

private:
	int width;
	int length;
public:
	void set(int w, int l);
	int area();
}

main(){
	Rectangle r1;

	r1.set(5,8);
	cout << r1.area() << endl; // dot notation

	Rectangle *r2;

	r2 = &r1;
	r2 -> set(8,10); // arrow notation

	Rectangle *r3;
	r3 = new Rectangle();

	r3 -> set(80,100);

	delete r3;
	r3 = NULL;  // r3: dynamically allocated
}


// if any constructor with any number of parameters is declared,
// no default constructor will exist