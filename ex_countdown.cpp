#include <iostream>
#include <chrono>
#include <thread>

using std::cout; 
using std::endl;

int main(int argc, char const *argv[])
{
	cout << "countdown from 10 to -5:" << endl;

	for(int i=10; i>-6; i--){
		cout << i << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
