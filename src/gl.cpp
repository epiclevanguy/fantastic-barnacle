#include "gl.h"
#include "graph.h"
#include <omp.h>
#include <iostream>

GL::GL(int N, int Q) : N(N), Q(Q)
{
    AddTable.resize(Q, std::vector<int> (Q));
    SubTable.resize(Q, std::vector<int> (Q));
    MultTable.resize(Q, std::vector<int> (Q));
    DivTable.resize(Q, std::vector<int> (Q));

    AddReverse.resize(Q);
    MultReverse.resize(Q);

    for (int i = 0; i < Q; ++i)
    {
        for (int j = 0; j < Q; ++j)
        {
            AddTable[i][j] = (i + j) % Q;
            SubTable[i][j] = i - j;
            if (SubTable[i][j] < 0)
            {
                SubTable[i][j] += Q;
            }
            MultTable[i][j] = (i * j) % Q;
        }
    }
    AddReverse[0] = 0;
    MultReverse[0] = 0;
    for (int i = 1; i < Q; ++i)
    {
        for (int j = 1; j < Q; ++j)
        {
            if (AddTable[i][j] == 0)
            {
                AddReverse[i] = j;
                break;
            }
        }
        for (int j = 1; j < Q; ++j)
        {
            if (MultTable[i][j] == 1)
            {
                MultReverse[i] = j;
                break;
            }
        }
    }
    std::vector<int> tmp(N * N);
    GetGroup(tmp, 0);
}

void GL::GetGroup(std::vector<int> &CurrM, int n)
{
    if (n == N * N)
    {
        if (GetDet(CurrM) != 0)
        {
            //#pragma omp critical (GetGroup_push_back)
            {
                Group.push_back(CurrM);
            }
        }
        return;
    }
    //#pragma omp parallel for
    for (int i = 0; i < Q; ++i)
    {
        CurrM[n] = i;
        GetGroup(CurrM, n + 1);
    }
}


int GL::GetDet(std::vector<int> M)
{
    int res = 1;
    for (int i = 0; i < N; ++i)
    {
        int k = i;
        for (int j = i ; j < N; ++j)
        {
            if (M[j * N + i] > 0)
            {
                k = j;
                break;
            }
        }
        if (M[k * N + i] == 0)
        {
            return 0;
        }
        if (k != i)
        {
            res = Q - res;
            for (int j = i; j < N; ++j)
            {
                std::swap(M[i * N + j], M[k * N + j]);
            }
        }
        res = MultTable[res][M[i * N + i]];
        for (int j = i + 1; j < N; ++j)
        {
            if (M[j * N + i] > 0)
            {
                for (int k = N - 1; k >= i; --k)
                {
                    M[j * N + k] = SubTable[M[j * N + k]][MultTable[M[i * N + k]][MultTable[MultReverse[M[i * N + i]]][M[j * N + i]]]];
                }
            }
        }
    }
    return res;
}

void GL::GetConjugateClass(std::vector<int> &M, std::vector<std::vector<int> > &Res)
{
    std::vector<int> tmp1(N*N), tmp2(N*N), tmp3(N*N);
    for (int i = 0; i < Group.size(); ++i)
    {
        MultiplyM(Group[i], M, tmp1);
        GetInvM(Group[i],tmp2);
        MultiplyM(tmp1, tmp2, tmp3);
        bool flag = true;
        for (int j = 0; j < Res.size(); ++j)
        {
            if (IsEq(Res[j], tmp3))
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            if(GetDet(tmp3) > 0)
            {
                Res.push_back(tmp3);
            }
        }
    }
}

void GL::MultiplyM(std::vector<int> &M1, std::vector<int> &M2, std::vector<int> &Res)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Res[i * N + j] = 0;
            for (int k = 0; k < N; ++k)
            {
                Res[i * N + j] = AddTable[Res[i * N + j]][MultTable[M1[i * N + k]][M2[j + k * N]]];
            }
        }
    }
}

bool GL::IsEq(std::vector<int> &M1, std::vector<int> &M2)
{
    if (M1.size() != M2.size())
    {
        return false;
    }
    for (int i = 0; i < M1.size(); ++i)
    {
        if (M1[i] != M2[i])
        {
            return false;
        }
    }
    return true;
}

