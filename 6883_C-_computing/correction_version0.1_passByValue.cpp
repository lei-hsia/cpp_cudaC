

// correction version0.1, still flawed: pass by value
int *GetNum(int a){
	int a; // local variable
	cin >> a;
	return &a;  // return addr(a)
}

int main(){
	int num = 0;
	int *ptr = NULL;
	ptr = GetNum(num);
	*ptr = *ptr+1;
	cout << *ptr;
	return 0;
}
