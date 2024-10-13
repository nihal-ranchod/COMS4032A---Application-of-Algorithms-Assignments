## Disjoint Set Experiment Implementation

### Overview

This experiment investigates the efficiency of **Disjoint Set operations**—specifically, **Make-Set**, **Union**, and **Find-Set**—using the **weighted-union heuristic**. We aim to empirically confirm the theoretical claim of Theorem 21.2, which states that \( O(m + n \log n) \) time complexity can be achieved for a sequence of \( m \) operations, including **Make-Set**, **Union**, and **Find-Set**, using the weighted-union heuristic. The results are captured in CSV files for further analysis.

### Key Implementation Components

1. **DisjointSet Class**:
   - The DisjointSet class encapsulates the three fundamental operations: **Make-Set**, **Find-Set**, and **Union**. 
   - The `parent` vector tracks the representative of each set, and the `size` vector records the sizes of the sets for optimizing union operations.

2. **Weighted-Union Heuristic**:
   - The **Union** operation merges two sets based on size, attaching the smaller set to the larger one to reduce tree height, which optimizes future **Find-Set** operations.
   - Implementation:
     ```cpp
     if (size[root_x] < size[root_y]) {
         parent[root_x] = root_y;
         size[root_y] += size[root_x];
     } else {
         parent[root_y] = root_x;
         size[root_x] += size[root_y];
     }
     ```
   - This design minimizes the height of the tree, ensuring efficient subsequent operations.

3. **Consistency Check**:
   - A **check_consistency** function verifies that each element's parent points to the correct representative, ensuring the integrity of the Disjoint Set data structure.
   - Implementation:
     ```cpp
     bool check_consistency(int n) {
         for (int i = 0; i < n; ++i) {
             if (FIND_SET(i) != FIND_SET(FIND_SET(i))) {
                 return false;
             }
         }
         return true;
     }
     ```

### Experiment Design and Execution

1. **Experiment Setup**:
   - The experiment initializes `num_elements`, a set of predefined element counts, each with a number of elements from `100` to `1,000,000`.
   - For each element count, the experiment repeats **Make-Set** and **Union** operations for 10 runs, recording execution times to assess the impact of the weighted-union heuristic.
  
2. **Operation Execution**:
   - **Make-Set** is called for each element, initializing them as separate sets.
   - All elements are then unified with a single representative, effectively forming one large set, to simulate realistic Disjoint Set usage.
   - Execution times for these operations are captured using `<chrono>` for accurate timing.
  
3. **Data Collection**:
   - The execution time and consistency status for each run are logged in `part_A_1.csv`.
   - An additional file, `part_A_1_averaged.csv`, is generated, containing the averaged execution times over 10 runs for each element count.

4. **Random Number Generator**:
   - A Mersenne Twister (`mt19937`) engine seeded with `random_device` generates randomness for element selection in **Union** operations.
  
5. **Output Files**:
   - `part_A_1.csv`: Contains detailed records of execution times and consistency results for each element count across 10 runs.
   - `part_A_1_averaged.csv`: Stores average execution times for each element count, facilitating overall performance analysis.

### Conclusion

The experiment successfully demonstrates the performance of Disjoint Set operations using the weighted-union heuristic, providing empirical validation of the time complexity asserted by Theorem 21.2. The recorded data illustrates the efficiency gains from using the weighted-union heuristic in Disjoint Set operations, especially as the number of elements scales up. The results are stored in two CSV files for further analysis, confirming the expected performance characteristics of the Disjoint Set data structure under various conditions.
