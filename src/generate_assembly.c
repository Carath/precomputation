#include "precomputation.h"


// Only used for generating the assembly code for the approximation functions:


float generate_asm_approximation(const Precomputation *precomputation, float x)
{
	return approximation(precomputation, x);
}


#if PRECOMP_VECT_SIZE > 1
void generate_asm_approx_simd(const Precomputation *precomputation, float *dest_array, float *src_array)
{
	approx_simd(precomputation, dest_array, src_array);
}
#endif
