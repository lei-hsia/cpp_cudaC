1. C++: pass-by-value VS pass-by-reference:
	a. by-value: called func e.g. swap() 接收的是calling func, e.g. main()中的value COPY, called/swap func改变了值之后不改变原calling func中的value;
	b. by-reference: called func,swap()接收的是calling func main()中的value ALIAS, 这会改变原calling func中的value;
	
2. pass-by-reference VS pass-by-pointer?
	a. when pass by reference, the parameter inside the called func is an alias to the the variable passed from outside;
	b. pass variable by a pointer, you take the address of the variable and pass the address into the function.
	c. Main difference: can pass values without an address(like a number) into a function which takes a const reference;
	d. but cannot pass address-less values into a func which takes const pointers