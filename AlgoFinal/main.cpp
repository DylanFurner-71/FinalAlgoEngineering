#include <iostream>
#include "LinkedList.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include "graphGenerator.h"
#include "courseSchedule.h"
#include <unordered_set>
#include "vertex.h"

vector<float> coloringsTimes;
void outputColoringTimes(){
    ofstream ofs( "OutputTimes/ColoringTimes.csv" );
    for (int i = 0; i < coloringsTimes.size(); i++){
        ofs<<coloringsTimes[i]<<endl;
    }
    ofs.close();
}
void TimesToCSV(float** times, int sizes[], int size, string fileName){
    fileName = fileName.substr(fileName.find("/")+1, fileName.length());
    ofstream ofs( "OutputTimes/output"+fileName+".csv" );
    ofs<<"NUM VERTICES,"<<"SMLVO"<<", "<<"SMODL"<<", "<<"welshpowell"<<","<<"largestoriginaldegreelast, largestlast, uniformrandom"<<endl;
        for (int i = 0; i < size-2; i++){
            ofs<<to_string(sizes[i]+3)<<","<<times[0][i+2]<<","<<times[1][i+2]<<","<<times[2][i+2]<<","<<times[3][i+2]<<","<<times[4][i+2]<<","<<times[5][i+2]<<endl;
    }
    ofs.close() ;
}
void GraphTimesToCSV(float** times, int sizes[], int size, string fileName){
    ofstream ofs( "GraphTimes/"+fileName+".csv" );
    ofs<<"NUM VERTICES,"<<"UniformDistribution"<<", "<<"Complete"<<", "<<"Cyclic"<<","<<"Skew, Normal"<<endl;
    for (int i = 0; i < size-2; i++){
        ofs<<to_string(sizes[i]+3)<<","<<times[0][i+2]<<","<<times[1][i+2]<<","<<times[2][i+2]<<","<<times[3][i+2]<<","<<times[4][i+2]<<","<<times[5][i+2]<<endl;
    }
    ofs.close();
}
void resultsToFile(vertex<int>* vlist, int size, string fileName, string path, courseSchedule*ptr){
    ofstream ofs( "Data/" +path+"/"+fileName+"/"+fileName+path+to_string(size)+".csv" );
    ofs<<"vertex id,originalDegree,color,orderColored"<<endl;
    for (int i = 0; i < size; i++){
        ofs<<vlist[i].getID()<<","<<vlist[i].getDegree()<<","<<vlist[i].getColor()<<","<<vlist[i].getOrderColored()<<endl;
    }
    ofs<<endl;
    ofs.close();
}
void calculateNumberOfColors(string* fileNames, string* algoNames, int maxSize, int numDistributions, int numAlgos){
for (int i = 0; i < numDistributions; i++){
    fileNames[i] = fileNames[i].substr(fileNames[i].find("/")+1, fileNames[i].length());
}
//num edges complete = formula
//num edges everything but cycle and complete = formula /2
//num edges cycle = v
struct data {
    int V;
    int E;
    int avg;
    int numColors;
    string graphType= "";
    string algoType="";
    int terminalClique = -1;
};
    vector<vector<data>> vecMaster;
    ifstream io;
for (int i = 0; i < numAlgos; i++){
    vector<data> vec;
    for (int k = 0; k < numDistributions; k++){
        for (int q = 3; q < maxSize; q++){
            data d;
        d.V = q;
        d.E = ((d.V*(d.V-1))/2)/2;
        if (k == 1){
            d.E = (d.V*(d.V-1))/2;
        }
        if (k == 2){
            d.E = d.V;
        }
        io.open("Averages/"+algoNames[i]+"/"+fileNames[k]+"/"+fileNames[k]+algoNames[i]+"averageDegree"+to_string(q)+".csv");
        if (!io){
            cout<<"Sorry. The file you are looking for is not available bby"<<endl;
        }
        string curr;
        getline(io, curr);
        getline(io, curr);
        if (curr.length() == 9){
            string tc;
            tc = curr.substr(8, curr.length()); //fix this
            d.terminalClique = stoi(tc);
        }
            curr = curr.substr(curr.find(",")+1, curr.length());
            curr = curr.substr(curr.find(",")+1, curr.length());
            curr = curr.substr(curr.find(",")+1, curr.length());
            curr = curr.substr( curr.find(",")+1, curr.length());
        d.avg = stoi(curr);
        io.close();
        int * a = new int[q];
        int count = 0;
        io.open("Data/"+algoNames[i]+"/"+fileNames[k]+"/"+fileNames[k]+algoNames[i]+to_string(q)+".csv");
        if (!io){
            cout<<"Data/"+algoNames[i]+"/"+fileNames[k]+"/"+fileNames[k]+algoNames[i]+to_string(q)+".csv"<<endl;
            cout<<"Sorry. The file you are looking for is not available"<<endl;
        }
        getline(io, curr);
        for (int l = 0; l < q; l++){
            getline(io, curr);
            curr = curr.substr(curr.find(",")+1, curr.length());
            curr = curr.substr(curr.find(",")+1, curr.length());
            curr = curr.substr(0, curr.find(","));
            a[count] = stoi(curr);
            count++;
        }
        io.close();
        std::unordered_set<int> s(a, a + q);
        d.numColors = s.size();
        d.graphType = fileNames[k];
        d.algoType = algoNames[i];
        vec.push_back(d);
    }
}
vecMaster.push_back(vec);
}
ofstream ofs("Averages/AverageColors.csv");
ofs<<"V,E,NumColors,AvgDegree,GraphType,AlgoType,TerminalClique"<<endl;
for (int i = 0; i < vecMaster.size(); i++){
    for (int k = 0; k < vecMaster[i].size(); k++){
        ofs<<vecMaster[i][k].V<<","<<vecMaster[i][k].E<<","<<vecMaster[i][k].numColors<<","<<vecMaster[i][k].avg<<","<<vecMaster[i][k].graphType<<","<<vecMaster[i][k].algoType;
        if (vecMaster[i][k].terminalClique != -1) {ofs<<","<<vecMaster[i][k].terminalClique;}
            ofs<<endl;
    }
}
ofs.close();
}
void averageDataToFile(vertex<int>* vlist, int size, string fileName, string path, courseSchedule*ptr, int a = 0){
    ofstream ofs( "Averages/"+path+"/"+fileName+"/"+fileName+path+"averageDegree"+ to_string(size)+".csv" );
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum+= vlist[i].getOriginal();
    }
    sum /= size;
    if (a != 0){
        ofs<<"vertex id,originalDegree,degreeDelete,average,terminalClique"<<endl;
        for (int i = 0; i < size; i++){
            ofs<<vlist[i].getID()<<","<<vlist[i].getOriginal()<<","<<vlist[i].getDegreeDelete()<<","<<sum<<","<<ptr->terminalClique<<endl;
        }
    } else {
        ofs<<"vertex id,originalDegree,degreeDelete,average,"<<endl;
        for (int i = 0; i < size; i++){
            ofs<<vlist[i].getID()<<","<<vlist[i].getOriginal()<<","<<vlist[i].getDegreeDelete()<<","<<sum<<endl;
        }
    }


    ofs<<endl;
    ofs.close();
}
void createColorings(courseSchedule* ptr, LinkedList<int>* orderDeleted){
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int orderColored = 0;
    for (int i = 0; i < orderDeleted->getLength(); i++){
        int a = orderDeleted[0][i];
        std::unordered_set<int> s;
        int color = 0;
        for (int k = 0; k < ptr->ptr[a].getLength(); k++){
            s.insert(ptr->vlist[ptr->ptr[a][k]].getColor());
        }
        while (true){
                if (s.find(color) == s.end()) break;
                color++;
        }
        ptr->vlist[a].setColor(color);
        ptr->vlist[a].setOrderColored(orderColored);
        orderColored++;
    }
    high_resolution_clock::time_point end = high_resolution_clock::now();
    std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
    coloringsTimes.push_back(time.count());
}
void largestLast(courseSchedule* ptr, courseSchedule* ptr2){
    while (true) {
        int minDegree = 0;
        for (int i = 1; i < ptr->V; i++){
            if (ptr->degrees[i].getLength() > 0){
                minDegree = i;
                break;
            }
        }
        if (minDegree == 0) break;
        for (int i = 0; i < ptr->degrees[minDegree].getLength(); i++){
            ptr->remove(ptr->degrees[minDegree][0]);
        }
    }
    if (ptr->searchVertexByPointer(&ptr->ptr[0]) != -1){
        ptr->orderDeleted.insertFront(ptr->searchVertexByPointer(&ptr->ptr[0]));
    }
    LinkedList<int> T;
    for (int i = ptr->orderDeleted.getLength()-1; i>-1; i--){ //check this without -1
        T.insertBack(ptr->orderDeleted[i]);
    }
    createColorings(ptr2, &T);
}
void smallestLastVertexOrdering(courseSchedule* ptr, courseSchedule* ptr2){
//    int size1 = ptr->degrees[1].getLength();
//    if (size1 > 0){
//        for (int i = 0; i < size1; i++){
//            ptr->remove((ptr->degrees[1][0]));
//        }
//    }
    while (true) {
        int minDegree = 0;
        for (int i = 1; i < ptr->V; i++){
            if (ptr->degrees[i].getLength() > 0){
                minDegree = i;
                break;
            }
        }
        if (minDegree == 0) break;
        for (int i = 0; i < ptr->degrees[minDegree].getLength(); i++){
            ptr->remove(ptr->degrees[minDegree][0]);
        }
    }
    if (ptr->searchVertexByPointer(&ptr->ptr[0]) != -1){
        ptr->orderDeleted.insertFront(ptr->searchVertexByPointer(&ptr->ptr[0]));
    }
    createColorings(ptr2, &ptr->orderDeleted);
}
void smallestOriginalDegreeLast(courseSchedule*q) {
    AdjacencyList<LinkedList<int> *> *ptrL;
    ptrL = &q->degrees;
    LinkedList<int> *t = new LinkedList<int>();
    for (int i = 0; i < ptrL->getLength(); i++) {
        if (ptrL[0][i].getLength() > 0) {
            for (int k = 0; k < ptrL[0][i].getLength(); k++) {
                t->insertFront(q->searchVertexByPointer(ptrL[0][i][k]) );
            }
        }
    }
    createColorings(q, t);
}
void largestOriginalDegreeLast(courseSchedule*q) {
    AdjacencyList<LinkedList<int> *> *ptrL;
    ptrL = &q->degrees;
    LinkedList<int> *t = new LinkedList<int>();
    for (int i = ptrL->getLength()-1; i > -1 ; i--) {
        if (ptrL[0][i].getLength() > 0) {
            for (int k = 0; k < ptrL[0][i].getLength(); k++) {
                t->insertFront(q->searchVertexByPointer(ptrL[0][i][k]) );
            }
        }
    }

    createColorings(q, t);
}
void welshpowell(courseSchedule*q) {
    int color = 1, colored = 0;
    LinkedList<LinkedList<int>*> degreesOrdered;
    LinkedList<int> vertices;
    for (int i = q->degrees.getLength()-1; i > -1; i--){
        if (q->degrees[i].getLength() > 0){
            for (int k = 0; k < q->degrees[i].getLength(); k++){
               degreesOrdered.insertBack(q->degrees[i][k]);
               vertices.insertBack(q->searchVertexByPointer(q->degrees[i][k]));
            }
        }
    } //list of vertices in descending degrees
    std::unordered_set<int> setc;
    for (int i = 0; i < degreesOrdered.getLength(); i++){
        std::unordered_set<int> set;
        for (int k = 0; k < degreesOrdered[i][0].getLength(); k++){
            set.insert(degreesOrdered[i][0][k]);
        }
        for (int k = 0; k < q->ptr.getLength(); k++){
            if (set.find(k) != set.end() || setc.find(k) != setc.end()) continue; //maybe break //|| setColored.find(k) != setColored.end()
            q->vlist[k].setColor(color);
            setc.insert(k);
        }
        setc.insert(q->searchVertexByPointer(degreesOrdered[i]));
        color++;
    }
}
void swap(int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void shuffle(int *arr, int n){
    for (int i = n-1; i > 0; --i){
        swap(&arr[i], &arr[rand()%n]);
    }
}
void uniformRandomOrdering(courseSchedule*q) {
    int * shuffled = new int[q->V];
    for (int k = 0; k < q->V; k++){
        shuffled[k] = k;
    }
    shuffle(shuffled, q->V);
    for (int i = 0; i < q->V; i++){
        q->orderDeleted.insertBack(shuffled[i]);
    }
    createColorings(q, &q->orderDeleted);
}
void AlgorithmWithTimings(courseSchedule*ptr, int c, float* times1, int size, courseSchedule*ptr2, string fileName){
    fileName = fileName.substr(fileName.find("/")+1, fileName.length());
    using namespace std::chrono;
    string algoName = "";
    if (c == 0){
        algoName = "SmallestLastVertex";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        smallestLastVertexOrdering(ptr2, ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
        averageDataToFile(ptr2->vlist, ptr2->V, fileName,algoName,ptr2, 1);
    }
    if (c == 1){
        algoName = "SmallestOriginalDegreeLast";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        smallestOriginalDegreeLast(ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
    }
    if (c == 2){
        algoName = "WelshPowell";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        welshpowell(ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
    }
    if (c == 3){
        algoName = "LargestOriginalDegreeLast";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        largestOriginalDegreeLast(ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
    }
    if (c == 4){
        algoName = "LargestLast";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        largestLast(ptr2, ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
        averageDataToFile(ptr2->vlist, ptr2->V, fileName,algoName, ptr2, 1);
    }
    if (c == 5){
        algoName = "uniformRandomOrdering";
        high_resolution_clock::time_point start = high_resolution_clock::now();
        uniformRandomOrdering(ptr);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
        times1[size] = time.count();
    }
    if (c != 0 && c != 4){
        averageDataToFile(ptr->vlist, ptr->V, fileName,algoName, ptr);
    }
    resultsToFile(ptr->vlist, ptr->V, fileName, algoName, ptr);
}
void algoChoice(string fileName, graphGenerator* g1, int choice, int withT, int size, courseSchedule *q, int indexTimingsData, float *times1){
    if (choice == 0){
        courseSchedule ptr2( g1->readFileGenerateGraph(fileName, size));
        (withT == 0) ? smallestLastVertexOrdering(q, &ptr2) : AlgorithmWithTimings(q, 0, times1, size, &ptr2, fileName);
    }
    if (choice == 1){
        (withT == 0) ? smallestOriginalDegreeLast(q) : AlgorithmWithTimings(q, 1, times1, size, q, fileName);
    }
    if (choice == 2){
        (withT == 0) ? welshpowell(q) : AlgorithmWithTimings(q, choice, times1, size, q, fileName);
    }
    if (choice == 3){
        (withT == 0) ? largestOriginalDegreeLast(q) : AlgorithmWithTimings(q, choice, times1, size, q, fileName);
    }
    if (choice == 4){
        courseSchedule ptr2( g1->readFileGenerateGraph(fileName, size));
        (withT == 0) ? largestLast(q, &ptr2) : AlgorithmWithTimings(q, choice, times1, size, &ptr2, fileName);
    }
    if (choice == 5){
        (withT == 0) ? uniformRandomOrdering(q) : AlgorithmWithTimings(q, choice, times1, size, q, fileName);
    }
}
int main() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    graphGenerator* g1;
    g1 = new graphGenerator();
    int sizeFactor = g1->getSizeFactor();
    int size = g1->getSize();
    int arr1[size];
    int valuesOfE[size];
    for (int i = 1; i < size; i++){
        int e;
        if (i > 2) {
            int max = ((sizeFactor*i)*(sizeFactor*i-1))/2;
            if (max > 2000000){
                max = 2000000;
            }
            std::uniform_int_distribution<int> dist(i-1, max);//this generates the values of e to use for each step
            e = max;
        } else {
            if (i == 2){
                e = 1;
            } else {
                e = 0;
            }
        }
        valuesOfE[i] =  e/2;
    }
    for (int k = 0; k < size; k++){
        arr1[k] = k;
    }
    //g1->runGraphCreationAndTimings(valuesOfE, arr1, generator);
    const int numAlgos = 6;
    int numDistributions = 5;
    string* fileName = new string[numAlgos];
    fileName[0] = "UniformDistributionR/UniformDistributionR";
    fileName[1] = "Complete/CompleteGraph";
    fileName[2] = "CyclicGraph/CyclicGraph";
    fileName[3] = "Skew/UniformDistributionSkew";
    fileName[4] = "ModifiedNormal/ModifiedNormal";
    float*** timesMaster = new float**[numDistributions];
    float*** timesMasterGraph = new float**[numDistributions];
    for (int i = 0; i < numAlgos; i++){
        timesMaster[i] = new float*[numAlgos];
        timesMasterGraph[i] = new float*[numAlgos];
        for (int y = 0; y < numAlgos; y++){
            timesMaster[i][y] = new float[size];
            timesMasterGraph[i][y] = new float[size];
        }
    }
    string* AlgoNames = new string[numAlgos];
    AlgoNames[0] = "SmallestLastVertex";
    AlgoNames[1] = "SmallestOriginalDegreeLast";
    AlgoNames[2] = "WelshPowell";
    AlgoNames[3] = "LargestOriginalDegreeLast";
    AlgoNames[4] = "LargestLast";
    AlgoNames[5] = "uniformRandomOrdering";
    //AdjacencyList<int> ptr = g1->readFileGenerateGraph("Simple/Simple", 5);
    //courseSchedule abc(ptr);
    //algoChoice("Simple/Simple", g1, 0, 1, 5, &abc, 5, timesMaster[0][0]);
    for (int fName = 0; fName < numDistributions; fName++){
    for (int i = 0; i < 6; i++){
        for (int k = 3; k < size; k++){
            cout<<fileName[fName]<<" "<<AlgoNames[i]<<" "<<k<<endl;
            using namespace std::chrono;
            high_resolution_clock::time_point start = high_resolution_clock::now();
            AdjacencyList<int> ptr = g1->readFileGenerateGraph(fileName[fName], k);
            high_resolution_clock::time_point end = high_resolution_clock::now();
            std::chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(end - start);
            timesMasterGraph[fName][i][k] = time.count();
            courseSchedule abc(ptr);
            algoChoice(fileName[fName], g1, i, 1, k, &abc, i, timesMaster[fName][i]);
        }
    }
    TimesToCSV(timesMaster[fName], arr1, size, fileName[fName]);
}
    GraphTimesToCSV(timesMaster[0], arr1, size, "GraphTimings");
    calculateNumberOfColors(fileName, AlgoNames, size, numDistributions, numAlgos);
    outputColoringTimes();
    return 0;
}


