#include <stdio.h>
#include <stdlib.h>

#include "precomputation.h"


// Allocates and initializes the pre-computation:
Precomputation* initPrecomputation(RealValuedFunction theFunction, int sampleNumber, float xMin, float xMax)
{
	if (sampleNumber < 2)
	{
		printf("Sample number must be greater or equal than 2.\n");
		exit(EXIT_FAILURE);
	}

	if (xMin >= xMax)
	{
		printf("xMin must be lower than xMax.\n");
		exit(EXIT_FAILURE);
	}

	Precomputation *precomputation = (Precomputation*) calloc(1, sizeof(Precomputation));

	if (!precomputation)
	{
		printf("NULL Precomputation.\n");
		exit(EXIT_FAILURE);
	}

	// Working: let us denote 'sampleNumber' by 'n'. The precomputed values array will be
	// of length n + 2, and for an input value 'x', its associated index in said array will be:
	// - if x < xMin : 0
	// - if xMin <= x < xMax : somewhere in [1, n - 1]
	// - if x >= xMax : n
	// The two first values (indexes 0 and 1) will be equal, and so will be the two last values (indexes n and n + 1).
	// Those redundant values are of use when the interpolation option is enabled, in order both to assure no array
	// overflow occurs, and that the returned values for inputs outside the preset interval are always the exact images
	// of the given function, at the relevant boundaries, i.e f(xMin) and f(xMax) respectively.

	// N.B: inverse of step size is stored, in order to do multiplications instead of divisions during the runtime.
	*(int*) &(precomputation -> lastIndex) = sampleNumber;
	*(float*) &(precomputation -> invStepSize) = (sampleNumber - 1) / (xMax - xMin);
	*(float*) &(precomputation -> offset) = 1.f - xMin * precomputation -> invStepSize;

	float *precomputedValues = (float*) calloc(sampleNumber + 2, sizeof(float)); // 2 values in excess!

	if (!precomputedValues)
	{
		printf("Not enough memory to allocate pre-computed values.\n");
		free(precomputation);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < sampleNumber; ++i) // sampling stored at indexes in [1, n].
		precomputedValues[i + 1] = theFunction(xMin + i / precomputation -> invStepSize);

	// First and last values are redundant!
	precomputedValues[0] = precomputedValues[1];
	precomputedValues[sampleNumber + 1] = precomputedValues[sampleNumber];

	*(float**) &(precomputation -> precomputedValues) = precomputedValues;
	*(RealValuedFunction*) &(precomputation -> theFunction) = theFunction;

	return precomputation;
}


// Frees the given Precomputation, given by address.
void freePrecomputation(Precomputation **precomputation)
{
	if (!precomputation || !*precomputation)
		return;

	free((float*) ((*precomputation) -> precomputedValues));
	free(*precomputation);
	*precomputation = NULL;
}
