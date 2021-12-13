//
// Created by Dylan Furner on 10/17/21.
//

#ifndef UNTITLED_LISTNODE_H
#define UNTITLED_LISTNODE_H
/*
 * Templated Node Class
 */
template <typename T>
class ListNode
{
private:
public:
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;
    ListNode();
    ListNode(T val); //constructor
    ~ListNode (); //destructor
    ListNode(const ListNode& a); //copy constructor
    const T getData(); //returns copy of data
};

template <typename T>
const T ListNode<T>::getData(){
    return data;
}
template <typename T>
ListNode<T>::ListNode(T val)
{
    data = val;
    next = NULL;
    prev = NULL;
}
template <typename T>
ListNode<T>::ListNode()
{
    data = NULL;
    next = NULL;
    prev = NULL;
}
template <typename T>
ListNode<T>::~ListNode (){ //i think this may be empty...

}

template <typename T>
ListNode<T>::ListNode(const ListNode& a){
    data = a.data;
    next = a.next;
    prev = a.prev;
}
#endif //UNTITLED_LISTNODE_H
