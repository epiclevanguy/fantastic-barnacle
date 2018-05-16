#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <ostream>

template<typename T>
class Group
{
public:
    Group() {}

    size_t Size()
    {
        return Elements.size();
    }
    void AddElement(const T & E)
    {
        Elements.push_back(E);
    }


    Group& operator=(const Group& Right)
    {
        this->Elements = Right.Elements;
        return (*this);
    }

    T& operator [](const size_t i)
    {
        return Elements[i];
    }

    bool Exist(const T & E)
    {
        for(size_t i = 0 ; i < Elements.size() ; ++i)
        {
            if(Elements[i] == E)
            {
                return true;
            }
        }
        return false;
    }

    Group GetConjugateClass(const T& E)
    {
        Group Res;
        T tmp;
        for (size_t i = 0; i < Elements.size(); ++i)
        {
            tmp = Elements[i] * E * Elements[i].GetInverseMatrix();
            if (!Res.Exist(tmp))
            {
                Res.AddElement(tmp);
            }
        }
        return Res;
    }


private:
    std::vector<T> Elements;

    friend std::ostream & operator<< (std::ostream & Output, const Group<T> &G)
    {
        Output << G.Elements.size() << std::endl;
        for(size_t i = 0 ; i < G.Elements.size() ; ++i)
        {
            Output << G.Elements[i] << std::endl;
        }
        return Output;
    }
};


#endif // GROUP_H
