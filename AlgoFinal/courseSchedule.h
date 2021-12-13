//
// Created by Dylan Furner on 12/8/21.
//

#ifndef ALGOFINAL_COURSESCHEDULE_H
#define ALGOFINAL_COURSESCHEDULE_H

#include "LinkedList.h"
#include "adjacencyList.h"
#include "vertex.h"
class courseSchedule {
public:
    courseSchedule();
    ~courseSchedule();
    courseSchedule(AdjacencyList<int>);
    vertex<int> * vlist;
    LinkedList<int> orderDeleted;
    AdjacencyList<LinkedList<int>*> degrees;
    LinkedList<int>* getOrderDeleted();
    int terminalClique = 0;
    int maxDegree;
    int getNumDeleted();
    vertex<int>* getVList();
    int getMaxDegree();
    void calculateColorings();
    void setOrderDeleted();
    int getLowestDegree();
    void print(int choice);
    void printAll();
    AdjacencyList<int> ptr;
    int searchVertexByPointer(LinkedList<int>* ptr);
    int searchIndexByVertexID(int id);
    int searchIndexByVertexP(LinkedList<int> *ptr1);
    void remove(LinkedList<int>* vertexID);
    int V;
};


#endif //ALGOFINAL_COURSESCHEDULE_H
