#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <algorithm>

template<typename T, int N>
class Matrix
{
public:
    Matrix()
    {
        A1 = arr1;
        A2 = arr2;
    }
    Matrix(const Matrix &M)
    {
        A1 = arr1;
        A2 = arr2;
        for(int i = 0 ; i < N * N ; ++i)
        {
            A1[i] = M.A1[i];
        }
    }
    Matrix& operator+=(const Matrix& Right)
    {
        return (*this);
    }
    Matrix& operator-=(const Matrix& Right)
    {
        return (*this);
    }
    Matrix& operator*=(const Matrix& Right)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                A2[i * N + j] = 0;
                for (int k = 0; k < N; ++k)
                {
                    A2[i * N + j] += A1[i * N + k] * Right.A1[j + k * N];
                }
            }
        }
        std::swap(A1,A2);
        return (*this);
    }
    Matrix& operator/=(const Matrix& Right)
    {
        return (*this);
    }

    friend bool operator==(const Matrix& Left, const Matrix& Right)
    {
        for (int i = 0; i < N * N; ++i)
        {
            if (Left.A1[i] != Right.A1[i])
            {
                return false;
            }
        }
        return true;
    }

    T& operator [](const int i)
    {
        return A1[i];
    }

    T GetDet()
    {
        for(int i = 0 ; i < N * N ; ++i)
        {
            A2[i] = A1[i];
        }
        T Res = 1;
        for (int i = 0; i < N; ++i)
        {
            int k = i;
            for (int j = i ; j < N; ++j)
            {
                if (A2[j * N + i] != 0)
                {
                    k = j;
                    break;
                }
            }
            if (A2[k * N + i] == 0)
            {
                return 0;
            }
            if (k != i)
            {
                Res = -Res;
                for (int j = i; j < N; ++j)
                {
                    std::swap(A2[i * N + j], A2[k * N + j]);
                }
            }
            Res *= A2[i * N + i];
            for (int j = i + 1; j < N; ++j)
            {
                if (A2[j * N + i] != 0)
                {
                    for (int k = N - 1; k >= i; --k)
                    {
                        A2[j * N + k] -= (A2[i * N + k] / A2[i * N + i]) * A2[j * N + i];
                    }
                }
            }
        }
        return Res;
    }

    Matrix GetInverseMatrix()
    {
        for(int i = 0 ; i < N * N ; ++i)
        {
            A2[i] = A1[i];
        }
        Matrix Res;
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
            int k = i;
            T rev;
            for(int j = k ; j < N ; ++j)
            {
                if(A2[j * N + i] > 0)
                {
                    k = j;
                    break;
                }
            }
            if (k != i)
            {
                for(int j = 0; j < N; ++j)
                {
                    std::swap(A2[i * N + j], A2[k * N + j]);
                    std::swap(Res[i * N + j], Res[k * N + j]);
                }
            }
            rev = T(1) / A2[i * N + i];
            for(int j = 0; j < N; ++j)
            {
                A2[i * N + j] *= rev;
                Res[i * N + j] *= rev;
            }
            for(int j = 0; j < N; ++j)
            {
                if(j != i)
                {
                    rev = A2[j * N + i];
                    for(int t = 0; t < N; ++t)
                    {
                        A2[j * N + t] -= A2[i * N + t] * rev;
                        Res[j * N + t] -= Res[i * N + t] * rev;
                    }
                }
            }
        }
        return Res;
    }

private:
    T arr1[N * N], arr2[N * N], *A1, *A2;
    friend std::ostream & operator<< (std::ostream & Output, const Matrix<T, N> & A)
    {
        Output << "(";
        for(int i = 0 ; i < N * N ; ++i)
        {
            if(i > 0)
            {
                if(i % N == 0)
                {
                    Output << " ; ";
                }
                else
                {
                    Output << " ";
                }
            }
            Output << A.A1[i];
        }
        Output << ")";
        return Output;
    }

};



template<typename T, int N>
bool operator != (const Matrix<T,N>& Left, const Matrix<T,N>& Right)
{
    return !(Left == Right);
}

template<typename T, int N>
const Matrix<T,N> operator* (const Matrix<T,N>& Left, const Matrix<T,N>& Right)
{
    return Matrix<T,N> (Left) *= Right;
}




#endif // MATRIX_H
