

// work well, pass by pointer
int *GetNum(int *a){
	cin >> *a;
	return a;  // return addr(a)
}

int main(){
	int num = 0;
	int *ptr = NULL;
	ptr = GetNum(num);
	*ptr = *ptr+1;
	cout << *ptr;
	return 0;
}