void GL::GetInvM(std::vector<int> M, std::vector<int> &Res)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                Res[i * N + j] = 1;
            }
            else
            {
                Res[i * N + j] = 0;
            }
        }
    }
    for(int i = 0 ; i < N ; ++i)
    {
        int k = i, rev;
        for(int j = k ; j < N ; ++j)
        {
            if(M[j * N + i] > 0)
            {
                k = j;
                break;
            }
        }
        if (k != i)
        {
            for(int j = 0; j < N; ++j)
            {
                std::swap(M[i * N + j], M[k * N + j]);
                std::swap(Res[i * N + j], Res[k * N + j]);
            }
        }
        rev = MultReverse[M[i * N + i]];
        for(int j = 0; j < N; ++j)
        {
            M[i * N + j] = MultTable[M[i * N + j]][rev];
            Res[i * N + j] = MultTable[Res[i * N + j]][rev];
        }
        for(int j = 0; j < N; ++j)
        {
            if(j != i)
            {
                rev = M[j * N + i];
                for(int t = 0; t < N; ++t)
                {
                    M[j * N + t] = SubTable[M[j * N + t]][MultTable[M[i * N + t]][rev]];
                    Res[j * N + t] = SubTable[Res[j * N + t]][MultTable[Res[i * N + t]][rev]];
                }
            }
        }
    }
}


void GL::PrintGroupInfo()
{
    std::vector<int> tmp1(N * N), tmp2(N * N);
    Graph G;
    G.SetSize(Group.size());
    //#pragma omp parallel for
    for (int i = 0; i < Group.size(); ++i)
    {
        for (int j = i + 1; j < Group.size(); ++j)
        {
            MultiplyM(Group[i], Group[j], tmp1);
            MultiplyM(Group[j], Group[i], tmp2);
            if (IsEq(tmp1, tmp2))
            {
                //#pragma omp critical (GPrintGroupInfo_CE_add_edge)
                {
                    G.AddEdge(i,j);
                }
            }
        }
    }
    G.Calculate();
    G.Print();
}

void GL::PrintGroupInfo(std::vector<int> &CE)
{
    std::vector<int> tmp1(N * N), tmp2(N * N);
    Graph G;
    std::vector<std::vector<int> > MS;
    GetConjugateClass(CE, MS);
    G.SetSize(MS.size());
    //#pragma omp parallel for
    for (int i = 0; i < MS.size(); ++i)
    {
        for (int j = i + 1; j < MS.size(); ++j)
        {
            MultiplyM(MS[i], MS[j], tmp1);
            MultiplyM(MS[j], MS[i], tmp2);
            if (IsEq(tmp1, tmp2))
            {
                //#pragma omp critical (GPrintGroupInfo_CE_add_edge)
                {
                    G.AddEdge(i,j);
                }
            }
        }
    }
    G.Calculate();
    std::cout << "X" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << CE[i * N + j] << "  ";
        }
        std::cout << std::endl;
    }
    G.Print();
}





/*



void CGroup::CalculateE()
{
    std::vector<std::vector<int>> MSTMP;
    std::vector<int> ETMP(N * N), tmp1(N * N), tmp2(N * N);
    if(Type == "GL")
    {
        GetGLCClass(X, MSTMP);

    }
    if(Type == "U")
    {
        GetGUCClass(X, MSTMP);
    }
    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = 0 ; j < N ; ++j)
        {
            if(i == j)
            {
                ETMP[i * N + j] = DTable[0][1];
            }
            else
            {
                ETMP[i * N + j] = 0;
            }
        }
    }

    for(int i = 0 ; i < MSTMP.size() ; ++i)
    {
        bool flag = true;
        for(int j = 0 ; j < i ; ++j)
        {
            GetMultM(ETMP, MSTMP[i], tmp1);
            if(IsEq(MSTMP[j],tmp1))
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            MS.push_back(MSTMP[i]);
        }
    }

    G.SetSize(MS.size());
    for (int i = 0; i < MS.size(); ++i)
    {
        for (int j = i + 1; j < MS.size(); ++j)
        {
            GetMultM(MS[i], MS[j], tmp1);
            GetMultM(MS[j], MS[i], tmp2);
            if (IsEq(tmp1, tmp2))
            {
                G.AddEdge(i,j);
            }
        }
    }
    G.Calculate();
}









void CGroup::SetE(std::vector<int> &E)
{
    E.resize(N * N);
    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = 0 ; j < N ; ++j)
        {
            if(i == j)
            {
                E[i * N + j] = 1;
            }
            else
            {
                E[i * N + j] = 0;
            }
        }
    }
}

*/


