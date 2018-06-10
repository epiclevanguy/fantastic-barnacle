#include "graph.h"
#include "mcqd.h"
#include <iostream>
#include <queue>


Graph::Graph()
{
}

void Graph::Clear()
{
    for(size_t i = 0 ; i < MATRIX_V.size() ; ++i)
    {
        for(size_t j = 0 ; j < MATRIX_V.size() ; ++j)
        {
            MATRIX_V[i][j] = 0;
        }
    }
}

void Graph::SetSize(int N)
{
    MATRIX_V.resize(N, std::vector<int> (N,0));
    DISTANCES.resize(N, std::vector<int>(N, 0));
}

void Graph::AddEdge(int i, int j)
{
    MATRIX_V[i][j] = MATRIX_V[j][i] = 1;
}

void Graph::PrintGraphInfo()
{
    Calculate();
    std::cout << "Г1" << std::endl;
    Print();
    Graph G;
    G.SetSize(MATRIX_V.size());
    for(long long i = 2 ; i <= DIAMETER ; ++i)
    {
        G.Clear();
        for(size_t j = 0 ; j < MATRIX_V.size() ; ++j)
        {
            for(size_t k = j + 1 ; k < MATRIX_V.size() ; ++k)
            {
                if(DISTANCES[j][k] == i)
                {
                    G.AddEdge(j, k);
                }
            }
        }
        G.Calculate();
        std::cout << "Г" << i << std::endl;
        G.Print();
    }
}

void Graph::Calculate()
{
    DEGREES.clear();
    LYAMBDA.clear();
    MU.clear();
    Clique.clear();
    CoClique.clear();
    AI.clear();
    BI.clear();
    CI.clear();
    for (size_t i = 0; i < MATRIX_V.size(); ++i)
    {
        int tmp = 0;
        for (size_t j = 0; j < MATRIX_V[i].size(); ++j)
        {
            tmp += MATRIX_V[i][j];
        }
        DEGREES.insert(tmp);
    }
    for (size_t i = 0; i < MATRIX_V.size(); ++i)
    {
        for (size_t j = i + 1; j < MATRIX_V[i].size(); ++j)
        {
            int tmp = 0;
            for (size_t k = 0; k < MATRIX_V.size(); ++k)
            {
                if (MATRIX_V[i][k] == MATRIX_V[j][k])
                {
                    tmp = tmp + MATRIX_V[i][k];
                }
            }
            if (MATRIX_V[i][j] == 1)
            {
                LYAMBDA.insert(tmp);
            }
            else
            {
                MU.insert(tmp);
            }
        }
    }


    DIAMETER = GetDiameter(MATRIX_V);
    GetDistances(MATRIX_V, DISTANCES);

    for (int i = 1; i < DIAMETER + 1; ++i)
    {
        std::set<int> DA, DB, DC;
        for (size_t a = 0; a < MATRIX_V.size(); ++a)
        {
            for (size_t b = 0; b < MATRIX_V.size(); ++b)
            {
                if (DISTANCES[a][b] == i)
                {
                    std::set<int> tmpA, tmpB, tmpC;
                    for (int t = 0; t < MATRIX_V.size(); ++t)
                    {
                        if (DISTANCES[b][t] == 1 && DISTANCES[a][t] == i)
                        {
                            tmpA.insert(t);
                        }
                        if (DISTANCES[b][t] == 1 && DISTANCES[a][t] == (i + 1))
                        {
                            tmpB.insert(t);
                        }
                        if (DISTANCES[b][t] == 1 && DISTANCES[a][t] == (i - 1))
                        {
                            tmpC.insert(t);
                        }
                    }
                    DA.insert(tmpA.size());
                    DB.insert(tmpB.size());
                    DC.insert(tmpC.size());
                }
            }
        }
        AI.push_back(DA);
        BI.push_back(DB);
        CI.push_back(DC);
    }

    bool **conn = new bool *[MATRIX_V.size()];
    for(int i = 0 ; i < MATRIX_V.size() ; ++i)
    {
        conn[i] = new bool[MATRIX_V.size()];
        for(int j = 0 ; j < MATRIX_V.size() ; ++j)
        {
            conn[i][j] = MATRIX_V[i][j];
        }
    }


    Maxclique md1(conn, MATRIX_V.size(), 0.025);
    int *qmax, qaize;
    md1.mcqdyn(qmax, qaize);
    for(int i = 0 ; i < qaize ; ++i)
    {
        Clique.push_back(qmax[i]);
    }
    delete [] qmax;

    for(int i = 0 ; i < MATRIX_V.size() ; ++i)
    {
        for(int j = 0 ; j < MATRIX_V.size() ; ++j)
        {
            conn[i][j] = !(MATRIX_V[i][j]);
        }
    }

    Maxclique md2(conn, MATRIX_V.size(), 0.025);
    md2.mcqdyn(qmax, qaize);
    for(int i = 0 ; i < qaize ; ++i)
    {
        CoClique.push_back(qmax[i]);
    }
    delete [] qmax;
    for(size_t i = 0 ; i < MATRIX_V.size() ; ++i)
    {
        delete [] conn[i];
    }
    delete [] conn;
}

