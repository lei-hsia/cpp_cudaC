
// calculate the factorial of integer n

// recursive:
unsigned int factorial(unsigned int n) {
	if (n==0) return 1;
	return n * factorial(n-1);
}

// iterative:
unsigned int iter_factorial(unsigned int n) {
	unsigned int ret = 1;
	for (unsigned int i  = 1; i <= n; i++)
		ret *= i;
	return ret;
}

// dp
#define ll long long;
int result[1000] = {0};
ll fact_dp(int n) {
	if (n >= 0) {
		result[0] = 1;
		for (int i = 1; i <= n; i++)
			result[i] = i * result[i-1];
		return result[n];
	}
}