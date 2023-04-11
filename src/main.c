#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "the_benchmark.h"


///////////////////////////////////////////////////
// Functions to pre-compute:

float tanh_2(float x)
{
	return 1.f - 2.f / (1.f + expf(2.f * x));
}


float sigmoid(float x)
{
	return 1.f / (1.f + expf(-x));
}


// Choice of function to evaluate:
// #define to_approximate tanhf // massive performance difference!
// #define to_approximate tanh_2 // closer times - tanhf is terribly slow!
// #define to_approximate sigmoid
#define to_approximate expf


int main(void)
{
	int sample_number = 25000;
	float xmin = -10.f, xmax = 10.f;

	// Adding an offset so that benchmark_test_number % 4 != 0 :
	int benchmark_test_number = 1000000000 + 2; // the benchmark will use ~ 3,9 GB of RAM!
	int verif_test_number = 100000000;

	Precomputation *precomputation = initPrecomputation(to_approximate, sample_number, xmin, xmax);

	float x = 1.f;
	float real_value = precomputation -> theFunction(x);
	float approx = approximation(precomputation, x);

	printf("\nSample number: %d\n\n", sample_number);
	printf("f(%.3f) = %f\n", x, real_value);
	printf("Approx. of f(%.3f) = %f\n", x, approx);
	printf(" -> Relative error: %.3e\n", relative_error(real_value, approx));

	test_relative_error(precomputation, xmin, xmax, verif_test_number);

	benchmark(precomputation, benchmark_test_number);

	freePrecomputation(&precomputation);

	return EXIT_SUCCESS;
}
