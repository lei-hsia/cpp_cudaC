
// STL 中的函数对象类模板
// 模版 equal_to, greater, less...是类模版, 可以生成函数对象


// 所以之前看到要从大到小排序用 greater
// e.g. greater 函数对象类模版, 这是greater已经定义好的代码
template<class T> 
struct greater : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const {
		return x > y;  // 跟一般的greater定义是相反的
	}
};  

#include <list>
#include <iostream>
using namespace std;

class MyLess {
public:
	bool operator() (const int& c1, const int& c2) {
		return (c1 % 10) < (c2 % 10);
	}
};

template<class T>
void Print(T fisrt, T last) {
	for ( ; first != last; ++first) cout << *first << ",";
}

int main() {
	const int SIZE = 5;
	int a[SIZE] = {5, 21, 14, 2, 3};
	list<int> lst(a, a+SIZE);
	lst.sort(MyLess());  // 通过函数对象进行排序
	Print(lst.begin(), lst.end());
	cout << endl;
	lst.sort(greater<int>());  // greater<int>()是一个对象
	Print(lst.begin(), lst.end());
	cout << endl;
	return 0;
}