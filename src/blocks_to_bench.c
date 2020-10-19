#include <stdio.h>
#include <stdlib.h>

#include "blocks_to_bench.h"
#include "the_benchmark.h" // for relative_error()
#include "get_time.h"


// Those functions are in their own translation unit, as to not
// be over optimised and thus enabling relevant benchmarks:


float benchmark_true_function(const Precomputation *precomputation, const float *inputs_array, int test_number)
{
	printf("\nBenchmark - True function:\n");

	double start = get_time();

	double sum = 0.;

	for (int i = 0; i < test_number; ++i)
	{
		sum += precomputation -> theFunction(inputs_array[i]);
	}

	double elapsed_time = get_time() - start;

	printf("\n(Real sum: %.3f)\n -> Time: %f s\n", sum, elapsed_time);

	return sum;
}


void benchmark_approximation(const Precomputation *precomputation, const float *inputs_array, int test_number, float ref)
{
	printf("\nBenchmark - Approximation:\n");

	double start = get_time();

	double sum = 0.;

	for (int i = 0; i < test_number; ++i)
	{
		sum += approximation(precomputation, inputs_array[i]);
	}

	double elapsed_time = get_time() - start;

	printf("\n -> Time: %f s\n -> Relative error: %.3e\n", elapsed_time, relative_error(ref, sum));
}


#if PRECOMP_VECT_SIZE > 1
void benchmark_approx_simd(const Precomputation *precomputation, const float *inputs_array, int test_number, float ref)
{
	printf("\nBenchmark - Approximation SIMD:\n");

	double start = get_time();

	const int remainder = test_number % PRECOMP_VECT_SIZE, bound = test_number - remainder;

	double sum = 0.;

	// This may be multithreaded:
	for (int i = 0; i < bound; i += PRECOMP_VECT_SIZE)
	{
		float __attribute__ ((aligned(PRECOMP_ALIGNMENT))) dest[PRECOMP_VECT_SIZE];

		approx_simd(precomputation, dest, (float*) inputs_array + i);

		// Same order, to get the exact same result:
		if (PRECOMP_VECT_SIZE == 4)
			sum = sum + dest[0] + dest[1] + dest[2] + dest[3];
		else // PRECOMP_VECT_SIZE == 8
			sum = sum + dest[0] + dest[1] + dest[2] + dest[3] + dest[4] + dest[5] + dest[6] + dest[7];
	}

	// Handling the remaining values:
	for (int i = bound; i < test_number; ++i)
	{
		sum += approximation(precomputation, inputs_array[i]);
	}

	double elapsed_time = get_time() - start;

	printf("\n -> Time: %f s\n -> Relative error: %.3e\n", elapsed_time, relative_error(ref, sum));
}
#endif
