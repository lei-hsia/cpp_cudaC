1. pointer can be used as an array name!!

```
int *valptr = vals;
valptr[1]; // equals: vals[1]
```

```
int *a;// *前有dt, *: pointer
* vals; // *前没有dt, *: dereference

int &b=a; // &前有dt, &: reference, i.e.创建一个新的label/alias, 指向同一个object
&a; // &前没有dt, &: address operator: 取地址符
```

1. if(ptr1== ptr2) //compare addresses
2. if(*pr1== *pr2) //compare contents

<b>pointers as function parameters</b>
1. pointer can be parameters;
2. works like a reference parameter to allow <b>changes to argument from within called function</b>


1. 如果parameters是pointer; 
	a. void swap(int *x, int *y){…}
	b. 调用: swap(&num1, &num2); // 给地址2. 如果parameters是reference, i.e. alias,
	a. void swapNum(int &i, int &j){…}
	b. swapNum(a,b); // 直接给值

1. pointer to a constant: cannot change the value that is pointed at;
```const double *ratePtr;```
2. constant pointer: address in pointer cannot change once pointer is initialized:
```int *const classPtr= &classSize;```