void Graph::Print()
{
    std::cout << "Vertex number" << std::endl;
    std::cout << MATRIX_V.size() << std::endl;
    std::cout << "Degrees" << std::endl;
    for (std::set<int>::const_iterator it = DEGREES.begin(); it != DEGREES.end(); ++it)
    {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
    std::cout << "Lyambda" << std::endl;
    for (std::set<int>::const_iterator it = LYAMBDA.begin(); it != LYAMBDA.end(); ++it)
    {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
    std::cout << "Mu" << std::endl;
    for (std::set<int>::const_iterator it = MU.begin(); it != MU.end(); ++it)
    {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
    std::cout << "Diameter" << std::endl << DIAMETER << std::endl;
    std::cout << "Ai" << std::endl;
    for (int i = 0; i < AI.size(); ++i)
    {
        std::cout << "[ ";
        for (std::set<int>::const_iterator it1 = AI[i].begin(); it1 != AI[i].end(); ++it1)
        {
            std::cout << *it1 << "   ";
        }
        std::cout << " ]   ";
    }
    std::cout << std::endl;
    std::cout << "Bi" << std::endl;
    for (int i = 0; i < BI.size(); ++i)
    {
        std::cout << "[ ";
        for (std::set<int>::const_iterator it1 = BI[i].begin(); it1 != BI[i].end(); ++it1)
        {
            std::cout << *it1 << "   ";
        }
        std::cout << " ]   ";
    }
    std::cout << std::endl;
    std::cout << "Ci" << std::endl;
    for (int i = 0; i < CI.size(); ++i)
    {
        std::cout << "[ ";
        for (std::set<int>::const_iterator it1 = CI[i].begin(); it1 != CI[i].end(); ++it1)
        {
            std::cout << *it1 << "   ";
        }
        std::cout << " ]   ";
    }
    std::cout << std::endl;
    PrintAVTCount();
    std::cout << "Max clique size " << Clique.size() << std::endl;
    for(auto i : Clique)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    std::cout << "Max coclique size " << CoClique.size() << std::endl;
    for(auto i : CoClique)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

void Graph::GetDistances(std::vector<std::vector<int> > &M, std::vector<std::vector<int> > &Res)
{
    for (size_t start = 0; start < M.size(); ++start)
    {
        std::queue<int> q;
        q.push(start);
        std::vector<bool> used(M.size(), false);
        used[start] = true;
        std::vector<int> d(M.size(), 0);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (size_t i = 0; i < M[v].size(); ++i)
            {
                if (M[v][i] > 0 && !used[i])
                {
                    used[i] = true;
                    q.push(i);
                    d[i] = d[v] + 1;
                }
            }
        }
        for (size_t i = 0; i < d.size(); ++i)
        {
            Res[start][i] = d[i];
        }
    }
}

long long Graph::GetDiameter(std::vector<std::vector<int> > &M)
{
    std::queue<long long> q;
    q.push(0);
    std::vector<bool> used(M.size(), false);
    std::vector<long long> d(M.size(), 0);
    used[0] = true;
    long long res = 0;
    while (!q.empty())
    {
        long long v = q.front();
        q.pop();
        for (size_t i = 0; i < M[v].size(); ++i)
        {
            if (M[v][i] > 0 && !used[i])
            {
                used[i] = true;
                q.push(i);
                d[i] = d[v] + 1;
            }
        }
    }
    for (size_t i = 0; i < used.size(); ++i)
    {
        if (!used[i])
        {
            return -1;
        }
    }
    for (size_t i = 0; i < d.size(); ++i)
    {
        if (res < d[i])
        {
            res = d[i];
        }
    }
    return res;
}
