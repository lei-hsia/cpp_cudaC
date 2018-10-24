#### dynamic memory allocation

1. can allocate storage for a variable while program is running: memory not pre-defined, but dynamically allocated when program is running!

2. Use <b>new</b> operator to allocate memory

```
double *dptr;
dptr = new double;
```

1. new returns address of memory allocation

2. release Dynamic Memory: delete; ONLY use delete to free dynamic memory

3. Dangling pointer: if it contains the address of memory that has been freed by a call to delete: solution: set such pointers to 0 as soon as memory is freed

4. memory leak: if no-longer-needed dynamic memory is not freed. Solution: free up dynamic memory after use

5. Function should only return a pointer:
```int* newNum()```
	a. to data that was passed to the function as an argument
	b. to dynamically allocated memory
	
6. structure variables:

```
// similar: dict of python
struct Student{...}; 

Student *stuPtr = &stu1;

// Need () when using * and .
(*stuPtr).studentID = 12204;
```
7. Simple notation than ( *ptr).member

```
//Use: ptr->member:
stuPtr->studentID = 12204;
// in place of (*ptr).member:
(*stuPtr).studentID = 12204;
```


















