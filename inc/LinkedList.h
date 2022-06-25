#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

template <class Type>
struct Node
{
	Type data;
	Node *next = nullptr;
};

template <class Type>
class OrderedLinkedList;

template <class Type>
std::ostream& operator<<(std::ostream&, const OrderedLinkedList<Type>& list);


template <class Type>
class OrderedLinkedList
{
public:
	OrderedLinkedList();
	OrderedLinkedList(const OrderedLinkedList& other);
	OrderedLinkedList<Type>& operator=(const OrderedLinkedList<Type>& other);
	~OrderedLinkedList();
    int size() const;
    bool empty() const;
	Type get(int) const;
	Type getFirst() const;
	Type getLast() const;
	void insert(const Type&);
	int find(const Type&) const;
	void remove(const Type&);
    void clear();
    OrderedLinkedList<Type> everyOtherOdd();
    OrderedLinkedList<Type> everyOtherEven();
    friend std::ostream& operator<< <>(std::ostream&, const OrderedLinkedList<Type>& list);
protected:
    Node<Type> *head;
    int count;
};

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList()
{
    // initialize count to 0, create an empty head
    count = 0;
    head = nullptr;
    head = new Node<Type>;
    head->next = nullptr;
}

/**
 * This is the copy constructor, it creates a new OrderedLinkedList from an existing OrderedLinkedList, but with
 *      different memory locations
 * @tparam Type
 * @param other
 */

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList(const OrderedLinkedList<Type>& other)
{
    // create a head node
    head = new Node<Type>;
    // initialize head->next to a null value
    head->next = nullptr;
    // nodes for traversing each list
    auto thisCurrentNode = this->head;
    auto otherCurrentNode = other.head->next;
    while(otherCurrentNode != nullptr) {
        // new node to be entered into list
        auto temp = new Node<Type>;
        // setting the new nodes data to the other list items data
        temp->data = otherCurrentNode->data;
        // setting the next node to the temp node in the new list
        thisCurrentNode->next = temp;
        // going to the next node in each list
        otherCurrentNode = otherCurrentNode->next;
        thisCurrentNode = thisCurrentNode->next;
    }
    // setting to have equal counts
    this->count = other.count;
}

/**
 * This is the overloaded operator =. This creates a deep copy of an OrderedLinkedList
 * @tparam Type
 * @param other
 * @return
 */

template <class Type>
OrderedLinkedList<Type>& OrderedLinkedList<Type>::operator=(const OrderedLinkedList& other)
{
    // self assign prevention
    if(this == &other) {
        return *this;
    }
    else {
        // initialize list to be empty
        clear();
        // finding the starting nodes in each list
        auto thisCurrentNode = this->head;
        auto otherCurrentNode = other.head->next;
        while(otherCurrentNode != nullptr) {
            // new node to be entered into the now cleared list
            auto temp = new Node<Type>;
            // setting the new node to have the data of the of other lists node
            temp->data = otherCurrentNode->data;
            // setting the next in current lists to the new node
            thisCurrentNode->next = temp;
            // getting to the next node in each list
            otherCurrentNode = otherCurrentNode->next;
            thisCurrentNode = thisCurrentNode->next;
        }
        this->count = other.count;
    }
    return *this;
}

