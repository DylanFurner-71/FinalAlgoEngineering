//
// Created by Dylan Furner on 12/5/21.
//

#ifndef ALGOFINAL_VERTEX_H
#define ALGOFINAL_VERTEX_H
#include "LinkedList.h"
template <typename T>
class vertex {
private:
    int vertexID;
    int originalDegree=0;
    int degreeDelete = 0;
    int prevDegree = 0;
    int orderColored = 0;
    int currIndex = 0;
    int degree = 0;
    int color = 0;
    LinkedList<LinkedList<LinkedList<T>*>>* SameDeg;
    LinkedList<T> *OrderedDelete;
    LinkedList<T>* og;
public:
    LinkedList<T> *pEdge;
    vertex();
    vertex(int ID, LinkedList<T>* z, LinkedList<T>* od);
    ~vertex();
    void setCurrIndex();
    int getCurrIndex();
    void clear();
    int getOrderColored();
    void setOrderColored(int s );
    LinkedList<T>* getPI();
    LinkedList<T>* getOriginalN();
    LinkedList<T>* getSameDegree();
    LinkedList<T>* getOrderedDelete();
    vertex(int ID, LinkedList<T>*z,  LinkedList<LinkedList<LinkedList<T>*>>* q, LinkedList<T>* od);
    int getColor();
    void setColor(int col);
    int getDegree();
    int getOriginal();
    int getID();
    void setDegree(int deg);
    void setSameDegree(LinkedList<T> *);
    void fixDegree();
    void setPID(LinkedList<T>*);
    void setDegreeDeleted();
    int getDegreeDelete();
};

template<typename T>
vertex<T>::vertex() {
}
template<typename T>
void vertex<T>::setDegreeDeleted() {
    degreeDelete = degree;
}
template<typename T>
int vertex<T>::getID() {
    return vertexID;
}
template<typename T>
vertex<T>::~vertex() {
}
template<typename T>
LinkedList<T> *vertex<T>::getSameDegree() {
    return SameDeg;
}
template<typename T>
LinkedList<T> *vertex<T>::getPI() {
    return pEdge;
}
template<typename T>
LinkedList<T> *vertex<T>::getOriginalN() {
    return og;
}

template<typename T>
LinkedList<T> *vertex<T>::getOrderedDelete() {
    return OrderedDelete;
}
template<typename T>
void vertex<T>::setCurrIndex(){
    currIndex--;
}
template<typename T>
void vertex<T>::clear(){
    pEdge->clear();
    degree = getDegree();
}

template<typename T>
void vertex<T>::setDegree(int deg) {
    degree = deg;
}
template<typename T>
int vertex<T>::getDegree() {
    return degree;
}
template<typename T>
int vertex<T>::getOriginal() {
    return originalDegree;
}
template<typename T>
vertex<T>::vertex(int ID, LinkedList<T>* z, LinkedList<T>* od) {
    vertexID = ID;
    currIndex = vertexID;
    pEdge = z;
    originalDegree = pEdge->getLength();
    degree = z->getLength();
    OrderedDelete = od;

}
template<typename T>
vertex<T>::vertex(int ID, LinkedList<T>* z, LinkedList<LinkedList<LinkedList<T>*>>* q, LinkedList<T>* od) {
    vertexID = ID;
    pEdge = z;
    SameDeg = q;
    SameDeg[0][0].insertBack(z);
    OrderedDelete = od;
}
template<typename T>
int vertex<T>::getColor() {
    return color;
}
template<typename T>
void vertex<T>::setColor(int col) {
    color = col;
}

template<typename T>
int vertex<T>::getCurrIndex() {
    return currIndex;
}

template<typename T>
int vertex<T>::getDegreeDelete() {
    return degreeDelete;
}

template<typename T>
int vertex<T>::getOrderColored() {
    return orderColored;
}

template<typename T>
void vertex<T>::setOrderColored(int s) {
    orderColored = s;
}


#endif //ALGOFINAL_VERTEX_H
