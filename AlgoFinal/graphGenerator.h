//
// Created by Dylan Furner on 12/5/21.
//

#ifndef ALGOFINAL_GRAPHGENERATOR_H
#define ALGOFINAL_GRAPHGENERATOR_H
#include <iostream>
#include <unordered_map>
#include "LinkedList.h"
#include <iostream>
#include <set>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include "adjacencyList.h"
using namespace std;
struct added {
    int x;
    int y;
    bool operator==(added const &rhs) const{
        return (x == rhs.x && y == rhs.y) || (y == rhs.x && x == rhs.y);
    }
};
typedef pair<int, int> pairs;
class graphGenerator {
private:
    int size = 500;
//    int size = 7;
    static std::random_device m_rd;
    static std::mt19937  m_rng;
    static vector<int> p1;
    static vector<int> p2;
    static set<pairs> set;
    static int vprev;
    static vector<added> p3;
    int sizeFactor = 1;
    const string CompleteGraph = "CompleteGraph/CompleteGraph";
    const string CyclicGraph = "CyclicGraph/CyclicGraph";
    const string UniformDistributionSkew = "Skew/UniformDistributionSkew";
    const string UniformDistribution = "UniformDistributionR/UniformDistributionR";
    const string ModifiedNormal = "ModifiedNormal/ModifiedNormal";
public:
    graphGenerator();
    ~graphGenerator();
    static double getRandomNumber(double start, double end);
    static double getNormalNumber(double end);
    void runGraphCreationAndTimings(int valuesOfE[], int arr1[], default_random_engine generator);
    static AdjacencyList<int> randomlyDistributedPairs(int V, int E, std::default_random_engine generator);
    static AdjacencyList<int> completeGraph(int V);
    static AdjacencyList<int> cycle(int V);
    static AdjacencyList<int> skew(int V, int E, std::default_random_engine generator);
    static AdjacencyList<int> modifiedNormal(int V, int E, std::default_random_engine generator);
    void saveGeneratedEdgeValuesToFile(int e[], int size, bool randomized);
    void TimesToCSV(int** times, int sizes[], int size);
    void TimesToCSV(float** times, int sizes[], int size);
    int* runTimings(int arrV[], int arrE[], int size, AdjacencyList<int>(*func)(int, int, std::default_random_engine), std::default_random_engine generator, bool random, bool normal = false);
    int* runTimings(int arr[], int size, AdjacencyList<int>(*func)(int), bool zq);
    void printToFile(int sizeOfZ, AdjacencyList<int> z, int step, string nameOfFile);
    AdjacencyList<int> readFileGenerateGraph(string fileName, int size);
    int getSize();
    int getSizeFactor();
    AdjacencyList<int> requestSameGraph();
    };


#endif //ALGOFINAL_GRAPHGENERATOR_H
