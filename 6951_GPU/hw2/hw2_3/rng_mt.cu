/* random number generator in CUDA
	
	Brownian motion evolves w. Normally distributed
	random steps, I use normal generator.
*/
#include <curand.h>

// var declaration
curandGenerator_t curandGenerator;

// curandCreateGenerator(generator_var, generator_method)
// use Mersenne Twister algorithm
curandCreateGenerator(&curandGenerator, CURAND_RNG_PSEUDO_MTGP32);

// set seed
curandSetPseudoRandomGeneratorSeed(curandGenerator, 1234ULL);

// generate normally distributed random numbers
curandGenerateNormal(curandGenerator, d_normal.getData(),
					N_NORMALS, 0.0f, sqrdt);

// destroy generator
curandDestroyGenerator(curandGenerator);