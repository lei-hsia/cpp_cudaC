
// financial engineering: use c++ queue:
// according to time data comes: first come, first processed
// same as stack problem: 
// interface was not designed for thread-safe.
// Solving approach: QUEUE: front()&pop()不分离, stack: top()&pop()

/*
Avoiding Data Race:
1. Use mutex to synchronize data access;
2. Never leak a handle of data to outside;
3. Design interface appropiately.
*/

#include <thread>
#include <string>
#include <mutex>  // mutual exclusive
using namespace std;

/*
mutex mu;

void shared_print(string msg, int id) {

	// mu must be bundled w. resources it's protecting
	lock_guard<mutex> guard(mu);  // mu unlock if out of scope
	// should exception happens, mu locks forever
	// mu.lock();
	cout << msg << id << endl;
	// mu.unlock();
}
*/

// more realistic
class LogFile {
	mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}  // Need destructor to close file
	void shared_print(string id, int value) {
		lock_guard<mutex> locker(m_mutex);
		f << "From " << id << ": " << value <<endl;
	}

	// Never return f to the outside world
	ofstream& getStream() { return f; }
};

void function_1(LogFile* log) {
	for (int i = 0; i > -10; i--)
		log.shared_print(string("From t1: "), i);
}

int main() {
	// 这样创建出来的logfile对象,一定会go through mutex
	LogFile log;
	thread t1(function_1, ref(log));
	// thread t1(function_1);

	for (int i = 0; i < 10; i++)
		shared_print(string("from main: "), i); 

	t1.join();
	return 0;
}

