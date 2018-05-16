#ifndef GU_H
#define GU_H

#include <iostream>

#include <ostream>
#include <vector>
#include "specificalgorithms.h"
#include "ffield.h"
#include "matrix.h"

template<int N, int Q>
class GU
{
public:

    GU()
    {
        if(NeedInit)
        {
            NeedInit = false;
            Init();
        }
    }

    const Matrix<CField<Q>, N> & operator [](const size_t i)
    {
        return Group[i];
    }


    size_t Size()
    {
        return Group.size();
    }

private:
    static bool NeedInit;
    static std::vector<Matrix<CField<Q>, N>> Group;

    void Init()
    {
        std::vector<std::vector<CField<Q>>> strings;
        std::vector<CField<Q>> tmp1 (N);
        size_t tmp2[N];
        GetGUStrings(tmp1, 0, strings);
        std::cout << strings.size() << std::endl;
        for(size_t i = 0 ; i < strings.size() ; ++i)
        {
            for(int j = 0 ; j < strings[i].size() ; ++j)
            {
                std::cout << strings[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::vector<std::vector<size_t>> gstrings(strings.size());
        for (size_t i = 0; i < strings.size(); ++i)
        {
            for (size_t j = 0; j < strings.size(); ++j)
            {
                CField<Q> R = 0;
                for (int k = 0; k < N; ++k)
                {
                    R += strings[i][k] * strings[j][k].GetConjugate();
                }
                if (R == 0)
                {
                    gstrings[i].push_back(j);
                }
            }
        }
        for (size_t i = 0; i < gstrings.size(); ++i)
        {
            for (size_t j = 0; j < gstrings[i].size(); ++j)
            {
                std::cout << gstrings[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        for (size_t i = 0; i < gstrings.size(); ++i)
        {
            tmp2[0] = i;
            GetGUDM(tmp2, gstrings, strings, 1);
        }
    }

    void GetGUStrings(std::vector<CField<Q>> &CurStr, int n, std::vector<std::vector<CField<Q>>> &Strings)
    {
        if (n == N)
        {
            CField<Q> R = 0;
            for (int i = 0; i < N; ++i)
            {
                R += CurStr[i] * CurStr[i].GetConjugate();
            }
            if (R == 1)
            {
                Strings.push_back(CurStr);
            }
            return;
        }
        for (int i = 0; i < Q * Q; ++i)
        {
            CurStr[n] = i;
            GetGUStrings(CurStr, n + 1, Strings);
        }
    }


    void GetGUDM(size_t CurM[N], std::vector<std::vector<size_t> > &Gstrings, std::vector<std::vector<CField<Q>> > &strings, int n)
    {
        if (n == N)
        {
            Matrix<CField<Q>, N> tmp;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    tmp[i * N + j] = strings[CurM[i]][j];
                }
            }
            Group.push_back(tmp);
            return;
        }
        for (size_t i = 0; i < Gstrings[CurM[n - 1]].size(); ++i)
        {
            bool flag = true;
            for (int j = 0; j < n - 1; ++j)
            {
                if (BinarySearch(Gstrings[Gstrings[CurM[n - 1]][i]], CurM[j]) < 0)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                CurM[n] = Gstrings[CurM[n - 1]][i];
                GetGUDM(CurM, Gstrings, strings, n + 1);
            }
        }
    }




    /*


    void GetGroup(std::vector<int> &CurrM, int n, std::vector<std::vector<int> > &Res);

    void GetGUCClass(std::vector<int> &M, std::vector<std::vector<int>> & Res);
    bool IsEq(std::vector<int> &M1, std::vector<int> &M2);
    void SetE(std::vector<int> &E);

    void InitU();*/
};

template<int N, int Q>
bool GU<N, Q>::NeedInit = true;
template<int N, int Q>
std::vector<Matrix<CField<Q>, N>> GU<N, Q>::Group;

#endif // GU_H

