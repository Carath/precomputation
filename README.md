# Precomputation

Utility used to pre-compute values of a real-valued function, in order to speedup its evaluation
by returning approximate values. Only the 'precomputation.c' and 'precomputation.h' files need
to be included in a given project.


## How to use

Copy the following files in your project: *precomputation.c* and *precomputation.h*.
The other files are for demonstration purposes.


## Compilation

Compiling is done by running ``` make ```. Note that if using a custom made *makefile*, one should use as CFLAGS the option ``` -march=native ```, for enabling SSE and AVX instructions sets.


## Runtime

For testing the library:

```
./precomptest.exe
```
