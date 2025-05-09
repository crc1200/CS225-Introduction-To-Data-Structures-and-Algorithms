/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**destroy~
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  List<T>::ListIterator result = List<T>::ListIterator(tail_ -> next);
  result.setTail(tail_);
  return result;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode* tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;
  length_ ++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr -> next != NULL; i++) {
    curr = curr -> next;
  }

  if (curr != NULL && curr->prev) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * tmp = head_;
  for (int i = 1; i <= length_; i++) {
    if ((i % 3) == 0) {
      if (tmp == head_) {
        head_ = head_ -> next;
      }  
      tmp -> next -> prev = tmp -> prev;
      if (tmp -> prev) {
        tmp -> prev -> next = tmp -> next;
      }
      if (curr -> next) {
        curr -> next -> prev = tmp;
      }
      tmp->next = curr-> next;
      tmp->prev = curr;
      curr -> next = tmp;
      if (curr == tail_) {
        tail_ = curr-> next;
      }
      curr = tmp;
      tmp = tmp -> next;
    }
    curr = curr -> next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
 /// @todo Graded in MP3.2
  // ListNode* curr = startPoint;
  ListNode* endNext = endPoint -> next;
  ListNode* preStart = startPoint -> prev;
  ListNode* curr = startPoint;

  if (endNext != NULL) { endNext -> prev = startPoint; }

  if (preStart != NULL) { preStart -> next = endPoint; }

  while (curr && curr != endPoint) {
    ListNode* temp = curr -> next;
    curr -> next = endNext;
    endNext = curr;
    curr -> prev = temp;
    curr = curr -> prev;
  }
  //final swap at the end
  curr -> next = curr -> prev;
  curr -> prev = preStart;

  auto holder = startPoint;

  if (startPoint == head_) {
    head_ = endPoint;
  }
  if (endPoint == tail_) {
    tail_ = startPoint;
  }
  startPoint = endPoint;
  endPoint = holder;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  int i = 1;
  ListNode * end = head_;
  ListNode * start = head_;
  while (end -> next && i <= length_) {
    if (i == n) {
      reverse(start, end);
      i = 0;
      start = end->next;
    }
    end = end->next;
    i += 1;
  }
  if (i > 1) {
    reverse(start, end);
  }
}
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  //null check
  if (first == NULL) { return second; }
  if (second == NULL) { return first; }

  //set the current value (head)
  ListNode * curr = NULL;
  if (first -> data < second -> data) {
    curr = first;
    first = first -> next;
    curr -> prev = NULL;
  } else {
    curr = second;
    second = second -> next;
    curr -> prev = NULL;
  }
  ListNode* newTail = curr;

  while (first != NULL && second != NULL) {
    ListNode* tmp = NULL;
    if (first -> data < second -> data) {
      tmp = first;
      first = first -> next;
    } else {
      tmp = second;
      second = second -> next;
    }
    newTail -> next = tmp;
    newTail -> prev = newTail;
    newTail = tmp;
  }

  if (first != NULL) {
    newTail -> next = first;
  } else if (second != NULL) {
    newTail -> next = second;
  }
  return curr;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1) {
    return start;
  }
  ListNode* right = split(start, int(chainLength / 2));

  auto left = mergesort(start, int(chainLength / 2));
  if (chainLength % 2 != 0) {
      right = mergesort(right, int(chainLength / 2) + 1);
  } else {
      right = mergesort(right, int(chainLength / 2));
  }

  return  merge(left, right);
}
