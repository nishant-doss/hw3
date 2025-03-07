#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: if the list is empty
    if (head == nullptr) {
        smaller = nullptr;
        larger = nullptr;
        return;
    }
    
    // Save the current head node
    Node* current = head;
    
    // Move head to the next node
    head = head->next;
    
    // Recursively process the rest of the list
    llpivot(head, smaller, larger, pivot);
    
    // Determine where current node should go
    if (current->val <= pivot) {
        // Add to smaller list
        current->next = smaller;
        smaller = current;
    } else {
        // Add to larger list
        current->next = larger;
        larger = current;
    }
}

