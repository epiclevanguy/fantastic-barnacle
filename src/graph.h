#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <set>

class Graph
{
public:
    Graph();
    void Clear();
    void SetSize(int N);
    void AddEdge(int i, int j);
    void PrintGraphInfo();




private:
    std::vector<std::vector<int>> MATRIX_V, DISTANCES;
    std::set<int> DEGREES, LYAMBDA, MU;
    std::vector<int> Clique, CoClique;
    std::vector<std::set<int>> AI, BI, CI;
    long long DIAMETER;

    void GetDistances(std::vector<std::vector<int>> &M, std::vector<std::vector<int>> & Res);
    long long GetDiameter(std::vector<std::vector<int>> & M);

    void PrintAVTCount();
    void Calculate();
    void Print();


};

#endif // GRAPH_H
