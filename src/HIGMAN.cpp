#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>
#include <vector>
#include <string>
#include <iostream>


boost::multiprecision::cpp_int SQRT(boost::multiprecision::cpp_int n);

int main()
{
    try
    {
        size_t N = 3;
        boost::multiprecision::cpp_int n, a, c, d, P1, P2, F1, F2;
        std::vector<boost::rational<boost::multiprecision::cpp_int>> P(9), Q(9), tmp(9);
        std::cout << "Input vertex number, degrees, lyambda, mu." << std::endl;
        std::cin >> n >> a >> c >> d;
        P1 = c - d + SQRT((c - d) * (c - d) + boost::multiprecision::cpp_int (4) * (a - d));
        if(P1 % 2 != 0)
        {
            throw std::string("Bad input!");
        }
        P1 /= boost::multiprecision::cpp_int (2);
        P2 = c - d - SQRT((c - d) * (c - d) + boost::multiprecision::cpp_int (4) * (a - d));
        if(P2 % 2 != 0)
        {
            throw std::string("Bad input!");
        }
        P2 /= boost::multiprecision::cpp_int (2);
        F1 = ((n - boost::multiprecision::cpp_int (1)) * (d - c) - boost::multiprecision::cpp_int (2) * a);
        if(F1 % SQRT((d - c) * (d - c) + boost::multiprecision::cpp_int (4) * (a - d)) != 0)
        {
            std::string("Bad input!");
        }
        F1 /= SQRT((d - c) * (d - c) + boost::multiprecision::cpp_int (4) * (a - d));
        F1 += n - 1;
        if(F1 % 2 != 0)
        {
            std::string("Bad input!");
        }
        F1 /= 2;
        F2 = -((n - boost::multiprecision::cpp_int (1)) * (d - c) - boost::multiprecision::cpp_int (2) * a);
        if(F2 % SQRT((d - c) * (d - c) + boost::multiprecision::cpp_int (4) * (a - d)) != 0)
        {
            std::string("Bad input!");
        }
        F2 /= SQRT((d - c) * (d - c) + boost::multiprecision::cpp_int (4) * (a - d));
        F2 += n - 1;
        if(F2 % 2 != 0)
        {
            std::string("Bad input!");
        }
        F2 /= 2;
        P[0] = boost::multiprecision::cpp_int (1);
        P[1] = boost::multiprecision::cpp_int (1);
        P[2] = boost::multiprecision::cpp_int (1);
        P[3] = a;
        P[4] = P1;
        P[5] = P2;
        P[6] = n - a - boost::multiprecision::cpp_int (1);
        P[7] = -P1 - boost::multiprecision::cpp_int (1);
        P[8] = -P2 - boost::multiprecision::cpp_int (1);
        for(size_t i = 0 ; i < P.size() ; ++i)
        {
            tmp[i] = P[i];
        }
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                if (i == j)
                {
                    Q[i * N + j] = 1;
                }
                else
                {
                    Q[i * N + j] = boost::multiprecision::cpp_int (0);
                }
            }
        }
        for(size_t i = 0 ; i < N ; ++i)
        {
            size_t k = i;
            boost::rational<boost::multiprecision::cpp_int> rev(1);
            for(size_t j = k ; j < N ; ++j)
            {
                if(tmp[j * N + i] != 0)
                {
                    k = j;
                    break;
                }
            }
            if (k != i)
            {
                for(size_t j = 0; j < N; ++j)
                {
                    std::swap(tmp[i * N + j], tmp[k * N + j]);
                    std::swap(Q[i * N + j], Q[k * N + j]);
                }
            }
            rev /= tmp[i * N + i];
            for(size_t j = 0; j < N; ++j)
            {
                tmp[i * N + j] *= rev;
                Q[i * N + j] *= rev;
            }
            for(size_t j = 0; j < N; ++j)
            {
                if(j != i)
                {
                    rev = tmp[j * N + i];
                    for(size_t t = 0; t < N; ++t)
                    {
                        tmp[j * N + t] -= tmp[i * N + t] * rev;
                        Q[j * N + t] -= Q[i * N + t] * rev;
                    }
                }
            }
        }
        for(size_t i = 0 ; i < Q.size() ; ++i)
        {
            Q[i] *= n;
        }
        std::cout << "k = " << a << ", r = " << P1 << ", s = " << P2 <<std::endl;
        std::cout << "f0 = " << 1 << ", f1 = " << F1 << ", f2 = " << F2 <<std::endl;
        std::cout << "P = (";
        for(size_t i = 0 ; i < P.size() ; ++i)
        {
            std::cout << P[i];
            if(i < 8)
            {
                if((i + 1) % 3 == 0)
                {
                    std::cout << " ; ";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << ")" << std::endl;
        std::cout << "Q = (";
        for(size_t i = 0 ; i < Q.size() ; ++i)
        {
            std::cout << Q[i];
            if(i < 8)
            {
                if((i + 1) % 3 == 0)
                {
                    std::cout << " ; ";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << ")" << std::endl;
    }
    catch(const std::string & str)
    {
        std::cerr << "ERROR! " << str << std::endl;
    }
    catch(...)
    {
        std::cerr << "Something bad happend." << std::endl;
    }
    return 0;
}


boost::multiprecision::cpp_int SQRT(boost::multiprecision::cpp_int n)
{
    if(n < 0)
    {
        throw std::string ("It is impossible to extract an integer square root of " + boost::lexical_cast<std::string> (n));
    }
    boost::multiprecision::cpp_int l = -1;
    boost::multiprecision::cpp_int r = n;
    boost::multiprecision::cpp_int m;
    for( ; l < r - 1 ;)
    {
        m = (l + r) / 2;
        if(m * m < n)
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    if(r * r != n)
    {
        throw std::string ("It is impossible to extract an integer square root of " + boost::lexical_cast<std::string> (r));
    }
    return r;
}
