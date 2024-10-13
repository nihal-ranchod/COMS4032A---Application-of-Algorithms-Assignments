
## Implementation Details for Disjoint Set Experiment

### Overview

The purpose of this experiment is to evaluate the performance of Disjoint Set operations, specifically focusing on the **Make-Set**, **Union**, and **Find-Set** operations. The experiment aims to provide empirical evidence for Theorem 21.2, which states that a sequence of \( m \) **Make-Set**, **Union**, and **Find-Set** operations takes \( O(m + n \log n) \) time when using the weighted-union heuristic.

### Key Components of the Implementation

1. **Disjoint Set Data Structure**:
   - The Disjoint Set (or Union-Find) data structure manages a collection of non-overlapping sets. Each element starts in its own set.
   - The **Make-Set** operation initializes the sets, the **Union** operation combines two sets based on their sizes using the weighted-union heuristic, and the **Find-Set** operation identifies the representative (or root) of the set containing a specific element.

2. **Implementation of Operations**:
   - The operations are encapsulated in a class called `DisjointSet`, which includes:
     - **MAKE_SET**: Initializes a single set for each element.
     - **FIND_SET**: Returns the representative of the set that contains a specified element.
     - **UNION**: Merges two sets based on their sizes using the weighted-union heuristic to ensure efficient operations.

### Weighted-Union Heuristic

1. **Principle**:
   - The weighted-union heuristic optimizes the structure of the sets during the **Union** operation. When merging two sets, the smaller set is appended to the larger set to minimize tree height.
   - This is accomplished by comparing the sizes of the two sets and making the root of the smaller set point to the root of the larger set.

2. **Implementation**:
   - The **UNION** function employs the following logic:
     ```cpp
     if (size[root_x] < size[root_y]) {
         parent[root_x] = root_y; // Attach smaller set (root_x) to larger set (root_y)
         size[root_y] += size[root_x]; // Update the size of the new root
         depth[root_y] = max(depth[root_y], depth[root_x] + 1);
     } else {
         parent[root_y] = root_x; // Attach smaller set (root_y) to larger set (root_x)
         size[root_x] += size[root_y]; // Update the size of the new root
         depth[root_x] = max(depth[root_x], depth[root_y] + 1);
     }
     ```
   - This approach guarantees that each union operation is efficient and minimizes future search times.

### Consistency Check

1. **Purpose**:
   - To ensure the Disjoint Set implementation operates correctly after a series of **MAKE_SET** and **UNION** operations, a consistency check is performed.
   - This check verifies that each element points to the correct representative of its set, maintaining the integrity of the data structure.

2. **Implementation**:
   - The **check_consistency** function iterates through all elements, asserting that the representative returned by **FIND_SET** for each element matches the representative returned for its representative:
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
   - The experiment involves creating a `DisjointSet` instance for varying numbers of elements.
   - Each element in the set is represented by an index from `0` to `n-1`, where `n` is the number of elements.

2. **Selecting Elements for UNION Operations**:
   - For each UNION operation, two elements are randomly selected from the range of indices using:
     ```cpp
     uniform_int_distribution<> dist(0, n - 1);
     int x = dist(gen);
     int y = dist(gen);
     ds.UNION(x, y);
     ```
   - This approach ensures that the selected elements are valid indices in the Disjoint Set, allowing the experiment to simulate realistic usage scenarios.

3. **Choice of Ranges for Elements and Operations**:
   - The ranges for the number of elements (`n`) and the number of operations (`m`) are chosen to cover a wide spectrum of potential use cases, reflecting small to very large datasets. The following arrays are used:
     ```cpp
     int num_elements[] = {1000, 5000, 10000};
     int num_operations[] = {1000, 5000, 10000, 25000, 50000};
     ```
   - Each element of `num_elements` corresponds to an entry in `num_operations`, allowing for the evaluation of the Disjoint Set operations with varying ratios of operations to elements.

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

This experiment is designed to comprehensively assess the performance of Disjoint Set operations under various conditions, explicitly utilizing the weighted-union heuristic to optimize the union process. By varying the number of elements and operations while randomly selecting elements for union operations, the experiment captures the behavior of the algorithm in a realistic scenario. The data collected will facilitate the analysis of time complexity, supporting the theoretical claims made in Theorem 21.2.

The results will contribute to understanding how the performance of the Disjoint Set structure scales with increasing input sizes and operation counts.
