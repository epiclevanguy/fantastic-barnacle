#include <iostream>
#include "group.h"
#include "gu.h"

int main()
{

    /*
    {
        Group<Matrix<RField<3>,2>> G;
        GL<2,3> A;
        Matrix<RField<3>,2> CE;
        CE[0] = 1;
        CE[1] = 0;
        CE[2] = 0;
        CE[3] = 2;
        for(size_t i = 0 ; i < A.Size() ; ++i)
        {
            G.AddElement(A[i]);
        }
        G.PrintGroupInfo();
    }
    {
        Group<Matrix<RField<5>,2>> G;
        GL<2,5> A;
        Matrix<RField<5>,2> CE;
        CE[0] = 1;
        CE[1] = 0;
        CE[2] = 0;
        CE[3] = 4;
        for(size_t i = 0 ; i < A.Size() ; ++i)
        {
            G.AddElement(A[i]);
        }
        G.PrintGroupInfo();
    }*/
    /*{
        Group<Matrix<CField<3>,3>> G;
        GU<3,3> A;
        Matrix<CField<3>,3> CE;
        CE[0] = 2;
        CE[1] = 0;
        CE[2] = 0;
        CE[3] = 0;
        CE[4] = 1;
        CE[5] = 0;
        CE[6] = 0;
        CE[7] = 0;
        CE[8] = 1;
        for(size_t i = 0 ; i < A.Size() ; ++i)
        {
            G.AddElement(A[i]);
        }
        G.GetConjugateClass(CE).PrintGroupInfo();
    }
    */

    {
            Group<Matrix<CField<3>,3>> G;
            GU<3,3> A;
            Matrix<CField<3>,3> CE;
            CE[0] = 2;
            CE[1] = 0;
            CE[2] = 0;
            CE[3] = 0;
            CE[4] = 1;
            CE[5] = 0;
            CE[6] = 0;
            CE[7] = 0;
            CE[8] = 1;
            for(size_t i = 0 ; i < A.Size() ; ++i)
            {
                G.AddElement(A[i]);
            }
            G.GetConjugateClass(CE).PrintGroupInfo();
        }

    /*
    Matrix<RField<3>,3> A, B, C;
    A[0] = 1;
    A[1] = 0;
    A[2] = 0;
    A[3] = 0;
    A[4] = 1;
    A[5] = 0;
    A[6] = 0;
    A[7] = 0;
    A[8] = 2;

    B[0] = 2;
    B[1] = 0;
    B[2] = 0;
    B[3] = 0;
    B[4] = 1;
    B[5] = 0;
    B[6] = 0;
    B[7] = 0;
    B[8] = 1;

    C[0] = 1;
    C[1] = 0;
    C[2] = 0;
    C[3] = 0;
    C[4] = 2;
    C[5] = 0;
    C[6] = 0;
    C[7] = 0;
    C[8] = 1;

    std::cout << A * C << std::endl << C * A << std::endl << std::endl;
    std::cout << B * C << std::endl << C * B << std::endl << std::endl;

    /*
    Group<Matrix<RField<3>,3>> G1, G2, CG, C1, C2, C3;
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
                G1.AddElement(T);
            }
        }
        for(int i = 0 ; i < A.Size() ; ++i)
        {
            for(int j = 0 ; j < 2 ; ++j)
            {
                T[0] = j + 1;
                T[1] = 0;
                T[2] = 0;
                T[3] = 0;
                T[4] = A[i][0];
                T[5] = A[i][1];
                T[6] = 0;
                T[7] = A[i][2];
                T[8] = A[i][3];
                G2.AddElement(T);
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
    std::cout << G1 << std::endl;
    std::cout << G1 << std::endl;
    std::cout << CG << std::endl;


    for(size_t i = 0 ; i < G1.Size() ; ++i)
    {
        if(CG.Exist(G1[i]))
        {
            C1.AddElement(G1[i]);
        }
    }
    for(size_t i = 0 ; i < G2.Size() ; ++i)
    {
        if(CG.Exist(G2[i]))
        {
            C2.AddElement(G2[i]);
        }
    }
    for(size_t i = 0 ; i < C1.Size() ; ++i)
    {
        if(C2.Exist(C1[i]))
        {
            C3.AddElement(C1[i]);
        }
    }
    std::cout << C1 << std::endl;
    std::cout << C2 << std::endl;
    std::cout << C3 << std::endl;

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
