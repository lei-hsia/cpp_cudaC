/*
    第一个GPU程序:
    0,1,...63：前64个自然数求平方和
    只写最核心的部分
*/

// CPU code: sqaure each element of an array
// 只有一个线程, one independent path of execution through code;
// no explicit parallelism;
// 64次乘，如果一次 2 nanoseconds, 一共128纳秒
for (int i=0; i<64; ++i) {
    out[i] = in[i] * in[i];
}

// GPU:
// GPU 只是表述了kernel的任务, i.e. Express out = in * in; 并没有
// 写任何有关parallel的东西;
//
// CPU:
// 1. allocate memory
// 2. copy data to/from GPU
// 3. launch kernel <---- specifies degree of parallelism：这一步才是实现并发的地方!!!
//
// CPU code: squareKernel<<<64>>>(outArray, inArray)
//           这里做的是,写一个kernel这个kernel的名字叫squareKernel;
//           显式声明64个这样的kernel instances, 每个instance都会
//           执行一次GPU的kernel中的任务;
//     launch 64 instances of same program:
//          每个instance都知道自己是在哪个thread;
//     ---> assign thread N 解决第 N 个array;
//
//
// 1. 自己写kernel, 然后kernel每次在一个thread上面运行;
//     kernel 实际上就是要运行的program;
// 2. CPU launch很多threads, 每个thread都自己独立运行那个kernel
//
// 64次乘, 每个都是花费10纳秒: 因为并行所以一共也是10纳秒;
// GPU的latency是比CPU的时间长的，但是因为可以并行所以还是10纳秒

#include <stdio.h>
// kernel: 实际上就是要run的函数, 在GPU上运行
__global__ void square(float * d_out, float * d_in) {
    // kernel中, threadIdx是CUDA内置的变量, 这是一个C的struct,通过这个每个线程知道了自己的index
    // threadIdx有3个属性x,y,z;这里都用x以示区分
    // 所以main函数中创建了64个instances, 那么kernel函数中.x就是从0,1,...63
    int idx = threadIdx.x;
    float f = d_in[idx];  // read element: 从全局memory中读取这个index对应的元素值存进f
    d_out[idx] = f * f;
}

int main(int argc, char ** argv) {
    const int ARRAY_SIZE = 64;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

    // h: host;    d: device

    // generate input array on the host
    float h_in[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; ++i) {
        h_in[i] = float(i);
    }
    float h_out[ARRAY_SIZE];

    // declare GPU memory pointers
    float *d_in;
    float *d_out;

    // allocate GPU memory
    cudaMalloc((void **) &d_in, ARRAY_BYTES);
    cudaMalloc((void **) &d_out, ARRAY_BYTES);

    // transfer array to GPU (transfer input)
    // cudaMemcpy(dst, src, t_count)
    cudaMemcpy(d_in, h_in, ARRAY_BYTES,  cudaMemcpyHostToDevice);

    // launch the kernel (实际运行)
    // 函数定义为 __global__ void Func(float* parameter);
    // 这样被调用: Func<<<Dg, Db, Ns>>>(parameter);
    // Dg: dimension and size of grid;
    // Db: dimension and size of block;
    // Ns: shared memory中除静态内存外, 动态分配给每个block的内存
    // S: cudaStream_t的数量, default为0
    square<<<1, ARRAY_SIZE>>>(d_out, d_in);  // kernel传递的是kernel函数的参数/GPU程序的参数

    // copy back the result
    cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

    // print out the resulting array
    for (int i=0; i<ARRAY_SIZE; ++i) {
        printf("%f", h_out[i]);
        printf(((i%4) != 3) ? "\t" : "\n");
    }

    // free GPU memory allocation
    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}
