#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>  // For assertions
#include <cstdlib>  // For rand()

using namespace std;

class Element {
public:
    int p;     // Parent of the element
    int rank;  // Rank for union by rank
    Element* next; // Next member in the set linked list

    Element() : p(0), rank(0), next(nullptr) {}
};

class DisjointSet {
private:
    vector<Element> elements;

public:
    DisjointSet(int n) {
        elements.resize(n);
        for (int i = 0; i < n; i++) {
            elements[i].p = i; // Initialize each element to be its own parent
            elements[i].rank = 0; // Initialize rank
            elements[i].next = &elements[i]; // Next points to itself initially
        }
    }

    // Make-Set Operation: Initializes a single set for element x.
    void MAKE_SET(int x) {
        elements[x].p = x;
        elements[x].rank = 0; // Initialize rank
        elements[x].next = &elements[x]; // Point next to itself
    }

    // Find-Set Operation with path compression: Returns the representative of the set that contains x.
    int FIND_SET(int x) {
        if (elements[x].p != x) {
            elements[x].p = FIND_SET(elements[x].p); // Path compression
        }
        return elements[x].p;
    }

    // Link function: Links the trees rooted at x and y.
    void LINK(int x, int y) {
        if (elements[x].rank > elements[y].rank) {
            elements[y].p = x;
        } else {
            elements[x].p = y;
            if (elements[x].rank == elements[y].rank) {
                elements[y].rank += 1; // Increase rank if they are the same
            }
        }
    }

    // Union Operation: Combines the two sets that contain x and y.
    void UNION(int x, int y) {
        LINK(FIND_SET(x), FIND_SET(y));
    }

    // PRINT-SET Operation: Prints all members of the set containing x.
    void PRINT_SET(int x) {
        int root = FIND_SET(x);
        Element* current = &elements[root];
        std::vector<int> members;

        // Traverse through the members using the next pointers
        do {
            members.push_back(current->p); // Store the member's index
            current = current->next; // Move to the next member
        } while (current != &elements[root]); // Stop when we circle back to the root

        // Print the members
        std::cout << "Members of the set containing " << x << ": ";
        for (int member : members) {
            std::cout << member << " "; // Print each member
        }
        std::cout << std::endl;
    }

};
