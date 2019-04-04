/*
    易错点; 很多维状态下的 threadIdx, blockIdx, blockDim, gridDim
    这4个都是CUDA内置的参数，每个都是有自己的x, y, z方向上的值，map
    映射一般是用这些各个单位内的index映射得到全局index:

    如果就是一个平面上的pixel: gridDim就可以不管, 因为都是1;
    blockDim.x,y,z 给的是某一个方向上的block内的thread数目；
    gridDim.x,y,z  给的是某一个方向上的grid内的block的数目;

    blockDim.x * gridDim.x : x方向上的所有的thread的数量
    >>> 还是 blockDim.x * blockIdx.x ????
*/

__global__
void rgba_to_grey(const uchar4* const rgbaImage,
                  unsigned char* const greyImage,
                  int numRows, int numCols)
{
    //TODO
    // Fill in the kernel to convert from color to greyscale
    // the mappinng from components of a uchar4 to RGBA is:
    // .x -> R ; .y -> G; .z -> B; .w -> A/alpha:transparency
    //
    // The output (greyImage) at each pixel should be the result of
    // applying the formula: out = .299f * R + .587f * G + .114f * B;
    // Note: we will ignore the alpha channel for this conversion
    //
    // First create a mapping from the 2D block and grid locations
    // to an absolute 2D location in the image, then use that to
    // calculate a 1D offset

    // 解题:
    // 每个block在其所在的grid中, 有自己的blockIdx; 每个block有自己的dim;
    // 每个thread在其所在block中, 有自己的threadIdx;
    // blockDim实际上是这个block含有的thread的数量:
    // blockIdx * blockDim 得到前面所有的thread的数量, 加上当前的threadIdx得到globalIdx
    int y = threadIdx.y + blockIdx.y * blockDim.y;
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    if (y < numCols && x < numRows) {
        int index = numRows*y + x;
        uchar 4 color = rgbaImage[index];  // 1D结果: 每个线程的全局index
        unsigned char grey = (unsigned char)(0.299f*color.x+0.587f*color.y+0.114f*color.z);
        greyImage[index] = grey;
    }
}

void your_rgba_to_greyscale(const uchar4* const h_rgbaImage, uchar4* const d_rgbaImage,
                          unsigned char* const d_greyImage, size_t numRows, size_t numCols)
{
    // You must fill in the correct sizes for the blockSize and gridSize
    // currently only one block with one thread is being launched

    int blockWidth = 32;

    // const dim3 blockSize(1, 1, 1); // TODO
    const dim3 blockSize(blockWidth, blockWidth, 1);

    int blockX = numRows/blockWidth + 1;
    int blockY = numCols/blockWidth + 1

    const dim3 gridSize(blockX, blockY, 1);  // TODO
    rgba_to_grey<<<gridSize, blockSize>>>(d_rgbaImage, d_greyImage, numRows, numCols);

    cudaDeviceSynchronize();  checkCudaErrors(cudaGetLastError());
}
