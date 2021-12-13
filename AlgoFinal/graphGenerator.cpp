//
// Created by Dylan Furner on 12/5/21.
//

#include "graphGenerator.h"
 vector<int> graphGenerator::p2;
 int graphGenerator::vprev;
vector<int> graphGenerator::p1;
vector<added> graphGenerator::p3;
std::random_device graphGenerator::m_rd;
std::mt19937 graphGenerator::m_rng(graphGenerator::m_rd());
set<pairs> graphGenerator::set;
graphGenerator::graphGenerator() {
graphGenerator::vprev=0;
};
graphGenerator::~graphGenerator() {

};
int graphGenerator::getSize(){
    return size;
}
int graphGenerator::getSizeFactor(){
    return sizeFactor;
}
void graphGenerator::saveGeneratedEdgeValuesToFile(int e[], int size, bool randomized){
    if (randomized == true) {
        ofstream ofs( "edgesERandom.csv" ) ;
        for (int i = 0; i < size; i++){
            ofs<<e[i]<<", "<<i<<endl;
        }
        ofs.close();
    } else {
        ofstream ofs( "edges2E.csv" ) ;
        for (int i = 0; i < size; i++){
            ofs<<e[i]<<endl;
        }
        ofs.close();
    }
}
void graphGenerator::TimesToCSV(int** times, int sizes[], int size){
    ofstream ofs( "milky.csv" ) ;
    for (int i = 0; i < size; i++){
        ofs<<to_string(sizes[i])<<","<<times[0][i]<<","<<times[1][i]<<","<<times[2][i]<<","<<times[3][i]<<endl;
    }
    ofs.close() ;
}
void graphGenerator::TimesToCSV(float** times, int sizes[], int size){
    ofstream ofs( "milky.csv" ) ;
    for (int i = 0; i < size-3; i++){
        ofs<<to_string(sizes[i])<<","<<times[0][i+2]<<","<<times[1][i+2]<<","<<times[2][i+2]<<","<<times[3][i+2]<<endl;
    }
    ofs.close() ;
}
void graphGenerator::printToFile(int sizeOfZ, AdjacencyList<int> z, int step, string nameOfFile){
    ofstream ofs( nameOfFile+".txt" );
    int start = sizeOfZ;
    ofs<<sizeOfZ<<endl;
    ofs<<sizeOfZ+2<<endl;
    if (sizeOfZ > 0){
        for (int i = 1; i < sizeOfZ; i++){
            start = start + z[i].getLength();
            ofs<<2+start<<endl;
        }
        for (int i = 0; i < sizeOfZ; i++){
            int l2 = z[i].getLength();
            for (int k = 0; k < l2; k++){
                ofs<<z[i][k]<<endl;
            }
        }
    }
    ofs.close();
}
void graphGenerator::runGraphCreationAndTimings(int valuesOfE[], int arr1[], default_random_engine generator) {
    saveGeneratedEdgeValuesToFile(valuesOfE, size, true);
    int** times = new int*[5];
    for (int k = 0; k < size; k++){
        arr1[k] = k*sizeFactor;
    }
    times[0] = runTimings(arr1, size, &graphGenerator::completeGraph, true);
    times[1] = runTimings(arr1, size, &graphGenerator::cycle, false);
    times[2] = runTimings(arr1, valuesOfE, size, &graphGenerator::randomlyDistributedPairs, generator, true);
    graphGenerator::p2.clear();
    graphGenerator::p1.clear();
    graphGenerator::set.clear();
    graphGenerator::vprev = 0;
    times[3] = runTimings(arr1, valuesOfE, size, &graphGenerator::skew, generator, false);

    graphGenerator::p2.clear();
    graphGenerator::p1.clear();
    graphGenerator::set.clear();
    graphGenerator::vprev = 0;
    times[4] = runTimings(arr1, valuesOfE, size, &graphGenerator::modifiedNormal, generator, false, true);

//    for (int i = 0; i < size; i++){ //this generates the values of e to use for each step
//        valuesOfE[i] =  sizeFactor*i;
//    }
//    saveGeneratedEdgeValuesToFile(valuesOfE, size, false);
//    times[3] = runTimings(arr1, valuesOfE, size, &graphGenerator::randomlyDistributedPairs, generator, true);
    int * z = arr1;
    TimesToCSV((times), z, size);
}

