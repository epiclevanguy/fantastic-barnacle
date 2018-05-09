#include "gl.h"
#include <iostream>


int main()
{
    {
        std::vector<int> E1 = { 1 , 0 , 0 , 2};
        GL tmp(2,3);
        tmp.PrintGroupInfo(E1);
        std::cout << std::endl << std::endl;
        tmp.PrintGroupInfo();
    }
    std::cout << std::endl << std::endl;
    {
        std::vector<int> E1 = { 1 , 0 , 0 , 4};
        GL tmp(2,5);
        tmp.PrintGroupInfo(E1);
        std::cout << std::endl << std::endl;
        tmp.PrintGroupInfo();
    }
    std::cout << std::endl << std::endl;
    {
        std::vector<int> E1 = { 1 , 0 , 0 , 0, 1 , 0, 0, 0, 2};
        GL tmp(3,3);
        tmp.PrintGroupInfo(E1);
        std::cout << std::endl << std::endl;
        //tmp.PrintGroupInfo();
    }
    std::cout << std::endl << std::endl;
    {
        std::vector<int> E1 = { 1 , 0 , 0 , 0, 1 , 0, 0, 0, 4};
        GL tmp(3,5);
        tmp.PrintGroupInfo(E1);
        std::cout << std::endl << std::endl;
        //tmp.PrintGroupInfo();
    }
    return 0;
}
