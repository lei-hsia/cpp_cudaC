
// 顺序结构

#include <vector>
// constructor
vector();
vector(int n);
vector(int n, const T& val);  // leetcode中用的最多
vector(iterator first, iterator last);

// func
void pop_back();  // 因为是添加到末尾
void push_back();  
int size();
T& front();
T& back();

vec.at(index);
vec.insert(pos, val);

vector<vector<int>> v(3); 

// list: 双向链表, list的各种内置函数
#include <list>
除了支持vector中定义的函数之外, 还支持: 
push_front(); 
pop_front();
sort();  // sort是list自己的sort, 不支持STL的sort
remove();
unique();
merge();
reverse();
splice();

// find, e.g.
list<A>::iterator p1, p2, p3;
p1 = find(lst1.begin(), lst1.end(), 3);
p2 = find(lst2.begin(), lst2.end(), 200);
p3 = find(lst2.begin(), lst2.end(), 400);
lst1.splice(p1, lst2, p2, p3); //将[p2,p3)插入p1之前, 并从lst2删除[p2,p3)

// deque: 双向队列
#include <deque>
