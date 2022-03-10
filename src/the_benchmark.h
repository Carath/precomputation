#ifndef THE_BENCHMARK_H
#define THE_BENCHMARK_H


#include "precomputation.h"


// Returns the relative error between a reference and another value.
// Said error is in double precision, for better benchmark accuracy.
double relative_error(double ref, double value);


// Benchmarking the precomputation utility:
void benchmark(const Precomputation *precomputation, int test_number);


// Used to check the correctness of the approximation function:
void test_relative_error(const Precomputation *precomputation, float xmin, float xmax, int test_number);


#endif
