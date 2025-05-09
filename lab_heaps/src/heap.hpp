/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <bits/stdc++.h>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return (currentIdx * 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (currentIdx * 2) + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return (currentIdx) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return (currentIdx * 2) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    if (hasAChild(currentIdx)) {
        if (rightChild(currentIdx) < _elems.size()) {
            if (higherPriority(_elems[rightChild(currentIdx)], _elems[leftChild(currentIdx)])) {
                return rightChild(currentIdx);
            }
        } 
        return leftChild(currentIdx);
    }
    return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (hasAChild(currentIdx)) {
        auto loc = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[loc], _elems[currentIdx])) {
            std::swap(_elems[loc], _elems[currentIdx]);
            heapifyDown(loc);
        }
    }
    
    // @TODO Implement the heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    // because we are one indexed, we need to make sure that we have the empty element present
    std::vector<T> v;
    v.push_back(T());
    _elems = v;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = {T()};
    for (unsigned i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }
    //now we need to fix this
    for (size_t i = parent(_elems.size() - 1); i > 0; i--) {
        heapifyDown(i);
    }
    
}
// if you get a time out, try to change to size_t instead


template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (_elems.size() > 1) {
        auto t = _elems[1];
        std::swap(_elems[1], _elems[_elems.size() - 1]);
        _elems.pop_back();
        heapifyDown(1);
        return t;
    }
    // @TODO Remove, and return, the element with highest priority
    return T();
    
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    _elems[idx] = elem;
    heapifyUp(idx);
    heapifyDown(idx);
    
    // Corrects the heap to remain as a valid heap even after update
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 0;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}