template <class Type>
OrderedLinkedList<Type>::~OrderedLinkedList()
{
    // finding the head node (including the dummy node)
    auto currentNode = this->head;
    // pointer to store node to prevent loss of link in deletion of list
    Node<Type>* nextNode = nullptr;
    while(currentNode != nullptr) {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    delete nextNode;
}

template <class Type>
int OrderedLinkedList<Type>::size() const
{
return this->count;
}

template <class Type>
bool OrderedLinkedList<Type>::empty() const
{
return count == 0;
}

template <class Type>
Type OrderedLinkedList<Type>::get(int pos) const
{
    if(pos > count || this->head == nullptr || pos < 0) {
        throw std::out_of_range("Position outside bounds of the list");
    }
    int counter = 0;
    // setting the currentNode to the node directly after the dummy node
    auto currentNode = this->head->next;
    // finds the node at specified index
    while(counter != pos) {
        currentNode = currentNode->next;
        ++counter;
    }
    if(currentNode == nullptr) {
        throw std::out_of_range("Position outside bounds of the list");
    }
    return currentNode->data;
}

template <class Type>
Type OrderedLinkedList<Type>::getFirst() const
{
    if(this->head->next == nullptr) {
        throw std::out_of_range("list is empty");
    }
    //returns the data of the first node after the dummy node
    return this->head->next->data;
}

template <class Type>
Type OrderedLinkedList<Type>::getLast() const
{
    if(this->head->next == nullptr)
        throw std::out_of_range("list is empty");
    // first node after dummy node
    auto currentNode = this->head->next;
    // finds the last node
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template <class Type>
void OrderedLinkedList<Type>::insert(const Type& item)
{
    // gets first node/ dummy node
    auto currentNode = this->head;
    // new node to be added to list
    auto newNode = new Node<Type>;
    // setting the item value to the new nodes data
    newNode->data = item;
    // if this is the first item added
    if(count == 0) {
        head->next = newNode;
    }
    else {
        int counter = 0;
        // gets to the correct position in the list that keeps the list sorted
        while (currentNode->next != nullptr && currentNode->next->data < item) {
            currentNode = currentNode->next;
            ++counter;
        }
        // if end of the list
        if(counter == count) {
            currentNode->next = newNode;
        }
        else {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }
    }
    ++count;
}

template <class Type>
int OrderedLinkedList<Type>::find(const Type& item) const
{
    // finds head node/ dummy node
    auto currentNode = this->head;
    if(currentNode->next == nullptr) {
        return -1;
    }
    int counter = -1;
    // goes through entire list
    while(currentNode != nullptr) {
        // if the current node's data is equal to the item, return the counter indicating index of item
        if(currentNode->data == item) {
            return counter;
        }
        currentNode = currentNode->next;
        counter++;
    }
    return -1;
}

template <class Type>
void OrderedLinkedList<Type>::remove(const Type& item)
{
    // finds the head/dummy node
    auto currentNode = this->head;
    // if list is empty do nothing
    if(currentNode->next == nullptr) {
        return;
    }
    // if there is only one item in the list
    if (currentNode->next->data == item && count == 1) {
        Node<Type>* temp = currentNode->next;
        currentNode->next = nullptr;
        delete temp;
        --count;
        return;
    }
    // if there is more than 1 item in the list, and the node to remove is the first after the dummy
    else if(currentNode->next->data == item) {
        auto temp = currentNode->next->next;
        delete currentNode->next;
        currentNode->next = temp;
        --count;
        return;
    }
    // removes an item at anywhere in the list that is not the head
    else {
        for(int i = 0; i < count; ++i) {
            if(currentNode->next->data == item) {
                auto temp = currentNode->next->next;
                delete currentNode->next;
                currentNode->next = temp;
                --count;
                return;
            }
            currentNode = currentNode->next;
        }
    }
}

template <class Type>
void OrderedLinkedList<Type>::clear()
{
    if(count != 0) {
        auto currentNode = this->head->next;
        while(currentNode != nullptr) {
            auto temp = currentNode->next;
            delete currentNode;
            currentNode = temp;
        }
        this->head->next = nullptr;
        count = 0;
    }
}


template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherOdd(){
    OrderedLinkedList<Type> temp;
    //find the node after the dummy node
    auto currentNode = this->head->next;
    while(currentNode != nullptr) {
        temp.insert(currentNode->data);
        currentNode = currentNode->next;
        // if it is able to, it skips two positions to only get the odd numbers of indexes
        if(currentNode != nullptr) {
            currentNode = currentNode->next;
        }
    }
return temp;
}

template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherEven(){
    OrderedLinkedList<Type> temp;
    // find the ndoe after the dummy node
    auto currentNode = this->head->next;
    // if it is able to, goes 1 position forward then follows same algorithm for everyOtherOdd so that it is offset by
    // one, then only returning the even numbers
    if(currentNode != nullptr) {
        currentNode = currentNode->next;
    }
    while(currentNode != nullptr) {
        temp.insert(currentNode->data);
        currentNode = currentNode->next;
        if(currentNode != nullptr) {
            currentNode = currentNode->next;
        }
    }
    return temp;
}

template <class Type>
std::ostream& operator<<(std::ostream& out, const OrderedLinkedList<Type>& list)
{
    auto currentNode = list.head->next;
    while(currentNode != nullptr) {
        if(currentNode->next == nullptr) {
            out << currentNode->data;
            return out;
        }
        else {
            out << currentNode->data << "->";
            currentNode = currentNode->next;
        }
    }
    return out;
}
#endif
