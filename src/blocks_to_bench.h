#ifndef BLOCKS_TO_BENCH
#define BLOCKS_TO_BENCH


#include "precomputation.h"


// Those functions are in their own translation unit, as to not
// be over optimised and thus enabling relevant benchmarks:

float benchmark_true_function(const Precomputation *precomputation, const float *inputs_array, int test_number);

void benchmark_approximation(const Precomputation *precomputation, const float *inputs_array, int test_number, float ref);

#if PRECOMP_VECT_SIZE > 1
void benchmark_approx_simd(const Precomputation *precomputation, const float *inputs_array, int test_number, float ref);
#endif


#endif
