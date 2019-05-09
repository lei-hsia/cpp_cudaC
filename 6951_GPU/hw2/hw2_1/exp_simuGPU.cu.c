/* GPU code
*************
I mean to operate same-number multiplication from two vectors,
which is the same as performing an element-wise square operation
in one matrix.  

*************
*/

// CPU: 
/*
for (int i=0; i<64; ++i) {
    out[i] = in[i] * in[i];
} */

#include <stdio.h>
#include <sys/time.h>
#include <random>
#include <iostream>

/* The only thing changed in kernel: 
	1. kernel = square: h_in pattern numbers --> d_in
	2. kernel = inverseCDF: 
			generator uniform numbers: h_in --> d_in
*/

__global__ void inverseCDF(float *d_out, float *d_in) {
    int idx = threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = -log(1-f);
}

/*
__global__ void vectorMulti(float *d_out,float *d_a, float *d_b) {
	int idx = threadIdx.x;
	float fact1 = d_a[idx];
	float fact2 = d_b[idx];
	d_out[idx] = fact1 * fact2;
} */

int main(int argc, char ** argv) {
    const int ARRAY_SIZE = 1000000;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

    // uniform number generator
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);


    float h_in[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; ++i) {
        h_in[i] = dis(gen);
    }

    float h_out[ARRAY_SIZE];

    // 是按照 bytes 大小分配内存
    cudaMalloc((void **) &d_in, ARRAY_BYTES);
    cudaMalloc((void **) &d_out, ARRAY_BYTES);

    cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

    time_t current_time, current_time1;
	current_time = time(NULL);
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    inverseCDF<<<1, ARRAY_SIZE>>>(d_out, d_in);

    gettimeofday(&tp, NULL);
	long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	cout << (ms2 - ms1) << " milliseconds has passed in operations" << endl;

    cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

    // print results
    /*
    for (int i=0; i<ARRAY_SIZE; ++i) {
        printf("%f", h_out[i]);
        printf(((i%4) != 3) ? "\t" : "\n");
    }
	*/

    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}
