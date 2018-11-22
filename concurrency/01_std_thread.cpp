
/*process vs threads:

1. Multiprocessing: Process1 <--> process2: through interprocess communications;

2. Multithreading: communicate through Shared Memory.

3. 多并发:
	a. pro: fast to start, low overhead: better performance
	b. Difficult to implement
	c. CAN'T RUN ON DISTRIBUTED SYSTEMS, while multiprocessing can easily run on distributed systems.
4. in this class, mainly: MULTITHREADING: provided in C++ library.
*/

#include <iostream>
#include <thread>
using namespace std;

void function1() {
	cout << "I like beauty" << endl;
}

int main() {
	// standard library: std::thread
	thread t1(function1); // t1 starts running

	// t1.join();  // main thread waits for t1 to finish
	t1.detach();  // t1 will run freely on its own: daemon process

	/*
	when use detach, daemon thread runs independently from the main
	thread, so usually you don't know which thread would finish first.
	So you might want to sychronize these threads, or make them run
	in a specific controllable order
	*/
	
	// once join/detach, can't do again; joinable(): detect
	if (t1.joinable())
		t1.join();

	return 0;
}


