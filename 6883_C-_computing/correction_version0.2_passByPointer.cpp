
#include<iostream>
#include<stdio.h>

using std::cin;
using std::cout;

// work well, pass by pointer
int *GetNum(void){
	int *aptr = new int; // local variable
	cin >> *aptr;
	return aptr;  // return addr(a)
}

int main(){
	int *ptr = NULL;
	ptr = GetNum();
	*ptr = *ptr+1;
	cout << *ptr;
	return 0;
}
