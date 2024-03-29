#define _ISOC11_SOURCE // for aligned_alloc(). _Must_ be placed at the file beginning!

// Uncommenting what follows disable all assert in this file.
// It can also be defined via a makefile when all source files are targeted:
// #define NDEBUG

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for 'fabs'

#include "the_benchmark.h"
#include "blocks_to_bench.h"
#include "get_time.h"
// #include "rng32.h"
#include "rng64.h" // rng64_nextInt32() faster than rng32_nextInt() here.


// Settings:


// All values inside the preset range:
#define SIMUL_MIN -10.f
#define SIMUL_MAX 10.f

// Many values outside - most intensive case when branching. Precision loss to be expected:
// #define SIMUL_MIN -15.f
// #define SIMUL_MAX 15.f


#define ENABLE_WARMUP 1
#define ROUNDS_WARMUP 10000000

// Must be non-equal seeds, fixed for testing consistency!
#define SEED_GEN 123
#define SEED_TEST 456


// Returns the relative error between a reference and another value.
// Said error is in double precision, for better benchmark accuracy.
inline double relative_error(double ref, double value)
{
	assert(ref != 0); // cannot compute a relative error with a zero reference.
	return fabs((value - ref) / ref);
}


// Used as a warmup before the proper benchmark:
static double warmup_function(int rounds)
{
	double result = 0.123f;

	for (int i = 0; i < rounds; ++i) {
		result *= cos(result);
	}

	return result;
}


static void warmup(int rounds)
{
	if (!ENABLE_WARMUP)
		return;

	printf("\nWarmup:\n");

	double warmup_time_0 = get_time();
	double warmup_result = warmup_function(rounds);
	double warmup_time_1 = get_time();

	printf(" -> Time: %.3f s (result: %.3f)\n", warmup_time_1 - warmup_time_0, warmup_result);
}


static const float* generating_input_values(int test_number)
{
	#if PRECOMP_VECT_SIZE > 1
		printf("\n-> Data are aligned on %d-byte boundaries.\n", PRECOMP_ALIGNMENT);
		float *inputs_array = (float*) aligned_alloc(PRECOMP_ALIGNMENT, test_number * sizeof(float));
	#else
		float *inputs_array = (float*) malloc(test_number * sizeof(float));
	#endif

	if (!inputs_array)
	{
		printf("Not enough memory to allocate input values.\n");
		exit(EXIT_FAILURE);
	}

	rng64 rng;
	rng64_init(&rng, SEED_GEN, 0);

	const float delta = SIMUL_MAX - SIMUL_MIN;

	for (int i = 0; i < test_number; ++i) {
		inputs_array[i] = SIMUL_MIN + delta * rng64_nextFloat(&rng);
	}

	return inputs_array;
}


// Benchmarking the precomputation utility:
void benchmark(const Precomputation *precomputation, int test_number)
{
	warmup(ROUNDS_WARMUP);

	printf("\nGenerating input values:\n");
	const float *inputs_array = generating_input_values(test_number); // same values used in all tests.
	float ram_usage = test_number * (sizeof(float) / (1024.f * 1024.f * 1024.f));
	printf("-> Done. Using %.3f Go of RAM.\n", ram_usage);

	double ref_time = 0;
	double ref = benchmark_true_function(precomputation, inputs_array, test_number, &ref_time);

	benchmark_approximation(precomputation, inputs_array, test_number, ref, ref_time);

	#if PRECOMP_VECT_SIZE > 1
		benchmark_approx_simd(precomputation, inputs_array, test_number, ref, ref_time);
	#endif

	free((float*) inputs_array);
}


// Used to check the correctness of the approximation function:
void test_relative_error(const Precomputation *precomputation, float xmin, float xmax, int test_number)
{
	rng64 rng;
	rng64_init(&rng, SEED_TEST, 0);

	double sum = 0., max = 0., delta = xmax - xmin;

	for (int i = 0; i < test_number; ++i)
	{
		double x = xmin + delta * rng64_nextDouble(&rng);
		float y = precomputation -> theFunction(x);
		float approx = approximation(precomputation, x);
		double relat_error = relative_error(y, approx);

		sum += relat_error;
		max = max < relat_error ? relat_error : max;
	}

	sum /= test_number;

	printf("\nSampled relative error on preset interval:\n -> mean: %.3e, max: %.3e\n", sum, max);
}
