#ifndef SORTING_H
#define SORTING_H

#include "Heap.h"
#include <vector>
#include <random>

void SortArraySelection(int* arr, int size);
void SortArrayCycle(int* arr, int size);
void SortArrayHeap(int* arr, int size);

void SortArrayInsertion(int* arr, int size);
void SortArrayShell(int* arr, int size);

void SortArrayBubble(int* arr, int size);
void SortArrayComb(int* arr, int size);
void SortArrayQuick(int* arr, int left, int right);

void SortArrayMerge(int* arr, int left, int right);

void SortArrayCounting(int *arr, int size, int range);
void SortArrayRadix(int *arr, int size);


void PrintArray(int* arr, int size);

void TestSorting()
{
    int arr[] = { 8, 5, 2, 1, 0, 6, 4, 7, 9, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    auto rng = std::default_random_engine {};

    std::cout << "Sorting\n\n";
    PrintArray(arr, size);
    std::cout << "\n";

    std::shuffle(arr, arr + size, rng);
    std::cout << "Selection: ";
    SortArraySelection(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Cycle:     ";
    SortArrayCycle(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Heap:      ";
    SortArrayHeap(arr, size);
    PrintArray(arr, size);    

    std::shuffle(arr, arr + size, rng);
    std::cout << "Insertion: ";
    SortArrayInsertion(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Shell:     ";
    SortArrayShell(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Bubble:    ";
    SortArrayBubble(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Comb:      ";
    SortArrayComb(arr, size);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Quick:     ";
    SortArrayQuick(arr, 0, size - 1);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Merge:     ";
    SortArrayMerge(arr, 0, size - 1);
    PrintArray(arr, size);

    std::shuffle(arr, arr + size, rng);
    std::cout << "Counting:  ";
    SortArrayCounting(arr, size, 9);
    PrintArray(arr, size);


    int arr2[] = { 823, 1, 272, 211, 65, 22, 5, 645, 9, 829};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    std::cout << "\n";
    PrintArray(arr2, size2);
    std::cout << "Radix:     ";
    SortArrayRadix(arr2, size2);
    PrintArray(arr2, size2);
}



void SortArraySelection(int* arr, int size)
{
    if (size <= 1)
        return;

    int min_ind = 0;
    for (int i = 0; i < size - 1; i++)
    {
        min_ind = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_ind])
            {
                min_ind = j;
            }
        }

        if (i != min_ind)
        {
            std::swap(arr[i], arr[min_ind]);
        }
    }
}



void SortArrayCycle(int* arr, int size)
{
    if (size <= 1)
        return;

    int temp = 0;
    int pos = 0;
    for (int cycle_start = 0; cycle_start < size - 1; cycle_start++)
    {
        temp = arr[cycle_start];
        pos = cycle_start;

        for (int j = cycle_start + 1; j < size; j++)
            if (arr[j] < temp)
                pos++;

        if (pos == cycle_start)
            continue;

        while (temp == arr[pos])
            pos++;

        std::swap(temp, arr[pos]);

        while (pos != cycle_start)
        {
            pos = cycle_start;

            for (int j = cycle_start + 1; j < size; j++)
                if (arr[j] < temp)
                    pos++;

            while (temp == arr[pos])
                pos++;

            std::swap(temp, arr[pos]);

        }
    }
}



void SortArrayHeap(int *arr, int size)
{
    Heap heap(arr, size);

    for (int i = 0; i < size; i++)
        arr[size - 1 - i] = heap.ExtractMax();
}



void SortArrayInsertion(int* arr, int size)
{
    if (size <= 1)
        return;

    for (int i = 1; i < size; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}



void SortArrayShell(int* arr, int size)
{
    if (size <= 1)
        return;

    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            int temp = arr[i];
            int j = i - gap;
            while (j >= 0 && arr[j] > temp) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = temp;
        }
    }
}



void SortArrayBubble(int* arr, int size)
{
    if (size <= 1)
        return;

    for (int k = 0; k < size - 1; k++)
    {
        bool swapped = false;
        for (int i = 0; i < size - 1 - k; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}



void SortArrayComb(int* arr, int size)
{
    if (size <= 1)
        return;

    int gap = size;
    bool swapped = false;
    while (gap > 1 || swapped)
    {
        swapped = false;
        gap = std::max(1, static_cast<int>(gap / 1.25));
        for (int i = 0; i + gap < size; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}



int QuickSortPartition(int* arr, int left, int right)
{
    int pivot_val = arr[right];
    int last_smaller_ind = left - 1;
    for (int i = left; i < right; i++)
    {
        if (arr[i] < pivot_val)
        {
            last_smaller_ind++;
            std::swap(arr[i], arr[last_smaller_ind]);
        }
    }

    std::swap(arr[last_smaller_ind + 1], arr[right]);
    return (last_smaller_ind + 1);
}



void SortArrayQuick(int* arr, int left, int right)
{
    if (left >= right)
        return;

    int pivot = QuickSortPartition(arr, left, right);

    SortArrayQuick(arr, left, pivot - 1);
    SortArrayQuick(arr, pivot + 1, right);
}



void MergeArrays(int* arr, int left, int mid, int right)
{
    int size_left = mid - left + 1;
    int size_right = right - mid;

    std::vector<int> arr_left(size_left);
    std::vector<int> arr_right(size_right);

    for (int i = 0; i < size_left; i++)
    {
        arr_left[i] = arr[left + i];
    }
    for (int i = 0; i < size_right; i++)
    {
        arr_right[i] = arr[mid + 1 + i];
    }

    int it_left = 0;
    int it_right = 0;
    int it_merged = left;

    while (it_left < size_left && it_right < size_right)
    {
        if (arr_left[it_left] <= arr_right[it_right])
        {
            arr[it_merged] = arr_left[it_left];
            it_left++;
        } else {
            arr[it_merged] = arr_right[it_right];
            it_right++;
        }
        it_merged++;
    }

    while (it_left < size_left)
    {
        arr[it_merged] = arr_left[it_left];
        it_left++;
        it_merged++;
    }

    while (it_right < size_right)
    {
        arr[it_merged] = arr_right[it_right];
        it_right++;
        it_merged++;
    }
}



void SortArrayMerge(int* arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    SortArrayMerge(arr, left, mid);
    SortArrayMerge(arr, mid + 1, right);

    MergeArrays(arr, left, mid, right);
}



void SortArrayCounting(int *arr, int size, int range)
{
    std::vector<int> result(size);
    std::vector<int> count(range + 1);

    for (int i = 0; i < size; i++)
        count[arr[i]]++;

    for (int i = 1; i <= range; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
       result[count[arr[i]] - 1] = arr[i];
       count[arr[i]]--;
    }


    for (int i = 0; i < size; i++)
        arr[i] = result[i];
}



void RadixSubCountingSort(int* arr, int size, int exp)
{
    int range = 10;
    std::vector<int> result(size);
    std::vector<int> count(range);

    for (int i = 0; i < size; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        result[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++)
        arr[i] = result[i];

}



void SortArrayRadix(int *arr, int size)
{
    if (size <= 1)
        return;

    int max_val = arr[0];
    for(int i = 1; i < size; i++)
        if (arr[i] > max_val)
            max_val = arr[i];


    for (int exp = 1; max_val / exp > 0; exp++)
        RadixSubCountingSort(arr, size, exp);
}



void PrintArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

#endif // SORTING_H
