
#include <iostream>
#include <thread>
using namespace std;

void function_1() {
	cout << "from thread: aaaaaa" << endl;
}

// thread can run any Callable objects, e.g.
// functors, function objects
class Fctor {
public:
	/*
	void operator()() {
		for (int i = 0; i > -10; i--)
			cout << "from t1" << i << endl;
	} */
	void operator()(string msg){
		cout << "t1 says" << msg <<endl;
		msg = "change msg, main still same as t1: prove pass-by-value" ;
	}
};

int main() {
	thread t1(function_1);  // t1 starts running
	string s = "thread: pass-by-value, even & in params";
	// 用括号包起来创建一个functor对象, 传入的参数写在后面
	thread t1((Fctor()), s); 

	// pass-by-reference
	thread t1((Fctor()), ref(s)); 
	// pass by pointer, move的时候functor的参数必须是pass by value
	thread t1((Fctor()), move(s)); 
	// 实际上， thread对象自身: 永远都只能be moved, CAN'T be copied
	thread t2 = t1;  // wrong: can't copy thread: 想一想,copy thread完全没有解释性
	thread t2 = move(t1);  // right
	// 此时下面的t1.join() 要改成 t2.join(),因为t1已经没有了

	/*
	pass by value: thread default, inefficient
	pass by reference: dangerous, data overwrite
	pass by pointer: safe & efficient
	*/

	总是希望开thread: as many as possible;但是不希望 #thread > #CPU cores,
	这样会有 too many context switching: bad performance;
	called: Oversubscription;
	reference:  thread::hardware_concurrency(); // indication
	/*
	Fctor fct;
	thread t2(fct);
	thread t2(Fctor());  //报错, thread内,functor会被当成一个函数调用,而不是object
	thread t2((Fctor()));  // 用括号包起来就对了
	*/
	try {
	//	for (int i = 0; i< 10; i++)
	//		cout << "from main: " << i << endl;
		cout << "from main: " << s << endl;

	} catch (...) {
		t1.join();  // exceptions: main still waits for t1
		throw;
	}

	t1.join(); 
	// t2.join();

	return 0;
}