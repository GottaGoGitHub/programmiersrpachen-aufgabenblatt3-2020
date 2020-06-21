#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.12 - Teil 1)
    return node->value;
  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.12 - Teil 2)
    return &node->value;
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 3)
    node = node->next;
    return *this;
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 4)
    ListIterator<T> it = *this;
    node = node->next;
    return it;
  }


  /* check if 2 iterators point to the same node */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 5)
    // Iterators should be the same if they refer to the same node
      if (x.node == node) {
          return true;
      }
    return false;
  } // call it: == it

  /* check if 2 iterators point to a different node */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.12 - Teil 6)
    // Reuse operator==
      if (x == *this) {
          return false;
      }
    return true;
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // not fully implemented yet
    // TODO: do not forget about the initialiser list! (Aufgabe 3.2)
    /* default constructor */
    List():
        size_{ 0 }, first_{ nullptr }, last_{ nullptr }{}

    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)
    List(List<T> const& list) :
        size_{ 0 },
        first_{ nullptr },
        last_{ nullptr }  {
        ListNode<T>* elem = list.first_;
        while (elem != nullptr) {
            push_back(elem->value);
            elem = elem->next;
        }
        delete elem;
    }

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)
    List(List<T>&& list) :
        size_{ list.size() },
        first_{ list.first_ },
        last_{ list.last_ }{
        list.first_ = nullptr;
        list.last_ = nullptr;
        list.size_ = 0;
    }


    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* use standart swap to implement assignment operator */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)
    void swap(List& Liste) {
        std::swap(size_, Liste.size_);
        std::swap(first_, Liste.first_);
        std::swap(last_, Liste.last_);
    }
    
    List& operator=(List const* Liste) {
        swap(Liste);
        return *this;
    }

    /* compare if to lists are the same */
    // test and implement:

    //TODO: operator== (Aufgabe 3.8)
    bool operator==(List const& rhs) const
    {
        if (this->size_ != rhs.size_) {
            return false;
        }
        else {
            ListNode<T>* new_first = first_;
            ListNode<T>* rhs_first = rhs.first_;
            while (new_first != nullptr && rhs_first) {
                if (new_first->value == rhs_first->value) {
                    return true;
                }
                new_first = new_first->next;
                rhs_first = rhs_first->next;
            }
            return false;
        }
    }

    bool operator!=(List const& rhs) const
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
        if (*this == rhs) {
            return false;
        }
        return true;
    }

    /* destructor using clean method */
    ~List() {
      //TODO: Implement via clear-Method (Aufgabe 3.4)
        clear();
    } //can not really be tested

    /* begin() returns an iterator the the first element of a list */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.11)
        ListIterator<T> begin;
        begin.node = first_;
        return begin;
    }

    /* end() returns an iterator the the element after the last element of a list, beeing always nullptr */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.11)
        ListIterator<T> end;
        end.node = nullptr;
        return end;
    }

    /* pop all elements until list is empty */ 
    // test and implement:
    //TODO: clear()-Method (Aufgabe 3.4)
    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    /* insert an element with O(1) runtime at any given position via iterators */
    //TODO: member function insert (Aufgabe 3.13)
    ListIterator<T> insert(ListIterator<T> pos, T const& elem) {
        if (pos == begin()) {
            push_front(elem);
            return begin();
        }
        else {
            ListNode<T>* new_node = new ListNode<T>{ elem, pos.node->prev, pos.node };
            pos.node->prev->next = new_node;
            pos.node->prev = new_node;
            return ListIterator<T>{new_node};
        }
    }

    /* delete an element at any position in list via iterators and return element after deleted */
    //TODO: member function insert (Aufgabe 3.14)
    ListIterator<T> erase(ListIterator<T> pos) {
        auto temp_next = pos.node->next;
        if (pos == begin()) {
            pop_front();
            return begin();
        }
        else if (temp_next == nullptr) {
            pop_back();
            return end();
        }
        else {
            pos.node->prev->next = temp_next;
            temp_next->prev = pos.node->prev;
            delete pos.node;
            pos.node = nullptr;
            --size_;
            return ListIterator<T>{temp_next};
        }
    }


    

    /* reverse a list */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
        ListNode<T>* elem = first_;
        ListNode<T>* temp;
        while (elem != nullptr) {
            temp = elem->prev;
            elem->prev = elem->next;
            elem->next = temp;
            elem = elem->prev;
        }
        std::swap(first_, last_);
    }


    /* add element to the front of a list */
    void push_front(T const& element) {
      // TODO: push_front-method (Aufgabe 3.3)
      ListNode<T> *new_node = new ListNode<T>{ element };
      if(empty()){
          new_node->next = nullptr;
          last_ = new_node;
          }
      else {
          first_->prev = new_node;
          new_node->next = first_;
      }
      new_node->prev = nullptr;
      first_ = new_node;
      ++size_;
      //delete new_node;
    }

    /* add element to the back of a list */
    void push_back(T const& element) {
      // TODO: push_back-method (Aufgabe 3.3)
        ListNode<T>* new_node = new ListNode<T>{ element };
        if (empty()) {
            new_node->prev = nullptr;
            first_ = new_node;
        }
        else {
            last_->next = new_node;
            new_node->prev = last_;
        }
        new_node->next = nullptr;
        last_ = new_node;
        ++size_;
        //delete new_node;
    }

    /* deletes first element from list */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      else if (size_ == 1) {
          delete first_;
          first_ = nullptr;
          last_ = first_;
      }
      else {
          auto new_first = first_->next;
          new_first->prev = nullptr;
          delete first_;
          first_ = new_first;
      }
      --size_;
    }

      // TODO: remainder of pop_front-method (Aufgabe 3.3)
    

    /* deletes last element from list */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      else if (size_ == 1) {
          delete first_;
          first_ = nullptr;
          last_ = first_;
      }
      else {
          auto new_last = last_->prev;
          new_last->next = nullptr;
          delete last_;
          last_ = new_last;
      }
      --size_;
    }

      // TODO: remainder of pop_back-method (Aufgabe 3.3)
    

    /* returns the value of the first element in a list */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }

      // TODO: remainder of front-method (Aufgabe 3.3)
      else {
          return first_->value;
      }
    }

    /* returns the value of the last element in a list */
    T& back() {
      if(empty()) {
        throw "List is empty";
      }

      // TODO: remainder of back-method (Aufgabe 3.3)
      else {
          return last_->value;
      }
    }

    /* checks if list is empty */
    bool empty() const {

      // TODO: empty-method (Aufgabe 3.2)
        if (size_ == 0) {
            return true;
      }
      return false;
    };


    /* return size of list */
    std::size_t size() const{
      // TODO: size-method (Aufgabe 3.2)   
        return size_;
  };


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* its reverse but as a free funtion using the member function */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)
template<typename T>
List<T>* reverse(List<T> const& Liste) {
    List<T>* temp = new List<T>{ Liste };
    temp->reverse();
    return temp;
    delete temp;
}

/* checks if list and std::vector have the same content */
template <typename T>
bool has_same_content(List<T> const& list, std::vector<T> const& vec) {
    if(list.size() != vec.size()){
        return false;
    }
    else {
        auto list_pointer = get_first_pointer(list);
        for (int i = 0; i < vec.size(); ++i) {
            if (list_pointer->value != vec[i]) {
                return false;
            }
            list_pointer = list_pointer->next;
        }
    }
    return true;
}   

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP