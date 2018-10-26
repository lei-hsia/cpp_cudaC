
// clean-up of an object
class Account{
private:
	char *name;
	double balance;
	unsigned int id; // unique
public:
	Account();
	Account(const Account &a);
	Account(const char *person);
	~Account();
}

Account::~Account(){
	delete[] name;
}

/*
	name: class name preceded by a tilde

	has no argument

	used to release dynamically allocated memory and 
	to perfomr other 'cleanup' activities

	executed automatically when the object 
	goes out of scope

*/

// constructor, copy constructor, destructor:
// all automatically created by the compiler