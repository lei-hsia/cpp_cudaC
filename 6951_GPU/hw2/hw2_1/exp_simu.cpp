#include <iostream> 
#include <fstream>
#include <thread> 
#include <random>
#include <future>
#include <vector>
#include <math.h>
// #include <iomanip>
// #include <sys/time.h>
using namespace std; 

/*   g++ multithreading_demo.cpp -std=c++11 -pthread  */

float expSimu(int n, int k) {
	// for simplicity, assume mu = 1, then X = -ln(1-u)
	
	ofstream myfile;
	myfile.open("simu_res.txt");

	vector<float> vec(n);

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    float sum = 0;
	for (int i=0; i<n; ++i) {
		vec[i] = dis(gen);
		vec[i] = (-1) * log(1-vec[i]);
		sum += vec[i];
		// 其实这样写入file有问题, 因为最后一次的会覆盖之前所有的
		// myfile << i+1 << ", " ;
		myfile << vec[i] << endl;
	}

	cout << "sum" << k << " = " << sum << endl;
	float mean = sum / n;
	cout << "mean" << k << " = " << mean << endl;
	
	float variance = 0;
	for (int i=0; i<n; ++i) {
		variance += pow(vec[i]-mean, 2);
	}
	variance /= n;
	cout << "variance" << k << " = " << variance << endl;

	float std_dev = sqrt(variance);
	cout << "std_dev" << k << " = " << std_dev << endl;
	cout << endl;

	myfile.close();
	return sum;
}


int main() {
	cout << endl; 
	cout << "Assume mu = 1 for simplicity, then X = -ln(1-u)" << endl;
	cout << "Use 4 threads to generate X: " << endl;
	cout << endl;
	/* 1. thread
	thread t1(expSimu, 250000, 1);   t1.join();
		
		2. async; return something
	auto future1 = async(expSimu, 250000, 1);
	float sum1 = future1.get();
	*/
	float total = 0;
	float total_var = 0;
	/*
	time_t current_time, current_time1;
	current_time = time(NULL);
	
	struct timeval tp;
	gettimeofday(&tp, NULL);
	float ms1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	*/
	for (int i=1; i<5; ++i) {
		auto future = async(expSimu, 250000, i);
		float sum  = future.get();
		total += sum;
	} 
	/*
	current_time1 = time(NULL);
	gettimeofday(&tp, NULL);
	float ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	*/
	float mean = total / 1e6; 
	cout << "total_mean" << " = " << mean << endl;
	cout << endl;

	// cout << setprecision(7) << (ms2-ms1) << " milliseconds has passed in operations" << endl;

	/*
	for (int i=1; i<5; ++i) {
		thread t(expSimu, 250000, i);   t.join();
	} */

	return 0;
}