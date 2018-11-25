/*
C++ Virtual Destructors: How to Avoid Memory Leaks

once an inheritance hierarchy is created, 
with memory allocations occurring at each stage in the hierarchy, 
it is necessary to be very careful about 
how objects are destroyed so that any memory leaks are avoided:

virtual destructor
*/

/*
a virtual destructor ensures that when derived subclasses 
go out of scope or are deleted, the order of destruction of each 
class in a hierarchy is carried out correctly.
If the destruction order of the class objects is incorrect, 
it can lead to what is known as a memory leak. 
This is when memory is allocated by the C++ program 
but is never deallocated upon program termination

Since memory is a finite resource, 
if this leak persists over continued program usage, 
eventually there will be no available RAM (random access memory) 
to carry out other programs.

For instance, consider a pointer to a base class (such as PayOff) 
being assigned to a derived class object address via a reference. 
If the object that the pointer is pointing to is deleted, 
and the destructor is not set to virtual, 
then the base class destructor will be called 
instead of the derived class destructor. 
这个是pass by reference, baseClass的destructor没有设为virtual;
结果就是delete pointer指向的object的时候，直接就call了Base class的
destructor 而没有call Derived Class的destructor, 结果就是Derived
class中的field一些等等没有被delete: 导致了memory leak.
This can lead to a memory leak. Consider the following code:
*/

class Base {
public:
	Base();
	~Base();
};

class Derived : public Base {
private:
	double val;
public:
	Derived(const double& val);
	~Derived();
};

void do_something() {
	Base* p = new Derived;
	// Derived dustructor NOT CALLED!
	delete p;
}
// 相当于destruct的顺序：直接跳过了derived class的destructor, 直接call
// 了BaseClass的destructor

// 正确的: 
class Base {
public:
	Base();
	virtual ~Base();
};

class Derived : public Base {
private:
	double val;
public:
	Derived(const double& val);
	virtual ~Derived();
}

void do_something() {
	Base* p = new Derived;
	// Derived destructor is called
	delete p;
}

/*
	Once do_something() is called, delete is invoked on the pointer p.
	At code execution-time, the correct destructor is looked up in an
	object known as vtable. Hence the destructor associated with Derived
	will be called prior to a further call to the destructor associated
	with Base. This is the behavior we originally desired. val will be
	correctly deallocated. No memory leak this time.
*/





