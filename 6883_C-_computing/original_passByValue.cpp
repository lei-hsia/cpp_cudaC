
#include<iostream>
#include<stdio.h>

using std::cin;
using std::cout;

// ORIGINAL SERIOUSLY FLAWED
int *GetNum(void){
	int a; // local variable
	cin >> a;
	return &a;  // return addr(a)
}

int main(){
	int *ptr = NULL;
	ptr = GetNum();
	*ptr = *ptr+1;
	cout << *ptr;
	return 0;
}
