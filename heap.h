#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heapVector;
  void trickleUp(int loc);
  void heapify(int idx);
  int xnary;
  PComparator c;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  xnary = m;
  this->c = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}

template <typename T, typename PComparator> //
void Heap<T,PComparator>::push(const T& item){
  heapVector.push_back(item); 
  trickleUp(heapVector.size()-1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return heapVector.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return heapVector.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx){
  int largest = idx;  // Initialize largest as root
  int leftChild = 2 * idx + 1;  // Left child index
  int rightChild = 2 * idx + 2; // Right child index

  // If left child is larger than root
  if (leftChild < heapVector.size() && c(heapVector[leftChild] , heapVector[largest]))
      largest = leftChild;

  // If right child is larger than largest so far
  if (rightChild < heapVector.size() && c(heapVector[rightChild] , heapVector[largest]))
      largest = rightChild;

  // If largest is not root
  if (largest != idx) {
      std::swap(heapVector[idx], heapVector[largest]);

      // Recursively heapify the affected sub-tree
      heapify(largest);
  }
  
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc){
  int parent = (loc-1)/2; 
  while(parent >= 0 && c(heapVector[loc], heapVector[parent])) {
    std::swap(heapVector[parent], heapVector[loc]);
    loc = parent;
    parent = (loc-1)/2;
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("Heap Empty!");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heapVector[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap empty!");
  }
  heapVector[0] = heapVector.back(); 
  heapVector.pop_back();
  Heap<T,PComparator>::heapify(0); // a.k.a. trickleDown()

}



#endif

