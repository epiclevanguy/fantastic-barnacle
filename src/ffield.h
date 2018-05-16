#ifndef FFIELD_H
#define FFIELD_H


#include <ostream>


template<int Q>
class RField
{
public:
    RField()
    {
        this->Number = 0;
        if(NeedInit)
        {
            Init();
        }
    }
    RField(const RField<Q> &Number)
    {
        this->Number = Number.Number;
        if(NeedInit)
        {
            Init();
        }
    }
    RField(int Number)
    {
        this->Number = Number;
        if(NeedInit)
        {
            Init();
        }
    }
    RField& operator=(const RField& Right)
    {
        this->Number = Right.Number;
        return (*this);
    }
    RField& operator=(const int& Right)
    {
        this->Number = Right;
        return (*this);
    }
    RField& operator+=(const RField& Right)
    {
        this->Number = AddTable[this->Number][Right.Number];
        return (*this);
    }
    RField& operator-=(const RField& Right)
    {
        this->Number = SubTable[this->Number][Right.Number];
        return (*this);
    }
    RField& operator*=(const RField& Right)
    {
        this->Number = MultTable[this->Number][Right.Number];
        return (*this);
    }
    RField& operator/=(const RField& Right)
    {
        this->Number = DivTable[this->Number][Right.Number];
        return (*this);
    }
private:
    int Number;
    static bool NeedInit;
    static int AddTable[Q][Q], SubTable[Q][Q], MultTable[Q][Q], DivTable[Q][Q], AddReverse[Q], MultReverse[Q];
    void Init()
    {
        NeedInit = false;
        for(int i = 0 ; i < Q ; ++i)
        {
            for(int j = 0 ; j < Q ; ++j)
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
        for(int i = 0 ; i < Q ; ++i)
        {
            for(int j = 0 ; j < Q ; ++j)
            {
                DivTable[i][j] = MultTable[i][MultReverse[j]];
            }
        }
    }

    friend const RField operator-(const RField& Right)
    {
        return RField(Right.AddReverse[Right.Number]);
    }

    friend bool operator==(const RField& Left, const RField& Right)
    {
        return Left.Number == Right.Number;
    }

    friend bool operator==(const RField& Left, const int& Right)
    {
        return Left.Number == Right;
    }

    friend bool operator<(const RField& Left, const RField& Right)
    {
        return Left.Number < Right.Number;
    }

    friend bool operator<(const RField& Left, const int& Right)
    {
        return Left.Number < Right;
    }

    friend std::ostream & operator<< (std::ostream & Output, const RField<Q> & N)
    {
        Output << N.Number;
        return Output;
    }

};

template<int Q>
bool RField<Q>::NeedInit = true;
template<int Q>
int RField<Q>::AddTable[Q][Q];
template<int Q>
int RField<Q>::SubTable[Q][Q];
template<int Q>
int RField<Q>::MultTable[Q][Q];
template<int Q>
int RField<Q>::DivTable[Q][Q];
template<int Q>
int RField<Q>::AddReverse[Q];
template<int Q>
int RField<Q>::MultReverse[Q];

template<int Q>
const RField<Q> operator+ (const RField<Q>& Left, const RField<Q>& Right)
{
    return RField<Q> (Left) += Right;
}

template<int Q>
const RField<Q> operator- (const RField<Q>& Left, const RField<Q>& Right)
{
    return RField<Q> (Left) -= Right;
}

template<int Q>
const RField<Q> operator* (const RField<Q>& Left, const RField<Q>& Right)
{
    return RField<Q> (Left) *= Right;
}

template<int Q>
const RField<Q> operator/ (const RField<Q>& Left, const RField<Q>& Right)
{
    return RField<Q> (Left) /= Right;
}

template<int Q>
bool operator != (const RField<Q>& Left, const RField<Q>& Right)
{
    return !(Left == Right);
}

template<int Q>
bool operator != (const RField<Q>& Left, const int& Right)
{
    return !(Left == Right);
}

template<int Q>
bool operator > (const RField<Q>& Left, const RField<Q>& Right)
{
    return !(Left == Right || Left < Right);
}

template<int Q>
bool operator > (const RField<Q>& Left, const int& Right)
{
    return !(Left == Right || Left < Right);
}


template<int Q>
class CField
{
public:
    CField()
    {
        this->Number = 0;
        if(NeedInit)
        {
            Init();
        }
    }
    CField(const CField<Q> &Number)
    {
        this->Number = Number.Number;
        if(NeedInit)
        {
            Init();
        }
    }
    CField(int Number)
    {
        this->Number = Number;
        if(NeedInit)
        {
            Init();
        }
    }
    CField& operator=(const CField& Right)
    {
        this->Number = Right.Number;
        return (*this);
    }
    CField& operator=(const int& Right)
    {
        this->Number = Right;
        return (*this);
    }
    CField& operator+=(const CField& Right)
    {
        this->Number = AddTable[this->Number][Right.Number];
        return (*this);
    }
    CField& operator-=(const CField& Right)
    {
        this->Number = SubTable[this->Number][Right.Number];
        return (*this);
    }
    CField& operator*=(const CField& Right)
    {
        this->Number = MultTable[this->Number][Right.Number];
        return (*this);
    }
    CField& operator/=(const CField& Right)
    {
        this->Number = DivTable[this->Number][Right.Number];
        return (*this);
    }
    CField GetConjugate()
    {
        return CField(Conjugate[Number]);
    }
private:
    int Number;
    static bool NeedInit;
    static int Field[Q * Q][2], AddTable[Q * Q][Q * Q], SubTable[Q * Q][Q * Q], MultTable[Q * Q][Q * Q],
    DivTable[Q * Q][Q * Q], AddReverse[Q * Q], MultReverse[Q * Q], Conjugate[Q * Q];
    void Init()
    {
        NeedInit = false;
        for (int i = 0; i < Q; ++i)
        {
            for (int j = 0; j < Q; ++j)
            {
                Field[j * Q + i][0] = i;
                Field[j * Q + i][1] = j;
            }
        }

        for (int i = 0; i < Q * Q; ++i)
        {
            if (Field[i][1] > 0)
            {
                for (int j = 0; j < Q * Q; ++j)
                {
                    if (Field[i][0] == Field[j][0] && Q - Field[i][1] == Field[j][1])
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
                int a = (Field[i][0] + Field[j][0]) % Q;
                int b = (Field[i][1] + Field[j][1]) % Q;
                for (int k = 0; k < Q * Q; ++k)
                {
                    if (a == Field[k][0] && b == Field[k][1])
                    {
                        AddTable[i][j] = k;
                        break;
                    }
                }
                a = (Field[i][0] - Field[j][0]);
                b = (Field[i][1] - Field[j][1]);
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
                    if (a == Field[k][0] && b == Field[k][1])
                    {
                        SubTable[i][j] = k;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < Q * Q; ++i)
        {
            for (int j = 0; j < Q * Q; ++j)
            {
                int tmp[2] = { Field[i][0] * Field[j][0] - Field[i][1] * Field[j][1], Field[i][0] * Field[j][1] + Field[i][1] * Field[j][0] };
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
                    if (tmp[0] == Field[k][0] && tmp[1] == Field[k][1])
                    {
                        MultTable[i][j] = k;
                        break;
                    }
                }
            }
        }

        AddReverse[0] = 0;
        MultReverse[0] = 0;
        for (int i = 1; i < Q * Q; ++i)
        {
            for (int j = 1; j < Q * Q; ++j)
            {
                if (AddTable[i][j] == 0)
                {
                    AddReverse[i] = j;
                    break;
                }
            }
            for (int j = 1; j < Q * Q; ++j)
            {
                if (MultTable[i][j] == 1)
                {
                    MultReverse[i] = j;
                    break;
                }
            }
        }

        for(int i = 0 ; i < Q * Q ; ++i)
        {
            for(int j = 0 ; j < Q * Q ; ++j)
            {
                DivTable[i][j] = MultTable[i][MultReverse[j]];
            }
        }

    }

    friend const CField operator-(const CField& Right)
    {
        return CField(Right.AddReverse[Right.Number]);
    }

    friend bool operator==(const CField& Left, const CField& Right)
    {
        return Left.Number == Right.Number;
    }

    friend bool operator==(const CField& Left, const int& Right)
    {
        return Left.Number == Right;
    }

    friend std::ostream & operator<< (std::ostream & Output, const CField<Q> & N)
    {
        Output << Field[N.Number][0] << " + " << Field[N.Number][1] << "i";
        return Output;
    }

};

template<int Q>
bool CField<Q>::NeedInit = true;
template<int Q>
int CField<Q>::Field[Q * Q][2];
template<int Q>
int CField<Q>::AddTable[Q * Q][Q * Q];
template<int Q>
int CField<Q>::SubTable[Q * Q][Q * Q];
template<int Q>
int CField<Q>::MultTable[Q * Q][Q * Q];
template<int Q>
int CField<Q>::DivTable[Q * Q][Q * Q];
template<int Q>
int CField<Q>::AddReverse[Q * Q];
template<int Q>
int CField<Q>::MultReverse[Q * Q];
template<int Q>
int CField<Q>::Conjugate[Q * Q];

template<int Q>
const CField<Q> operator+ (const CField<Q>& Left, const CField<Q>& Right)
{
    return CField<Q> (Left) += Right;
}

template<int Q>
const CField<Q> operator- (const CField<Q>& Left, const CField<Q>& Right)
{
    return CField<Q> (Left) -= Right;
}

template<int Q>
const CField<Q> operator* (const CField<Q>& Left, const CField<Q>& Right)
{
    return CField<Q> (Left) *= Right;
}

template<int Q>
const CField<Q> operator/ (const CField<Q>& Left, const CField<Q>& Right)
{
    return CField<Q> (Left) /= Right;
}

template<int Q>
bool operator != (const CField<Q>& Left, const CField<Q>& Right)
{
    return !(Left == Right);
}

template<int Q>
bool operator != (const CField<Q>& Left, const int& Right)
{
    return !(Left == Right);
}

#endif // FFIELD_H
