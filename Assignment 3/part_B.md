To tackle Exercise 21.3-4 from the textbook, you can enhance the disjoint-set forest implementation by adding a single attribute to each node that enables efficient printing of all members in the same set. This can be achieved by adding a `next` pointer to each node that points to the next member in the set. This allows us to traverse the members of a set in linear time when executing the `PRINT-SET(x)` operation.

### Implementation Steps

1. **Add a `next` Pointer**: Modify the existing node structure to include a `next` pointer. This pointer will help in maintaining the linked list of members within the same set.

2. **Modify `MAKE-SET`**: When creating a new set, initialize the `next` pointer to point to itself (as it is the only member).

3. **Modify `UNION`**: When performing a union operation, update the `next` pointers of the nodes to link members from the two sets together.

4. **Implement `PRINT-SET`**: Traverse through the members of the set starting from the given node using the `next` pointers and print each member.

### Explanation of the Code:

1. **Node Class**: Each node now contains `parent`, `size`, and `next` attributes. The `next` pointer is initialized to point to itself when a new set is created.

2. **DisjointSet Class**: This class manages a collection of `Node` instances:
   - **MAKE_SET**: Initializes a set for a single element and sets its `next` pointer.
   - **FIND_SET**: Uses path compression for efficient find operations.
   - **UNION**: Combines two sets, updating the `next` pointers to link the members of the sets together.
   - **PRINT_SET**: Traverses through the members of the set starting from the root and prints each member.

3. **Main Function**: This function demonstrates the usage of the disjoint set structure, including the creation of sets and printing the members of specific sets.

### Performance Analysis
- The `PRINT-SET` operation traverses the members using the `next` pointers, leading to a linear time complexity \( O(k) \), where \( k \) is the number of members in the set.
- The asymptotic running times for `MAKE-SET`, `UNION`, and `FIND-SET` operations remain unchanged at \( O(1) \) for `MAKE-SET`, \( O(\log n) \) for `FIND-SET` (due to path compression), and \( O(\log n) \) for `UNION` (due to size consideration).

This implementation meets the requirements of Exercise 21.3-4 and demonstrates the new `PRINT-SET` functionality effectively.

### Time Complexity Analysis

- **PRINT-SET(x):** This operation runs in \( O(m) \) time, where \( m \) is the number of members in the set, since we traverse and print each member.
- **MAKE-SET:** \( O(1) \)
- **FIND-SET:** \( O(\alpha(n)) \) (with path compression)
- **UNION:** \( O(\alpha(n)) \) (with union by size/rank)

### Conclusion

By adding a `next` pointer to each node, we enable efficient traversal of the members of a set, allowing the `PRINT-SET(x)` operation to print all members in linear time while preserving the asymptotic complexities of the other operations.