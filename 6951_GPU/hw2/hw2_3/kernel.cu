#include "kernel.h"

// GPU Monte Carlo simulation
__global__ void mc_kernel(
  float * d_s,
  float T,
  float B,
  float K,
  float S0,
  float sigma,
  float mu,
  float r,
  float dt,
  float * d_normals,
  unsigned N_STEPS,
  unsigned N_PATHS) {
      const unsigned tid = threadIdx.x;
      const unsigned bid = blockIdx.x;
      const unsigned bsz = blockDim.x;
      int s_idx = tid + bid * bsz;  // price array
      int n_idx = tid + bid * bsz;  // random num array
      float s_curr = S0;
      // array index is lower than max number of threads
      if (s_idx < N_PATHS) {
          int n = 0;
          // when reaches max steps or hit barrier, no need to loop
          do {
              s_curr = s_curr + mu*s_curr*dt + sigma*s_curr*d_normals[n_idx];
              ++n_idx;
              ++n;
          }
          while (n < N_STEPS && s_curr > B);
          // end loop, calculate payoff
          double payoff = (s_curr>K ? s_curr-K : 0.0);
          _syncthreads();
          // save to device price array
          d_s[s_idx] = exp(-r*T) * payoff;
      }
  }
// mc_call wrapper: call real kernel function
void mc_call(
    float * d_s,
    float T,
    float B, float K,
    float S0, float sigma, float mu, float r,

    float dt, float * d_normals,

    unsigned N_STEPS, unsigned N_PATHS) {
        const unsigned BLOCK_SIZE = 1024;
        const unsigned GRID_SIZE = ceil(float(N_PATHS)/float(BLOCK_SIZE));
        mc_kernel<<<GRID_SIZE, BLOCK_SIZE>>> (
            d_s,T,B,K,S0,sigma,mu,r,dt,d_normals,N_STEPS,N_PATHS
        );
    }
