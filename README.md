# Precomputation

Utility used to pre-compute values of a real-valued function, in order to speedup its evaluation
by returning approximate values. Only the 'precomputation.c' and 'precomputation.h' files need
to be included in a given project.


## How to use

Copy the following files in your project: *precomputation.c* and *precomputation.h*.
The other files are for demonstration purposes. Below is an example of approximating ``` expf ``` between -10 and 10 with 25000 samples (no SIMD):

```C
Precomputation *precomputation = initPrecomputation(expf, 25000, -10.f, 10.f);
float approx = approximation(precomputation, 1.f); // 2.717305
freePrecomputation(&precomputation);
```


## Results

The following benchmark has been done on the ``` expf ``` function between -10 and 10.
Precision tests make use of 100M samples, and time tests use 3.725 GB of generated values aligned on 16-bit boundaries.
Note that measured times depend greatly on the ratio between the samples number and the CPU cache size, here of 6 MB (Intel i5-7300HQ 2.50GHz).
Values reported per cell are the speedup factor, and the mean relative error on the generated samples:

| Samples number | Approx | Approx + SIMD | Approx <br> with interpolation | Approx + SIMD <br> with interpolation |
| :------------: | :----------------: | :----------------: | :----------------: | :----------------: |
| 5K             | x 2.4 <br> 2.0e-03 | x 3.0 <br> 2.0e-03 | x 1.3 <br> 1.5e-06 | x 2.2 <br> 1.5e-06 |
| 10K            | x 2.4 <br> 1.0e-03 | x 3.0 <br> 1.0e-03 | x 1.3 <br> 3.6e-07 | x 2.0 <br> 3.6e-07 |
| 25K            | x 2.3 <br> 4.0e-04 | x 3.0 <br> 4.0e-04 | x 1.2 <br> 5.2e-07 | x 1.8 <br> 5.2e-07 |
| 50K            | x 2.1 <br> 2.0e-04 | x 2.9 <br> 2.0e-04 | x 1.1 <br> 3.7e-07 | x 1.7 <br> 3.7e-07 |
| 100K           | x 1.8 <br> 1.0e-04 | x 2.5 <br> 1.0e-04 | x 1.0 <br> 4.8e-07 | x 1.4 <br> 4.8e-07 |
| 500K           | x 1.6 <br> 1.9e-05 | x 1.9 <br> 1.9e-05 | x 0.9 <br> 4.4e-07 | x 1.2 <br> 4.4e-07 |
| 1M             | x 1.3 <br> 9.3e-06 | x 1.5 <br> 9.3e-06 | x 0.7 <br> 3.5e-07 | x 1.0 <br> 3.5e-07 |


## Compilation

Compiling is done by running ``` make ```. Note that if using a custom made *makefile*, one should use as CFLAGS the option ``` -march=native ```, for enabling SSE and AVX instructions sets.


## Runtime

For testing the library:

```
./precomptest.exe
```
