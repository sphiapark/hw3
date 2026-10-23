#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: empty list
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    // Save the current node
    Node* curr = head;

    // Move head to the next node
    head = head->next;

    // Recursively split the remaining list
    llpivot(head, smaller, larger, pivot);

    // Place current node into the correct list
    if (curr->val <= pivot) {
        curr->next = smaller;
        smaller = curr;
    }
    else {
        curr->next = larger;
        larger = curr;
    }
}
