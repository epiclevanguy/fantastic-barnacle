#ifndef SPECIFICALGORITHMS_H
#define SPECIFICALGORITHMS_H

#include <vector>

template<typename T>
int BinarySearch(std::vector<T> &arr, T key)
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

#endif // SPECIFICALGORITHMS_H