AdjacencyList<int> graphGenerator::completeGraph(int V){
    AdjacencyList<int> adjList(V);
    for (int i = 0; i < V; i++){
        for (int k = 0; k < V; k++){
            if (k != i) {
                adjList.insert(i, k);
            }
        }
    }
    return adjList;
}
AdjacencyList<int> graphGenerator::cycle(int V){
    AdjacencyList<int> adjList(V);// = new LinkedList<int>*[V];
    if (V > 1){
            for (int i = 1; i < V-1; i++){
                adjList.insert(i, i+1);
                adjList.insert(i, i-1);
            }
            adjList.insert(V-1, 0);
            adjList.insert(0, V-1);
            if (V > 2){
                adjList.insert(0, 1);
                adjList.insert(V-1, V-2);
            }
    }
return adjList;
}
AdjacencyList<int> graphGenerator::skew(int V, int E, std::default_random_engine generator){
    graphGenerator::p2.clear();
    graphGenerator::p1.clear();
    graphGenerator::set.clear();
    AdjacencyList<int> adjList(V);
    if (E == (V*(V-1)/2)){
        return completeGraph(V);
    }
    std::uniform_int_distribution<int> dist(0, V-1);
    int count = 0;
    if (E == V && V==2){
        E = 1;
    }
    for (int i = graphGenerator::vprev; i < V; i++){
        added a2;
        a2.x = i;
        int z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1))); //dist(generator);
        while (i == z){ //error check
            z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
        }
        a2.y = z;
        pairs p = make_pair(i, z);
        if (graphGenerator::set.find(p) == graphGenerator::set.end()){
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        } else {
            vector<int> already;
            z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
            while (i == z || !(find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(i, z)) == graphGenerator::set.end())){ //error check
                z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
                a2.y = z;
            }
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        }
    }
    while (count < E && E > 1){
        int x =  (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
        int z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
        while (x == z){ //error check
            z = (V-1) * (1-sqrt(graphGenerator::getRandomNumber(0, 1)));
        }
        added a2;
        a2.x = x;
        a2.y = z;
        auto l = find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(x, z));
        if ((l == graphGenerator::set.end())){
            graphGenerator::p1.push_back(x);
            graphGenerator::p2.push_back(z);
            count++;
        }
    }
    for (int i = 0; i < graphGenerator::p1.size(); i++){
        adjList.insert(graphGenerator::p1[i], graphGenerator::p2[i]);
        if (graphGenerator::p1.size() > V){
            adjList.insert(graphGenerator::p2[i], graphGenerator::p1[i]);
        }
    }
    graphGenerator::vprev = V;
    return adjList;
}

AdjacencyList<int> graphGenerator::randomlyDistributedPairs(int V, int E, std::default_random_engine generator){
    AdjacencyList<int> adjList(V);
    if (E == (V*(V-1)/2)){
        return completeGraph(V);
    }
    std::uniform_int_distribution<int> dist(0, V-1);
    int count = 0;
    if (E == V && V==2){
        E = 1;
    }
    for (int i = graphGenerator::vprev; i < V; i++){
        added a2;
        a2.x = i;
        int z = dist(generator);
        while (i == z){ //error check
            z = dist(generator);
        }
        a2.y = z;
        pairs p = make_pair(i, z);
        if (graphGenerator::set.find(p) == graphGenerator::set.end()){
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        } else {
            vector<int> already;
            z = dist(generator);
            while (i == z || !(find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(i, z)) == graphGenerator::set.end())){ //error check
                z = dist(generator);
                a2.y = z;
            }
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        }
    }
    while (count < E && E > 1){
        int x =  dist(generator);
        int z = dist(generator);
        while (x == z){ //error check
            z = dist(generator);
        }
        added a2;
        a2.x = x;
        a2.y = z;
        auto l = find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(x, z));
        if ((l == graphGenerator::set.end())){
            graphGenerator::p1.push_back(x);
            graphGenerator::p2.push_back(z);
            count++;
        }
        }
        for (int i = 0; i < graphGenerator::p1.size(); i++){
            adjList.insert(graphGenerator::p1[i], graphGenerator::p2[i]);
            if (graphGenerator::p1.size() > V){
                adjList.insert(graphGenerator::p2[i], graphGenerator::p1[i]);
            }
        }
    graphGenerator::vprev = V;
    return adjList;
}
int* graphGenerator::runTimings(int *arr, int size, AdjacencyList<int>(*func)(int), bool zq){
    int* times = new int[size];
    int sizeFactor = 1;
    using namespace std::chrono;
    for (int k = 3; k < size; k ++) {
        high_resolution_clock::time_point start = high_resolution_clock::now();
        AdjacencyList<int>z = func(arr[k]);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        auto total_time = duration_cast<microseconds>(end - start).count();
        times[k] = total_time;
            if (zq == true) {
                printToFile(arr[k], z, k, CompleteGraph + to_string(k*sizeFactor));
            } else {
                printToFile(arr[k], z, k, CyclicGraph + to_string(k*sizeFactor));
            }
    }
    return times;
}

