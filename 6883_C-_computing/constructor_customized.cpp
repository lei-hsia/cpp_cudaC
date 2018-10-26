
class Account{

private:
	char *name;
	double balance;
	unsigned int id;

public:
	// declare constructors
	Account();
	Account(const Account &a);
	Account(const char *person);
}

// define constructors
Account::Account(){
	name = NULL;
	balance = 0.0;
	id = 0;
}

Account::Account(const Account &a){
	name = new char[strlen(a.name)+1];
	strcpy(name, a.name);
	// cannot:  name = a.name,因为name是一个pointer,
	// 这样是copy一个pointer,指向同一个object,并不是创建一个新的
	// pointer指向不同的东西
	balance = a.balance;
	id = a.id;
}

Account::Account(const char *person){
	name = new char[strlen(person)+1];
	strcpy(name, person);
	balance = 0.0;
	id = 0;
}
