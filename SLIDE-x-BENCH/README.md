# SLIDE-x-Bench
This directory contains all the benchmarks that can be used to calculate the Processor's metrics. In the README.md file of each directory, it is specified the equation used to calculate the occupied memory. The result of this equation is used to estimate a number that works as an upper bound for the ranges included in the parameters.json.

The 8051's instruction set simulator (ISS) needs to set its I/O ports to 0 to stop its execution. The following equation does not comprise, the memory occupied, to store the values of the variables representing the ports.


## Framework Benchmark
The benchmark contains the functions that can be used to calculate the processor's metrics:
* AFFINITY
  * Allpass
  * Bitrev
  * Can
  * Conv
  * Corr
  * Dir
  * FDCT
  * FDCT Init
  * Fibonacci 1
  * Fibonacci 2
  * Tap
  * Viterbi
  * Wave
  * Wrap
* KERNEL
  * A-star
  * Banker's algorithm
  * Bellman-ford
  * Breadth-first search
  * Depth-first search
  * Binary search
  * Dijkstra
  * Quick sort
  * Merge sort
  * Selection sort
  * Straight sort
* POLYBENCH
* RECIPE
  * Bubble sort
  * Bubble sort 100
  * Cnt
  * Factorial
  * FDCT
  * FFT
  * Fibonacci
  * Insertion sort
  * Lud
  * Matrix Multiplication
  * Park-miller
  * Prime
  * Select
  * Shell sort
  * Sqrt

#### Files 
Each directory contains:
* frst.c: contains the code to be executed on the ISS/HLS tools; 
* scnd.c: includes the code executed on the Intel MCS-51 (8051); 
* parameters.c: contains the possible values assumed by the parameters of each function;
