/*
    square 改成 cube; 其他的不变
    这次不写一大堆注释了
*/
#include <stdio.h>

// __global__: CUDA knows it's a kernel
__global__ void cube(float* d_out, float* d_in) {
    // threadIdx: CUDA内置的成员,表示在block中的index, 有3个成员属性x,y,z;
    // 这里都用x对应自己的index; threadIdx实际上是C中的struct
    // 所以main函数中创建了64个instances, 那么kernel函数中.x就是从0,1,...63
    int idx = threadIdx.x;
    // read element: 从全局memory中读取这个index对应的元素值
    float f = d_in[idx];
    d_out[idx] = f * f * f;
}

int main(int argc, char **argv) {
    const int ARRAY_SIZE = 96;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

    // generate input array on the host
    float h_i[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; ++i) {
        h_in[i] = float(i);
    }
    float h_out[ARRAY_SIZE];

    // declare GPU memory pointers
    float * d_in;
    float * d_out;

    // allocate GPU memory
    cudaMalloc((void **) &d_in, ARRAY_BYTES);  // 因为内存分配都是按字节来的
    cudaMalloc((void **) &d_out, ARRAY_BYTES);

    // transfer array to GPU
    cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

    // launch the kernel
    cube<<<1, ARRAY_SIZE>>>(d_out, d_in);

    // copy back the result from GPU to CPU
    cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

    // print the resulting array
    for (int i=0; i<ARRAY_SIZE; ++i) {
        printf("%f", h_out[i]);
        printf(((i%4) != 3) ? "\t" : "\n");
    }

    // free GPU memory allocation
    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}
