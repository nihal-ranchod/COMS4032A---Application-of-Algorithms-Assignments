# Disjoint Set Experiment: Implementation Details

## Overview

This project examines the performance of three different union operations within disjoint sets data structures:
1. **Basic Union**
2. **Weighted Union**
3. **Union-by-Rank with Path Compression**

The purpose of these experiments is to provide empirical evidence supporting **Theorem 21.1** from the textbook, which states:

> *Using the linked-list representation of disjoint sets and the weighted-union heuristic, a sequence of \( m \) MAKE-SET, UNION, and FIND-SET operations, \( n \) of which are MAKE-SET operations, takes \( O(m + n \log n) \) time.*

The experiments analyze the performance of these operations across a range of set sizes, providing insights into the efficiency of each union method.

## Theorem 21.1: Empirical Validation

Theorem 21.1 suggests that for \( m \) operations (a combination of MAKE-SET, UNION, and FIND-SET), with \( n \) MAKE-SET operations, the runtime is bounded by \( O(m + n \log n) \). This project aims to empirically validate this bound by recording execution times over increasingly large data sizes and observing how they scale.

### Experimental Setup and Theorem Coverage
1. **Setup**: For each size \( n \), an initial disjoint set of \( n \) elements is created using MAKE-SET operations. Each element starts as its own set.
2. **Operations**: 
   - UNION operations are performed between elements in sequence to reduce \( n \) individual sets into one.
   - This experiment focuses on UNION operations to assess how the union method’s runtime aligns with \( O(n \log n) \) scaling when combined with MAKE-SET operations.
3. **Measured Complexity**:
   - By measuring the execution time of UNION operations across various \( n \) sizes, we can observe how well they adhere to the expected complexity.
   - The **Weighted Union** operation specifically aligns with Theorem 21.1, as it utilizes a linked-list representation with a heuristic based on set sizes.

### Range of \( n \) Values
The experiment covers the following disjoint set sizes:
- 100, 500, 1,000, 5,000, 10,000, 25,000, 50,000, 100,000, 250,000, 500,000, 1,000,000

Each size \( n \) is tested 5 times, and the averaged results are recorded. This enables comparison across different sizes to evaluate how well the observed performance aligns with the expected \( O(n \log n) \) behavior.

## Union Operations Implementation

### Basic Union
This operation serves as a baseline and does not implement any heuristics to optimize for runtime. It merges two sets by directly reassigning elements.

### Weighted Union
Weighted Union leverages a heuristic where the smaller set is merged into the larger one, minimizing the growth of the data structure’s height. This method directly aligns with the requirements of Theorem 21.1 by employing a linked-list representation and the weighted-union heuristic, which theoretically provides \( O(n \log n) \) performance in the context of UNION and MAKE-SET operations.

### Union-by-Rank with Path Compression
Union-by-Rank further optimizes Weighted Union by ensuring that elements within each set point directly to the root. This reduces the time complexity of FIND-SET operations, making it potentially more efficient in practice, especially for large data sizes.

## Results and Analysis

The results from these experiments confirm that Weighted Union with the linked-list structure adheres closely to the \( O(m + n \log n) \) time bound stated in Theorem 21.1. The average performance of Weighted Union and Union-by-Rank across varying sizes can be found in `disjoint_set_average_results.csv`.

The empirical results support the theorem by showing how the weighted-union heuristic maintains efficiency even as \( n \) grows large, which demonstrates the effectiveness of the theoretical complexity bound when applied to practical scenarios.
