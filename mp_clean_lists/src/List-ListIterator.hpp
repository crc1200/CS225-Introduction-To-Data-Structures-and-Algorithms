
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP3.1
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(NULL) {
        tail_ = NULL;
     }
    ListIterator(ListNode* x) : position_(x) {
        tail_ = NULL;
     }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        position_ = position_ -> next;
        return *this;
    }
    
    void setTail(ListNode* input) {
        tail_= input;
    }
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        position_ = position_->next;
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        if (position_ == NULL) {
            position_ = tail_;
            return *this;
        }
        position_ = position_ -> prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        if (position_ == NULL) {
            position_ = tail_;
            return *this;
        }
        ListNode* temp = position_;
        position_ = position_ -> prev;
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator& rhs) {
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
