
// 函数对象
// 如果一个类重载了运算符 (), 这个类的对象就是函数对象, 
// 因为对象会用 (), 这就像调用函数一样

class CMyAverage {  // 函数对象类
public:
	double operator() (int a1, int a2, int a3) {
		return (double)(a1+a2+a3)/3;
	}
};

CMyAverage average;  // 函数对象
cout << average(3,2,3); // 实际上是用: average.operator()(3,2,3)


// 函数对象的应用
// Dev C++ source code:
template<typename _InputIterator, typename _Tp> 
_Tp accumulate(_InputIterator _first, _InputIterator _last, _Tp _init) {
	for (; _first != _last; ++_first)
		_init = _init + *_first;
	return _init;
}
// accumulate用不同种类的binary操作
template<typename _InputIterator, typename _Tp, typename _BinaryOperation> 
_Tp accumulate(_InputIterator _first, _InputIterator _last, _Tp _init, 
				_BinaryOperation __binary_op) {
	for (; _first != _last; ++_first)
		_init = __binary_op(_init, *_first);
	return _init;
}

// 下面是一个实例
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

int sumSquares(int total, int value) {
	return total + value *value;
}

// 模版的核心: 类型当成参数传递, 所以不同类型传递这个参数就行了不用重复写函数／类
// 下面是一个函数模版
template<class T> void PrintInterval(T first, T last) {
	// 输出区间 [first, last)中的元素
	for (; first != last; ++first)
		cout << *first << " ";
	cout << endl;
}

// 下面是一个类模版
template<class T> class SumPowers {
	private:
		int power;
	public:
		SumPowers(int p): power(p){ }
		const T operator() (const T& total, const T& value) {
			T v = value;
			for (int i = 0; i < power - 1; ++i)
				v = v* value;
			return total + v;
		}
}

int main() {
	const int SIZE = 10;
	int a1[] = {1,2,3,4,5,6,7,8,9,10};
	vector<int> v(a1, a1+SIZE);
	cout << "1)"; 
	PrintInterval(v.begin(), v.end());

/*	这里accumulate调用 sumSquares 的具体实例化
	accumulate(vector<int>::iterator first, vector<int>::iterator last, 
				int init, int (* op)(int, int)) {
	for (; _first != _last; ++_first)
		init = op(init, *first);
	return init;
} */
	int result = accumulate(v.begin(), v.end(), 0, sumSquares);
	cout << "2) 平方和:" << result << endl;


	// SumPowers本来是一个类模板, 类后面加上< >指明类型之后, 
	// 具体化成了模版类, 因为这个类重载了( ), 所以可以直接加上()
	// 在类的后面: 这个 "类()" 就是函数对象 function object

/*	这里accumulate调用 SumPowers<int>(3) 的具体实例化
	accumulate(vector<int>::iterator first, vector<int>::iterator last, 
				int init, SumPowers<int> op) {
	for (; _first != _last; ++_first)
		init = op(init, *first);
	return init;
} */
	result = accumulate(v.begin(),v.end(),0, SumPowers<int>(3));
	cout << "3) 立方和:" << result << endl;

	result = accumulate(v.begin(),v.end(),0, SumPowers<int>(4));
	cout << "3) 4次方和:" << result << endl;

	// 看出，用函数对象的价值: 只用临时创建出来的函数对象就可以求不同
	// 任意次方的和, 用定义的类生成函数对象,然后就可以直接求次方和
	// 如果不用函数对象,要么对应每一个次方和要写一个函数,要么用全局变量
	// 记录这个几次方, 但是这样不符合OOP的思想了，都没有隔离开
	return 0;
}