int* graphGenerator::runTimings(int *arrV, int *arrE, int size,
                                AdjacencyList<int> (*func)(int, int, std::default_random_engine),
                                std::default_random_engine generator, bool random, bool normal){
    int* times = new int[size];
    using namespace std::chrono;
    for (int k = 3; k < size; k ++) {
        high_resolution_clock::time_point start = high_resolution_clock::now();
        AdjacencyList<int> z = func(arrV[k], arrE[k], generator);
        high_resolution_clock::time_point end = high_resolution_clock::now();
        auto total_time = duration_cast<microseconds>(end - start).count();
        times[k] = total_time;
            if (random == true){
                printToFile(arrV[k], z, k, UniformDistribution + to_string(k));
            } else {
                if (normal) {
                    printToFile(arrV[k], z, k, ModifiedNormal + to_string(k));
                } else {
                    printToFile(arrV[k], z, k, UniformDistributionSkew + to_string(k));

                }
            }
    }
    return times;
}
AdjacencyList<int> graphGenerator::readFileGenerateGraph(string fileName, int size1){

    ifstream io;
    int size;
    int * pos;
    io.open(fileName+to_string(size1)+".txt");
    if (!io){
        cout<<"Sorry. The file you are looking for is not available"<<endl;
    }
    string curr;
    getline(io, curr);
    size = stoi(curr);
    AdjacencyList<int> toReturn(size);
    pos = new int[size];
    int currLine = 1;
    for (int i = 0; i < size; i++){
        getline(io, curr);
        pos[i] = stoi(curr);
        currLine++;
    }
        int step = 0;
        while(getline(io, curr)){
            toReturn.insert(step, stoi(curr));
            toReturn.insert(stoi(curr),step);
            currLine++;
            if ((step < size) && currLine == pos[step+1]-1){
                step++;
            }
        }
//        for (int i = 0; i < size; i++){
//            delete &pos[size];
//        }
//        delete pos;
    return toReturn;
}

double graphGenerator::getRandomNumber(double s, double e) {
    uniform_real_distribution<> randomizer(s, e);
    return randomizer(m_rng);
}

AdjacencyList<int> graphGenerator::modifiedNormal(int V, int E, std::default_random_engine generator) {
    graphGenerator::p2.clear();
    graphGenerator::p1.clear();
    graphGenerator::set.clear();
    AdjacencyList<int> adjList(V);
    if (E == (V*(V-1)/2)){
        return completeGraph(V);
    }
    std::uniform_int_distribution<int> dist(0, V-1);
    int count = 0;
    if (E == V && V==2){
        E = 1;
    }
    for (int i = graphGenerator::vprev; i < V; i++){
        added a2;
        a2.x = i;
        int z = graphGenerator::getRandomNumber(0, V-1); //dist(generator);
        while (i == z){ //error check
            z = graphGenerator::getRandomNumber(0, V-1);
        }
        a2.y = z;
        pairs p = make_pair(i, z);
        if (graphGenerator::set.find(p) == graphGenerator::set.end()){
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        } else {
            vector<int> already;
            z = graphGenerator::getRandomNumber(0, V-1);
            while (i == z || !(find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(i, z)) == graphGenerator::set.end())){ //error check
                z =graphGenerator::getRandomNumber(0, V-1);
                a2.y = z;
            }
            graphGenerator::p1.push_back(i);
            graphGenerator::p2.push_back(z);
            count++;
        }
    }
    while (count < E && E > 1){
        int x =  graphGenerator::getNormalNumber(V-1);
        int z = graphGenerator::getRandomNumber(0, V-1);
        while (x == z){ //error check
            z = graphGenerator::getRandomNumber(0, V-1);
        }
        added a2;
        a2.x = x;
        a2.y = z;
        auto l = find(graphGenerator::set.begin(), graphGenerator::set.end(), make_pair(x, z));
        if ((l == graphGenerator::set.end())){
            graphGenerator::p1.push_back(x);
            graphGenerator::p2.push_back(z);
            count++;
        }
    }
    for (int i = 0; i < graphGenerator::p1.size(); i++){
        adjList.insert(graphGenerator::p1[i], graphGenerator::p2[i]);
        if (graphGenerator::p1.size() > V){
            adjList.insert(graphGenerator::p2[i], graphGenerator::p1[i]);
        }
    }
    graphGenerator::vprev = V;
    return adjList;
}

double graphGenerator::getNormalNumber(double end) {
    double sum = 0;
    for (int x = 0; x < 3; x++){
        sum += graphGenerator::getRandomNumber(0, 1);
    }
    return sum / 3 * end;
}




