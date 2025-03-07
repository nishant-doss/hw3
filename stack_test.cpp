#include <iostream>
#include <string>
#include "stack.h"

// Function to print whether a test passed or failed
void print_test_result(const std::string& test_name, bool passed) {
    std::cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    bool passed = true;
    
    // Test 1: Basic integer stack operations
    std::cout << "=== Testing Integer Stack ===" << std::endl;
    try {
        Stack<int> int_stack;
        
        // Check initial state
        print_test_result("Initial empty", int_stack.empty());
        print_test_result("Initial size 0", int_stack.size() == 0);
        
        // Push elements
        int_stack.push(10);
        int_stack.push(20);
        int_stack.push(30);
        
        // Check stack state after pushes
        print_test_result("Not empty after push", !int_stack.empty());
        print_test_result("Size 3 after pushes", int_stack.size() == 3);
        print_test_result("Top element is 30", int_stack.top() == 30);
        
        // Pop and check top
        int_stack.pop();
        print_test_result("Top after pop is 20", int_stack.top() == 20);
        print_test_result("Size 2 after pop", int_stack.size() == 2);
        
        // Pop until empty
        int_stack.pop();
        int_stack.pop();
        print_test_result("Empty after all pops", int_stack.empty());
        
    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
        passed = false;
    }
    
    // Test 2: Testing exception handling
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    {
        Stack<double> double_stack;
        
        // Test top() on empty stack
        bool caught_exception = false;
        try {
            double_stack.top();
        } catch (const std::underflow_error& e) {
            caught_exception = true;
            std::cout << "Correctly caught underflow exception on top(): " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Caught wrong exception type on top()" << std::endl;
        }
        print_test_result("top() throws underflow_error on empty stack", caught_exception);
        
        // Test pop() on empty stack
        caught_exception = false;
        try {
            double_stack.pop();
        } catch (const std::underflow_error& e) {
            caught_exception = true;
            std::cout << "Correctly caught underflow exception on pop(): " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Caught wrong exception type on pop()" << std::endl;
        }
        print_test_result("pop() throws underflow_error on empty stack", caught_exception);
    }
    
    // Test 3: Stack with string type
    std::cout << "\n=== Testing String Stack ===" << std::endl;
    {
        Stack<std::string> string_stack;
        string_stack.push("Hello");
        string_stack.push("World");
        
        print_test_result("String stack size 2", string_stack.size() == 2);
        print_test_result("String stack top is 'World'", string_stack.top() == "World");
        
        string_stack.pop();
        print_test_result("String stack top after pop is 'Hello'", string_stack.top() == "Hello");
    }

    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "All tests " << (passed ? "PASSED!" : "had FAILURES") << std::endl;

    return passed ? 0 : 1;
}