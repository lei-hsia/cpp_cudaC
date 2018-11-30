
// 函数模板，支持同一个函数作用在多种类型变量上
/* declare:
	template <class identifier> function_declaration;
	template <typename identifier> function_declaration;
	核心: 在定义函数的时候并不指明是要用什么类型:这样使得多种类型都可以用;
	而在main中调用这个函数的时候才指明具体是什么类型
	 
*/

// function template
#include <iostream>
using namespace std;

template <class T>
T GetMax(T a, T b) {
	T result;
	result = (a>b)? a : b;
	return (result);
}

int main() {
	int i = 5, j = 6, k;
	long l = 10, m = 5, n;
	k = GetMax<int>(i, j);
	n = GetMax<long>(l, m);
	cout << k << endl;
	cout << n << endl;
	return 0;
}