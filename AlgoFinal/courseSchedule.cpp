//
// Created by Dylan Furner on 12/8/21.
//

#include "courseSchedule.h"


courseSchedule::~courseSchedule() {
}

courseSchedule::courseSchedule() {

}

courseSchedule::courseSchedule(AdjacencyList<int> ptr1) {
    ptr = ptr1;
    V = ptr.getLength();
    AdjacencyList<LinkedList<int> *> degrees1(ptr.getLength());
    vlist = new vertex<int>[V];
    for (int i = 0; i < ptr.getLength(); i++) {
        for (int k = 0; k < ptr.getLength(); k++) {
            LinkedList<int> *L = &ptr[k];
            if (L->getLength() == i) {
                vlist[k] = vertex<int>(k, &ptr[k], &orderDeleted);
                degrees1.insert(i, &ptr[k]);
            }
        }
    }
    degrees = degrees1;
}

int courseSchedule::searchVertexByPointer(LinkedList<int> *ptr)
    {
        for (int i = 0; i < V; i++){
            if (ptr == vlist[i].getPI()){
                return i;
            }
        }
        return -1;
    }
void courseSchedule::remove(LinkedList<int>* vertexID9) {
    int vertexID1 = searchVertexByPointer(vertexID9);
    int vertexID = searchIndexByVertexID(vertexID1);
    vlist[vertexID1].setDegreeDeleted();
    if (vertexID != -1){
        vector<int> children1;
        LinkedList<int>* children = &ptr[vertexID];
        for (int i = 0; i < children->getLength(); i++){
            children1.push_back(children[0][i]);
        }
        if (degrees[vlist[vertexID1].getDegree()].getLength() == ptr.getLength() && terminalClique == 0){
            terminalClique = ptr.getLength();
        }
        for (int i = 0; i <children1.size(); i++){
                if (vlist[children1[i]].getDegree() > 0){
                    degrees[vlist[children1[i]].getDegree()].remove(vlist[children1[i]].getPI());
                    vlist[children1[i]].getPI()->remove(vertexID1);
                    vlist[children1[i]].setDegreeDeleted();
                    vlist[children1[i]].setDegree(vlist[children1[i]].getDegree()-1);
                    degrees[vlist[children1[i]].getDegree()].insertFront(vlist[children1[i]].getPI());
                }
        }
        ptr.removeElement(vertexID);
        degrees[vlist[vertexID1].getDegree()].remove(vlist[vertexID1].getPI());
        degrees[0].insertFront(vlist[vertexID1].getPI());
        orderDeleted.insertFront(vertexID1);
    }
}

int courseSchedule::getNumDeleted() {
    return orderDeleted.getLength();
}
vertex<int>* courseSchedule::getVList() {
    return vlist;
}
int courseSchedule::getMaxDegree() {
    return maxDegree;
}
LinkedList<int>* courseSchedule::getOrderDeleted(){
    return &orderDeleted;
}

void courseSchedule::calculateColorings() {
    int c = 0;
    vlist[orderDeleted[0]].setColor(c);
    for (int i = 1; i < orderDeleted.getLength(); i++){
        LinkedList<int>* og = vlist[orderDeleted[i]].getOriginalN();
        for (int l = 0; l < og[0].getLength(); l++){
            if (vlist[og[0][l]].getColor() == c){
                cout<<og[0][l]<<endl;
                c++;
            }
        }
        vlist[orderDeleted[i]].setColor(c);
        cout<<"Vertex #"<<orderDeleted[i]<<"'s color is "<<vlist[orderDeleted[i]].getColor()<<endl;
    }
}

void courseSchedule::setOrderDeleted() {

}

void courseSchedule::print(int choice) {
    if (choice == 0){
        ptr.print();
    }
    if (choice == 1){
        degrees.print();
        for (int i = 0; i < degrees.getLength(); i++){
            cout<<i<<"->";
            for (int k = 0; k < degrees[i].getLength(); k++){
                cout<<searchVertexByPointer(degrees[i][k])<<"->";
            }
            cout<<endl;
        }
    }
    if (choice == 2){
        printAll();
    }
}

void courseSchedule::printAll() {
    print(0);
    print(1);
    orderDeleted.print();
}

int courseSchedule::getLowestDegree() {
    for (int i = 1; i < degrees.getLength()-1; i++){
        if (degrees[i].getLength() > 0) return i;
    }
    return 0;
}

int courseSchedule::searchIndexByVertexID(int id) {
    LinkedList<int>* L = vlist[id].getPI();
    for (int i = 0; i < ptr.getLength(); i++) {
        if (ptr.getLength() != 0 && &ptr[i] == L){
            return i;
        }
    }
    return -1;
}

