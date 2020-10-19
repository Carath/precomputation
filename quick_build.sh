#!/bin/sh

# Building the project:
make clean
echo ''
make
echo ''

# Generating the assembly code, for the approximation functions:

COMP=gcc
# COMP=clang

# For enabling SSE/AVX instructions set:
PROCESSOR_ARCH=-march=native

(set -x; $COMP -std=c99 -Wall -O2 $PROCESSOR_ARCH src/generate_assembly.c -S) #echo on

echo ''

# Running the benchmark:

# ./exec
