//
// Created by Dylan Furner on 12/5/21.
//

#ifndef ALGOFINAL_ADJACENCYLIST_H
#define ALGOFINAL_ADJACENCYLIST_H

#include <vector>
#include "LinkedList.h"
#include "vertex.h"
template <typename T>
class AdjacencyList {
private:
    LinkedList<LinkedList<T>> adjList;
    int length = 0;
    int originalLength = 0;
public:
    AdjacencyList(int V);
    AdjacencyList();
    ~AdjacencyList();
    int searchByVertex(int vertexID);
    AdjacencyList(const AdjacencyList<T> &old);
    void insert(int loc, T val);
    bool insertPairCheckDuplicate(int loc1, int loc2, T val1, T val2);
    LinkedList<T>& operator[](int z); //int z = variable value passed in
    void print();
    int getLength();
    int getOriginal();
    int searchByPointer(LinkedList<T>* ptr);
    void removeElement(T element);
    int searchVertexByPointer(LinkedList<T>* ptr);
};

template <typename T>
AdjacencyList<T>::AdjacencyList(int V){
    length = V;
    originalLength = V;
    if (V > 0) {
            for (int i = 0; i < V; i++) { //initial iteration -> go through and create a null linked list for each
                LinkedList<T> ptr;
                adjList.insertBack(ptr);
            }
    }
}
template<typename T>
AdjacencyList<T>::AdjacencyList(const AdjacencyList<T> &old){
    length = old.length;
    adjList = old.adjList;
    originalLength = old.originalLength;
}
template <typename T>
AdjacencyList<T>::~AdjacencyList(){
//    for (int i = length-1; i > 0; i--){
//        delete &adjList[i];
//    }
}
template <typename T>
int AdjacencyList<T>::getOriginal() {
    return originalLength;
}
template <typename T>
int AdjacencyList<T>::searchByPointer(LinkedList<T>* ptr){
    for (int i = 0; i < length; i++){
        if (ptr == &adjList[i]){
            return i;
        }
    }
    return -1;
}


template <typename T>
void AdjacencyList<T>::print(){
        int qREM = 0;
        for (int i = 0; i < length; i++) {
            int l2 = adjList[i].getLength();
            cout << "Index " << i<< " :: ";
            for (int k = 0; k < l2; k++) {
                cout << adjList[i][k];
                if (k != l2 - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
}

template <typename T>
void AdjacencyList<T>::insert(int loc, T val){
    if (loc > adjList.getLength()-1){
        ListNode<T> a;
        a.data = val;
        adjList.insertBack(a);
    }
    if (!adjList[loc].exists(val)) {
        adjList[loc].insertBack(val);
        if (adjList.getLength() > originalLength){
            originalLength = adjList.getLength();
        }
    }
    length = adjList.getLength();
}
template <typename T>
void AdjacencyList<T>::removeElement(T element){
    adjList.removeAt(element);
    length--;
}
template <typename T>
LinkedList<T>& AdjacencyList<T>::operator [](int z){
    return adjList[z];
}
template <typename T>
bool AdjacencyList<T>::insertPairCheckDuplicate(int loc1, int loc2, T val1, T val2) {
    if (loc1 == loc2) return false;
    if (!adjList[loc1].exists(val2) && !adjList[loc2].exists(val1)){
        insert(loc1, val2);
        insert(loc2, val1);
        return true;
    }
    return false;
}
template <typename T>
int AdjacencyList<T>::getLength() {
    return length;
}




template<typename T>
AdjacencyList<T>::AdjacencyList() {

}




#endif //ALGOFINAL_ADJACENCYLIST_H
