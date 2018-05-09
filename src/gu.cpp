#include "gu.h"
#include <iostream>

/*
GU::GU(int N, int Q) : N(N), Q(Q)
{
    std::cout << this->N << std::endl;
    std::cout << this->Q << std::endl;

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
}





void CGroup::SetCE(std::vector<int> &CE)
{
    for(int i = 0 ; i < CE.size() ; ++i)
    {
        X[i] = CE[i];
    }
}

void CGroup::Calculate()
{
    std::vector<int> tmp1(N * N), tmp2(N * N);
    if(Type == "GL")
    {
        GetGLCClass(X, MS);

    }
    if(Type == "U")
    {
        GetGUCClass(X, MS);
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

void CGroup::Print()
{
    std::cout << "X" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if(Type == "GL")
            {
                std::cout << FField[X[i * N + j]][0] << "  ";
            }
            if(Type == "U")
            {
                std::cout << FField[X[i * N + j]][0] << " + " << FField[X[i * N + j]][1] << "i   ";
            }
        }
        std::cout << std::endl;
    }
    G.Print();
}

int CGroup::GetDet(std::vector<int> M)
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
        res = MTable[res][M[i * N + i]];
        for (int j = i + 1; j < N; ++j)
        {
            if (M[j * N + i] > 0)
            {
                for (int k = N - 1; k >= i; --k)
                {
                    M[j * N + k] = DTable[M[j * N + k]][MTable[M[i * N + k]][MTable[ReverseM[M[i * N + i]]][M[j * N + i]]]];
                }
            }
        }
    }
    return res;
}

void CGroup::GetInvM(std::vector<int> M, std::vector<int> &Res)
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
        rev = ReverseM[M[i * N + i]];
        for(int j = 0; j < N; ++j)
        {
            M[i * N + j] = MTable[M[i * N + j]][rev];
            Res[i * N + j] = MTable[Res[i * N + j]][rev];
        }
        for(int j = 0; j < N; ++j)
        {
            if(j != i)
            {
                rev = M[j * N + i];
                for(int t = 0; t < N; ++t)
                {
                    M[j * N + t] = DTable[M[j * N + t]][MTable[M[i * N + t]][rev]];
                    Res[j * N + t] = DTable[Res[j * N + t]][MTable[Res[i * N + t]][rev]];
                }
            }
        }
    }
}

void CGroup::GetMultM(std::vector<int> &M1, std::vector<int> &M2, std::vector<int> &Res)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Res[i * N + j] = 0;
            for (int k = 0; k < N; ++k)
            {
                Res[i * N + j] = STable[Res[i * N + j]][MTable[M1[i * N + k]][M2[j + k * N]]];
            }
        }
    }
}

void CGroup::GetGLMS(std::vector<int> &CurrM, int n, std::vector<std::vector<int> > &Res)
{
    if (n == N * N)
    {
        if (GetDet(CurrM) != 0)
        {
            Res.push_back(CurrM);
        }
        return;
    }
    for (int i = 0; i < Q; ++i)
    {
        CurrM[n] = i;
        GetGLMS(CurrM, n + 1, Res);
    }
}

void CGroup::GetGUMS(std::vector<std::vector<int> > &Res)
{
    std::vector<std::vector<int>> strings;
    std::vector<int> tmp (N);
    GetGUStrings(tmp, 0, strings);
    std::vector<std::vector<int>> Gstrings(strings.size());
    for (long long i = 0; i < strings.size(); ++i)
    {
        for (long long j = 0; j < strings.size(); ++j)
        {
            int R = 0;
            for (int k = 0; k < N; ++k)
            {
                R = STable[R][MTable[strings[i][k]][Conjugate[strings[j][k]]]];
            }
            if (R == 0)
            {
                Gstrings[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < Gstrings.size(); ++i)
    {
        tmp[0] = i;
        GetGUDM(tmp, Gstrings, strings, 1, Res);
    }
}

void CGroup::GetGUDM(std::vector<int> &CurM, std::vector<std::vector<int> > &Gstrings, std::vector<std::vector<int> > &strings, int n, std::vector<std::vector<int> > &MS)
{
    if (n == N)
    {
        std::vector<int> tmp(N*N);
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                tmp[i*N + j] = strings[CurM[i]][j];
            }
        }
        MS.push_back(tmp);
        return;
    }
    for (int i = 0; i < Gstrings[CurM[n - 1]].size(); ++i)
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
            GetGUDM(CurM, Gstrings, strings, n + 1, MS);
        }
    }
}

void CGroup::GetGUStrings(std::vector<int> &CurStr, int n, std::vector<std::vector<int> > &Strings)
{
    if (n == N)
    {
        int R = 0;
        for (int i = 0; i < N; ++i)
        {
            R = STable[R][MTable[CurStr[i]][Conjugate[CurStr[i]]]];
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

void CGroup::GetGLCClass(std::vector<int> &M, std::vector<std::vector<int> > &Res)
{
    std::vector<std::vector<int>> InV;
    std::vector<int> tmp1(N*N), tmp2(N*N), tmp3(N*N), tmp456(N * N);
    GetGLMS(tmp456, 0, InV);
    for (int i = 0; i < InV.size(); ++i)
    {
        GetMultM(InV[i], M, tmp1);
        GetInvM(InV[i],tmp2);
        GetMultM(tmp1, tmp2, tmp3);
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

bool CGroup::IsEq(std::vector<int> &M1, std::vector<int> &M2)
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

int CGroup::BinarySearch(std::vector<int> &arr, int key)
{
    int left = 0;
    int right = arr.size();
    int mid = 0;

    while (!(left >= right))
    {
        mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] > key)
            right = mid;
        else
            left = mid + 1;
    }
    return -(1 + left);
}


void CGroup::InitU()
{
    FField.resize(Q * Q, std::vector<int> (2));
    STable.resize(Q * Q, std::vector<int> (Q * Q));
    DTable.resize(Q * Q, std::vector<int> (Q * Q));
    MTable.resize(Q * Q, std::vector<int> (Q * Q));
    ReverseS.resize(Q * Q);
    ReverseM.resize(Q * Q);
    Conjugate.resize(Q * Q);
    for (int i = 0; i < Q; ++i)
    {
        for (int j = 0; j < Q; ++j)
        {
            FField[j * Q + i][0] = i;
            FField[j * Q + i][1] = j;
        }
    }

    for (int i = 0; i < Q * Q; ++i)
    {
        if (FField[i][1] > 0)
        {
            for (int j = 0; j < Q * Q; ++j)
            {
                if (FField[i][0] == FField[j][0] && Q - FField[i][1] == FField[j][1])
                {
                    Conjugate[i] = j;
                    break;
                }
            }
        }
        else
        {
            Conjugate[i] = i;
        }
    }

    for (int i = 0; i < Q * Q; ++i)
    {
        for (int j = 0; j < Q * Q; ++j)
        {
            int a = (FField[i][0] + FField[j][0]) % Q;
            int b = (FField[i][1] + FField[j][1]) % Q;
            for (int k = 0; k < Q * Q; ++k)
            {
                if (a == FField[k][0] && b == FField[k][1])
                {
                    STable[i][j] = k;
                    break;
                }
            }
            a = (FField[i][0] - FField[j][0]);
            b = (FField[i][1] - FField[j][1]);
            if(a < 0)
            {
                a += Q;
            }
            if(b < 0)
            {
                b += Q;
            }
            for (int k = 0; k < Q * Q; ++k)
            {
                if (a == FField[k][0] && b == FField[k][1])
                {
                    DTable[i][j] = k;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < Q * Q; ++i)
    {
        for (int j = 0; j < Q * Q; ++j)
        {
            int tmp[2] = { FField[i][0] * FField[j][0] - FField[i][1] * FField[j][1], FField[i][0] * FField[j][1] + FField[i][1] * FField[j][0] };
            for (int k = 0; k < 2; ++k)
            {
                if (tmp[k] < 0)
                {
                    tmp[k] = tmp[k] + (-tmp[k] / Q + 1) * Q;
                }
                if (tmp[k] >= Q)
                {
                    tmp[k] = tmp[k] - (tmp[k] / Q) * Q;
                }
            }
            for (int k = 0; k < Q * Q; ++k)
            {
                if (tmp[0] == FField[k][0] && tmp[1] == FField[k][1])
                {
                    MTable[i][j] = k;
                    break;
                }
            }
        }
    }

    ReverseS[0] = 0;
    ReverseM[0] = 0;
    for (int i = 1; i < Q * Q; ++i)
    {
        for (int j = 1; j < Q * Q; ++j)
        {
            if (STable[i][j] == 0)
            {
                ReverseS[i] = j;
                break;
            }
        }
        for (int j = 1; j < Q * Q; ++j)
        {
            if (MTable[i][j] == 1)
            {
                ReverseM[i] = j;
                break;
            }
        }
    }
}

void CGroup::GetGUCClass(std::vector<int> &M, std::vector<std::vector<int> > &Res)
{
    std::vector<std::vector<int>> InV;
    std::vector<int> tmp1(N*N), tmp2(N*N), tmp3(N*N);
    GetGUMS(InV);
    for (int i = 0; i < InV.size(); ++i)
    {
        GetMultM(InV[i], M, tmp1);
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                tmp2[k * N + j] = Conjugate[InV[i][j * N + k]];
            }
        }
        GetMultM(tmp1, tmp2, tmp3);
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
            Res.push_back(tmp3);
        }
    }
}

*/
