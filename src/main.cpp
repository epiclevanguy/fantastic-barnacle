#include <iostream>
#include "group.h"
#include "gl.h"

int main()
{
    Group<Matrix<RField<3>,3>> G, CG, C1;
    {
        Group<Matrix<RField<3>,2>> A;
        GL<2,3> B;
        for(size_t i = 0 ; i < B.Size() ; ++i)
        {
            A.AddElement(B[i]);
        }
        Matrix<RField<3>,3> T;
        for(int i = 0 ; i < A.Size() ; ++i)
        {
            for(int j = 0 ; j < 2 ; ++j)
            {
                T[0] = A[i][0];
                T[1] = A[i][1];
                T[2] = 0;
                T[3] = A[i][2];
                T[4] = A[i][3];
                T[5] = 0;
                T[6] = 0;
                T[7] = 0;
                T[8] = j + 1;
                G.AddElement(T);
            }
        }
    }
    {
        GL<3,3> A;
        Group<Matrix<RField<3>,3>> tmp;
        Matrix<RField<3>,3> CE;
        CE[0] = 1;
        CE[1] = 0;
        CE[2] = 0;
        CE[3] = 0;
        CE[4] = 1;
        CE[5] = 0;
        CE[6] = 0;
        CE[7] = 0;
        CE[8] = 2;
        for(size_t i = 0 ; i < A.Size() ; ++i)
        {
            tmp.AddElement(A[i]);
        }
        CG = tmp.GetConjugateClass(CE);
    }
    std::cout << G << std::endl;
    std::cout << CG << std::endl;


    for(size_t i = 0 ; i < G.Size() ; ++i)
    {
        if(CG.Exist(G[i]))
        {
            C1.AddElement(G[i]);
        }
    }
    std::cout << C1 << std::endl;
    /*{
        GL<3,3> A;
        for(size_t i = 0 ; i < A.Size() ; ++i)
        {
            G.AddElement(A[i]);
        }
    }
    Matrix<RField<3>,3> T;
    T[0] = 1;
    T[1] = 0;
    T[2] = 0;
    T[3] = 0;
    T[4] = 1;
    T[5] = 0;
    T[6] = 0;
    T[7] = 0;
    T[8] = 2;
    std::cout << G.GetConjugateClass(T) << std::endl;*/
    return 0;
}
