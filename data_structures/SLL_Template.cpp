#include <iostream>
#include <string>

using namespace std;

template <class T>
class SNode{
    public:
        const T& getElem() const { return elem; };
        SNode<T>* getNext() const { return next; };
    private:
        T elem;
        SNode<T>* next;

friend class SLinkedList<T>;
}

//List of Nodes
template <class T>
class SLinkedList{
    
public:
    SLinkedList();

    // Rule of three
    SLinkedList(SLinkedList<T>&);               // copy constructor
    ~SLinkedList();                             // destructor
    SLinkedList<T>& operator=(SLinkedList<T>&); // Assignment operator

    void addFront(const E& e);  // Adds to the front
    void removeFront();         // Removes front and reassigns head
    const T& front() const;     // Returns the front element
    void addBack(const E& e);   // Adds to the back
    bool empty();               // Returns true if list is empty head==null

    //Getters
    SNode<T>* getHead() const {return this.head;}
    SNode<T>* getTail() const {return this.tail;}

private:
    SNode<T>* head;
    SNode<T>* tail;
}
template<T>
SLinkedList<T>::SLinkedList() : head(NULL), tail(NULL){ }

template<T>
SLinkedList<T>::SLinkedList(SLinkedList<T>& rhs) : head(NULL, tail(NULL)){

    *this = rhs;

}

template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(SLinkedList<T>& rhs) // assignment operator
{
    if (this != &rhs) {
        while (head != NULL)
            removeFront();

        for (SNode<T>* current = rhs.head; current != NULL; current = current->getNext())
        {
            addBack(current->getElem());
        }

    }
    return *this;
}

/* TODO: IMPLEMENT
    template <class T>
    void SLinkedList<T>::addFront(const E& e){}

    template <class T>
    void SLinkedList<T>::removeFront(){}

    template <class T>    
    const T& SLinkedList<T>::front() const{}

    template <class T>
    void SLinkedList<T>::addBack(const E& e){}

    template <class T>
    bool SLinkedList<T>::empty(){}
*/