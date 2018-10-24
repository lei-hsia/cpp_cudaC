#include <stdio.h>

void swapNum(int &i, int &j){
	int temp = i;
	i=j;
	j = temp;
}

void swapNum2(int i, int j){
	int temp = i;
	i=j;
	j = temp;
}

int main(void){
	int a = 10;
	int b = 20;

	int c = 10;
	int d = 20;

	swapNum(a,b);
	swapNum2(c,d);
	printf("A is %d, B is %d\n", a, b);  // A is 20, B is 10;
	printf("C is %d, D is %d\n", c, d);  // C is 10, D is 20;
	return 0;
}

/* pass by reference: pass the refenence/alias to the function
	this will indeed change the value in the calling function,
	i.e. main() here. Value in the called function is also changed
	i.e. Values in called function swap() and calling function
	main() are both changed

	pass by value: pass the COPY of the value to the called func;
	this will change the value in the called function, i.e. swap,
	but those are value copy of initial arguments, so it doesn't 
	change the initial values. i.e. will not change the value of
	a. b

*/

// 一句话总结: 

// by value: called func takes value copy of arguments from calling
// func, does NOT change value in the calling func

// by reference: called func takes value ALIAS of arguments from 
// calling func, WILL CHANGE value in the calling func.