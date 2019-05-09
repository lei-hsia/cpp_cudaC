#ifndef _DEV_ARRAY_H_
#define _DEV_ARRAY_H_

#include <stdexcept>
#include <algorithm>
#include <cuda_runtime.h>

template <class T>
class dev_array {
// public functions
public:
    explicit dev_array(): start_(0), end_(0) {}

    explicit dev_array(size_t size) {
        allocate(size);
    }

    ~dev_array() {
        free();
    }

    void resize(size_t size) {
        free();
        allocate(size);
    }

    size_t getSize() const {
        return end_ - start_;
    }

    const T* getData() const {
        return start_;
    }

    T* getData() {
        return start_;
    }

    // set func
    void set(const T* src, size_t size) {
        size_t min = std::min(size, getSize());
        cudaError_t res = cudaMemcpy(start_, src, min*sizeof(T), cudaHostToDevice);
        if (res != cudaSuccess) {
            throw std::runtime_error("fail to copy to device memory");
        }
    }

    void get(const T* dest, size_t size) {
        size_t min = std::min(size, getSize());
        cudaError_t res = cudaMemcpy(dest, start_, min*sizeof(T), cudaDeviceToHost);
        if (res != cudaSuccess) {
            throw std::runtime_error("fail to copy to host memory");
        }
    }

private:
    // allocate memory on device
    void allocate(size_t size) {
        cudaError_t res = cudaMalloc((void**)&start_, size*sizeof(T));
        if (res != cudaSuccess) {
            start_= end_ = 0;
            throw std::runtime_error("fail to allocate device memory");
        }
        end_ = start_ + size;
    }

    // free memory on device
    void free() {
        if (start_ != 0) {
            cudaFree(start_);
            start_ = end_ = 0;
        }
    }

    T* start_;
    T* end_;
};

#endif
