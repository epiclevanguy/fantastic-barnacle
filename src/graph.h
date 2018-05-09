#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>

class Graph
{
public:
    Graph();
    void SetSize(int N);
    void AddEdge(int i, int j);
    void Calculate();
    void Print();




private:
    std::vector<std::vector<int>> MATRIX_V, DISTANCES, AVTMS;
    std::set<int> DEGREES, LYAMBDA, MU;
    std::vector<int> Clique, CoClique;
    std::vector<std::set<int>> BI, CI;
    long long DIAMETER;

    void GetDistances(std::vector<std::vector<int>> &M, std::vector<std::vector<int>> & Res);
    long long GetDiameter(std::vector<std::vector<int>> & M);

    void PrintAVTCount();

    void GenerateMaxClique(std::vector<std::vector<int>> &G, std::vector<int> &candidates, std::vector<int> &not_c, std::vector<int> &compsub, std::vector<int> &res);




};

#endif // GRAPH_H
