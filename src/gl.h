#ifndef GL_H
#define GL_H

#include <vector>

class GL
{
public:
    GL(int N, int Q);
    void PrintGroupInfo();
    void PrintGroupInfo(std::vector<int> &CE);

private:
    const int N, Q;
    //DivTable add init in constructor
    std::vector<std::vector<int>> AddTable, SubTable, MultTable, DivTable;
    std::vector<int> AddReverse, MultReverse;
    std::vector<std::vector<int> > Group;

    void GetGroup(std::vector<int> &CurrM, int n);
    int GetDet(std::vector<int> M);
    void GetConjugateClass(std::vector<int> &M, std::vector<std::vector<int> > &Res);

    void MultiplyM(std::vector<int> &M1, std::vector<int> &M2, std::vector<int> &Res);
    bool IsEq(std::vector<int> &M1, std::vector<int> &M2);
    void GetInvM(std::vector<int> M, std::vector<int> &Res);


    void GetGLMS(std::vector<int> &CurrM, int n, std::vector<std::vector<int>> &Res);
    void GetGUMS(std::vector<std::vector<int>> &Res);
    void GetGUDM(std::vector<int> & CurM, std::vector<std::vector<int>> & Gstrings, std::vector<std::vector<int>> &strings, int n, std::vector<std::vector<int>> & MS);
    void GetGUStrings(std::vector<int> & CurStr, int n, std::vector<std::vector<int>> & Strings);
    void GetGLCClass(std::vector<int> &M, std::vector<std::vector<int>> & Res);
    void GetGUCClass(std::vector<int> &M, std::vector<std::vector<int>> & Res);
    int BinarySearch(std::vector<int> &arr, int key);
};



#endif // GL_H
