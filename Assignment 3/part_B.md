To tackle Exercise 21.3-4 from the textbook, you can enhance the disjoint-set forest implementation by adding a single attribute to each node that enables efficient printing of all members in the same set. This can be achieved by adding a `next` pointer to each node that points to the next member in the set. This allows us to traverse the members of a set in linear time when executing the `PRINT-SET(x)` operation.

1. Node Structure
   - parent: points to parent node
   - next: points to next node in the set

2. Implementation details:
   - Each node will have a 'next' pointer.
   - The root of each set will point to the first node in the list.
   - The last node in the list will point back to the root.
   - This forms a circular linked list for each set.

3. Modifying existing operations:
   - MAKE-SET(x): 
     Set x.next = x (node points to itself)
   
   - UNION(x, y):
     After linking the roots, we need to merge the linked lists:
     1. Save x_root.next and y_root.next
     2. Set x_root.next = y_root.next
     3. Set y_root.next = x_root.next
     4. Update the last node of each list to point to the new root

   - FIND-SET(x):
     No change needed

4. New operation:
   PRINT-SET(x):
   1. y = FIND-SET(x) // Find the root
   2. Print y
   3. z = y.next
   4. While z ≠ y:
        Print z
        z = z.next

5. Performance Analysis:
   - The `PRINT-SET` operation traverses the members using the `next` pointers, leading to a linear time complexity \( O(k) \), where \( k \) is the number of members in the set.
   - The asymptotic running times for `MAKE-SET`, `UNION`, and `FIND-SET` operations remain unchanged at \( O(1) \) for `MAKE-SET`, \( O(\log n) \) for `FIND-SET` (due to path compression), and \( O(\log n) \) for `UNION` (due to size consideration).

6. This solution meets all the requirements:
   - Adds only one attribute (next) to each node
   - PRINT-SET takes linear time in the number of set members
   - Other operations maintain their asymptotic running times
   - Each member can be printed in O(1) time