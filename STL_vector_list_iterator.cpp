
#include <vector>;
using namespace std;
// Iterator of vector:  random access iterator

// several ways of traversal vector:
vector <int> v(100);
int i;

for(i=0; i<v.size(); i++){
	cout << v[i];  // 根据下标随机访问
}

vector<int>::const_iterator ii;

for (ii = v.begin(); ii != v.end(); ii++)
	cout << *ii;

for (ii = v.begin(); ii < v.end(); ii++)
	cout << *ii;

// 间隔一个输出
ii = v.begin();
while (ii < v.end()){  //可以用大于小于比较，因为是随机访问迭代器
	cout << *ii;
	ii = ii + 2;
}


// list的迭代器是双向迭代器
// 正确的方法
#include <list>

list<int> v;
list<int>::const_iterator ii;
for (ii = v.begin(); ii != v.end(); ++ii)  // 可以用 !=
	cout << *ii;

// ERROR !! 因为双向迭代器不支持<
for (ii = v.begin(); ii < v.end(); ii++)
	cout << *ii;

// list也没有 [ ] 成员函数
for (int i = 0; i < v.size(); i++)
	cout << v[i];
