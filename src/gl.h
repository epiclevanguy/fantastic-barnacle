#ifndef GL_H
#define GL_H


#include <ostream>
#include <vector>
#include "ffield.h"
#include "matrix.h"



template<int N, int Q>
class GL
{
public:
    GL()
    {
        if(NeedInit)
        {
            NeedInit = false;
            Matrix<RField<Q>, N> CurrM;
            Init(CurrM, 0);
        }
    }

    const Matrix<RField<Q>, N> & operator [](const size_t i)
    {
        return Group[i];
    }

    size_t Size()
    {
        return Group.size();
    }

private:
    static bool NeedInit;
    static std::vector<Matrix<RField<Q>, N>> Group;    
    void Init(Matrix<RField<Q>, N> &CurrM, int n)
    {
        if (n == N * N)
        {
            if (CurrM.GetDet() != 0)
            {
                Group.push_back(CurrM);
            }
            return;
        }
        for (int i = 0; i < Q; ++i)
        {
            CurrM[n] = i;
            Init(CurrM, n + 1);
        }
    }

    friend std::ostream & operator<< (std::ostream & Output, const GL<N, Q> &G)
    {
        Output << Group.size() << std::endl;
        for(size_t i = 0 ; i < G.Group.size() ; ++i)
        {
            Output << G.Group[i] << std::endl;
        }
        return Output;
    }

};

template<int N, int Q>
bool GL<N, Q>::NeedInit = true;
template<int N, int Q>
std::vector<Matrix<RField<Q>, N>> GL<N, Q>::Group;

#endif // GL_H
