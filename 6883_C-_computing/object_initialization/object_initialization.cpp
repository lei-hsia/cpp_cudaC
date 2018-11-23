
class Rectangle
{
	private:
	   int width;
	   int length;
	public:
	   void set(int w, int l);
	   int area();
};


main()
{
	Rectangle r1;
	r1.set(5,8);  // dot notation

	Rectangle *r2; // pointer
	r2 = &r1;
	r2 -> set(8, 10); // arrow notation

	Rectangle *r3;
	r3 = new Rectangle();
	r3 -> set(80, 100);
	delete r3;  // delete pointer
	r3 = NULL;  // pointer要指向NULL
}

