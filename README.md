# COMS4032A - Applications of Algorithms 

## Assignment Work

### Assignment 1: [Assignment 1 PDF](./Assignment%201/Assignment1.pdf)

### To run all algorithms and measure their runtimes:
```bash
g++ measure_runtime.cpp smm_algorithms.cpp -o measure_time
./measure_time
```

### To run the correctness check file:
```bash
g++ correctness_check.cpp smm_algorithms.cpp -o check
./check
```

### To run the memory usage file:
```bash
g++ measure_memory_usage.cpp smm_algorithms.cpp -o usage -lpsapi
./usage
```