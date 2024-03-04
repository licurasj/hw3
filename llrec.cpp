#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    if(head == nullptr){
        smaller = nullptr;
        larger = nullptr;
        return;
    }
    
    if(head->val > pivot){
        llpivot(head->next, smaller, larger, pivot);
        head->next = larger;
        larger = head;
    }
    else{
        llpivot(head->next, smaller, larger, pivot);
        head->next = smaller;
        smaller = head;
    }
    head = nullptr;
    return;
}