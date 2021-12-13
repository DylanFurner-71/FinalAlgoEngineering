//
// Created by Dylan Furner on 10/19/21.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

#include <iostream>
#include "ListNode.h"
using namespace std;

template <typename T>
class LinkedList
{
private:
    ListNode<T> *tail;
    int length = 0; //increment or decrement with every insertion or removal
    void print_Backward(ListNode<T> * curr); //recursive private function
    ListNode<T> * myIterator;
public:
    LinkedList();
    LinkedList(int size);
    LinkedList(ListNode<T> val);
    ~LinkedList();
    LinkedList(const LinkedList<T> &old);
//    LinkedList& operator=(const LinkedList<T>& rhs); //overloaded assignment operator
    T& operator[](int z); //int z = variable value passed in
    const void operator++();
    void insertFront(const T val); //insert front
    void insertBack(T val); //linked list adds to back
    void insertBack(T *val);
    void insertAt(int pos, T val); //add value to specific position
    void removeAt(int pos); //remove at specific position
    void removeFront(); //removes head node
    void removeBack(); //remove tail node
    void remove(T val);
//    void remove(ListNode<T>* val);
    T search(T val); //returns the value of val if contains
    void resetIter(); //sets iterator pointer to head.
    T next(); //Returns data in the node
    void print(); //prints linked list
    void printForward();//prints linked list forwards
    void printBackwards();//prints linked list tail to head
    int getLength(); //returns num nodes in linked list
    void clear(); //unfinished, should delete all node in linked list
    bool exists(T search);
    ListNode<T> *head;
};

template <typename T>
LinkedList<T>::LinkedList(){ //sets all to zero or nullptr
    length = 0;
    head = nullptr;
    tail = nullptr;
    myIterator = nullptr;
}
template <typename T>
LinkedList<T>::LinkedList(int size){ //initialized first node in list with data passed in
    length = size;
    myIterator = nullptr;
    head = new ListNode<T>();
    tail = new ListNode<T>();
    tail -> prev = head;
    int k = 1;
    head -> next = new ListNode<T>();
    ListNode<T>* ptr = head->next;
    ptr->prev = head;
    while (k < length){
        k++;
        ptr -> next = new ListNode<T>();
        ptr -> next -> prev = ptr;
        ptr = ptr->next;
    }
    ptr ->next = tail;
}

template <typename T>
LinkedList<T>::LinkedList(ListNode<T> val){ //copy constructor
    length = 0;
    head = val.next;
    tail = val.prev;
}
//destructor
template<typename T>
LinkedList<T>::~LinkedList(){
//cout<<"DESTRUCTOR"<<endl;
//while (length > 0){
//    removeFront();
//head = tail = nullptr;
//    if (length != 0){
//        ListNode<T> * curr;
//        while (head != nullptr && head != tail){
//            curr = head;
//            delete curr;
//            if (head -> next != NULL){
//                head = head->next;
//            }
//        }
//        ListNode<T> * curr = head;
//        while ((curr != NULL)){
//            if ( curr-> next != NULL){
//                curr = curr->next;
//            }
//            if (curr->prev != NULL){
//                delete curr->prev;
//            } else {
//                delete curr;
//                curr = NULL;
//            }
//        }
//        head = tail = nullptr;
//        delete head;
//        delete tail;
//    }
//    if (this->head != NULL){
//        ListNode<T> * curr;
//        curr = head;
//        while (curr->next != NULL){
//            curr = curr->next;
//            delete curr->prev;
//        }
//    }
//    cout<<"length"<<length<<endl;
//    if (length > 0){
//        for (int i = 0; i < length-1; i++){
//                ListNode<T>*curr = head;
//                if (curr->next != NULL){
//                    curr = curr->next;
//                    delete curr->prev;
//                }
//        }
//    }
//    length = 0;
//    ListNode<T>*curr = head;
//    while (curr != NULL && (curr->next != NULL) && (curr->next != nullptr)){
//        curr = curr->next;
//        delete curr->prev;
//    }
//    if (curr != NULL){
//        delete curr;
//    }
//cout<<"DESTRUCTION"<<endl;
}
//template <typename T>
//LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rhs){ //assignment operator
//    if (head != nullptr){
//        //  clear();//add this functionality
//    }
//    ListNode<T> *temp = rhs.head;
//    while (temp != nullptr){
//        insertBack(temp->getData());
//        temp = temp->next;
//    }
//    return *this;
//}

template <typename T>
const void LinkedList<T>::operator ++(){
    next();
}
template <typename T>
T& LinkedList<T>::operator [](int z){
    ListNode<T> * temp = head;
    for (int i = 0; i < z; i++){

        temp = temp->next;
    }
    return temp->data;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &old){ //const copy constructor
    ListNode<T> * curr = old.head;
    head = nullptr;
    tail = nullptr;
    while (curr != nullptr){
        insertBack(curr->getData());
        curr = curr->next;
        length++;
    }

}

template <typename T>
void LinkedList<T>::print_Backward(ListNode<T> * curr){ //recursive print function outlined by Jake in lecture
    if (curr == nullptr) { return; }
    print_Backward(curr->next);
    cout<<curr->data<<endl;
    return;
}

template <typename T>
void LinkedList<T>::insertFront(const T val){ //Properly working insert front function
    if (head == nullptr){//if empty
        head = new ListNode<T>(val);
        tail = head;
    } else { //any other case
        ListNode<T> *Temp = new ListNode<T>(val);
        Temp->next = head;
        Temp->prev = nullptr;
        head->prev = Temp;
        head = Temp;
    }
    length++;
}

