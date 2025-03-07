#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator()) :
    m_(m),
    comp_(c),
    data_()
  {
    if(m < 2) {
      throw std::invalid_argument("m-ary heap must have m >= 2");
    }
  }

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() {}

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item) {
    // Add the item to the end of the vector
    data_.push_back(item);
    
    // Trickle up to maintain heap property
    size_t index = data_.size() - 1;
    trickleUp(index);
  }

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const
  {
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()){
      // throw the appropriate exception
      throw std::underflow_error("Heap is empty");
    }
    // If we get here we know the heap has at least 1 item
    return data_[0];
  }

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop()
  {
    if(empty()){
      // throw the appropriate exception
      throw std::underflow_error("Heap is empty");
    }
    
    // Replace the root with the last element
    data_[0] = data_.back();
    data_.pop_back();
    
    // Trickle down to maintain heap property
    if(!empty()) {
      trickleDown(0);
    }
  }

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const {
    return data_.empty();
  }

  /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const {
    return data_.size();
  }

private:
  /// Helper functions and data members
  
  /**
   * @brief Get the parent index
   * 
   * @param index Current index
   * @return size_t Parent index
   */
  size_t parent(size_t index) const {
    return (index - 1) / m_;
  }
  
  /**
   * @brief Get the k-th child index
   * 
   * @param index Current index
   * @param k Child number (0-based)
   * @return size_t Child index
   */
  size_t child(size_t index, size_t k) const {
    return m_ * index + k + 1;
  }
  
  /**
   * @brief Trickle up to maintain heap property
   * 
   * @param index Index to start trickle up from
   */
  void trickleUp(size_t index) {
    // Base case: reached the root
    if(index == 0) return;
    
    size_t parentIdx = parent(index);
    
    // If the current item has priority over its parent, swap them
    if(comp_(data_[index], data_[parentIdx])) {
      std::swap(data_[index], data_[parentIdx]);
      trickleUp(parentIdx);
    }
  }
  
  /**
   * @brief Trickle down to maintain heap property
   * 
   * @param index Index to start trickle down from
   */
  void trickleDown(size_t index) {
    size_t highestPriorityChild = getHighestPriorityChild(index);
    
    // If no valid child or current node has priority over all children, stop
    if(highestPriorityChild == data_.size() || 
       !comp_(data_[highestPriorityChild], data_[index])) {
      return;
    }
    
    // Otherwise, swap with highest priority child and continue
    std::swap(data_[index], data_[highestPriorityChild]);
    trickleDown(highestPriorityChild);
  }
  
  /**
   * @brief Get the highest priority child index
   * 
   * @param index Current index
   * @return size_t Highest priority child index, or data_.size() if no valid children
   */
  size_t getHighestPriorityChild(size_t index) {
    size_t firstChild = child(index, 0);
    
    // If no children, return invalid index
    if(firstChild >= data_.size()) {
      return data_.size();
    }
    
    // Find the highest priority child
    size_t highestPriorityIdx = firstChild;
    
    // Check all possible children (up to m_ children)
    for(size_t i = 1; i < m_; i++) {
      size_t nextChild = child(index, i);
      
      // Break if we're beyond the array bounds
      if(nextChild >= data_.size()) {
        break;
      }
      
      // Update highest priority if this child has higher priority
      if(comp_(data_[nextChild], data_[highestPriorityIdx])) {
        highestPriorityIdx = nextChild;
      }
    }
    
    return highestPriorityIdx;
  }
  
  /// Data members
  int m_;  // m-ary heap (number of children per node)
  PComparator comp_;  // Comparator function
  std::vector<T> data_;  // Vector to store heap elements
};

#endif