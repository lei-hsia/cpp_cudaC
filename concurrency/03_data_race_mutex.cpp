
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
	// 如果没有mutex,两个thread competes running for the same common resources: cout.
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

////////////////////////////	                       ThreadA 			ThreadB
class stack {						
	int* _data;				     int v = st.top();//6
	std::mutex _mu;	   	 if stack:				   int v = st.top();//6
public:					6		st.pop(); //6
	void pop();			8					st.pop(); //8
	int& top();			3					process(v);
	// ...				9		process(v);
};								
							Then: 6 is processed twice, 
void function_1(stack& st) {				      8 is never processed/lost.
	int v = st.top();				NOT THREAD SAFE.
	st.pop();					reason: interface is not designed to be
	process(v);					thread-safe: DON'T separate them:
}
///////////////////////////

解决办法: pop()的同时top(): 不要分离interface的功能。
///////////////////////////
class stack {
	int* _data;
	std::mutex _mu;
public:
	int& pop();  // pop, return a value/ top() at the same time
	int& top();
	// ...
};

void function_1(stack& st) {
	int v = st.pop();
	process(v);
//////////////////////////

新的问题: STL的interface的功能不分离使得thread-safe,但是此时不是exception-safe, 这也是为什么pop()设计的时候并没有让其返回一个value,
	but that would not be my interest here.







