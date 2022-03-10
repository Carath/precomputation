#ifndef BLOCKS_TO_BENCH
#define BLOCKS_TO_BENCH


#include "precomputation.h"


// Those functions are in their own translation unit, as to not
// be over optimised and thus enabling relevant benchmarks.

// Note that printed relative errors are computed only on the values sum, thus aren't relevant
// to measure the approximation precision and are only used to check results coherence.

double benchmark_true_function(const Precomputation *precomputation, const float *inputs_array, int test_number, double *ref_time);

void benchmark_approximation(const Precomputation *precomputation, const float *inputs_array,
	int test_number, double refSum, double ref_time);

#if PRECOMP_VECT_SIZE > 1
void benchmark_approx_simd(const Precomputation *precomputation, const float *inputs_array,
	int test_number, double refSum, double ref_time);
#endif


#endif
