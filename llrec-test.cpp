#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------





int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    // Test llpivot function
    cout << "\nTesting llpivot with pivot = 10:" << endl;
    Node* smaller = nullptr;
    Node* larger = nullptr;
    int pivot = 10;
    
    // Make a copy of the original list for llpivot
    Node* head_copy = readList(argv[1]);
    
    cout << "Before pivot - Original list: ";
    print(head_copy);
    
    llpivot(head_copy, smaller, larger, pivot);
    
    cout << "After pivot - head should be empty: ";
    print(head_copy);
    cout << "Smaller list (values <= " << pivot << "): ";
    print(smaller);
    cout << "Larger list (values > " << pivot << "): ";
    print(larger);
    
    // Clean up the smaller and larger lists
    dealloc(smaller);
    dealloc(larger);
    
    // Define a predicate for llfilter
    // This example removes even numbers
    struct IsEven {
        bool operator()(int value) { return value % 2 == 0; }
    };
    
    cout << "\nTesting llfilter (removing even numbers):" << endl;
    cout << "Before filter: ";
    print(head);
    
    head = llfilter(head, IsEven());
    
    cout << "After filter (odd numbers only): ";
    print(head);
    
    // Clean up
    dealloc(head);
    
    return 0;



    
    return 0;

}