template <typename T>
void LinkedList<T>::insertBack(T val){//properly working insert back function
    if (head == nullptr){ //if empty
        head = new ListNode<T>(val);
        tail = head;
    } else if (tail == head){//if there's one node in the list
        tail = new ListNode<T>(val);
        head->next = tail;
        tail->prev = head;
    } else {
        ListNode<T> * prevTail = tail;
        ListNode<T> * temp = new ListNode<T>(val);
        temp->prev = prevTail;
        prevTail->next = temp;
        tail = temp;
    }
    length++;
}

template <typename T>
void LinkedList<T>::insertBack(T *val){
    if (head == nullptr){ //if empty
        head = new ListNode<T>(*val);
        tail = head;
    } else if (tail == head){//if there's one node in the list
        tail = new ListNode<T>(*val);
        head->next = tail;
        tail->prev = head;
    } else { //any other size
        ListNode<T> * prevTail = tail;
        ListNode<T> * temp = new ListNode<T>(*val);
        temp->prev = prevTail;
        prevTail->next = temp;
        tail = temp;
    }
    length++;
}
template <typename T>
void LinkedList<T>::insertAt(int pos, T val){ //insert at specific position in the linked list
    ListNode<T> * curr = head; //curr starts pointing at head
    if (curr == nullptr){ //if head is nullptr
        insertFront(val);//call insert front(val) and add to epty list
        return;
    }
    while (curr->next != nullptr && pos > 0){ //otherwise, while still in the linkedList or at the end if pos > length
        curr = curr->next; //current equals next
        pos--; //subtract one from pos to keep track of position
    }
    if (curr == head){//after moving through the linked list if curr is head of the linked list, add before
        insertFront(val);
    } else if ( curr == tail){ //if pos > length
        insertBack(val);
    } else { //otherwise if pos < length
        ListNode<T> * temp = new ListNode<T>(val);
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        length++;
    }
}
template <typename T>
void LinkedList<T>::remove(T val){ //remove specific value from list
    ListNode<T> * curr;
    if (head == NULL || head == nullptr) {
        length = 0;
        return;
    }
    curr = head;
    if (curr->data == val){
        removeFront();
        return;
    }
    if (tail->data == val){
        removeBack();
        return;
    }
    while (curr != NULL && curr != nullptr) {
        if (curr->data == val){
                curr->prev->next = curr->next;
            if (!(curr->next == nullptr || curr->next == NULL)){
                curr->next->prev = curr->prev;
            }
            delete curr;
            length --;
            if (head->data == tail->data){
                head->next == nullptr;
                tail->prev == nullptr;
                tail->next == nullptr;
                head->prev == nullptr;
            }
            return;
        }
        curr = curr->next;
    }
    if (curr == tail){
        removeBack();
    }
}
template <typename T>
void LinkedList<T>::removeAt(int pos){ //remove at specific position in linkedlist
    if (pos >= length){}// throw //error}
    ListNode<T> * curr = head; //backwards philosphy from insertAt function
    while (pos > 0){
        curr = curr->next;
        pos --;
    }
    if (curr == head){
        removeFront();
    } else if (curr == tail){
        removeBack();
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        length --;
    }
}
template <typename T>
void LinkedList<T>::removeBack(){ //remove from back of linked list
    if (tail == nullptr || tail == NULL){//empty list
        length = 0;
        return;
    }
    if (head == tail){ //one node in list
        head = nullptr;
        tail = nullptr;
       length = 0;
    } else { //more than one node in list
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
        length--;
        return;
    }
}

template <typename T>
void LinkedList<T>::removeFront(){
    if (head == nullptr || head == NULL)
    {   length = 0;
        return;
    } //empty list
    if (head == tail){//one node in list
        head = nullptr;
        tail = nullptr;
        length = 0;
        delete head;
        delete tail;
    } else { //any other case
        if (head->next != NULL){
            head = head->next;
            delete head->prev;
        } else {
            delete head;
        }
        length--;
    }
}
template <typename T>
T LinkedList<T>::search(T val){ //search for a value in the linked list, returns -1 if not in list
    ListNode<T> * temp = head;
    if (temp->getData() == val) return temp->data;
    while (temp != nullptr && temp->next != nullptr){
        temp = temp->next;
        if (temp->data == val) return temp->data;
    }
    return -1;
}
template <typename T>
void LinkedList<T>::resetIter(){ //Switching to other work for the rest of the night. Hopefully can come back to this before bed. 10/22/18 - 12:09 am
    myIterator = head;
}
template <typename T>
T LinkedList<T>::next(){
    if (myIterator->next != nullptr) {
        myIterator = myIterator->next;
        return myIterator->getData();
    } else {
        return "END";
    }
}
template <typename T>
void LinkedList<T>::print(){// print function, called in print_backward
    ListNode<T> * curr;
    curr = head;
    while ((curr != nullptr) && (curr!=NULL)){
        cout<<curr->data<<" -> ";
        curr = curr->next;
    }
    cout<<endl;
}
template <typename T>
void LinkedList<T>::printForward(){//print forwards through linked list
    ListNode<T> *curr = head;
    while (curr != nullptr){
        cout<<curr->data<<endl;
        curr = curr->next;
    }
}
template <typename T>
void LinkedList<T>::printBackwards(){ //recursively prints the linked list from tail to head
    print_Backward(head);
}
template <typename T>
int LinkedList<T>::getLength(){//number of elements in list
    return length;
}
template<typename T>
void LinkedList<T>::clear(){
    while (length > 0){
        removeFront();
    }
}
template <typename T>
bool LinkedList<T>::exists(T search){
    if (head == nullptr  ) {return false;}
    myIterator = head;
    if (myIterator -> data == search) return true;
    while (myIterator->next != nullptr){
        myIterator = myIterator->next;
        if (myIterator->data == search){
            return true;
        }
    }
    return false;
}

#endif //UNTITLED_LINKEDLIST_H
