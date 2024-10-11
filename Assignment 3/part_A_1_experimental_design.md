## Implementation Details for Disjoint Set Experiment

### Overview

The purpose of this experiment is to evaluate the performance of Disjoint Set operations, specifically focusing on the **Make-Set**, **Union**, and **Find-Set** operations. The experiment aims to provide empirical evidence for Theorem 21.2, which states that a sequence of \( m \) **Make-Set**, **Union**, and **Find-Set** operations takes \( O(m + n \log n) \) time when using the weighted-union heuristic.

### Key Components of the Implementation

1. **Disjoint Set Data Structure**:
   - The Disjoint Set (or Union-Find) data structure is used to manage a collection of non-overlapping sets.
   - Each element is initially in its own set. The **Make-Set** operation initializes the sets, while the **Union** operation combines two sets based on their sizes using the weighted-union heuristic, and the **Find-Set** operation identifies the representative (or root) of the set containing a specific element.

2. **Implementation of Operations**:
   - The operations are implemented in a class called `DisjointSet` that includes:
     - **Make-Set**: Initializes a single set for each element.
     - **Find-Set**: Returns the representative of the set that contains a specified element.
     - **Union**: Merges two sets based on their size using the weighted-union heuristic to ensure efficient operations.

### Weighted-Union Heuristic

1. **Principle**:
   - The weighted-union heuristic is implemented during the **Union** operation to optimize the structure of the sets. When merging two sets, the smaller set is appended to the larger set to keep the tree height minimal.
   - This is achieved by comparing the sizes of the two sets and making the root of the smaller set point to the root of the larger set.

2. **Implementation**:
   - The **Union** function uses the following logic:
     ```cpp
     if (size[root_x] < size[root_y]) {
         parent[root_x] = root_y; // Attach smaller set (root_x) to larger set (root_y)
         size[root_y] += size[root_x]; // Update the size of the new root
     } else {
         parent[root_y] = root_x; // Attach smaller set (root_y) to larger set (root_x)
         size[root_x] += size[root_y]; // Update the size of the new root
     }
     ```
   - This approach ensures that each union operation is efficient and minimizes future search times.

### Consistency Check

1. **Purpose**:
   - To ensure that the Disjoint Set implementation operates correctly after a series of **Make-Set** and **Union** operations, a consistency check is performed.
   - This check verifies that each element points to the correct representative of its set, maintaining the integrity of the data structure.

2. **Implementation**:
   - The **check_consistency** function iterates through all elements, asserting that the representative returned by **Find-Set** for each element matches the representative returned for its representative:
     ```cpp
     bool check_consistency(int n) {
         for (int i = 0; i < n; ++i) {
             if (FIND_SET(i) != FIND_SET(FIND_SET(i))) {
                 return false; // Inconsistent structure
             }
         }
         return true; // Consistent structure
     }
     ```
   - If the check passes, the structure is deemed consistent; otherwise, it indicates an error.

### Experiment Design

1. **Setup**:
   - The experiment is conducted by creating a `DisjointSet` instance for varying numbers of elements.
   - Each element in the set is represented by an index from `0` to `n-1`, where `n` is the number of elements.

2. **Selecting Elements for UNION Operations**:
   - For each UNION operation, two elements are randomly selected from the range of indices using:
     ```cpp
     ds.UNION(rand() % n, rand() % n);
     ```
   - This line generates two random integers in the range `[0, n-1]`, ensuring that the selected elements are valid indices in the Disjoint Set.
   - The randomness allows the experiment to simulate a realistic usage scenario, where elements are united without predictable patterns.

3. **Choice of Ranges for Elements and Operations**:
   - The ranges for the number of elements (`n`) and the number of operations (`m`) are chosen to cover a wide spectrum of potential use cases, reflecting small to very large datasets. The following arrays are used:
     ```cpp
     int num_elements[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
     int num_operations[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
     ```
   - Each element of `num_elements` corresponds to an entry in `num_operations`, allowing the experiment to evaluate the performance of the Disjoint Set operations with more operations than elements (e.g., \( m = 5000 \) for \( n = 1000 \)) and vice versa.

4. **Execution Timing**:
   - The execution time for the series of operations is measured using the `<chrono>` library. This is done by capturing the time before and after the operations:
     ```cpp
     auto start = chrono::high_resolution_clock::now();
     // Make n sets
     // Perform m UNION operations
     auto end = chrono::high_resolution_clock::now();
     ```
   - The elapsed time is computed and recorded for each experiment iteration.

### Conclusion

This experiment is designed to comprehensively assess the performance of Disjoint Set operations under various conditions, explicitly utilizing the weighted-union heuristic to optimize the union process. By varying the number of elements and operations while selecting elements randomly for union operations, the experiment captures the behavior of the algorithm in a realistic scenario. The data collected will facilitate the analysis of time complexity, supporting the theoretical claims made in Theorem 21.2.

The results will contribute to understanding how the performance of the Disjoint Set structure scales with increasing input sizes and operation counts.
