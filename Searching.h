#ifndef SEARCHING_H
#define SEARCHING_H

#include <cmath>
#include <algorithm>
#include <iostream>

int BinarySearch(int key, int *arr, int size);
int JumpSearch(int key, int *arr, int size);
int InterpolationSearch(int key, int *arr, int size);

void PrintArr(int* arr, int size);

void TestSearching()
{
    int arr[] = { 2, 5, 8, 11, 16, 19, 22, 24, 27, 30};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Searching\n\n";
    PrintArr(arr, size);
    std::cout << "\n";


    int search_value = 11;
    std::cout << "Selection:     element {" << search_value << "} is at the index [";
    std::cout << BinarySearch(search_value, arr, size) << "]\n";

    std::cout << "Jump:          element {" << search_value << "} is at the index [";
    std::cout << JumpSearch(search_value, arr, size) << "]\n";

    std::cout << "Interpolation: element {" << search_value << "} is at the index [";
    std::cout << InterpolationSearch(search_value, arr, size) << "]\n";


    search_value = 77;
    std::cout << "\nSelection:     element {" << search_value << "} is at the index [";
    std::cout << BinarySearch(search_value, arr, size) << "]\n";

    std::cout << "Jump:          element {" << search_value << "} is at the index [";
    std::cout << JumpSearch(search_value, arr, size) << "]\n";

    std::cout << "Interpolation: element {" << search_value << "} is at the index [";
    std::cout << InterpolationSearch(search_value, arr, size) << "]\n";


}



int BinarySearch(int key, int *arr, int size)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] > key)
        {
            right = mid - 1;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}



int JumpSearch(int key, int *arr, int size)
{
    int ret_ind = -1;
    int jump_value = static_cast<int>(std::sqrt(size));
    int prev_ind = 0;
    int curr_ind = jump_value - 1;
    while (arr[std::min(curr_ind, size - 1)] < key)
    {
        prev_ind = curr_ind;
        curr_ind += jump_value;
        if (prev_ind >= size - 1)
            break;
    }

    for (int i = prev_ind; i <= std::min(prev_ind + jump_value, size - 1); i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
        else if (arr[i] > key)
        {
            return ret_ind;
        }
    }

    return ret_ind;
}



int InterpolationSearch(int key, int *arr, int size)
{
    int left = 0;
    int right = size - 1;
    int pos = 0;
    while (left <= right && arr[left] <= key && arr[right] >= key)
    {
        if (arr[right] != arr[left])
            pos = left + (right - left) * (key - arr[left]) / (arr[right] - arr[left]);
        else
            pos = left;

        if (arr[pos] > key)
        {
            right = pos - 1;
        }
        else if (arr[pos] < key)
        {
            left = pos + 1;
        }
        else
        {
            return pos;
        }
    }
    return -1;
}



void PrintArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}


#endif // SEARCHING_H
